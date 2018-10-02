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


/***************����URL������������������Դ��******************/
bool ParseURL(const string & url, string & host, string & resource)
{
	//����Ϊ����c���Լ��ݣ���c������û��string���ͣ�
	//�ʱ���ͨ��string�����ĳ�Ա����c_str()��string ����ת����c�е��ַ�����ʽ
	//ע�⣺һ��Ҫʹ��strcpy()���� ������������c_str()���ص�ָ��
	if (strlen(url.c_str()) > 2000)
		return false;

	const char * pos = strstr(url.c_str(), "http://");
	//strstr(str1,str2) ���������ж��ַ���str2�Ƿ���str1���Ӵ���
	//����ǣ���ú�������str2��str1���״γ��ֵĵ�ַ�����򣬷���NULL
	if (pos == NULL)
		pos = url.c_str();
	else
		pos += strlen("http://");  //����http://����
	if (strstr(pos, "/") == 0)
		return false;
	char pHost[100];  //������
	char pResource[2000];  //����Դ·��
	sscanf(pos, "%[^/]%s", pHost, pResource);  // https://baike.baidu.com/item/sscanf/10551550?fr=aladdin
	host = pHost;
	resource = pResource;
	return true;
}


/*******************ʹ��Get���󣬵õ���Ӧ*********************/
bool GetHttpResponse(const string & url, char * &response, int &bytesRead)
{
	string host, resource;
	if (!ParseURL(url, host, resource))
	{
		cout << "Can not parse the url" << endl;
		return false;
	}
	//����socket
	struct hostent * hp = gethostbyname(host.c_str());  //���ض�Ӧ�ڸ����������İ����������ֺ͵�ַ��Ϣ��hostent�ṹ��ָ�롣
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
	//������������ַ
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;  //ipv4
	sa.sin_port = htons(80);  //�˿ں�80
	//char addr[5];
	//memcpy( addr, hp->h_addr, 4 );
	//sa.sin_addr.s_addr = inet_addr(hp->h_addr);
	memcpy(&sa.sin_addr, hp->h_addr, 4);  //����
	//��������
	if (0 != connect(sock, (SOCKADDR*)&sa, sizeof(sa)))
	{
		cout << "Can not connect: " << url << endl;
		closesocket(sock);
		return false;
	};
	//׼����������
	string request = "GET " + resource + " HTTP/1.1\r\nHost:" + host + "\r\nConnection:Close\r\n\r\n";
	//��������
	if (SOCKET_ERROR == send(sock, request.c_str(), request.size(), 0))
	{
		cout << "send error" << endl;
		closesocket(sock);
		return false;
	}
	//��������
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
			pageBuf = (char*)realloc(pageBuf, m_nContentLength);       //���·����ڴ�
		}
	}
	pageBuf[bytesRead] = '\0';
	response = pageBuf;
	closesocket(sock);
	return true;

}

/*******************�������ĵ�HTML*********************/
bool Extract(int count, char * &response)
{
	string httpResponse = response;
	stringstream ss;
	ss << count;
	string paper = ss.str() + "\r\n";
	const char *p = httpResponse.c_str();
	/****************************��ȡtitle*********************************/
	char t[] = "papertitle\">\n";
	char *tag = t;
	const char *pos = strstr(p, tag);
	pos += strlen(tag);  //����tag
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

	/****************************��ȡauthor*********************************/
	char t1[] = "i>";
	char *tag1 = t1;
	const char *pos1 = strstr(p, tag1);
	pos1 += strlen(tag1);  //����tag
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

	/****************************��ȡabstract*********************************/
	char t2[] = "abstract\" >\n";
	char *tag2 = t2;
	const char *pos2 = strstr(p, tag2);
	pos2 += strlen(tag2);  //����tag
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

	/****************************��ȡpdf link*********************************/
	char t3[] = "href=\"../../";
	char *tag3 = t3;
	const char *pos3 = strstr(p, tag3);
	while (pos3)
	{
		pos3 += strlen(tag3);  //����tag
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

	/****************************д���ļ�*********************************/
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


/*******************���������ṩ��ҳ������ĵ�URL*********************/
void ParsepaperUrl(char * &response)
{
	int bytes;
	int count = 0;
	string httpResponse = response;  //������ҳ���HTML����httpResponse������
	//���������ӣ�����q_Url�У��ҷ����������Ӻ��涼��.html
	const char *p = httpResponse.c_str();  //����һ����ҳ���HTML��Ϣ������Ҫ����url����ȡ
	char t[] = "href=\"";  //����ƥ���õ�tag
	char *tag = t;         //����ƥ���õ�tag
	const char *pos = strstr(p, tag);  //strstr�����ж��Ƿ����ִ����Ǿͷ���ƥ�䵽�ĵ�һ��λ��
	while (pos)
	{
		pos += strlen(tag);  //����tag
		const char * nextQ = strstr(pos, "\"");
		if (nextQ) {
			char * url = new char[nextQ - pos + 1];
			sscanf(pos, "%[^\"]", url);
			if (strstr(url, "html"))            //�����ж��Ƿ������ĵ�����
			{
				string paperUrl = "http://openaccess.thecvf.com/";  // ת����string���ͣ������Զ��ͷ��ڴ�
				paperUrl += url;                                    //�õ����õ�����
				if (strstr(url, "\r\n1000\r\n"))                        //���������url���д���
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
			delete[] url;  // �ͷŵ�������ڴ�
		}
	}
	return;
}



int main()
{
	/*******************************************************************************/
	// ��ȡ��ʼ��ַurlStart������������ĵ����ӷ���q_url,֮�����������ȡ������
	//��q_url����ȡ�����ӷ��ʣ�����ȡtitle��abstract����result.txt
	/*******************************************************************************/

	/**** ��ʼ��socket������tcp�������� ****/
	WSADATA wsaData;                               //���windows socket��ʼ����Ϣ��Winsock.h
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //ʹ��Socket�ĳ�����ʹ��Socket֮ǰ�������WSAStartup������
	{	                                           //wsastartup��Ҫ���ǽ�����Ӧ��socket���
		return 0;                                  //https://blog.csdn.net/clemontine/article/details/53141041
	}

	/**** ��������ʼ��ַ ****/
	string urlStart = "http://openaccess.thecvf.com/CVPR2018.py";
	//string urlStart = "http://openaccess.thecvf.com/content_cvpr_2018/html/Kanazawa_End-to-End_Recovery_of_CVPR_2018_paper.html";
	char * response;
	int bytes;
	if (!GetHttpResponse(urlStart, response, bytes))  // ��ȡ��ҳ����Ӧ������response�С��˺���������
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

	WSACleanup();               //����WindowsSockets DLL�ͷ��κθ�Ӧ�ó������Դ

	cout << "Script finish" << endl;

	return 0;
}