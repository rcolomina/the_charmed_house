#ifndef _ievent_
#define _ievent_

#include <string>

// Abstract interfacew for an Event.
// This class has a virtual method which will
// be implemented on concrete classes.
// Furthermore, it avoids cyclic dependendencies
// among scenes and events.
class IEvent{
public:
	virtual ~IEvent() = default;
	virtual const std::string activate() = 0;
	virtual const std::string message() = 0;
};

#endif
