#include "EvServer.h"
void readCB(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
	char buffer[BUFFER_SIZE]={0};
	ssize_t read;
	ev_io *list = EvServer::getInstance().getEvList(watcher->fd);
	if (EV_ERROR & revents)
	{
		printf("error event in read\n");
		return;
	}
	read = recv(watcher->fd, buffer, BUFFER_SIZE, 0);
	if (read < 0)
	{
		printf("read error\n");
		return;
	}

	if (read == 0)
	{
		printf("client disconnected.\n");

		if (list == NULL)
		{
			printf("the fd already freed[%d]\n", watcher->fd);
		}
		else
		{
			printf("fd:%d will be closed!\n",watcher->fd);
			close(watcher->fd);
			ev_io_stop(loop, list);
			free(list);
			EvServer::getInstance().setEvList(watcher->fd,NULL);
		}
		return;
	}
	else
	{
		printf("recv Msg from[%d]:%s\n",watcher->fd,buffer);
		if(memcmp(buffer,"quit",strlen("quit")) == 0)
		{
			printf("recv quit cmd,fd:%d will be closed!\n",watcher->fd);
			close(watcher->fd);
			ev_io_stop(loop, list);
			free(list);
			EvServer::getInstance().setEvList(watcher->fd,NULL);
			return ;
		}
	}
	send(watcher->fd, buffer, read, 0);
	bzero(buffer, sizeof(buffer));
}

void acceptCB(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
	printf("I am: %d\n", getpid());

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_sd;

	if (EV_ERROR & revents)
	{
		printf("error event in accept\n");
		return;
	}

	client_sd = accept(watcher->fd, (struct sockaddr*) &client_addr, &client_len);
	if (client_sd < 0)
	{
		printf("accept error\n");
		return;
	}
	if (client_sd > MAX_CONNECTIONS)
	{
		printf("fd too large[%d]\n", client_sd);
		close(client_sd);
		return;
	}
	ev_io *list = EvServer::getInstance().getEvList(client_sd);

	if (list != NULL)
	{
		printf("client_sd not NULL fd is [%d]\n", client_sd);
		return;
	}

	printf("client connected\n");
	struct ev_io *client_watcher = (struct ev_io*) malloc(sizeof(struct ev_io));
	if (client_watcher == NULL)
	{
		printf("malloc error in accept_cb\n");
		return;
	}
	ev_io_init(client_watcher, readCB, client_sd, EV_READ);
	ev_io_start(loop, client_watcher);
	EvServer::getInstance().setEvList(client_sd,client_watcher);
}

EvServer::EvServer()
{
	loop = ev_default_loop(0);
	socket_watcher = (struct ev_io*)malloc(sizeof(struct ev_io));

	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		printf("socket error\n");
		return;
	}
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sd, (struct sockaddr*) &addr, sizeof(addr)) != 0)
	{
		printf("bind error\n");
		return;
	}
	if (listen(sd, SOMAXCONN) < 0)
	{
		printf("listen error\n");
		return;
	}
	int bReuseaddr = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (const char*) &bReuseaddr, sizeof(bReuseaddr)) != 0)
	{
		printf("setsockopt error in reuseaddr[%d]\n", sd);
		return;
	}
}

void EvServer::Run()
{
	ev_io_init(socket_watcher, acceptCB, sd, EV_READ);
	ev_io_start(loop, socket_watcher);
	ev_run(loop, 0);
}
