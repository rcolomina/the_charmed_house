#include "inventario.h"

Inventario::Inventario(){}


string Inventario::listar(){
	  string lista_inventario="";
	  //Recorrer map
	  for(map<string,Objeto*>::iterator it=objetos_inventario.begin();
			it!=objetos_inventario.end();it++){
			 lista_inventario+=" ";
			 lista_inventario+=it->second->get_nombre();
	  }
	  if(lista_inventario=="")
			 lista_inventario="Tu inventario está vacío.";
	 
	 return lista_inventario;
}


bool Inventario::get_existe_objeto(string nombre){
	  for(map<string,Objeto*>::iterator it=objetos_inventario.begin();
		  it!=objetos_inventario.end();it++)
			 if(it->first==nombre)return true;
	  return false;

}


void Inventario::insertar_objeto(Objeto *objeto){
	  // if(objeto.get_nombre()!="")
	  string nombre=objeto->get_nombre();
  	  if(nombre!="")
	    objetos_inventario[nombre]=objeto;
}


Objeto* Inventario::get_objeto(string nombre){
	  return objetos_inventario[nombre];
}
