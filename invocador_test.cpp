#include <map>
//#include "escenario.h"
#include "factory.h"
#include "invocador.h"
#include "operaciones.h"

int main(){

    bool continuar_loop=true;
    Inventario inventario;
    string parametro1;
    string parametro2;
    bool primera_entrada;
    EventsQueue eventsQueue;

    FactoryGame fac("gamesInfo.xml");
    string gameId="";
    Escenario* escena_actual = fac.buildGameById(gameId);

    CommandBuilder *commandBuilder    = new CommandBuilder();
    map<string,ICommand*> mapComandos = commandBuilder->buildCommands(continuar_loop,
                                                                      escena_actual,
                                                                      inventario,
                                                                      parametro1,
                                                                      parametro2,
                                                                      primera_entrada,
                                                                      eventsQueue);     
    // Build command trigger
    Invocador invocador_comandos = Invocador(mapComandos);

    cout<<escena_actual->get_description()<<endl;
    invocador_comandos.exec("o",parametro1,parametro2);

    cout<<escena_actual->get_description()<<endl;

    return 0;   
}
