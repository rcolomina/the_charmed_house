#ifndef _escenario_
#define _escenerio_

#include <string>
#include <map>

#include "entidad.h"
#include "objeto.h"

using namespace std;

//class Objeto;
class Escenario;
typedef Escenario* pScene;
typedef Escenario** ppScene;

//Clase que describe un escenario: Salidas, Objetos, Descripción, Imagen
class Escenario : public Entidad {
	public:
	  //constructores
	  Escenario(){}
	  Escenario(int id,string nombre,string descripcion,string observacion);

	  //////getters//////
	  string get_observacion(){return observacion;}
	  map<string,Escenario*> get_salidas(){return salidas;} //devuelve lista de escenarios salidas
	  Escenario* get_salida(string coordenada){return salidas[coordenada];} //devuelve nulo si no existe
	  map<string,pItem> get_objetos(){return objetos;} //que objetos hay disponible
	  string get_objetos_disponibles();
	  
	  pItem get_objeto(string nombre){return objetos[nombre];}
	  bool get_existe_objeto_escenario(string nombre);

	  //////setters/////
	  void set_salidas(map<string,Escenario*> salidas); //se invocará en la construcción del mundo
	  void set_salida(Escenario* escenario,string coordenada){
			 salidas[coordenada]=escenario;
	  }

	  void set_objeto(Objeto* objeto);
	  void eliminar(Objeto *obj);

	  //procedimientos
	  void pintado(); //permite pintar el escenario

	private:	
	  string observacion;
	  map<string,Escenario*> salidas; //guarda par (coordenada, Escenario*)
	  map<string,Objeto*> objetos;    //nombre y referenca a objeto
};

/*
class ScenePuzzle : public Escenario{
	public:
	  ScenePuzzle(){}

};*/

#endif


