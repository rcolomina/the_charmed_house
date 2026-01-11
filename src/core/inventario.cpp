#include "inventario.h"

Inventario::Inventario(){}

string Inventario::listar(){
    string lista_inventario=string("");
    //Recorrer map
    for(map<string,Objeto*>::iterator it=objetos_inventario.begin();
        it!=objetos_inventario.end();it++){
        lista_inventario+=" ";			
        lista_inventario+=it->second->Name();
    }
    if(lista_inventario=="")
        lista_inventario="Tu inventario está vacío.";
	 
    return lista_inventario;
}


bool Inventario::get_existe_objeto(string nombre){
    for(map<string,Objeto*>::iterator it=objetos_inventario.begin();
        it!=objetos_inventario.end();it++){
        if(it->first==nombre)
            return true;
    }
    return false;
}


Objeto* Inventario::get_objeto(string nombre){
    return objetos_inventario[nombre];
}


bool Inventario::posee_alcanzador(){
    map<string,Objeto*>::iterator it;
    for(it=objetos_inventario.begin();it!=objetos_inventario.end();it++)
    {
        if(it->second->get_value<bool>("reacher"))
            return true;
    }
    return false;
}


Objeto* Inventario::tomar_alcanzador(){
    map<string,Objeto*>::iterator it;
    for(it=objetos_inventario.begin();it!=objetos_inventario.end();it++)
    {
        if(it->second->get_value<bool>("reacher"))
            return it->second;
    }
    return 0;
}



bool Inventario::posee_desatascador(){
    map<string,Objeto*>::iterator it;
    for(it=objetos_inventario.begin();it!=objetos_inventario.end();it++)
    {
        if(it->second->get_value<bool>("desatascador"))
            return true;
    }
    return false;
}

Objeto* Inventario::tomar_desatascador(){
    map<string,Objeto*>::iterator it;
    for(it=objetos_inventario.begin();it!=objetos_inventario.end();it++)
    {
        if(it->second->get_value<bool>("desatascador"))
            return it->second;
    }
    return nullptr;
}



void Inventario::insertar_objeto(Objeto *objeto){	  
    string nombre=objeto->Name();
    if(nombre!="")
        objetos_inventario[nombre]=objeto;
}

void Inventario::eliminar(string nombre){
    objetos_inventario.erase(nombre);
}
