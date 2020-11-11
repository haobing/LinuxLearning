#include "DemuxEpoll.h"
#include<unistd.h>

bool DemuxEpoll::handleEvent()
{
	struct epoll_event epoll[m_conNum];
	printf("in the handleEvent\n");
	int evNum = epoll_wait(m_epollfd, epoll, m_conNum, -1);
	if (evNum < 0)
	{
		perror("epoll_wait error\n");
		return false;
	}
	for (int i = 0; i < evNum; i++)
	{
		EventHandle *ev = (EventHandle*)epoll[i].data.ptr;
		if (epoll[i].events&EPOLLIN)
		{
			ev->read();
		}
		else if (epoll[i].events&EPOLLOUT)
		{
			ev->write();
		}
	}

	return true;
}


void DemuxEpoll::epollRegister(EventHandle *ev, EventHandle::EventType type)
{
	struct epoll_event event;
	event.data.ptr = (void*)ev;
	int fd = ev->getfd();
	
	if (type == EventHandle::kRead)
	{
		event.events = EPOLLIN;
	}
	else if (type == EventHandle::kWrite)
	{
		event.events = EPOLLOUT;
	}

	if (epoll_ctl(m_epollfd, EPOLL_CTL_MOD, fd, &event) != 0)
	{
		if (errno == ENOENT)
		{
			epoll_ctl(m_epollfd, EPOLL_CTL_ADD, fd, &event);
			m_conNum++;
		}
	}
}
void DemuxEpoll::epollRemove(EventHandle *ev)
{
	int fd = ev->getfd();
	struct epoll_event event;
	epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, &event);
	printf("remove the %d\n", fd);
	close(fd);
	m_conNum--;
}