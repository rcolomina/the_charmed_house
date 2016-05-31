#ifndef _GAME_
#define _GAME_

#include <map>

#include "objeto.h"

using namespace std;

class Escenario;

// This class is an interface to storage
// for scenearios and items.
// It saves the state of the world game
class Game : public Entidad{
	public:
	  Game();

	  Escenario *get_scenario(string key);
	  void set_scenario(Escenario *scenario);

	  Objeto *get_item(string key);
	  void set_item(Objeto *item);

	  Escenario *get_current_scene();
	  void set_current_scene();

	  void save_game(string game_name);
	  void load_game(string game_name);
	private:
	  // Save the state of the game world
	  map<string,Escenario*> world;
	  map<string,Objeto> items;

	  // References to the current scene
	  Escenario *current_scene; 
	  //Escenario current_scene1; 

};

#endif
