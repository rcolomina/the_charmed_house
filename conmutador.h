#include <map>

class Conmutador{

	public:
	  Conmutador(int numero_estados,int estado_por_defecto,bool revierte);

	  //setters
	  void set_estado(int nuevo_estado){estado=nuevo_estado;} 

	  //getters
	  bool get_estado(){return estado;}


	private:
	  int numero_estados;
	  int estado;

	  //se fina en construccion
	  int estado_por_defecto;
	  bool revierte_estado_defecto; //despues de pulsarse revierte a estado por defecto
	  double tiempo_reversion; //0 si es un pulso
};
