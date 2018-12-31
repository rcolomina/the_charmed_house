#ifndef _INVOCADOR_
#define _INVOCADOR_

#include <map>
#include "operaciones.h"

// This class gathers all existing commands in game by a string command key
// Exection method determines wheter the command exist or not.
class Invocador{
public:
    Invocador(){}
    Invocador(map<string,ICommand*> mapCommands):
        mapCommands(mapCommands){}

    int exec(string commandKey,string parametro1,string parametro2);    
    
    list<string> get_commands(){
        list<string> keysCommands;
        // TODO; run keys of map of commands        
        return keysCommands;
    }
    
private:
    map<string,ICommand*> mapCommands;
};

#endif
