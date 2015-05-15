#ifndef _escenario_
#define _escenerio_

#include <string>
#include <map>
#include "objeto.h"

using namespace std;


//Clase que describe un escenario: Salidas, Objetos, Descripción, Imagen
class Escenario{
	public:
	  //constructores
	  Escenario(int id,string nombre,string descripcion,string observacion);

	  //////getters//////
	  int get_id(){return id;}
	  string get_nombre_escenario(){return nombre_escenario;}
	  string get_descripcion(){return descripcion;}	 
	  string get_observacion(){return observacion;}
	  map<string,Escenario*> get_salidas(){return salidas;} //devuelve lista de escenarios salidas
	  Escenario* get_salida(string coordenada){return salidas[coordenada];} //devuelve nulo si no existe
	  map<string,Objeto*> get_objetos(){return objetos;} //que objetos hay disponible
	  string get_objetos_disponibles();
	  

	  Objeto* get_objeto(string nombre){return objetos[nombre];}

	  bool get_existe_objeto_escenario(string nombre);



	  //////setters/////
	  void set_salidas(map<string,Escenario*> salidas); //se invocará en la construcción del mundo

	  void set_salida(Escenario* escenario,string coordenada){
			 salidas[coordenada]=escenario;
	  }

	  void set_objeto(Objeto* objeto){
			 string nombre=objeto->get_nombre();
			 objetos[nombre]=objeto;
	  }

	  //procedimientos
	  void pintado(); //permite pintar el escenario

	private:
	  int id;  //identificador del escenario
	  string nombre_escenario;  //nombre del escenario
	  string descripcion;
	  string observacion;
	  map<string,Escenario*> salidas; //guarda par (coordenada, Escenario*)
	  map<string,Objeto*> objetos;    //nombre y referenca a objeto
};

#endif


