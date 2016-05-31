#ifndef _objeto_
#define _objeto_

#include <string>
#include <iostream>

#include "entidad.h"

using namespace std;

class Objeto : public Entidad{
	public:
	  Objeto();
	  Objeto(int id,string nombre,string descripcion);

	  void usar_sobre(Objeto *objeto);

	  // void eliminar(Objeto objeto); //si no está no hay nada que quitar
	  // void incluir_objeto(Objeto *objeto);
	  // void dejar_objeto();

	  //GETTERS
	  bool get_usado(){return usado;}
	  bool get_visible(){return visible;}
	  bool get_fijo(){return fijo;}
	  bool get_tirable(){return tirable;}
	  bool get_atascado(){return atascado;}
	  bool get_desatascador(){return desatascador;}
	  bool get_alcanzable(){return alcanzable;}
	  bool get_alcanzador(){return alcanzador;}

	  //SETTERS
	  void set_visible(bool estado){visible=estado;}
	  void set_usado(bool estado){usado=estado;}
	  void set_fijo(bool estado){fijo=estado;}
	  void set_tirable(Objeto *objeto,string descrip_tirable);
	  void set_atascado(bool estado){ atascado=estado;}
	  void set_desatascador(bool estado){ desatascador=estado;}
	  void set_alcanzable(bool estado){ alcanzable=estado;}
	  void set_alcanzador(bool estado){ alcanzador=estado;}

	  // Operaciones
	  void tirar();
	  void alcanzar();
	  void insertar();

	private:
	  //const string nombre_alternativo;
	  string descripcion_secundaria;
	  string descripcion_tirar;

	  // Hacer visible y/o alcanzable tras la accion
	  Objeto *objeto_rel_tirar;
	  Objeto *objeto_rel_alcanzar;

	  // Otra salida tras la accion
//	  Escenario *escena_rel_abrir;
//	  Escenario *escena_rel_insertar;

	  

	  // Atributos del objeto
	  bool fijo;         // True: No es posible cogerlo para el inventario.
	  bool usado;        // True: Ya no tiene utilidad en el juego.
	  bool visible;      // True: No es visible a simple vista.
	  bool visualizador; // True: Permite examinar en detalle.
	  bool tirable;      // True: Se puede tirar para desbloquearlo.
	  bool atascado;     // True: Necesita ser desatascado.
	  bool desatascador; // True: Permite desatascar otros objetos.
	  bool alcanzable;   // True: Se puede alcanzar facil.
	  bool alcanzador;   // True: Permite coger objeto no alcanzables
	  bool movible;      // True: Puede cambiarse de posicion
	  bool movedor;      // True: Sirve para mover otros objetos
	  bool abrible;      // True: Permite ser abierto  (id 
	  bool abridor;      // True: Sirve para abrir.
	  bool insertable;   // True: Permite ser insertado

	  //list<Objeto*> subscriptores; //los subcriptores estan pendientes de cambios del estado del objeto subscrito
};

#endif

