#include "../events/event.h"
#include "../patterns/factory/factory.h"

int main(){

    // Preparing a factory
    string xmlSpecs("gamesInfo.xml");
    FactoryGame fac(xmlSpecs);

    // Build Escenarios
    string idScen("game.scenes.scene.sce001");
    cout<<"Building Scenario "<<idScen<<" "<<endl;	  
    pScene scene1=fac.buildScenarioById(idScen);

    string idScen2("game.scenes.scene.sce002");
    cout<<"Building Scenario "<<idScen2<<" "<<endl;	  
    pScene scene2=fac.buildScenarioById(idScen2);

    scene1->set_salida(scene2,s_norte,false);
    scene2->set_salida(scene1,s_sur,true);

    cout<<"Salidas disponibles desde scene1:"<<scene1->salidasDisponibles()<<endl;
	  
    // Build Event	  
    string cardinal=s_norte;
    string postMessage="Evento activado OK.";
    IEvent *event = new EventOpenConnection(scene1,
                                            cardinal,
                                            postMessage);
    
    cout<<"Activar evento sobre scene1:"<<event->activate()<<endl;
    cout<<"Salidas disponibles desde scene1:"<<scene1->salidasDisponibles()<<endl;;

    //
    cout<<"-- Usando objeto EventsQueue como wrapper de cola de evento"<<endl;
    EventsQueue eventsQueue;
    eventsQueue.push(event);
    eventsQueue.fire();	  
    return 0;
}
