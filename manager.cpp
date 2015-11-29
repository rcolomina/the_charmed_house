#include "manager.h"

using namespace parametros;

const double freq=1.0/60.0; 

Manager::Manager():dt(freq),
						 tiempo(0),
						 continuar_loop(true),
						 contador_mal_comportamiento(0)
{
	  //Crear vector de comandos
	  comandos_disponibles="Comandos disponibles:";
	  for(int i=0;i<10;++i)
			 v_comandos.push_back(comandos[i]);

	  //Continuar con el bucle principal del juego
//	  continuar_loop=true;

	  //configurar reloj
//	  tiempo=0; //segundos	  
	  //variables del jugador
//	  contador_mal_comportamiento=0;
	  int id_escena;

	  //CONSTRUIMOS LA PRIMERA ESCENA: TODO:Cargar desde fichero 
	  string nombre="La entrada principal de la mansion";
	  //string escena=nombre;
     //creamos la escena 
	  Escenario *escena=new Escenario(id_escena1,nombre1,descripcion1,observacion1);

	  //insertar escenario en mundo
	  mundo[nombre1]=escena;

	  //selecionamos la escena de arranque del juego. TODO: Cargar desde fichero de salvaguarda
	  escena_actual=escena;

	  //SEGUNDA ESCENA
	  id_escena=2;
	  nombre="El monumento de piedras";
     string escena2=nombre;

	  escena=new Escenario(2,nombre,descripcion2,observacion2);

	  //insertar escenario en mundo
	  mundo[nombre]=escena;

	  //TERCENRA ESCENA: Lapida
	  id_escena=3;
	  nombre="EL cementerio";
     string escena3=nombre;

	  escena=new Escenario(3,nombre,descripcion3,observacion3);
	  
	  //insertar escenario en mundo
	  mundo[nombre]=escena;

	  //ENLAZAR ESCENARIOS ENTRE SI
	  //Id: 1->(2,3) ,2<->1, 3<->1
	  mundo[escena1]->set_salida(mundo[escena2],oeste);
	  mundo[escena1]->set_salida(mundo[escena3],este);
	  mundo[escena2]->set_salida(mundo[escena1],este);
	  mundo[escena3]->set_salida(mundo[escena1],oeste);

	  //CONSTRUIR OBJETOS
	  int id_obj=1;
	  string nombre_obj="bastón alargado";
	  string descripcion_obj="Es un batón de madera bastante largo, con una empuñadura en su extremo.";
	  Objeto *o_baston=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_baston->set_visible(true); o_baston->set_usado(false); o_baston->set_fijo(false);

	  id_obj=2;
	  nombre_obj="ladrillo";
	  descripcion_obj="Ladrillo saliente en la pared de la casa. Es posible que se puede tirar de él.";
	  Objeto *o_ladrillo=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_ladrillo->set_visible(false);
	  o_ladrillo->set_fijo(true);

	  id_obj=3;
	  nombre_obj="llave dorada";
	  descripcion_obj="Una llave dorada y antigua.";
	  Objeto *o_llave=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_llave->set_visible(false);
	  o_llave->set_fijo(false);


	  //INSERTAR OBJETOS EN ESCENARIOS
	  
	  mundo[escena2]->set_objeto(o_baston);

	  //entrada de la mandion
	  mundo[escena1]->set_objeto(o_ladrillo);
	  mundo[escena1]->set_objeto(o_llave);

	  //CONSTRUIR INVENTARIO
	  //inventario.insertar_objeto(objeto);

	  //Construir los comandos y conectarlos al invocador
	  ICommand *c_exit=new Exit(continuar_loop);
	  ICommand *c_ayuda=new Ayuda(v_comandos);
	  ICommand *c_ver=new Ver(&escena_actual); //pasar direccion del puntor a una escena
	  ICommand *c_examinar=new Examinar(*escena_actual,inventario,parametro1); //pasamos direccion al escenario actual y al inventario

	  ICommand *c_inventario=new CommandInventario(inventario);

	  mapComandos[s_exit]=c_exit;
	  mapComandos[s_ayuda]=c_ayuda;
	  mapComandos[s_ver]=c_ver;
	  mapComandos[s_examinar]=c_examinar;
	  mapComandos[s_inventario]=c_inventario;
	  
	  //construir invocador de comandos
	  invocador_comandos=Invocador(mapComandos);
	  
}

void Manager::prologo(){

	  cout<<endl<<"¡BIENVENIDO QUERIDO JUGADOR! \n\nLA CASA ENVANTADA v1.0"<<endl<<endl;
	  cout<<tituloPreludio<<endl;

	  string my_string=textoPreludio1;
	  string::iterator my_iter;
	  for(my_iter = my_string.begin(); my_iter != my_string.end(); my_iter++)
	  {
			 usleep(50000);
			 cout<<*my_iter<<flush;
	  }

	  cout<<endl;
//	  cout<<textoPreludio1<<endl;
	  sleep(2);

	  my_string=textoPreludio2;
	  for(my_iter = my_string.begin(); my_iter != my_string.end(); my_iter++)
	  {
			 usleep(50000);
			 cout<<*my_iter<<flush;
	  }
	  

	  sleep(3);
	  cout<<endl;
	  cout<<textoComienzo<<endl;
	  cout<<endl;
	  sleep(4);

}

void Manager::run(){

	  //Marcar la primera entrada al metodo
	  primera_entrada=true;

//	  prologo();


	  while(continuar_loop){

			 ///DIBUJAR ESCENARIO///
			 if(primera_entrada)
			     {
						 cout<<endl;dibujar();cout<<endl;
						 cout<<get_descripcion_estado_actual()<<endl;
						 primera_entrada=false;
				  }

			 ///RECOGIDA DE COMMANDOS CONSOLA///
//			 cout<<"[Escena: "<<escena_actual->get_nombre_escenario()<<"]"
//				  <<"[Objetos: "<<escena_actual->get_objetos_disponibles()<<"]"
//				  <<"[Salidas: "<<escena_actual->
//				  <<endl<<">>>";
			 cout<<">>>";

			 //EXTRACCION DEL COMANDOS Y LOS PARAMETROS
			 string entrada_consola;
			 getline(cin,entrada_consola);
			 //cout<<"Se ha introducido: "<<comando;
			 list<string> lista_comandos;
			 istringstream iss(entrada_consola);
			 do{string sub;
						  iss >> sub;
						  //					  cout<< "Substring: " << sub << endl;
						  lista_comandos.push_back(sub);
			 }while(iss);

			 if(!lista_comandos.empty()){
					comando=lista_comandos.front();
					lista_comandos.pop_front();}

			 if(!lista_comandos.empty()){
		   	  parametro1=lista_comandos.front();
			     lista_comandos.pop_front();
			     }

			 if(!lista_comandos.empty()){
			     parametro2=lista_comandos.front();
			     lista_comandos.pop_front();
			     }


			 ///TRATAMIENTO DE COMANDOS
			 tratamiento_comandos(comando);

			 //Actualizar Objetos
			 actualizar_objetos();

			 //Actualizar Salidas
			 actualizar_salidas();
	  }

	  //TODO: GUARDAR LA PARTIDA CON TODOS SUS ESTADOS

	  //SALIDA DEL JUEGO
	  if(contador_mal_comportamiento<3)
			 cout<<endl<<"GRACIAS POR JUGAR! :),TE ESPERO PRONTO DE VUELTA."<<endl<<endl;
	  else
	 		 cout<<endl<<"ERES UN MALEDUCADO, NECESITAS CLASES DE MODALES."<<endl<<endl;


}

string Manager::get_comandos_disponibles()
{
	  return comandos_disponibles;
}

string Manager::get_descripcion_estado_actual(){
	  string descripcion=escena_actual->get_descripcion();
	  descripcion+="\n";
	  if(escena_actual->get_objetos_disponibles()!="")
	       {
			 descripcion+="Puedes ver : \n";
	       descripcion+=escena_actual->get_objetos_disponibles();
          }
		return descripcion;

}

string Manager::get_salidas_estado_actual(){
	  
	  string lista_salidas;
	  map<string,Escenario*> salidas=escena_actual->get_salidas();

	  for(map<string,Escenario*>::iterator it=salidas.begin();
		  it!=salidas.end();it++)
	  {
			 lista_salidas+=it->first;
			 lista_salidas+=" ";
	  }

	  return lista_salidas;

}





//Tratamiento de la línea de comandos 
void Manager::tratamiento_comandos(string comando){

     if(comando==s_exit or comando==s_ayuda or comando==s_ver or comando==s_inventario)
          invocador_comandos.exec(comando);

	  if(comando==s_examinar)
			 invocador_comandos.examinar_comando(parametro1);

//	  if(comando=="inventario" or comando=="i")
//			 cout<<endl<<"Posees lo siguiente: "<<endl<<inventario.listar()<<endl;

//			  if(comando==s_ver))
//			  invocador_comandos.ver_descripcion();

//			 if(comando=="exit")
//					continuar_loop=false;

//			 else if(comando=="ayuda")
//					cout<<endl<<get_comandos_disponibles();

//					cout<<endl<<get_descripcion_estado_actual();
/*
			 else if(comando=="examinar"){
					if(parametro1=="")
						  cout<<escena_actual->get_observacion()<<endl;
					else 
					   {
						//OBJETO DEL MUNDO

						//Si está en el inventario, lo describes
						  if(inventario.get_existe_objeto(parametro1))
								cout<<inventario.get_objeto(parametro1)->get_descripcion(); 			  		   	   
						//Si está en el escenario actual, lo describes
  					     else if(escena_actual->get_existe_objeto_escenario(parametro1))
							  cout<<escena_actual->get_objeto(parametro1)->get_descripcion();
 					   
						  else
							  cout<<"No se puede examinar eso.";
						}
						  
			      }*/


	  if(comando=="norte" or comando=="n")
               {
					  if(escena_actual->get_salida("norte"))
					     {
						  escena_actual=(escena_actual->get_salida("norte"));
						  primera_entrada=true;
				    	  } 
					  else
						  cout<<"No puedes ir al norte.";					
               }

	        else if(comando=="sur" or comando=="s")
               {
					if(escena_actual->get_salida("sur"))
					     {
						  escena_actual=(escena_actual->get_salida("sur"));
						  primera_entrada=true;
				    	  } 
					else
						  cout<<"No puedes ir al sur.";
					
              }

			 else if(comando=="oeste" or comando=="o"){
					if(escena_actual->get_salida("oeste"))
					     {
						  escena_actual=(escena_actual->get_salida("oeste"));
						  primera_entrada=true;
				    	  } 
					else
						  cout<<"No puedes ir al oeste.";
					}

			 else if(comando=="este" or comando=="e"){
					if(escena_actual->get_salida("este"))
					     {
								 escena_actual=(escena_actual->get_salida("este"));
						  primera_entrada=true;
				    	  } 
					else
						  cout<<"No puedes ir al este.";
					}
			 
			 else if(comando=="arriba");
			 else if(comando=="abajo")	;			
			 else if(comando=="entrar");
			 else if(comando=="salir");					
			 else	if(comando=="salidas")
					cout<<endl<<"Las salidas disponibles son:"<<get_salidas_estado_actual()<<endl;
			 else if(comando=="tiempo")
					cout<<endl<<"Han pasado "<<tiempo<<" segundos desde que comenzó la partida."<<endl;
			 else if(comando=="");
			 else 
			      {
					//
					  bool hijo=(comando=="hijo" or comando=="Hijo");
					  bool puta=(parametro1=="puta" or parametro1=="Puta") or (parametro2=="puta" or parametro2=="Puta");
					  bool idiota=(comando=="Idiota" or comando=="idiota") or 
                             (parametro1=="Idiota" or parametro1=="idiota") or 
                             (parametro2=="Idiota" or parametro2=="idiota");

					  bool maricon=(comando=="maricón" or comando=="Maricón") or (comando=="maricon" or comando=="Maricon") or
							         (parametro1=="maricón" or parametro1=="Maricón") or (parametro1=="maricon" or parametro1=="Maricon") or
							 (parametro2=="maricón" or parametro2=="Maricón") or (parametro2=="maricon" or parametro2=="Maricon");

					  bool cabron=(comando=="cabron" or comando=="Cabron") or (comando=="Cabrón" or comando=="cabrón") or
					              (parametro1=="cabron" or parametro1=="Cabron") or (parametro1=="Cabrón" or parametro1=="cabrón") or
									  (parametro2=="cabron" or parametro2=="Cabron") or (parametro2=="Cabrón" or parametro2=="cabrón");		 


					  if(hijo and puta){
							 cout<<"Hijo puta lo serás tu, se un poco más serio, o morirás.";
							 contador_mal_comportamiento++;
					       }
					  else if(idiota){
							 cout<<"La idiotez de persigue, vas a morir.";
							 contador_mal_comportamiento++;
					       }
					  else if(maricon){
							 cout<<"¿Te gusta la sodomía?.";
							 contador_mal_comportamiento++;
					       }
					  else if(cabron){
							 cout<<"¿Consientes que tu mujer se acueste con otro?";
							 contador_mal_comportamiento++;
					       }
					  else 
					       {
									;}		
					  //cout<<endl<<"Comando inválido, escribe (ayuda)";}
					}


			 if(contador_mal_comportamiento>3){
					cout<<endl<<endl<<"Eres una desgracia humana mentalmente o no tienes la sufiente madurez, así que vuelve tan sólo cuando hayas soluciodado ese asunto. ADIOS!.";				
					continuar_loop=false;
			 }


			 if(comando!="")
					cout<<endl;
			 
}



void Manager::clock(){

	  while(continuar_loop){

			 int itime=(int)tiempo;
			 if(itime%(5*60)==0)
			 {
					cout<<"\nHan pasado "<<tiempo<<" segundos desde el inicio del juego\n"<<">>>";
	       }

 			 sleep(1); //detiene el hilo durante 1 segundo
			 tiempo++;
	  }
}



//Actualizar atributos de objetos
//Definir las reglas y relaciones entre objetos
void Manager::actualizar_objetos(){

//Genericos: Si un objeto esta usado, hacerlo invisible, para que no se liste en su escenario
//SEGURO??

// Escenario 1: La entrada de la mansion
	  if(escena_actual->get_id()==id_escena1){
			 //Chequear el ladrillo de la puerta
/*			 Objeto *ladrillo=mundo[escena1]->get_objeto(o_ladrillo);
			 Objeto *llave=mundo[escena1]->get_objeto(o_llave);
			 if(llave!=NULL and ladrillo!=NULL)
					if(not llave->get_visible() and ladrillo->get_usado()){
						  cout<<"Una llave dorada aparece ante tu vista."<<endl;
						  llave->set_visible(true);
					}*/

			 //
	  }

	  //if(



}

//Actualizar salidas del escenario
void Manager::actualizar_salidas(){

	  //Establecer reglas de activacion de salidas

}



void Manager::dibujar(){

	  int id_esc=escena_actual->get_id();

	  fstream fs;
	  string fileImagetext;

	  if(id_esc==1)
			 fileImagetext="./txt/fronthouse.txt";
	  else if(id_esc==3)
			 fileImagetext="./txt/cementery.txt";
	  else if(id_esc==2)
			 fileImagetext="./txt/stones.txt";

	  fs.open(fileImagetext.c_str(),fstream::in);
	  string line;
	  if(fs.is_open()){
			 while(getline(fs,line)){
					cout<<line<<endl;
			 }
			 fs.close(); 
	  }
}
