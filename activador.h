#include <list>

#ifndef _DISPARADOR_H_
#define _DISPARADOR_H_

/*
template <typename T>
class Condicion {
	public:
	  Condicion(


};*/

// Relaciona estados entre entidades. Las causas produce efectos entre la entidades del juego. Ciertos estados de la lista de entidades causadora cambiaran los estados de la lista de las entidades en efectos.

using namespace std;

class Entidad;

class Disparador{
	public:
	  Disparador(){}
	private:
	  list<Entidad*> causas;
	  list<Entidad*> efectos;
};


#endif
