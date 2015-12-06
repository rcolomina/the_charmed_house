#ifndef _DISPARADOR_H_
#define _DISPARADOR_H_

#include <string>

using namespace std;

class Entidad {
	public:
	  Entidad():id(0){}
	  Entidad(int id,string nombre,string descripcion):
			 id(id),
			 nombre(nombre),
	       descripcion(descripcion){}

	  int get_id(){return id;}
	  void set_id(int id){this->id=id;}

	  string get_nombre(){return nombre;}
	  void set_nombre(string nombre){this->nombre=nombre;}

	  string get_descripcion(){return descripcion;}
	  void set_descripcion(string descripcion){this->descripcion=descripcion;}
	protected:
	  int id;  //identificador del escenario
	  string nombre;
	  string descripcion;
};


#endif
