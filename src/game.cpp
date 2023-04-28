#include "game.h"

Game::Game(){	
}

Escenario* Game::get_scenario(string key){	  
    return world[key];
}
