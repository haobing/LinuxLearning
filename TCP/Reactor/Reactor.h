#pragma once
#include "DemuxEpoll.h"
#include "EventHandle.h"
class Reactor
{
private:
	DemuxEpoll *m_depoll;
	static int m_num;
public:
	Reactor();
	~Reactor();
	void handEvent();
	void registerEvent(EventHandle *ev, EventHandle::EventType type);
	void unregisterEvent(EventHandle *ev);

};

