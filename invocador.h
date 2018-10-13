#ifndef _INVOCADOR_
#define _INVOCADOR_

#include <map>

#include "operaciones.h"

// This class gathers all existing commands in game by a string command key
// Exxection method determines wheter the command exist or not.
class Invocador{
	public:
	  Invocador(){}
	  Invocador(map<string,ICommand*> mapComandos):
	  mapComandos(mapComandos){}

	  void exec(string commandKey,string parametro1,string parametro2);    
 
	private:
	   map<string,ICommand*> mapComandos;
};

#endif
