#ifndef _game_
#define _game_

#include <map>
#include <iostream>


#include "../patterns/command/operaciones.h"
//#include "../events/event.h"

using namespace std;

//class Escenario;
//class Objeto;

//typedef Escenario* pScene;
//typedef Objeto* pItem;
// This class is an interface to storage
// for scenearios and items.
// It saves the state of the world game

//class Escenario;


class Game;
typedef Game* pGame;

class Game : public Entidad{
public:
    Game();
    Game(string idGame,string xmlSpecs){}

    pScene get_scenario(string key);
    void set_scenario(Escenario *scenario);

    pItem get_item(string key);
    void set_item(Objeto *item);

    pScene get_current_scene();
    void set_current_scene();

    void save_game(string game_name);
    void load_game(string game_name);

private:
    // Storing the state of the game world
    map<string,pScene> world;
    map<string,pItem> items;

    // References to the current scene
    pScene current_scene; 
    //Escenario current_scene1; 

};

#endif
