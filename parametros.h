#ifndef _PARAMETROS_
#define _PARAMETROS_
    
#include <string>
#include <iostream>

#define NUMBER_COMMANDS 13

using namespace std;
  
namespace parametros{
	  const string c1="exit";
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
	  const string s_salir="salir";
	  const string s_ayuda="ayuda";
	  const string s_examinar="examinar";
	  const string s_ver="ver";
	  const string s_inventario="inventario";
	  const string s_salidas="salidas";
	  const string s_norte="norte";
	  const string s_sur="sur";
	  const string s_este="este";
	  const string s_oeste="oeste";
	  const string s_tiempo="tiempo";
	  const string s_tirar="tirar";
	  const string s_coger="coger";
	  const string s_dejar="dejar";
	  const string s_alcanzar="alcanzar";
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


	  
	  const string comandos[NUMBER_COMMANDS]={s_exit,
										  s_salir,
										  s_examinar,
										  s_ver,
										  s_inventario, 
										  s_salidas,
										  s_norte,
										  s_sur,
										  s_este,
										  s_oeste,
										  s_tiempo,
										  s_tirar,
										  s_alcanzar};


     //DESCRIPCIONES ESCENARIOS: TODO ¿Cómo organizar las descripciones y observaciones de un escenario?

	  const int id_escena1=1;

	  const string tituloPreludio="PRELUDIO:";

 	  const string textoPreludio1="En un pueblo lejos de la ciudad, había una casa ruinosa y antigua desde que tengo ojos para ver. Como aventurero que soy, he tenido en mente explorarla en todo momento, pero nunca me he atrevido. Existen carteles prohibiendo el paso en sus alrededores. Quien quiera que sea el dueño, desea que los intrusos permanezcan lejos.";
	  const string textoPreludio2="Durante noches había estado soñando con aquella casa en ruinas, imaginando que podría haber en su inferior. Una noche, en uno de mis sueños, vislumbré una figura humana irreconocible. Lo único que pude descifrar en aquel enigmático sueño, es la llamada de aquella entidad. Susurraba, -Ayuuudame!!, ayuudame!!-.  \n Desde aquel momento, no pude esperar más. Debía entrar en aquella casa abandonada,  a pesar de que las advertencias en los alrededores.";

	 const string textoComienzo="La aventura comienza…" ; 

	  const int id1=1;
	  const string nombre1="La Entrada a la Casa";
	  const string escena1=nombre1;
	  const string descripcion1="Una casa antigua construída en piedra y madera se presenta ante tí. \nA duras penas se sostiene sobre sus\n cimientos.\nHay carteles de cortesia advirtiendo a los intrusos. \n¡ATENCION! NO PASAR, PELIGRO, FUERA!, A LA MIERDA, ¿NO TE HAS ENTERADO?.";
	  const string observacion1="Puedes ver una rama de árbol indicando ladrillo en la pared";

	  const int id2=2;
	  const string nombre2="El monumento de piedras";
	  const string escena2=nombre2;
	  const string descripcion2="Piedras amontonadas en tres grupos parecían representar algún tipo de monumento en otro tiempo.";
	  const string observacion2="Las piedras están amontonadas en 3 grupos, cada uno con un número determinado. Es una combinación de 3 números.";

	  const int id3=3;
	  const string nombre3="Cementerio";
	  const string escena3=nombre3;
	  const string descripcion3="Cerca de la casa hay un pequeños cementerio. En una de las lápidas puedes leer unas extrañas inscripciones grabadas en forma de árbol.";
	  const string observacion3="Mirando atentamente sobre una de las lápida, descubres una inscripción: I-D-I-I-D-D-I-D-I-D-D-D. ¿Podrían ser paso de baile?";

	  const int id4=4;
	  const string nombre4="Arco de arboles";
	  const string escena4=nombre4;	  
	  const string descripcion4="Un arco de piedra se alza en tu camino. Puedes ver que un objeto metálico en su parte mas alta. No crees que puedas alcanzarlo con las manos desnudas."; 
	  const string observacion4="Puedes ver que el objeto es una palanca para tirar de cualquier cosa";

	  const string descripcion5="";
	  //OBJETOS DEL MUNDO
	  


}

#endif
