#ifndef SOCK_SERVER_H_H
#define SOCK_SERVER_H_H
#include "SockDefines.h"

class SockServer
{
public:
	SockServer(int port);
	void Process();
private:
	void InitSock(int port);
	int Accept();
	int Recv(char* buf,size_t size);
	void Close();
private:
	int connfd;
	int listenfd;
	char buff[MAXLINE];
	struct sockaddr_in sockaddr;
};

#endif
