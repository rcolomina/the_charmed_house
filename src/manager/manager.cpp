#include "manager.h"
#include "lib/logger/logger.h"
#include "../data/JSONGameDataLoader.h"
#include "../patterns/command/operaciones.h"
#include <functional>

using namespace parametros;

const double freq=1.0/60.0; 

// Legacy constructor using XML
Manager::Manager():dt(freq),
                   tiempo(0),
                   continuar_loop(true),
                   contador_mal_comportamiento(0),
                   jsonLoader(nullptr)
{
    fac = new FactoryGame("gamesInfo.xml");

    string gameId="";
    //scene using id
    escena_actual = fac->buildGameById(gameId);
    cout<<"manager() escena_actual address: "<<escena_actual<<endl;

    CommandBuilder cb;
    map<string,ICommand*> cmds = cb.buildCommands(continuar_loop, escena_actual, inventario,
                                                  parametro1, parametro2, primera_entrada, eventsQueue);
    this->invocador_comandos = Invocador(cmds);
}

// New constructor with language support using JSON
Manager::Manager(const std::string& language):dt(freq),
                   tiempo(0),
                   continuar_loop(true),
                   contador_mal_comportamiento(0)
{
    // Build game data file path based on language
    std::string gameDataFile = "gameData_" + language + ".json";

    // Create JSON loader and factory
    jsonLoader = new JSONGameDataLoader();
    fac = new FactoryGame(jsonLoader, gameDataFile);

    string gameId="";
    //scene using id
    escena_actual = fac->buildGameById(gameId);
    cout<<"manager() escena_actual address: "<<escena_actual<<endl;

    CommandBuilder cb;
    map<string,ICommand*> cmds = cb.buildCommands(continuar_loop, escena_actual, inventario,
                                                  parametro1, parametro2, primera_entrada, eventsQueue);
    this->invocador_comandos = Invocador(cmds);
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
    for(my_iter = my_string.begin();
        my_iter != my_string.end();
        my_iter++)
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

void Manager::run() {
    using namespace std::placeholders;
    auto update_objects_func = std::bind(&Manager::actualizar_objetos, this);
    auto update_exits_func = std::bind(&Manager::actualizar_salidas, this);

    GameLoop gameLoop(continuar_loop, escena_actual, invocador_comandos,
                      comando, parametro1, parametro2, contador_mal_comportamiento,
                      update_objects_func, update_exits_func);
    gameLoop.run();

    // TODO: Save game state
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

/*string Manager::get_salidas_estado_actual(){
	  
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
  }*/


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
	  assert(event!=nullptr);
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
			 if(llave!=nullptr and ladrillo!=nullptr)
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
