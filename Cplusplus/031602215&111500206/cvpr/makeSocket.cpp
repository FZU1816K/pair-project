#include<makeSocket.h>
int makeSocket(string host, int port)
{
	WSADATA inet_WsaData;
	WSAStartup(MAKEWORD(2, 0), &inet_WsaData);
	if (LOBYTE(inet_WsaData.wVersion) != 2 || HIBYTE(inet_WsaData.wVersion) != 0)
	{
		WSACleanup();
		return -1;
	}
	int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct hostent * hp = ::gethostbyname(host.c_str());
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);

	memcpy(&saddr.sin_addr, hp->h_addr, 4);
	if (connect(tcp_socket, (const struct sockaddr *)&saddr, sizeof(saddr)) == -1)
	{
		cerr << "error in connect" << endl;
	}
	return tcp_socket;
}