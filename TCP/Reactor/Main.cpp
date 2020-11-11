#include"Reactor.h"

//事件Dog
class EventDog :public EventHandle
{
private:
	Reactor *re;
public:
	EventDog(Reactor *rea, int sock) :re(rea) { sockfd = sock; }
	bool read()
	{
		printf("in the EventDog read()\n");
		char buf[64];
		memset(buf, 0, sizeof(buf));
		int len=recv(sockfd, buf, sizeof(buf), 0);
		if (len == 0)
		{
			re->unregisterEvent(this);
			return true;
		}
		
		printf("the sockfd=%d,recv buf=%s\n", sockfd,buf);
		re->registerEvent(this, kWrite);
		return true;
	}
	bool write()
	{
		char buf[64] = "hello world form the EventDog\n";
		int len=send(sockfd, buf, sizeof(buf), 0);
		printf("send to the client len=%d\n", len);
		re->registerEvent(this, kRead);
	}
};




class EventAccept :public EventHandle
{
private:
	Reactor *re;
public:
	EventAccept(Reactor *rea) :re(rea) 
	{ 
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		int opt = 1;
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
		struct sockaddr_in server,client;
		socklen_t socklen = sizeof(client);
		memset(&server, 0, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(8888);
		server.sin_addr.s_addr = htonl(INADDR_ANY);
		bind(sockfd, (struct sockaddr*)&server, sizeof(server));
		listen(sockfd, 100);
		re->registerEvent(this, kRead);
	}
	bool write()
	{
		
	}

	bool read()
	{
		struct sockaddr_in  client;
		socklen_t socklen = sizeof(client);
		int fd = accept(sockfd, (struct sockaddr*)&client, &socklen);
		printf("the accept fd=%d\n", fd);
		EventHandle* ev = new EventDog(re, fd);
		re->registerEvent(ev, kRead);
		re->registerEvent(this, kRead);
	}
};



//事件Bird

class EventBird :public EventHandle
{
private:
	Reactor *re;
public:
	EventBird(Reactor *rea, int sock) :re(rea) { sockfd = sock; }
	bool read()
	{
		printf("in the EventBird read()\n");
		char buf[64];
		memset(buf, 0, sizeof(buf));
		int len = recv(sockfd, buf, sizeof(buf), 0);
		if (len == 0)
		{
			re->unregisterEvent(this);
			return true;
		}

		printf("the sockfd=%d,recv buf=%s\n", sockfd, buf);
		re->registerEvent(this, kWrite);
		return true;
	}
	bool write()
	{
		char buf[64] = "hello world form the EventBird\n";
		int len = send(sockfd, buf, sizeof(buf), 0);
		printf("send to the client len=%d\n", len);
		re->registerEvent(this, kRead);
	}
};



class EventAcceptBird :public EventHandle
{
private:
	Reactor *re;
public:
	EventAcceptBird(Reactor *rea) :re(rea)
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		int opt = 1;
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
		struct sockaddr_in server, client;
		socklen_t socklen = sizeof(client);
		memset(&server, 0, sizeof(server));
		server.sin_family = AF_INET;
		server.sin_port = htons(9999);
		server.sin_addr.s_addr = htonl(INADDR_ANY);
		bind(sockfd, (struct sockaddr*)&server, sizeof(server));
		listen(sockfd, 100);
		re->registerEvent(this, kRead);
	}
	bool write()
	{

	}

	bool read()
	{
		struct sockaddr_in  client;
		socklen_t socklen = sizeof(client);
		int fd = accept(sockfd, (struct sockaddr*)&client, &socklen);
		printf("the accept fd=%d\n", fd);
		EventHandle* ev = new EventBird(re, fd);
		re->registerEvent(ev, kRead);
		re->registerEvent(this, kRead);
	}
};

int main()
{
	Reactor *re = new Reactor();
	EventAccept *ev = new EventAccept(re);
	EventAcceptBird *ev1 = new EventAcceptBird(re);
	re->handEvent();

}

