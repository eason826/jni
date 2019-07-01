#include "SockClient.h"
int main(int argc,char **argv)
{
	SockClient *client = new SockClient(PORTNUM,(char*)"192.168.53.108");
	client->Process();

}
