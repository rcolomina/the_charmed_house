#include "eventsqueue.h"
#include "event.h"
#include <cassert>
#include <iostream>

void EventsQueue::push(IEvent *event)
{
    eventsQueue.push(event);	 
}

void EventsQueue::fire(){
    if(!eventsQueue.empty())
    {
        IEvent *event=eventsQueue.front();
        assert(event!=nullptr);
//			 cout<<event->message()<<endl;
        cout<<event->activate()<<std::endl;
        eventsQueue.pop();
    }	  
}
