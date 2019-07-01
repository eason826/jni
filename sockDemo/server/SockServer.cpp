#include "SockServer.h"

SockServer::SockServer(int port):connfd(-1)
{
	InitSock(port);
}

void SockServer::InitSock(int port)
{
	memset(&sockaddr,0,sizeof(sockaddr));

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(port);

	listenfd = socket(AF_INET,SOCK_STREAM,0);
	bind(listenfd,(struct sockaddr *) &sockaddr,sizeof(sockaddr));
	listen(listenfd,1024);
}

void SockServer::Process()
{
	printf("Socker Server Started....\n");
	for(;;)
	{
		if(Accept() == -1)
		{
			printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
			continue;
		}
		Recv(buff,MAXLINE);
	}
	Close();
}

int SockServer::Accept()
{
	connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
	return connfd;
}		

int SockServer::Recv(char* buf,size_t size)
{
	int sizeRead = recv(connfd,buf,size,0);
	printf("Message:%s",buf);
	return sizeRead;
}

void SockServer::Close()
{
	close(connfd);
	close(listenfd);
}	
