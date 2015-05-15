#ifndef _INVOCADOR_
#define _INVOCADOR_

#include <map>

#include "operaciones.h"

// Ejecuta los comandos
class Invocador{
	public:
	  Invocador(){}
//	  Invocador(ICommand *exit=0):exit(exit){}
	  Invocador(ICommand *exit,
					ICommand *ayuda,
					ICommand *ver):
			 exit(exit),ayuda(ayuda),ver(ver){}
	  //Invocador(list<ICommand*> lcomandos):lcomandos(lcomandos){}
	  Invocador(map<string,ICommand*> mapComandos):mapComandos(mapComandos){}

	  void salir();
	  void ayuda_comandos();
	  void ver_comando();
	  void set_command(ICommand *command);

	private:
	  ICommand *exit;
	  ICommand *ayuda;
	  ICommand *ver;

	  //list<ICommand*> lcomandos;
	   map<string,ICommand*> mapComandos;
};

#endif
