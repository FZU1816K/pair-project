#include "get_crpv2018.h"

void get_crpv2018()
{
	

		string url = "openaccess.thecvf.com";
		string name = "/CVPR2018.py";
		int port = 80;
		int client_socket = makeSocket(url, port);
		string request = "GET " + name + " HTTP/1.1\r\nHost:" + url + "\r\nConnection:Close\r\n\r\n";

		if (send(client_socket, request.c_str(), request.size(), 0) == SOCKET_ERROR)
		{
			cout << "send error" << endl;
		}

		fstream file;
		string fileName = FileName(name);
		file.open(fileName, ios::out | ios::binary);

		char buf[2048];
		::memset(buf, 0, sizeof(buf));
		int n = 0;
		int count = 0;



		while ((n = recv(client_socket, buf, sizeof(buf) - sizeof(char), 0)) > 0)
		{
			try
			{
				file << buf;
			}
			catch (...)
			{
				cerr << "ERROR" << endl;
			}
		}
		file.close();
		closesocket(client_socket);

	
}
