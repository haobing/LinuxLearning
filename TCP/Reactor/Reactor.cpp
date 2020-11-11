#include "Reactor.h"
int Reactor::m_num = 1;
Reactor::Reactor()
{
	m_depoll = new DemuxEpoll(10);
}
Reactor::~Reactor()
{
	if (m_depoll != nullptr)
	{
		delete m_depoll;
	}
}
void Reactor::handEvent()
{
	while (1)
	{
		m_depoll->handleEvent();
	}
}
void Reactor::registerEvent(EventHandle *ev, EventHandle::EventType type)
{
	m_depoll->epollRegister(ev, type);
}
void Reactor::unregisterEvent(EventHandle *ev)
{
	m_depoll->epollRemove(ev);
}
