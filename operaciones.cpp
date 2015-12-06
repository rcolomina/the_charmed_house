#include "operaciones.h"

void Exit::execute(){
			 continuar_loop=false;
}

// Muestra los comandos disponibles
void Ayuda::execute(){

	  cout<<"Comandos disponibles:"<<endl;
				 
	  for(vector<string>::iterator it=v_comandos.begin();
			it!=v_comandos.end();
			it++)
	  {
			 cout<<*it<<" ";
	  }
}

void Ver::execute(){

	  string descripcion=(*escena_actual)->get_descripcion();
	  descripcion+="\n";
	  if((*escena_actual)->get_objetos_disponibles()!="")
	       {
			 descripcion+="Puedes ver los siguiente: ";
	       descripcion+=(*escena_actual)->get_objetos_disponibles();
          }
	  cout<<descripcion;	 
}

void Examinar::execute(){

     // This shows user a description of objects examinated
	  // recorrer objetos del escenario actual y del inventario
	  if(string(parametro)==string(""))
			cout<<"Examinar que?"<<endl;
	 else if(inventario.get_existe_objeto(parametro))
			cout<<(inventario.get_objeto(parametro))->get_descripcion()<<endl;
	 else if((*escenario)->get_existe_objeto_escenario(parametro))
			cout<<((*escenario)->get_objeto(parametro))->get_descripcion()<<endl;		  
	 else 
			cout<<"No hay nada llamado '"<<parametro<<"'"<<endl;

}


void CommandInventario::execute(){
	  cout<<endl<<"En tu inventario posees lo siguiente: "<<endl<<inventario.listar()<<endl;
}


void Cardinal::execute(){

	  if((*escena_actual)->get_salida(cardinal))
	  {
			 *escena_actual = (*escena_actual)->get_salida(cardinal);
			 primera_entrada=true;
			 // cout<<"cambiando de escena"<<endl;
	  } 
	  else
			 cout<<"No puedes ir al "<<cardinal;					


}

// Si es "tirable", se puede tirar del mismo.
void Tirar::execute(){

	  // Existe el objeto especificado en parametro 1
	 if((*escenario)->get_existe_objeto_escenario(parametro))
		  {
				Objeto *objeto=(*escenario)->get_objeto(parametro);
				//Si se puede tirar del objeto pasado por parametro
				if(objeto->get_tirable())
					 {
						  if(objeto->get_atascado())
								{
									 bool desatascador=inventario.posee_desatascador();
									 
									 if(desatascador)
										  {
												Objeto *objDesatascador=inventario.tomar_desatascador();											  
												string desatascador;
												if(objDesatascador!=0){
													  desatascador=objDesatascador->get_nombre();
													  inventario.eliminar(desatascador);
												}
												//Determinar genero del objeto desatascador para poner "del" o "de la"
												cout<<"Has conseguido tirar del "<<parametro<<" con ayuda de "<<objDesatascador->get_nombre()<<endl;

												objeto->tirar();
												(*escenario)->eliminar(objeto);					
										  }
									 else
										  {
												cout<<"Esta atascado"<<endl;
										  }
								}						
						  else
								{
									 objeto->tirar();
									 (*escenario)->eliminar(objeto);					
								}
					 }
				else
					 cout<<"No puedes tirar de "<<parametro<<endl;
		  }
	 else
		  {
				if(parametro!="")
					 cout<<"No puedo tirar de '"<<parametro<<"'."<<endl;
				else
					 cout<<"Tirar de que?."<<endl;
		  }
}


void Coger::execute(){

//	  cout<<(*escenario)->get_nombre()<<endl;
//	  cout<<"Parametro "<<parametro<<endl;
	  // Existe el objeto especificado en parametro 1
	  if((*escenario)->get_existe_objeto_escenario(parametro))
	  {			 
			 Objeto *objeto=(*escenario)->get_objeto(parametro);
			 //Si se puede tirar del objeto pasado por parametro
			 if(!objeto->get_fijo())
			 {
					if(objeto->get_alcanzable()){
						  inventario.insertar_objeto(objeto);
						  (*escenario)->eliminar(objeto);
						  cout<<"Has cogido "<<parametro<<endl;
					}
					else
						  cout<<"No se puedes coger porque no es alcanzable "<<endl;
			 }
			 else
					cout<<"No puedes cogerlo porque esta fijado."<<parametro<<endl;			 
	  }
	  else
	  {
			 if(parametro!="")
					cout<<""<<parametro<<" no se puede coger."<<endl;
			 else
					cout<<"Coger que?"<<endl;
	  }
}

void Alcanzar::execute(){
	  // Si tienes algo para alcanza	
  if((*escenario)->get_existe_objeto_escenario(parametro))
  {
		 if(inventario.posee_alcanzador())
		 {
			 Objeto *objAlcanzador=inventario.tomar_alcanzador();

			 string alcanzador;
			 if(objAlcanzador!=0)
			 {
					alcanzador=objAlcanzador->get_nombre();
					inventario.eliminar(alcanzador);
			 }

			 //Determinar genero del objeto alcanzador para poner "del" o "de la"
			 cout<<"Has cogido "<<parametro<<" con ayuda del "<<alcanzador<<endl;			 

			 Objeto *objeto=(*escenario)->get_objeto(parametro);
			 inventario.insertar_objeto(objeto);
			 (*escenario)->eliminar(objeto);

		 }
		 else
				cout<<"No tienes nada con que alcanzar eso."<<endl;
  }
  else
  {
		 if(parametro!="")
				cout<<""<<parametro<<" no se puede alcanzar."<<endl;
		 else
				cout<<"Alcanzar que?"<<endl;
  }

	  // y quieres coger algo no alcanzable
	  // puedes cogerlo

}




void Dejar::execute(){
/*
	  // Existe el objeto especificado en parametro 1
	  if((*escenario)->get_existe_objeto_escenario(parametro))
	  {			 
			 Objeto *objeto=(*escenario)->get_objeto(parametro);
			 //Si se puede tirar del objeto pasado por parametro
			 if(!objeto->get_fijo())
					inventario.insertar_objeto(objeto);
			 else
					cout<<"No puedes coger de "<<parametro<<endl;

	  }
	  else
	  {
			 if(parametro!="")
					cout<<"No puedes coger '"<<parametro<<"'."<<endl;
			 else
					cout<<"Coger que?."<<endl;
	  }
*/

}
