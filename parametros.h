#ifndef _PARAMETROS_
#define _PARAMETROS_

#include <string>
#include <iostream>
#include <map>
#include <vector>

#define NUMBER_COMMANDS 14

using namespace std;

namespace parametros{

/*

//TODO: Create list from XML game
const map<string,pair<string,TYPE_VAR> >  listDefaultProperties =
{{string("used"),paFalse},
{string("fix"),paFalse},
{string("visibility"),paTrue},
{string("tirable"),paFalse}};


*/

     enum TYPE_VAR {BOOLEAN,INTEGER,FLOAT,DOUBLE,STRING};
	  
     static const string sFalse = string("false");
     static const string sTrue  = string("true");
	  
     static const pair<string,TYPE_VAR> paFalse = {sFalse,BOOLEAN};
     static const pair<string,TYPE_VAR> paTrue  = {sTrue,BOOLEAN};
	  
     static const map<string,pair<string,TYPE_VAR> >  listDefaultProperties =
     {{string("used"),paFalse},
      {string("fix"),paFalse},
      {string("visibility"),paTrue},
      {string("tirable"),paFalse}};

     static const vector<string> commands = {
	  "exit","examinar","ver","inventario","salidas","norte(n)",
	  "sur(s)","este(e)","oeste(o)","tiempo"};

	  
     static const string c1="exit";
     static const string c2="examinar";
     static const string c3="ver";
     static const string c4="inventario";
     static const string c5="salidas";
     static const string c6="norte(n)";
     static const string c7="sur(s)";
     static const string c8="este(e)";
     static const string c9="oeste(o)";
     static const string c10="tiempo";
     static const string space=" ";
	  
     static const string s_exit="exit";
     static const string s_salir="salir";
     static const string s_ayuda="ayuda";
     static const string s_examinar="examinar";
     static const string s_ver="ver";
     static const string s_inventario="inventario";
     static const string s_salidas="salidas";
     static const string s_norte="norte";
     static const string s_sur="sur";
     static const string s_este="este";
     static const string s_oeste="oeste";
     static const string s_tiempo="tiempo";
     static const string s_tirar="tirar";
     static const string s_coger="coger";
     static const string s_dejar="dejar";
     static const string s_alcanzar="alcanzar";
     static const string s_space=" ";
     static const string s_colocar="colocar";
	  
     static const string oeste="oeste";
     static const string este="este";
     static const string norte="norte";
     static const string sur="sur";

     static const string bajar="bajar";
     static const string subir="subir";
     static const string abrir="abrir";
     static const string cerrar="cerrar";
     static const string golpear="golpear";
     static const string tirar="tirar";
     static const string empujar="empujar";
     static const string pulsar="pulsar";
	  
     static const string comandos[NUMBER_COMMANDS]={s_exit,
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
						    s_alcanzar,
						    s_colocar};


     enum cardinal{north, northwest,west,southwest, south, southeast, east,northeast};
			 

     static const string tituloPreludio="PRELUDIO:";

     static const string nombre1="La Entrada a la Casa";
     static const string nombre2="El monumento de piedras";
     static const string nombre3="Cementerio"; 
	  
     //DESCRIPCIONES ESCENARIOS: TODO ¿Cómo organizar las descripciones y observaciones de un escenario?
     // static const int id_escena1=1;
     // static const string tituloPreludio="PRELUDIO:";

     static const string textoPreludio1="En un pueblo lejos de la ciudad, había una casa ruinosa y antigua desde que tengo ojos para ver. Como aventurero que soy, he tenido en mente explorarla en todo momento, pero nunca me he atrevido. Existen carteles prohibiendo el paso en sus alrededores. Quien quiera que sea el dueño, desea que los intrusos permanezcan lejos.";
     static const string textoPreludio2="Durante noches había estado soñando con aquella casa en ruinas, imaginando que podría haber en su inferior. Una noche, en uno de mis sueños, vislumbré una figura humana irreconocible. Lo único que pude descifrar en aquel enigmático sueño, es la llamada de aquella entidad. Susurraba, -Ayuuudame!!, ayuudame!!-.  \n Desde aquel momento, no pude esperar más. Debía entrar en aquella casa abandonada,  a pesar de que las advertencias en los alrededores.";

     static const string textoComienzo="La aventura comienza…" ; 

	
     static const string postMessageActivationToEventOpenConnection1 = string("Unas rocas se levantan de las profundidades del lago, formando un pasadizo que te permite acceder al centro de la isla. Una nueva salida se abre hacia el oeste.");

}




#endif
