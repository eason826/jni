#ifndef EV_SERVER_H_H
#define EV_SERVER_H_H
#include "EvDefines.h"

class EvServer
{
private:
	EvServer();
public:
	static EvServer& getInstance();
	void Run();
	void setEvList(int index,struct ev_io*);
	struct ev_io* getEvList(int);
private:
	int sd;
	struct ev_loop *loop;
	struct sockaddr_in addr;
	struct ev_io *socket_watcher;
	struct ev_io *libevlist[MAX_CONNECTIONS];
};

inline struct ev_io* EvServer::getEvList(int index)
{
	return libevlist[index];
}

inline void EvServer::setEvList(int index,struct ev_io *list)
{
	libevlist[index] = list;
}

inline EvServer& EvServer::getInstance()
{
	static EvServer evObj;
	return evObj;
}

#endif
