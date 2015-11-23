#include "operaciones.h"



void Exit::execute(){
//			 cout<<"Exit desde Exit"<<endl;
			 continuar_loop=false;
}


void Ayuda::execute(){
//				 cout<<"Ayuda : execute()"<<endl;
				 cout<<"Comandos disponibles:"<<endl;
				 
				 for(vector<string>::iterator it=v_comandos.begin();
					   it!=v_comandos.end();
						it++)
				 {
						cout<<*it<<" ";
				 }
}

void Ver::execute(){

	  //cout<<"Nombre escenario en ver:"<<(*escena_actual)->get_nombre_escenario()<<endl;

	  string descripcion=(*escena_actual)->get_descripcion();
	  descripcion+="\n";
	  if((*escena_actual)->get_objetos_disponibles()!="")
	       {
			 descripcion+="Puedes ver: ";
	       descripcion+=(*escena_actual)->get_objetos_disponibles();
          }
	  cout<<descripcion;
	  

}

void Examinar::execute(){

     // This shows user a description of objects examinated
		  //recorrer objetos del escenario actual y del inventario
	  if(string(parametro)==string(""))
			cout<<"What examine? (spell it correctly)"<<endl;
	 else if(inventario.get_existe_objeto(parametro))
			cout<<(inventario.get_objeto(parametro))->get_descripcion()<<endl;
	 else if(escenario.get_existe_objeto_escenario(parametro))
			cout<<(escenario.get_objeto(parametro))->get_descripcion()<<endl;		  


}
