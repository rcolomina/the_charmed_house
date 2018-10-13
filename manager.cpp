#include "manager.h"
#include "logger.h"

using namespace parametros;

const double freq=1.0/60.0; 
Manager::Manager():dt(freq),
                   tiempo(0),
                   continuar_loop(true),
                   contador_mal_comportamiento(0),
		   fac("gamesInfo.xml")
{	  
	 
     string gameId="";

     // Build game scene using id
     escena_actual = fac.buildGameById(gameId);
     
     // Build Map of commands
     CommandBuilder *commandBuilder = new CommandBuilder();
     mapComandos = commandBuilder.buildCommands(continuar_loop,
						escena_actual,
						inventario,
						parametro1,
						parametro2,
						primera_entrada,
						eventsQueue);
     
     // Build command trigger
     invocador_comandos=Invocador(mapComandos);
	 
}

void Manager::prologo(){

     // TODO: Get data from sceneario object	  
     cout<<endl<<"¡BIENVENIDO QUERIDO JUGADOR! \n\nLA CASA ENCANTADA v1.0"<<endl<<endl;
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

//	 prologo();

     while(continuar_loop){

	  ///DIBUJAR ESCENARIO///
	  if(primera_entrada)
	  {
	       cout<<endl;
	       dibujar();
	       cout<<endl;
	       cout<<get_descripcion_estado_actual()<<endl;
	       primera_entrada=false;
	  }

	  ///RECOGIDA DE COMMANDOS CONSOLA///
//	     cout<<"[Escena: "<<escena_actual->get_nombre()<<"]"
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
	       lista_comandos.pop_front();
	  }

	  if(!lista_comandos.empty()){
	       parametro1=lista_comandos.front();
	       lista_comandos.pop_front();
	  }

	  if(!lista_comandos.empty()){
	       parametro2=lista_comandos.front();
	       lista_comandos.pop_front();
	  }

	  //list<string> params;
	  //params.push_back(parametro1);
	  //params.push_back(parametro2);

	  ///TRATAMIENTO DE COMANDOS	  
	  int ret_val = invocador_comandos.exec(comando,parametro1,parametro2);
	  if(ret_val == 1)
	  {
	       contador_mal_comportamiento++;
	  }

	  
	  //Actualizar Objetos
	  actualizar_objetos();

	  //Actualizar Salidas
	  actualizar_salidas();
     }

     //TODO: GUARDAR LA PARTIDA CON TODOS SUS ESTADOS

     //SALIDA DEL JUEGO
     if(contador_mal_comportamiento < 3 )
	  cout<<endl<<"GRACIAS POR JUGAR! :),TE ESPERO PRONTO DE VUELTA."<<endl<<endl;
     else
     {
	  
	  cout<<endl<<
	       endl<<
	       "Eres una desgracia humana mentalmente o no tienes"<<
	       " la sufiente madurez, así que vuelve tan sólo cuando hayas soluciodado ese asunto. ADIOS!.";				
	  cout<<endl<<"ERES UN MALEDUCADO, NECESITAS CLASES DE MODALES."<<endl<<endl;
     }
}

string Manager::get_comandos_disponibles()
{
     return comandos_disponibles;
}

string Manager::get_descripcion_estado_actual(){
     string descripcion=escena_actual->examine();
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

     //map<string,Escenario*> salidas=escena_actual->get_salidas();

     map<string,pScene> salidas=escena_actual->get_salidas();

     for(map<string,pScene>::iterator it=salidas.begin();
	 it!=salidas.end();it++)
     {
	  lista_salidas+=it->first;
	  lista_salidas+=" ";
     }
     return lista_salidas;
}


void Manager::clock(){

     while(continuar_loop)
     {
	  int itime = (int) tiempo;
	  if( itime % (5*60) == 0 )
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

     // Compsume events
     eventsQueue.fire();

/*	  IEvent *event;
	  if(!eventsQueue.empty())
	  {
	  cout<<"Size eventsQueue:"<<eventsQueue.size()<<endl;
	  event=eventsQueue.front();
  	
	  cout<<"Size eventsQueue:"<<eventsQueue.size()<<endl;
	  assert(event!=NULL);
	  Logger::instance().log("actualizar_objetos", Logger::kLogLevelInfo);
	  //cout<<event->message()<<endl;
	  cout<<event->activate()<<endl;
	  eventsQueue.pop();
	  }*/
	  
}
	  
	  
//Genericos: Si un objeto esta usado, hacerlo invisible, para que no se liste en su escenario
//SEGURO??

// Escenario 1: La entrada de la mansion
//    if(escena_actual->Id()==id_escena1)
//	 {
//Chequear el ladrillo de la puerta
/*			 Objeto *ladrillo=mundo[escena1]->get_objeto(o_ladrillo);
			 Objeto *llave=mundo[escena1]->get_objeto(o_cerradura);
			 if(llave!=NULL and ladrillo!=NULL)
                         if(not llave->get_visible() and ladrillo->get_usado()){
                         cout<<"Una llave dorada aparece ante tu vista."<<endl;
                         llave->set_visible(true);
                         }*/
//
			
//    }
//}

//Actualizar salidas del escenario
void Manager::actualizar_salidas(){
     //Establecer reglas de activacion de salidas
}

void Manager::dibujar(){
     escena_actual->pintar();
}
