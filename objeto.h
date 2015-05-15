#ifndef _objeto_
#define _objeto_

#include <string>

using namespace std;


//#include "escenario.h"

class Item{
	public:
	  Item(){}
	  ~Item(){}

};


class Objeto : public Item{
	public:
	  Objeto(const int id,const string nombre,const string descripcion);
	  void usar_sobre(Objeto *objeto);

	  //void eliminar(Objeto objeto); //si no está no hay nada que quitar
	  // void incluir_objeto(Objeto *objeto);
	  //void dejar_objeto();

	  //GETTERS
	  int get_id(){return id;}
	  string get_nombre(){return nombre;}
	  string get_descripcion(){return descripcion;}
	  bool get_usado(){return usado;}
	  bool get_visible(){return visible;}
	  bool get_fijo(){return fijo;}

	  //SETTERS
	  void set_fijo(bool estado){fijo=estado;}
	  void set_visible(bool estado){visible=estado;}
	  void set_usado(bool estado){usado=estado;}

	private:
	  const int id;
	  const string nombre;
	  //const string nombre_alternativo;
	  const string descripcion;
	  string descripcion_secundaria;

	  //atributos
	  bool fijo;  //es posible cogerlo para el inventario
	  bool usado; //ya no tiene utilidad en el juego
	  bool visible;

	  //list<Objeto*> subscriptores; //los subcriptores estan pendientes de cambios del estado del objeto subscrito
};

#endif

