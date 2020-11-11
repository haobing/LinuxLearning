#pragma once
#include"EventHandle.h"
#include <sys/epoll.h>
#include<stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>
#include<string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

class DemuxEpoll
{
private:
	int m_epollfd;
	int m_conNum;
public:
	DemuxEpoll(int maxCon)
	{
		m_conNum = 0;
		m_epollfd = epoll_create(maxCon);
	}
	bool handleEvent();
	void epollRegister(EventHandle *ev, EventHandle::EventType type);
	void epollRemove(EventHandle *ev);
};

