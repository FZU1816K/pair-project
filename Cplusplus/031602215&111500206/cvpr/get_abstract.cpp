#include<get_abstract.h>
#include<something.h>
void get_abstract()
{
	vector<string> lj;
	lj = abstract(lj);

	fstream file;
	file.open(fileName, ios::out | ios::binary);

	for (int i = 0; i < lj.size(); i++)  //Ñ­»·ÅÀÈ¡
	{
		string url = "openaccess.thecvf.com";
		string name = "/" + lj[i];
		int port = 80;
		int client_socket = makeSocket(url, port);//1
		string request = "GET " + name + " HTTP/1.1\r\nHost:" + url + "\r\nConnection:Close\r\n\r\n";

		if (send(client_socket, request.c_str(), request.size(), 0) == SOCKET_ERROR)
		{
			cout << "send error" << endl;
		}


		char buf[1024];
		::memset(buf, 0, sizeof(buf));
		int n = 0;
		n = recv(client_socket, buf, sizeof(buf) - sizeof(char), 0);
		char* cpos = strstr(buf, "\r\n\r\n");
		file.write(cpos + strlen("\r\n\r\n"), n - (cpos - buf) - strlen("\r\n\r\n"));

		while ((n = recv(client_socket, buf, sizeof(buf) - sizeof(char), 0)) > 0)
		{
			try
			{
				file.write(buf, n);
			}
			catch (...)
			{
				cerr << "ERROR" << endl;
			}
		}
		closesocket(client_socket);
		cout << i << endl;
	}
//	system("pause");
	file.close();
}
