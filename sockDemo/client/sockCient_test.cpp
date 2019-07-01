#include "SockClient.h"
int main(int argc,char **argv)
{
	char sendline[MAXLINE]={0};
	SockClient *client = new SockClient(PORTNUM,(char*)"192.168.1.101");
	client->Send(sendline,strlen(sendline));
	client->Close();

}
