#ifndef SOCK_CLIENT_H_H
#include "SockDefines.h"

class SockClient
{
public:
	SockClient(int port,char *serverUrl);
	void Send(char *buf,size_t size);
	void Close();
private:
	void Connect();
	void InitSocket(int port);
private:
	int socketfd;
	char serverAddr[128];
	struct sockaddr_in sockaddr;
};

#endif
