#include "escenario.h"

// Friend functions
void connect(pScene scenA,cardinal carA,pScene scenB,cardinal carB){

	  if(scenA->conexions[carA]==scenB)
			 throw "scenA already connected with scenB by carA";

	  if(scenB->conexions[carB]==scenA)
			 throw "scenB already connected with scenA by carB";
					
	  scenA->conexions[carA]=scenB;	  
	  scenB->conexions[carB]=scenA;	  	  
}


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

pScene Escenario::conexion(cardinal car){
			 if(conexions[car]!=NULL)
					return conexions[car];
			 return NULL;
	  }


bool Escenario::get_existe_objeto_escenario(string nombre){

	  
//	  for(map<string,Objeto*>::iterator it=objetos.begin();
			for(auto it=objetos.begin();
			it!=objetos.end();
			it++)
	  {
			 bool matchName = (it->first==nombre);
			 bool isVisible =it->second->get_value<bool>("visibility");
			 
			 if(matchName and isVisible)
					return true;
			 
//	 		 if(it->first==nombre and it->second->get_value<bool>("visibility"))
//					return true;
	  }
	  return false;
}

string Escenario::get_objetos_disponibles(){

	  string lista_objetos="";
	  //Recorrer map
	  for(map<string,Objeto*>::iterator it=objetos.begin();
			it!=objetos.end();it++){
			 lista_objetos+=" ";
			 if(it->second->get_value<bool>("visibility"))
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

// TODO: This operation should be outsourced to other class 
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



void Escenario::set_salida(pScene escenario,string coordenada,bool estado){
	  escenarioSalidas[coordenada]=escenario;
	  estadoSalidas[coordenada]=estado;
}

void Escenario::set_estado_salida(string coordenada,bool new_estado){
	  estadoSalidas[coordenada]=new_estado;
}

bool Escenario::get_estado_salida(string coordenada){
	  return estadoSalidas[coordenada];
}

string Escenario::salidasDisponibles(){
	  
	 string lista_salidas="";
	 map<string,pScene> salidas=this->get_salidas();

    for(map<string,pScene>::iterator it=salidas.begin();
        it!=salidas.end();it++)
    {
			string coordenada=it->first;
			if(estadoSalidas[coordenada]==true)
			{
				  lista_salidas+=it->first;
				  lista_salidas+=" ";				  
			}		  
    }
    return lista_salidas;
}








