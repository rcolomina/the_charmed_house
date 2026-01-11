#include <map>
//#include "../core/escenario.h"
#include "../patterns/factory/factory.h"
#include "../patterns/command/invocador.h"
#include "../patterns/command/operaciones.h"

int main(){

    // Building scenario
    FactoryGame fac("gamesInfo.xml");
    string gameId="";
    Escenario* escena_actual = fac.buildGameById(gameId);
    
    //CommandBuilder *commandBuilder    = new CommandBuilder();

    // Building map of commands
    bool continuar_loop=true;
    Inventario inventario;
    string parametro1;
    string parametro2;
    bool primera_entrada;
    EventsQueue eventsQueue;

    //Construir los comandos y conectarlos al invocador
    string comandos_disponibles="Comandos disponibles: ";
    vector<string> v_comandos;
    for(int i=0;i<NUMBER_COMMANDS;++i)
        v_comandos.push_back(comandos[i]);

    list<ICommand*> mycommands;

    mycommands.push_back(new Exit(continuar_loop));
    mycommands.push_back(new Ayuda(v_comandos));
    mycommands.push_back(new Ver(&escena_actual));
    mycommands.push_back(new Examinar(&escena_actual,inventario,parametro1));
    mycommands.push_back(new CommandInventario(inventario));
    mycommands.push_back(new Cardinal(&escena_actual,s_norte,primera_entrada));
    mycommands.push_back(new Cardinal(&escena_actual,s_sur,primera_entrada));
    mycommands.push_back(new Cardinal(&escena_actual,s_oeste,primera_entrada));
    mycommands.push_back(new Cardinal(&escena_actual,s_este,primera_entrada));
    mycommands.push_back(new Tirar(&escena_actual,inventario,parametro1,parametro2));
    mycommands.push_back(new Coger(&escena_actual,inventario,parametro1));
    mycommands.push_back(new Dejar(&escena_actual,inventario,parametro1));
    mycommands.push_back(new Alcanzar(&escena_actual,inventario,parametro1));
    mycommands.push_back(new Colocar(&escena_actual,inventario,eventsQueue,parametro1,parametro2));    
    
    map<string,ICommand*> mapComandos; // = new map<string,ICommand*>;

    for(auto it=mycommands.begin();
        it!=mycommands.end();
        ++it){
        string key=(*it)->get_command_id();
        mapComandos[key]=*it;
        cout<<"Added key "<<key<<endl;
    }
    
    Invocador invocador_comandos = Invocador(mapComandos);


    cout<<escena_actual->get_description()<<endl;

    return 0;   
}
