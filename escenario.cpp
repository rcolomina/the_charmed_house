#include "escenario.h"
#include "objeto.h"

Escenario::Escenario(int identificador,string nombre,string descripcion,string observacion):
	  id(identificador),
	  nombre_escenario(nombre),
	  descripcion(descripcion),
	  observacion(observacion){}


bool Escenario::get_existe_objeto_escenario(string nombre){
	  
	  for(map<string,Objeto*>::iterator it=objetos.begin();
			it!=objetos.end();
			it++){
	 		 if(it->first==nombre)
						return true;
	  }
	  return false;
}

string Escenario::get_objetos_disponibles(){

	  string lista_objetos="";
	  //Recorrer map
	  for(map<string,Objeto*>::iterator it=objetos.begin();
			it!=objetos.end();it++){
			 lista_objetos+=" ";
			 lista_objetos+=it->first;
	  }
	  if(lista_objetos=="")
			 return string("");
	  else
			 return lista_objetos;
}
