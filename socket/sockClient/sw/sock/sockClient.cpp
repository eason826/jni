#include "SockClient.h"

SockClient::SockClient(int port,char *serverUrl)
{
	strncpy(serverAddr,serverUrl,128);
	InitSocket(port);
	Connect();
}

void SockClient::InitSocket(int port)
{
	socketfd = socket(AF_INET,SOCK_STREAM,0);
	memset(&sockaddr,0,sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(10004);
	inet_pton(AF_INET,serverAddr,&sockaddr.sin_addr);
}

void SockClient::Connect()
{
	if((connect(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) < 0 )
	{
		printf("connect error %s errno: %d\n",strerror(errno),errno);
		exit(0);
	}
	printf("Connect to Server Success!\n");
}

void SockClient::Process()
{
	char buffer[MAXLINE]={0};
	for(;;)
	{
		printf("MSG:");
		fgets(buffer,1024,stdin);
		if(strncmp(buffer,"quit",strlen("quit")) ==0)
		{
			Close();
			return;
		}
		Send(buffer,MAXLINE);
	}
}

void SockClient::Send(char *buf,size_t size)
{
	if((send(socketfd,buf,strlen(buf),0)) < 0)
	{
		printf("send mes error: %s errno : %d",strerror(errno),errno);
		exit(0);
	}
}

void SockClient::Close()
{
	printf("client close..\n");
	close(socketfd);
}
