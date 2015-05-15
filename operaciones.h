#ifndef _OPERACIONES_
#define _OPERACIONES_

#include <iostream>
#include <vector>
#include <list>


#include "parametros.h"
#include "escenario.h"
#include "inventario.h"

using namespace std;
using namespace parametros;

//Permite ejecutar comandos 
class ICommand{
	public:
	  virtual void execute()=0;
//	  virtual void execute(string coordenada)=0;
};

class Exit : public ICommand{
	public:
	  Exit(bool &continuar_loop):
			 continuar_loop(continuar_loop){}
	  void execute();
   private:
	  bool &continuar_loop;
};

class Ayuda : public ICommand{
	public:
	  Ayuda(vector<string> &v_comandos):v_comandos(v_comandos){}
	  void execute();
	private:
	  vector<string> v_comandos;
};

class Ver : public ICommand{
	public:
	  Ver(Escenario **escena_actual):escena_actual(escena_actual){}	  
	  void execute();
	  void set_escenario(){}
	private:
	  Escenario **escena_actual; //puntero a un puntor a un escenario
};

//class Coger : public ICommand{};

//class Ver : public ICommand{};
class Examinar: public ICommand{
	public:
	 Examinar(Escenario &escenario,Inventario &inventario,string &parametro):
		  escenario(escenario),inventario(inventario),parametro(parametro){}	  
	  void execute();
	  string describir_objeto(Objeto *objeto);
	private:
	  Escenario &escenario;
 	  Inventario &inventario;
	  string &parametro;
};
//class Inventario : public ICommand{};

/*class Norte : public ICommand{

	public:
	  Norte(Escenario escenario):escenario(escenario){}

	  void execute(){
			 

	  }
	private:
	  Escenario &escenario;
};
*/

//class Sur : public ICommand{};
//class Este : public ICommand{};
//class Oeste : public ICommand{};
//class Subir : public ICommand{};
//class Bajar : public ICommand{};




#endif
