#ifndef _GAME_LOOP_
#define _GAME_LOOP_

#include <string>
#include <iostream>
#include <sstream>
#include <functional>
#include "../patterns/command/invocador.h"

using namespace std;

class Escenario;

class GameLoop {
public:
    GameLoop(bool& continuar_loop,
             Escenario*& escena_actual,
             Invocador& invocador_comandos,
             string& comando,
             string& parametro1,
             string& parametro2,
             int& contador_mal_comportamiento,
             function<void()> update_objects,
             function<void()> update_exits);

    void run();

private:
    bool& continuar_loop_;
    Escenario*& escena_actual_;
    Invocador& invocador_comandos_;
    string& comando_;
    string& parametro1_;
    string& parametro2_;
    int& contador_mal_comportamiento_;
    function<void()> update_objects_;
    function<void()> update_exits_;

    void processInput();
    string get_descripcion_estado_actual();
};

#endif
