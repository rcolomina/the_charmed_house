#ifndef _jugador_
#define _jugador_


#include <map>

class Inventario;
class Escenario;
class Objeto;

class Jugador{
   public:
	  Jugador();

	  void moverse(Escenario *escena); //tiene que ser válida
	  void coger_objeto(Objeto objeto); //de los que hay a su alcance
	  void examinar_escenario(Escenario *escena);
	  void examinar_objeto(Objeto objeto);
	  void usar_objeto(Objeto objeto); //de los disponibles

	  Escenario *get_posicion();
	  Inventario *get_intenvario();
	private:
	  

	  Escenario *posicion_escenario; //donde se encuentra nuestro jugador
//	  Inventario *inventario; //se guardan los
};


#endif

