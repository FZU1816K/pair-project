//#include <Windows.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "winsock2.h"
#include <ws2tcpip.h>
#include <time.h>
#include <queue>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
#define DEFAULT_PAGE_BUF_SIZE 1048576


/***************解析URL，解析出主机名，资源名******************/
bool ParseURL(const string & url, string & host, string & resource)
{
	//这是为了与c语言兼容，在c语言中没有string类型，
	//故必须通过string类对象的成员函数c_str()把string 对象转换成c中的字符串样式
	//注意：一定要使用strcpy()函数 等来操作方法c_str()返回的指针
	if (strlen(url.c_str()) > 2000)
		return false;

	const char * pos = strstr(url.c_str(), "http://");
	//strstr(str1,str2) 函数用于判断字符串str2是否是str1的子串。
	//如果是，则该函数返回str2在str1中首次出现的地址；否则，返回NULL
	if (pos == NULL)
		pos = url.c_str();
	else
		pos += strlen("http://");  //跳到http://后面
	if (strstr(pos, "/") == 0)
		return false;
	char pHost[100];  //存域名
	char pResource[2000];  //存资源路径
	sscanf(pos, "%[^/]%s", pHost, pResource);  // https://baike.baidu.com/item/sscanf/10551550?fr=aladdin
	host = pHost;
	resource = pResource;
	return true;
}


/*******************使用Get请求，得到响应*********************/
bool GetHttpResponse(const string & url, char * &response, int &bytesRead)
{
	string host, resource;
	if (!ParseURL(url, host, resource))
	{
		cout << "Can not parse the url" << endl;
		return false;
	}
	//建立socket
	struct hostent * hp = gethostbyname(host.c_str());  //返回对应于给定主机名的包含主机名字和地址信息的hostent结构的指针。
	if (hp == NULL)
	{
		cout << "Can not find host address" << endl;
		return false;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1 || sock == -2)
	{
		cout << "Can not create sock." << endl;
		return false;
	}
	//建立服务器地址
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;  //ipv4
	sa.sin_port = htons(80);  //端口号80
	//char addr[5];
	//memcpy( addr, hp->h_addr, 4 );
	//sa.sin_addr.s_addr = inet_addr(hp->h_addr);
	memcpy(&sa.sin_addr, hp->h_addr, 4);  //拷贝
	//建立连接
	if (0 != connect(sock, (SOCKADDR*)&sa, sizeof(sa)))
	{
		cout << "Can not connect: " << url << endl;
		closesocket(sock);
		return false;
	};
	//准备发送数据
	string request = "GET " + resource + " HTTP/1.1\r\nHost:" + host + "\r\nConnection:Close\r\n\r\n";
	//发送数据
	if (SOCKET_ERROR == send(sock, request.c_str(), request.size(), 0))
	{
		cout << "send error" << endl;
		closesocket(sock);
		return false;
	}
	//接收数据
	int m_nContentLength = DEFAULT_PAGE_BUF_SIZE;
	char *pageBuf = (char *)malloc(m_nContentLength);
	memset(pageBuf, 0, m_nContentLength);
	bytesRead = 0;
	int ret = 1;
	while (ret > 0)
	{
		ret = recv(sock, pageBuf + bytesRead, m_nContentLength - bytesRead, 0);
		if (ret > 0)
		{
			bytesRead += ret;
		}
		if (m_nContentLength - bytesRead < 100)
		{
			m_nContentLength *= 2;
			pageBuf = (char*)realloc(pageBuf, m_nContentLength);       //重新分配内存
		}
	}
	pageBuf[bytesRead] = '\0';
	response = pageBuf;
	closesocket(sock);
	return true;

}

/*******************解析论文的HTML*********************/
bool Extract(int count, char * &response)
{
	string httpResponse = response;
	stringstream ss;
	ss << count;
	string paper = ss.str() + "\r\n";
	const char *p = httpResponse.c_str();
	/****************************提取title*********************************/
	char t[] = "papertitle\">\n";
	char *tag = t;
	const char *pos = strstr(p, tag);
	pos += strlen(tag);  //跳过tag
	const char * nextQ = strstr(pos, "<");
	if (nextQ)
	{
		char * title = new char[nextQ - pos + 1];
		sscanf(pos, "%[^<]", title);
		paper += "Title: ";
		paper += title;
		paper += "\r\n";
		delete[] title;
	}

	/****************************提取author*********************************/
	char t1[] = "i>";
	char *tag1 = t1;
	const char *pos1 = strstr(p, tag1);
	pos1 += strlen(tag1);  //跳过tag
	const char * nextQ1 = strstr(pos1, "<");
	if (nextQ1)
	{
		char * author = new char[nextQ1 - pos1 + 1];
		sscanf(pos1, "%[^<]", author);
		paper += "Authors: ";
		paper += author;
		paper += "\r\n";
		delete[] author;
	}

	/****************************提取abstract*********************************/
	char t2[] = "abstract\" >\n";
	char *tag2 = t2;
	const char *pos2 = strstr(p, tag2);
	pos2 += strlen(tag2);  //跳过tag
	const char * nextQ2 = strstr(pos2, "<");
	if (nextQ2)
	{
		char * abstract = new char[nextQ2 - pos2 + 1];
		sscanf(pos2, "%[^<]", abstract);
		paper += "Abstract: ";
		paper += abstract;
		paper += "\r\n";
		delete[] abstract;
	}

	/****************************提取pdf link*********************************/
	char t3[] = "href=\"../../";
	char *tag3 = t3;
	const char *pos3 = strstr(p, tag3);
	while (pos3)
	{
		pos3 += strlen(tag3);  //跳过tag
		const char * nextQ3 = strstr(pos3, "\"");
		if (nextQ3)
		{
			char * pdf = new char[nextQ3 - pos3 + 1];
			sscanf(pos3, "%[^\"]", pdf);
			if (strstr(pdf,"papers"))
			{
				paper += "PDF_LINK: ";
				paper += "http://openaccess.thecvf.com/";
				paper += pdf;
				paper += "\r\n\n\n";
			}
			pos3 = strstr(pos3, tag3);
			delete[] pdf;
		}
	}

	/****************************写入文件*********************************/
	ofstream fout;
	string filename = "Eresult.txt";
	fout.open(filename, ios::out | ios::app);
	if (!fout.is_open())
	{
		cerr << "Can't open result.txt.\n";
		exit(EXIT_FAILURE);
	}
	fout << paper;
	fout.close();

	cout << count << endl;

	return true;
}


/*******************解析助教提供的页面的论文的URL*********************/
void ParsepaperUrl(char * &response)
{
	int bytes;
	int count = 0;
	string httpResponse = response;  //现在首页面的HTML就在httpResponse里面了
	//找所有链接，加入q_Url中，我发现论文链接后面都是.html
	const char *p = httpResponse.c_str();  //这是一整个页面的HTML信息，现在要进行url的提取
	char t[] = "href=\"";  //正则匹配用的tag
	char *tag = t;         //正则匹配用的tag
	const char *pos = strstr(p, tag);  //strstr用于判断是否是字串，是就返回匹配到的第一个位置
	while (pos)
	{
		pos += strlen(tag);  //跳过tag
		const char * nextQ = strstr(pos, "\"");
		if (nextQ) {
			char * url = new char[nextQ - pos + 1];
			sscanf(pos, "%[^\"]", url);
			if (strstr(url, "html"))            //这里判断是否是论文的链接
			{
				string paperUrl = "http://openaccess.thecvf.com/";  // 转换成string类型，可以自动释放内存
				paperUrl += url;                                    //得到可用的链接
				if (strstr(url, "\r\n1000\r\n"))                        //对有问题的url进行处理
				{
					int pos = 0;
					while ((pos = paperUrl.find("\r\n1000\r\n")) != -1)
					{
						paperUrl.erase(pos, strlen("\r\n1000\r\n"));
					}
				}
				if (!GetHttpResponse(paperUrl, response, bytes))
				{
					cout << "The paperUrl is wrong! ignore." << endl;
				}
				Extract(count++, response);
				/*****************File for test***********************************************************************
				ofstream fout;
				string filename = "All_Url.txt";
				fout.open(filename, ios::out| ios::app);
				if (!fout.is_open())
				{
					cerr << "Can't open rootUrl.txt.\n";
					exit(EXIT_FAILURE);
				}
				fout << count++ << " : "<<paperUrl<<endl;
				fout.close();
				/************************************************************************************************/
			}
			pos = strstr(pos, tag);
			delete[] url;  // 释放掉申请的内存
		}
	}
	return;
}



int main()
{
	/*******************************************************************************/
	// 提取起始地址urlStart里面的所有论文的链接放入q_url,之后就无需再提取链接了
	//从q_url里面取出链接访问，并提取title和abstract放入result.txt
	/*******************************************************************************/

	/**** 初始化socket，用于tcp网络连接 ****/
	WSADATA wsaData;                               //存放windows socket初始化信息，Winsock.h
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //使用Socket的程序在使用Socket之前必须调用WSAStartup函数，
	{	                                           //wsastartup主要就是进行相应的socket库绑定
		return 0;                                  //https://blog.csdn.net/clemontine/article/details/53141041
	}

	/**** 遍历的起始地址 ****/
	string urlStart = "http://openaccess.thecvf.com/CVPR2018.py";
	//string urlStart = "http://openaccess.thecvf.com/content_cvpr_2018/html/Kanazawa_End-to-End_Recovery_of_CVPR_2018_paper.html";
	char * response;
	int bytes;
	if (!GetHttpResponse(urlStart, response, bytes))  // 获取网页的响应，放入response中。此函数在上面
	{
		cout << "The url is wrong! ignore." << endl;
		return 0;
	}
	
	ParsepaperUrl(response);                          //homework requested

//	Extract(count++, response);                       //for test

	/*****************File for test***********************************************************************
	ofstream fout;
	string filename = "Nun.txt";
	fout.open(filename, ios::out);
	if (!fout.is_open())
	{
		cerr << "Can't open rootUrl.txt.\n";
		exit(EXIT_FAILURE);
	}
	fout << response;
	fout.close();
	/************************************************************************************************/

	free(response);

	WSACleanup();               //允许WindowsSockets DLL释放任何该应用程序的资源

	cout << "Script finish" << endl;

	return 0;
}