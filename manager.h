
#ifndef _MANAGER_
#define _MANAGER_

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <map>
#include <list>

//#include <thread>         // std::this_thread::sleep_for
//#include <chrono>         // std::chrono::seconds

#include <fstream> 

#include "inventario.h"
//#include "escenario.h"
#include "objeto.h"
#include "jugador.h"
#include "invocador.h"
#include "parametros.h"

using namespace std;
using namespace parametros;

class Manager{
//Crea los escenarios, los objetos, el jugador en estado incial.
//Proporciona al jugador la salidas, los objetos, 
//Desencaden los eventos que 
	public:
	  Manager();
	  ~Manager(){}

	  //METODOS LOOP PRINCIPAL
	  void run();
	  void update();
	  void dibujar();
     void tratamiento_comandos(string comando);

	  void prologo();

	  void actualizar_objetos();
	  void actualizar_salidas();
	  
	  //RELOJ
	  void clock();
	  int get_time(){return tiempo;}

	  //SETTERS
	  void set_comando(string comando);
	  void set_escena_actual(Escenario *escenario);

	  //GETTERS
	  string get_comandos_disponibles();
	  string get_descripcion_estado_actual();
	  string get_salidas_estado_actual();
	  map<string,Escenario*> get_escenarios_mundo();
	  map<string,Objeto> get_objetos_mundo();

	  Jugador get_jugador();
	  Inventario get_inventario();

	private:

	  //Time rate
	  const double dt;
	  //Reloj
	  double tiempo;

	  //Gestion de loop y comando de entrada de usuario
	  string comandos_disponibles;
	  bool continuar_loop;

	  // user inputs
	  string comando;
	  string parametro1;
	  string parametro2;
	  string parametro3;

	  vector<string> v_comandos;

	  //TODO: Construir escenarios y objetos del mundo
	  map<string,Escenario*> mundo;
	  map<string,Objeto> objetos_mundo;
	  
	  //Inventario y jugador por defecto.
	  Jugador jugador;       //
	  Inventario inventario; //guardar los objetos del jugador

	  //Contador mal comportamiento
	  int contador_mal_comportamiento;

	  //referencia al escenario actual
	  Escenario *escena_actual; //puntero al escenario actual
	  Escenario escena_actual1; //escenario actual


	  bool primera_entrada; //para mostrar la imagen del escenario

	  //string nombre;
	  //string descripcion;

	  Invocador invocador_comandos;	   //gestiona los comandos 
//	  map<string,ICommand*> mapComandos;

	  
}; 

#endif
