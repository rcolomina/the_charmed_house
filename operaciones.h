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
	  Ver(ppScene escena_actual):escena_actual(escena_actual){}	  
	  void execute();
	  void set_escenario(){}
	private:
	  ppScene escena_actual; //puntero a un puntor a un escenario
};

//class Coger : public ICommand{};

//class Ver : public ICommand{};
class Examinar: public ICommand{
	public:
	  Examinar(ppScene scene,
				  Inventario &inventario,
				  string &parametro):
			 scene(scene),
			 inventario(inventario),
			 parametro(parametro){}	  
	  void execute();
	  string describir_objeto(Objeto *objeto);
	private:
	  ppScene scene;
	  Inventario &inventario;
	  string &parametro;
};

class CommandInventario : public ICommand{
	public:
	  CommandInventario(Inventario &inventario):
			 inventario(inventario){}
	  void execute();
	private:
	  Inventario &inventario;
};

class Cardinal : public ICommand{
	public:
	  Cardinal(ppScene scene,
				  const string &cardinal,
				  bool &primera_entrada):
			 escena_actual(scene),
			 cardinal(cardinal),
			 primera_entrada(primera_entrada)
	  {}
	  void execute();
	private:
	  ppScene escena_actual;
	  const string &cardinal;
	  bool &primera_entrada;
};

class Tirar : public ICommand{
	public:
	  Tirar(ppScene scene,
			  Inventario &inventario,
			  const string &parametro,
			  const string &parametro2):
			 scene(scene),
			 inventario(inventario),
			 parametro(parametro),
			 parametro2(parametro2){}
	  void execute();
	private:
	  ppScene scene;
	  Inventario &inventario;
	  const string &parametro;
	  const string &parametro2;
};

class Coger : public ICommand{
	public:
	  Coger(ppScene scene,
			  Inventario &inventario,
			  const string &parametro):
			 scene(scene),
			 inventario(inventario),
			 parametro(parametro){}
	  void execute();
	private:
	  ppScene scene;
	  Inventario &inventario;
	  const string &parametro;
};

class Dejar : public ICommand{
	public:
	  Dejar(ppScene scene,
			  Inventario &inventario,
			  const string &parametro):
			 scene(scene),
			 inventario(inventario),
			 parametro(parametro){}
	  void execute();
	private:
	  ppScene scene;
	  Inventario &inventario;
	  const string &parametro;
};


class Alcanzar : public ICommand {
	public:
	  Alcanzar(ppScene scene,
				  Inventario &inventario,
				  const string &parametro):
			 scene(scene),
			 inventario(inventario),
			 parametro(parametro){}
	  void execute();
	private:
	  ppScene scene;
	  Inventario &inventario;
	  const string &parametro;
};


#endif
