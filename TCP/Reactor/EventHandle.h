#pragma once
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
class EventHandle
{
private:
protected:
	int sockfd;
public:
	
	enum EventType {
		kWrite=1,
		kRead=2,
		kError=3
	};
	virtual bool write()=0;
	virtual bool read()=0;
	int getfd() { return sockfd; }
};
