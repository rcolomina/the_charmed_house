#ifndef _INVOCADOR_
#define _INVOCADOR_

#include <map>

#include "operaciones.h"

// This class gathering all commands existing in game by a string command key
// An exection method determine wheter the command exist or not.
class Invocador{
	public:
	  Invocador(){}
	  Invocador(map<string,ICommand*> mapComandos):
			 mapComandos(mapComandos){}

	  void exec(string commandKey);    
 
	private:
	   map<string,ICommand*> mapComandos;
};

#endif
