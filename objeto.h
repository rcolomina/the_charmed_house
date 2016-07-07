#ifndef _objeto_
#define _objeto_

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <queue>

#include "property.h"
#include "entidad.h"
#include "parametros.h"

//#define DEBUG
using namespace std;

class Objeto;
class IEvent;

typedef Objeto* pItem;
typedef Objeto Item;
//typedef Property<bool>* pBool;

class Objeto : public Entidad{
	public:
	  Objeto(int id,const string &name,const string& description):
			 Entidad(id,name,description){}	  
	  Objeto(const Entidad &ent,
				vector<string> names,
				vector<string> descriptions,
				vector<pair<string,string> > nameValues,
				string pathFileText
			 );	  
	  Objeto(const Entidad &ent,
				vector<string> names,
				vector<string> descriptions,
				vector<pBool> properties);

	  // This methods allows getting a generic property from this object
	  template <typename T>
	  T get_value(const char* pro);

	  //void usar_sobre(pItem objeto);
	  // void eliminar(Objeto objeto); //si no está no hay nada que quitar
	  // void incluir_objeto(pItem objeto);
	  // void dejar_objeto();

	  //GETTERS
	  //pBool get_property(const string &name);

	  
	  //SETTERS
	  void set_value(string prop,bool value);
	  void set_tirable(Objeto *objeto,string descrip_tirable);

//	  void set_event(IEvent *event);
	  
	  // Operaciones
	  void tirar();
	  void alcanzar();
	  void insertar();


	  void insert_event(IEvent* event);
	  IEvent* activate_event();
	private:
	  const vector<string> descriptions;
	  const vector<string> names;
	  
	  map<string,pItem> relatedObjects;	  

	  // storage for booleans properties
	  map<string,pBool> map_pBools;
	  map<string,bool> mapBool;
	  // storage for integer properties
	  map<string,pInt> map_pInts;
	  
//const string nombre_alternativo;
	  string descripcion_secundaria;
	  string descripcion_tirar;
	  // Hacer visible y/o alcanzable tras la accion
	  pItem objeto_rel_tirar;
	  pItem objeto_rel_alcanzar;

	  // Otra salida tras la accion
//	  Escenario *escena_rel_abrir;
//	  Escenario *escena_rel_insertar;

	  // Path File text
	  string pathFileText;

	  // Events asociated to this object
	  queue<IEvent*> eventsToFire;
};


#endif

