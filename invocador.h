#ifndef _INVOCADOR_
#define _INVOCADOR_

#include <map>

#include "operaciones.h"

// This class gather all commands existing in game.
class Invocador{
	public:
	  Invocador(){}
	  Invocador(map<string,ICommand*> mapComandos):mapComandos(mapComandos){}

	  void salir();
	  void ayuda_comandos();
	  void ver_comando();
	  void examinar_comando(string parametro);

	  void set_command(ICommand *command);

      void exec(string command);    
 
	private:
     /*  ICommand *exit;
	  ICommand *ayuda;
	  ICommand *ver;*/

	  //list<ICommand*> lcomandos;
	   map<string,ICommand*> mapComandos;
};

#endif
