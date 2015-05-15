#ifndef _PARAMETROS_
#define _PARAMETROS_

#include <string>
#include <iostream>

using namespace std;

namespace parametros{
	  const string c1("exit");
	  const string c2="examinar";
	  const string c3="ver";
	  const string c4="inventario";
	  const string c5="salidas";
	  const string c6="norte(n)";
	  const string c7="sur(s)";
	  const string c8="este(e)";
	  const string c9="oeste(o)";
	  const string c10="tiempo";
	  const string space=" ";
	  
	  const string s_exit="exit";
	  const string s_ayuda="ayuda";
	  const string s_examinar="examinar";
	  const string s_ver="ver";
	  const string s_inventario="inventario";
	  const string s_salidas="salidas";
	  const string s_norte="norte(n)";
	  const string s_sur="sur(s)";
	  const string s_este="este(e)";
	  const string s_oeste="oeste(o)";
	  const string s_tiempo="tiempo";
	  const string s_space=" ";

	  const string oeste="oeste";
	  const string este="este";
	  const string norte="norte";
	  const string sur="sur";

	  const string bajar="bajar";
	  const string subir="subir";
	  const string abrir="abrir";
	  const string cerrar="cerrar";
	  const string golpear="golpear";
	  const string tirar="tirar";
	  const string empujar="empujar";
	  const string pulsar="pulsar";

	  const string comandos[10]={s_exit,
										  s_examinar,
										  s_ver,
										  s_inventario, 
										  s_salidas,
										  s_norte,
										  s_sur,
										  s_este,
										  s_oeste,
										  s_tiempo};


     //DESCRIPCIONES ESCENARIOS: TODO ¿Cómo organizar las descripciones y observaciones de un escenario?
	  const int id_escena1=1;
	  const string nombre1="La Entrada a la Casa";
	  const string escena1=nombre1;
	  const string descripcion1="Una casa antigua construída en piedra y madera se presenta ante tí. \nA duras penas se sostiene sobre sus\n cimientos.\nHay carteles de cortesia advirtiendo a los intrusos. \n¡ATENCION! NO PASAR, PELIGRO, FUERA!, A LA MIERDA, ¿NO TE HAS ENTERADO?.";
	  const string observacion1="Puedes ver una rama de árbol indicando ladrillo en la pared";

	  const string descripcion2="Piedras amontonadas en tres grupos parecían representar algún tipo de monumento en otro tiempo.";
	  const string observacion2="Las piedras están amontonadas en 3 grupos, cada uno con un número determinado. Es una combinación de 3 números.";

	  const string descripcion3="Cerca de la casa hay un pequeños cementerio. En una de las lápidas puedes leer unas extrañas inscripciones grabadas en forma de árbol.";
	  const string observacion3="Mirando atentamente sobre una de las lápida, descubres una inscripción: I-D-I-I-D-D-I-D-I-D-D-D. ¿Podrían ser paso de baile?";

	  const string descripcion4="";
	  const string descripcion5="";
	  //OBJETOS DEL MUNDO
	  


}

#endif
