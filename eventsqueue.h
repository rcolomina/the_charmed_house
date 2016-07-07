#ifndef _eventsqueue_
#define _eventsqueue_

#include "ievent.h"

#include <queue>

class EventsQueue {
	public:
	  EventsQueue(){}

	  void push(IEvent *event);
	  void fire();
	private:
	  std::queue<IEvent*> eventsQueue;
};

#endif

