#ifndef _OPERACIONES_
#define _OPERACIONES_

#include <iostream>
#include <vector>
#include <list>

//#include "parametros.h"
#include "../../events/event.h"
#include "../../core/inventario.h"
#include "../../events/eventsqueue.h"

using namespace std;
using namespace parametros;

//Interface for commands line
class ICommand{
public:
    ICommand(string command_id):command_id(command_id){}
    virtual ~ICommand() = default;
    virtual void execute()=0;
    string get_command_id(){return command_id;}
protected:
    string command_id;
};

class Exit : public ICommand{
public:
    Exit(bool &continuar_loop):
        continuar_loop(continuar_loop),
        ICommand(s_exit){}
    void execute();
private:
    bool &continuar_loop;
};

class Ayuda : public ICommand{
public:
    Ayuda(vector<string> &v_comandos):
        v_comandos(v_comandos),
        ICommand(s_ayuda){}
    void execute();
private:
    vector<string> v_comandos;
};

class Ver : public ICommand{
public:
    Ver(ppScene escena_actual):
        escena_actual(escena_actual),
        ICommand(s_ver){}	  
    void execute();
    void set_escenario(){}
private:
    ppScene escena_actual; //puntero a un puntor a un escenario
};

//class Ver : public ICommand{};
class Examinar: public ICommand{
public:
    Examinar(ppScene scene,
             Inventario &inventario,
             string &parametro):
        scene(scene),
        inventario(inventario),
        parametro(parametro),
        ICommand(s_examinar){}	  
    void execute();
    string describir_objeto(Objeto *objeto);
private:
    ppScene scene;
    Inventario &inventario;
    string &parametro;
};

class CommandInventario : public ICommand{
public:
    CommandInventario(Inventario &inventario):
        inventario(inventario),
        ICommand(s_inventario){}
    void execute();
private:
    Inventario &inventario;
};

class Cardinal : public ICommand{
public:
    Cardinal(ppScene scene,
             const string &cardinal,
             bool &primera_entrada):
        escena_actual(scene),
        cardinal(cardinal),
        primera_entrada(primera_entrada),
        ICommand(cardinal){}
    void execute();
    pScene getCurrentScene(){return *escena_actual;}
private:
    ppScene escena_actual;
    const string &cardinal;
    bool &primera_entrada;
};

class Tirar : public ICommand{
public:
    Tirar(ppScene scene,
          Inventario &inventario,
          const string &parametro,
          const string &parametro2):
        scene(scene),
        inventario(inventario),
        parametro(parametro),
        parametro2(parametro2),
        ICommand(s_tirar){}
    void execute();
private:
    ppScene scene;
    Inventario &inventario;
    const string &parametro;
    const string &parametro2;
};

class Coger : public ICommand{
public:
    Coger(ppScene scene,
          Inventario &inventario,
          const string &parametro):
        scene(scene),
        inventario(inventario),
        parametro(parametro),
        ICommand(s_coger){}
    void execute();
private:
    ppScene scene;
    Inventario &inventario;
    const string &parametro;
};

class Dejar : public ICommand{
public:
    Dejar(ppScene scene,
          Inventario &inventario,
          const string &parametro):
        scene(scene),
        inventario(inventario),
        parametro(parametro),
        ICommand(s_dejar){}
    void execute();
private:
    ppScene scene;
    Inventario &inventario;
    const string &parametro;
};

class Alcanzar : public ICommand {
public:
    Alcanzar(ppScene scene,
             Inventario &inventario,
             const string &parametro):
        scene(scene),
        inventario(inventario),
        parametro(parametro),
        ICommand(s_alcanzar){}
    void execute();
private:
    ppScene scene;
    Inventario &inventario;
    const string &parametro;
};

class Colocar : public ICommand {
public:
    Colocar(ppScene scene,
            Inventario &inventory,
            EventsQueue &eventsQueue,
            //queue<IEvent*> &eventsQueue,
            const string &parametro,
            const string &parametro2):
        scene(scene),
        inventory(inventory),
        eventsQueue(eventsQueue),
        parametro(parametro),
        parametro2(parametro2),
        ICommand(s_colocar){}
    void execute();
private:
    ppScene scene;
    Inventario &inventory;
    EventsQueue &eventsQueue;
    //queue<IEvent*> &eventsQueue;
    const string &parametro;
    const string &parametro2;
	  
			   	  
};


class CommandBuilder {
public:
    CommandBuilder(){}
     
    map<string,ICommand*> buildCommands(bool continuar_loop,
                                        pScene current_scene,
                                        Inventario &inventario,
                                        string &parametro1,
                                        string &parametro2,
                                        bool &primera_entrada,
                                        EventsQueue &eventsQueue)
        {
            // CONSTRUIR COMMANDOS E INVOCADOR
            //Crear vector de comandos
            //pScene current_scene = scene;	  
            vector<string> v_comandos;

            // TODO: Create ICommands from a list automatically
            string comandos_disponibles="Comandos disponibles: ";
            for(int i=0;i<NUMBER_COMMANDS;++i)
                v_comandos.push_back(comandos[i]);

            //Construir los comandos y conectarlos al invocador
            ICommand *c_exit     = new Exit(continuar_loop);
            ICommand *c_ayuda    = new Ayuda(v_comandos);
            ICommand *c_ver      = new Ver(&current_scene);   //pasar direccion del puntor a una escena
            ICommand *c_examinar = new Examinar(&current_scene,inventario,parametro1); //pasamos direccion al escenario actual y al inventario
            ICommand *c_inventario = new CommandInventario(inventario); // const Escena& current_scene=current_scene;
          
            ICommand *c_norte    = new Cardinal(&current_scene,s_norte,primera_entrada);
            ICommand *c_sur      = new Cardinal(&current_scene,s_sur,primera_entrada);
            ICommand *c_oeste    = new Cardinal(&current_scene,s_oeste,primera_entrada);
            ICommand *c_este     = new Cardinal(&current_scene,s_este,primera_entrada);
            ICommand *c_tirar    = new Tirar(&current_scene,inventario,parametro1,parametro2);
            ICommand *c_coger    = new Coger(&current_scene,inventario,parametro1);
            ICommand *c_dejar    = new Dejar(&current_scene,inventario,parametro1);
            ICommand *c_alcanzar = new Alcanzar(&current_scene,inventario,parametro1);
            ICommand *c_colocar  = new Colocar(&current_scene,inventario,eventsQueue,parametro1,parametro2);
	 
            map<string,ICommand*> mapComandos;
	 
            mapComandos[s_exit]      = c_exit;
            mapComandos[s_salir]     = c_exit;
            mapComandos[s_ayuda]     = c_ayuda;
            mapComandos[s_ver]       = c_ver;
            mapComandos[s_examinar]  = c_examinar;
            mapComandos[s_inventario]= c_inventario;
            mapComandos[s_norte]     = c_norte;
            mapComandos[s_sur]       = c_sur;
            mapComandos[s_este]      = c_este;
            mapComandos[s_oeste]     = c_oeste;
            mapComandos[s_tirar]     = c_tirar;
            mapComandos[s_coger]     = c_coger;
            mapComandos[s_dejar]     = c_dejar;
            mapComandos[s_alcanzar]  = c_alcanzar;
            mapComandos[s_colocar]   = c_colocar;

            // execution from command builder
            mapComandos[s_ver]->execute();
            mapComandos[s_norte]->execute();
          
            return mapComandos;	  
        }


    void initMapCommands(map<string,ICommand*> &mapComandos,
                         bool &continuar_loop,
                         pScene current_scene,
                         Inventario &inventario,
                         string &parametro1,
                         string &parametro2,
                         bool &primera_entrada,
                         EventsQueue &eventsQueue)
        {
            // CONSTRUIR COMMANDOS E INVOCADOR
            //Crear vector de comandos
            //pScene current_scene = scene;	  
            vector<string> v_comandos;

            // TODO: Create ICommands from a list automatically
            string comandos_disponibles="Comandos disponibles: ";
            for(int i=0;i<NUMBER_COMMANDS;++i)
                v_comandos.push_back(comandos[i]);

            //Construir los comandos y conectarlos al invocador
            ICommand *c_exit     = new Exit(continuar_loop);
            ICommand *c_ayuda    = new Ayuda(v_comandos);
            ICommand *c_ver      = new Ver(&current_scene);   //pasar direccion del puntor a una escena
            ICommand *c_examinar = new Examinar(&current_scene,inventario,parametro1); //pasamos direccion al escenario actual y al inventario
            ICommand *c_inventario = new CommandInventario(inventario); // const Escena& current_scene=current_scene;
          
            ICommand *c_norte    = new Cardinal(&current_scene,s_norte,primera_entrada);
            ICommand *c_sur      = new Cardinal(&current_scene,s_sur,primera_entrada);
            ICommand *c_oeste    = new Cardinal(&current_scene,s_oeste,primera_entrada);
            ICommand *c_este     = new Cardinal(&current_scene,s_este,primera_entrada);
            ICommand *c_tirar    = new Tirar(&current_scene,inventario,parametro1,parametro2);
            ICommand *c_coger    = new Coger(&current_scene,inventario,parametro1);
            ICommand *c_dejar    = new Dejar(&current_scene,inventario,parametro1);
            ICommand *c_alcanzar = new Alcanzar(&current_scene,inventario,parametro1);
            ICommand *c_colocar  = new Colocar(&current_scene,inventario,eventsQueue,parametro1,parametro2);
            
            mapComandos[s_exit]      = c_exit;
            mapComandos[s_salir]     = c_exit;
            mapComandos[s_ayuda]     = c_ayuda;
            mapComandos[s_ver]       = c_ver;
            mapComandos[s_examinar]  = c_examinar;
            mapComandos[s_inventario]= c_inventario;
            mapComandos[s_norte]     = c_norte;
            mapComandos[s_sur]       = c_sur;
            mapComandos[s_este]      = c_este;
            mapComandos[s_oeste]     = c_oeste;
            mapComandos[s_tirar]     = c_tirar;
            mapComandos[s_coger]     = c_coger;
            mapComandos[s_dejar]     = c_dejar;
            mapComandos[s_alcanzar]  = c_alcanzar;
            mapComandos[s_colocar]   = c_colocar;

            // execution from command builder
            // mapComandos[s_ver]->execute();
            //mapComandos[s_norte]->execute();
    
            //return mapComandos;	  
        }


    


    
};




#endif
