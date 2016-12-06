#ifndef _event_
#define _event_

#include "ievent.h"
#include "escenario.h"

// Event that open a scene connection on a cardinal point
class EventOpenConnection : public IEvent {
   public:
     // It should have the scene and the coordenate to be open
     EventOpenConnection(Escenario *scene,
			 const std::string cardinal,
			 const std::string postMessage):
	  scene(scene),
	  cardinal(cardinal),
	  postMessage(postMessage){}
			 
     const string activate();
     const string message();

   private:
     Escenario *scene;
     const std::string cardinal;
     const std::string postMessage;
};

#endif
