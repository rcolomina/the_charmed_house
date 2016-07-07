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
	  
	  const string sFalse = string("false");
	  const string sTrue  = string("true");
	  
	  const pair<string,TYPE_VAR> paFalse = {sFalse,BOOLEAN};
	  const pair<string,TYPE_VAR> paTrue  = {sTrue,BOOLEAN};
	  
	  const map<string,pair<string,TYPE_VAR> >  listDefaultProperties =
	  {{string("used"),paFalse},
		{string("fix"),paFalse},
		{string("visibility"),paTrue},
		{string("tirable"),paFalse}};

	  const vector<string> commands = {
			 "exit","examinar","ver","inventario","salidas","norte(n)",
			 "sur(s)","este(e)","oeste(o)","tiempo"};

	  
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
	  const string s_colocar="colocar";
	  
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
															s_alcanzar,
															s_colocar};


	  enum cardinal{
			 north, northwest,west,southwest, south, southeast, east,northeast};
			 

	  const string tituloPreludio="PRELUDIO:";

	  const string nombre1="La Entrada a la Casa";
	  const string nombre2="El monumento de piedras";
	  const string nombre3="Cementerio"; 
	  
     //DESCRIPCIONES ESCENARIOS: TODO ¿Cómo organizar las descripciones y observaciones de un escenario?

	  // const int id_escena1=1;

	  // const string tituloPreludio="PRELUDIO:";

 	  const string textoPreludio1="En un pueblo lejos de la ciudad, había una casa ruinosa y antigua desde que tengo ojos para ver. Como aventurero que soy, he tenido en mente explorarla en todo momento, pero nunca me he atrevido. Existen carteles prohibiendo el paso en sus alrededores. Quien quiera que sea el dueño, desea que los intrusos permanezcan lejos.";
	  const string textoPreludio2="Durante noches había estado soñando con aquella casa en ruinas, imaginando que podría haber en su inferior. Una noche, en uno de mis sueños, vislumbré una figura humana irreconocible. Lo único que pude descifrar en aquel enigmático sueño, es la llamada de aquella entidad. Susurraba, -Ayuuudame!!, ayuudame!!-.  \n Desde aquel momento, no pude esperar más. Debía entrar en aquella casa abandonada,  a pesar de que las advertencias en los alrededores.";

	  const string textoComienzo="La aventura comienza…" ; 

	
	  const string postMessageActivationToEventOpenConnection1 = string("Unas rocas se levantan de las profundidades del lago, formando un pasadizo que te permite acceder al centro de la isla. Una nueva salida se abre hacia el oeste.");

}

#endif
