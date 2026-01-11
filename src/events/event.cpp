#include "event.h"
#include "cassert"

const string EventOpenConnection::activate(){

    assert(scene!=nullptr);
    scene->set_estado_salida(cardinal,true);
    /// TODO: If something goes wrong this should return an error messages
//	  return string("message");
    return postMessage;
}

const string EventOpenConnection::message(){
//	  return string("message");
    return postMessage;
}
