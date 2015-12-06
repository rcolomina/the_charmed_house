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
//	  int size=v_
	  for(int i=0;i<13;++i)
			 v_comandos.push_back(comandos[i]);

	  //Continuar con el bucle principal del juego
//	  continuar_loop=true;
//   configurar reloj
//	  tiempo=0; //segundos	  
	  //variables del jugador
//	  contador_mal_comportamiento=0;

	  //CONSTRUIMOS LA PRIMERA ESCENA: TODO:Cargar desde fichero 
	  Escenario *esc1=new Escenario(id1,nombre1,descripcion1,observacion1);
	  Escenario *esc2=new Escenario(id2,nombre2,descripcion2,observacion2);
	  Escenario *esc3=new Escenario(id3,nombre3,descripcion3,observacion3);
	  Escenario *esc4=new Escenario(id4,nombre4,descripcion4,observacion4);

	  // Setear la escena de comienzo del juego
	  escena_actual=esc1;

	  //insertar escenario en mundo
	  mundo[nombre1]=esc1;
	  mundo[nombre2]=esc2;
	  mundo[nombre3]=esc3;
	  mundo[nombre4]=esc4;

	  // Enlaces entre escenas
	  //Id: 1->[2(o),3(e)] ,2->[1(e),4(i)), 3->[1(o)], 4->[2(e)]

	  mundo[escena1]->set_salida(mundo[escena2],oeste);
	  mundo[escena1]->set_salida(mundo[escena3],este);

	  mundo[escena2]->set_salida(esc1,este);
	  mundo[escena2]->set_salida(esc4,oeste);

	  mundo[escena3]->set_salida(esc1,oeste);

	  mundo[escena4]->set_salida(esc2,este);

	  //CONSTRUIR OBJETOS
	  int id_obj=1;
	  string nombre_obj="baston";
	  string descripcion_obj="Es un batón de madera alargado, con una empuñadura en su extremo.";
	  Objeto *o_baston=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_baston->set_visible(true); 
	  o_baston->set_usado(false); 
	  o_baston->set_fijo(false);
	  o_baston->set_alcanzador(true);

	  id_obj=2;
	  nombre_obj="ladrillo";
	  descripcion_obj="Ladrillo desencajado en la pared de la casa. Podrias intentar tirar de el.";
	  Objeto *o_ladrillo=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_ladrillo->set_visible(true);
	  o_ladrillo->set_fijo(true);
	  o_ladrillo->set_atascado(true);
	  
	  id_obj=3;
	  nombre_obj="cerradura";
	  descripcion_obj="Una cerradura dorada y antigua.";
	  Objeto *o_cerradura=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_cerradura->set_visible(false);
	  o_cerradura->set_usado(false);
	  o_cerradura->set_fijo(true);


	  //Relacionar objetos: Ladrillo con llave
	  string descrip_tirar_ladrillo="Tiras con fuerza del ladrillo de la pared, y parece que comienza a ceder. Una vez sacado el ladrillo, tras el, aparece una cerradura escondida.";
	  o_ladrillo->set_tirable(o_cerradura,descrip_tirar_ladrillo);
	  
	  id_obj=4;
	  nombre_obj="palanca";
	  descripcion_obj="Es una palanca retorcida en uno de sus extremos. Permite forzar puertas o ventanas para desbloquearlas. Escencial en la maleta de herramientas de un ladron.";
	  Objeto *o_palanca=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_palanca->set_visible(true);
	  o_palanca->set_usado(false);
	  o_palanca->set_fijo(false);
	  o_palanca->set_alcanzable(false);
	  o_palanca->set_desatascador(true);

	  id_obj=5;
	  nombre_obj="figurita";
	  descripcion_obj="Es una figurita tallada en piedra en forma de angel. En su base posee una forma saliente que podria encajar en alguna oquedad."; 
	  Objeto *o_figurita=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_figurita->set_visible(true);
	  o_figurita->set_usado(false);
	  o_figurita->set_fijo(false);

	  
	  //INSERTAR OBJETOS EN ESCENARIOS
	  mundo[escena1]->set_objeto(o_ladrillo);
	  mundo[escena1]->set_objeto(o_cerradura);
	  mundo[escena2]->set_objeto(o_baston);
	  mundo[escena3]->set_objeto(o_figurita);
	  mundo[escena4]->set_objeto(o_palanca);
	  //CONSTRUIR INVENTARIO
	  //inventario.insertar_objeto(objeto);

	  // CONSTRUIR COMMANDOS E INVOCADOR
	  //Construir los comandos y conectarlos al invocador
	  ICommand *c_exit  = new Exit(continuar_loop);
	  ICommand *c_ayuda = new Ayuda(v_comandos);
	  ICommand *c_ver   = new Ver(&escena_actual); //pasar direccion del puntor a una escena
	  ICommand *c_examinar = new Examinar(&escena_actual,inventario,parametro1); //pasamos direccion al escenario actual y al inventario
	  ICommand *c_inventario = new CommandInventario(inventario);
//	  const Escena& escena_actual=escena_actual;
	  ICommand *c_norte = new Cardinal(&escena_actual,s_norte,primera_entrada);
	  ICommand *c_sur   = new Cardinal(&escena_actual,s_sur,primera_entrada);
	  ICommand *c_oeste = new Cardinal(&escena_actual,s_oeste,primera_entrada);
	  ICommand *c_este  = new Cardinal(&escena_actual,s_este,primera_entrada);
	  ICommand *c_tirar = new Tirar(&escena_actual,inventario,parametro1,parametro2);

	  ICommand *c_coger = new Coger(&escena_actual,inventario,parametro1);

	  ICommand *c_dejar = new Dejar(&escena_actual,inventario,parametro1);
	  ICommand *c_alcanzar = new Alcanzar(&escena_actual,inventario,parametro1);

/*
	  ICommand *c_sur=new Cardinal(&*escena_actual);
	  ICommand *c_este=new Cardinal(&*escena_actual);
	  ICommand *c_oeste=new Cardinal(&*escena_actual);
*/			

	  map<string,ICommand*> mapComandos;
	  mapComandos[s_exit]=c_exit;
	  mapComandos[s_salir]=c_exit;
	  mapComandos[s_ayuda]=c_ayuda;
	  mapComandos[s_ver]=c_ver;
	  mapComandos[s_examinar]=c_examinar;
	  mapComandos[s_inventario]=c_inventario;
	  mapComandos[s_norte]=c_norte;
	  mapComandos[s_sur]=c_sur;
	  mapComandos[s_este]=c_este;
	  mapComandos[s_oeste]=c_oeste;
	  mapComandos[s_tirar]=c_tirar;
	  mapComandos[s_coger]=c_coger;
	  mapComandos[s_dejar]=c_dejar;
	  mapComandos[s_alcanzar]=c_alcanzar;

	  // Construir invocador de comandos con mapComandos
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
//			 cout<<"[Escena: "<<escena_actual->get_nombre()<<"]"
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

	  //Tratamiento del comando mal deletrado
	  //How to know that comando is in a list of strings
     bool info=(comando==s_exit or comando==s_salir or comando==s_ayuda or comando==s_ver or comando==s_inventario or comando==s_examinar);
	  bool norte=(comando=="norte" or comando=="n");
	  bool sur  =(comando=="sur" or comando=="s");
	  bool este =(comando=="este" or comando=="e");
	  bool oeste=(comando=="oeste" or comando=="o");

	  if(info)
          invocador_comandos.exec(comando);
	  if(norte)
			 invocador_comandos.exec(s_norte);
	  if(sur)
			 invocador_comandos.exec(s_sur);
	  if(este)
			 invocador_comandos.exec(s_este);
	  if(oeste)
			 invocador_comandos.exec(s_oeste);

	  bool tirar=comando==s_tirar;
	  if(tirar)
			 invocador_comandos.exec(s_tirar);

	  bool coger=comando==s_coger;
	  if(coger)
			 invocador_comandos.exec(s_coger);

	  bool alcanzar=comando==s_alcanzar;
	  if(alcanzar)
			 invocador_comandos.exec(s_alcanzar);



			 			 
	 if(comando=="arriba");
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
			 Objeto *llave=mundo[escena1]->get_objeto(o_cerradura);
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
	  else if(id_esc==4)
			 fileImagetext="./txt/arcoarboles.txt";

	  fs.open(fileImagetext.c_str(),fstream::in);
	  string line;
	  if(fs.is_open()){
			 while(getline(fs,line)){
					cout<<line<<endl;
			 }
			 fs.close(); 
	  }
}
