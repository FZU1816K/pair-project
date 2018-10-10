#include"stdafx.h"

queue<string> Texturl;


void GetHttpRespons(char * &response, string source)
{
	//使用GET请求,得到相应
	string host, resource;   
	host = "openaccess.thecvf.com";
	resource = source;
	struct hostent * hp = gethostbyname(host.c_str());
	if (hp == NULL)
	{
		cout << "can not find host address"<<endl;
		exit(0);
	}

	//建立socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == -1 || sock == -2) {
		cout << "Can not create sock." << endl;
		exit(0);
	}

	//建立服务器地址
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(80);
	memcpy(&sa.sin_addr, hp->h_addr, 4);

	//建立连接
	if (0 != connect(sock, (SOCKADDR*)&sa, sizeof(sa))) {
		cout << "can not connet" << endl;
		closesocket(sock);
		exit(0);
	}
	//connect(sock, (SOCKADDR*)&sa, sizeof(sa));

	//准备发送数据
	string request = "GET " + resource + " HTTP/1.1\r\nHost:" + host + "\r\nConnection:Close\r\n\r\n";
	//发送数据
	send(sock, request.c_str(), request.size(), 0);
	if (SOCKET_ERROR == send(sock, request.c_str(), request.size(), 0)) {
		cout << "send error" << endl;
		closesocket(sock);
		exit(0);
	}
	//接收数据
	int m_nContentLength = DEFAULT_PAGE_BUF_SIZE;
	int bytesRead = 0;
	int ret = 1;
	char *pageBuf = (char *)malloc(m_nContentLength);
	memset(pageBuf, 0, m_nContentLength);
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
			pageBuf = (char*)realloc(pageBuf, m_nContentLength);
		}
	}
	pageBuf[bytesRead] = '\0';
	response = pageBuf;
	closesocket(sock);
}

void GetTexturl()
{
	char *response;
	string source = "/CVPR2018.py";
	GetHttpRespons(response, source);
	const char *t = "content_cvpr_2018/html/";
	const char *result = strstr(response, t);
	string turl, gurl;
	while (result)
	{
		const char * nextQ = strstr(result, "\"");
		if (nextQ) {
			char * url = new char[nextQ - result + 1];
			//固定大小的会发生缓冲区溢出的危险
			sscanf(result, "%[^\"]", url);
			result += strlen(url);
			const char *urlp = url;
			const char *nextq = strstr(urlp, "\n");
			if (nextq)
			{
				char * furl = new char[nextq - urlp + 1];
				sscanf(urlp, "%[^\n]", furl);
				turl = furl;
				urlp += strlen(furl);
				urlp++;
				const char * next1 = strstr(urlp, "\n");
				if (next1)
				{
					char * furll = new char[next1 - urlp + 1];
					sscanf(urlp, "%[^\n]", furll);
					urlp += strlen(furll);
					urlp++;
					gurl = urlp;
					turl += gurl;
					delete[] furll;
				}
				delete[] furl;
			}
			else
			{
				turl = urlp;
			}
			turl = "/" + turl;
			Texturl.push(turl);
			delete[] url;
		}
		result = strstr(result, t);
	}
	free(response);
}

void GetText()
{
	char * response;
	const char * t = "papertitle\">";
	const char * a = "abstract\" >";
	int n = Texturl.size();
	string u;
	ofstream outfile("result.txt");
	if (!outfile)
	{
		cerr << "open error!" << endl;
		exit(1);
	}
	for (int i = 0; i < n; i++)
	{
		u = Texturl.front();
		const char *urlo = u.c_str();
		char ab[100];
		int j = 0;
		for (int k = 0; k < strlen(urlo); k++)
		{
			if (urlo[k] != '\r')
			{
				ab[j] = urlo[k];
				j++;
			}
		}
		ab[j] = '\0';
		u = ab;
		GetHttpRespons(response, u);
		const char * result = strstr(response, t);
		if (result)
		{
			result += strlen(t);
			result++;
			const char * next = strstr(result, "<");
			char * title = new char[next - result + 1];
			sscanf(result, "%[^<]", title);
			result = strstr(result, a);
			if (result)
			{ 
				result += strlen(a);
				result++;
				const char * next1 = strstr(result, "<");
				char * abstract = new char[next1 - result + 1];
				sscanf(result, "%[^<]", abstract);
				outfile << i << endl;
				outfile << "Title: " << title << endl;
				outfile << "Abstract: " << abstract << endl;
				outfile << endl;
				outfile << endl;
				delete[] abstract;
				
			}
			delete[] title;
		}
		Texturl.pop();

	}
	//free(response);
	outfile.close();
}

int main()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0) {
		return 0;
	}
	GetTexturl();
	GetText();
	WSACleanup();
	system("pause");
	return 0;
}
