#include "SockServer.h"

int main(int argc,char **argv)
{
	SockServer *server = new SockServer(10004);
	server->Process();
	return 0;
}
