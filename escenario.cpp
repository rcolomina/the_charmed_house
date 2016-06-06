#include "escenario.h"

Escenario::Escenario(int id,string nombre,string descripcion,string observacion):
	  Entidad(id,nombre,descripcion),
	  observacion(observacion){
}


Escenario::Escenario(const Entidad &ent,const string &observacion,const string &path):
	  Entidad(ent),
	  observacion(observacion),
	  pathFileImageText(path)
{

}


bool Escenario::get_existe_objeto_escenario(string nombre){
	  
	  for(map<string,Objeto*>::iterator it=objetos.begin();
			it!=objetos.end();
			it++){			 
	 		 if(it->first==nombre and it->second->get_visible())
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
			 if(it->second->get_visible())
					lista_objetos+=it->first;
	  }
	  if(lista_objetos=="")
			 return string("");
	  else
			 return lista_objetos;
}

void Escenario::eliminar(Objeto *obj){

	  string keyObj=obj->Name();
  	  if(keyObj!="")
			 objetos.erase(keyObj);
}

void Escenario::set_objeto(Objeto *obj)
{
	  string nombre=obj->Name();
	  objetos[nombre]=obj;
}


void Escenario::pintar(){

	  fstream fs;
	  string fileImagetext=pathFileImageText;
	  fs.open(fileImagetext.c_str(),fstream::in);
	  string line;
	  if(fs.is_open()){
			 while(getline(fs,line)){
					cout<<line<<endl;
			 }
			 fs.close(); 
	  }

}
