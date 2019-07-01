#include "SockServer.h"

static void* pthread_adminserver(void *arg)
{
	int rc;
	int client_sd =*((int*)arg);
	printf("client connected!sock_id:%d\n",client_sd);
	char buffer[4096];
	while(1)
	{
		memset(buffer,0,4096);
		rc=read(client_sd,buffer,4096);
		if(strlen(buffer) == 0)
		{
			printf("close connection!\n");
			close(client_sd); 
			pthread_exit(0);
		}
		printf("read data:%s\n",buffer);
	}
	close(client_sd);
	pthread_exit(0);
}

SockServer::SockServer(int port):client_fd(-1)
{
	InitSock(port);
}

void SockServer::InitSock(int port)
{
	memset(&sockaddr,0,sizeof(sockaddr));

	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(port);

	server_fd = socket(AF_INET,SOCK_STREAM,0);
	bind(server_fd,(struct sockaddr *) &sockaddr,sizeof(sockaddr));
	listen(server_fd,1024);
}

void SockServer::Process()
{
	printf("Socker Server Started....\n");
	for(;;)
	{
		client_fd = accept(server_fd,(struct sockaddr*)NULL,NULL);
		if (client_fd != -1 && pthread_create(&p_tcpserver, NULL, pthread_adminserver, &client_fd)!=0)
		{
			printf("Could not create thread check_work_time\n");
			return ;
		}
	}
	Close();
}

int SockServer::Recv(char* buf,size_t size)
{
	memset(buf,0,size);
	int sizeRead = recv(client_fd,buf,size,0);
	if(sizeRead!=0)
		printf("Message:%s",buf);
	return sizeRead;
}

void SockServer::Close()
{
	close(server_fd);
}
