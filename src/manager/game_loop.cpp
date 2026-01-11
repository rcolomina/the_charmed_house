#include "game_loop.h"

GameLoop::GameLoop(bool& continuar_loop,
                   Escenario*& escena_actual,
                   Invocador& invocador_comandos,
                   string& comando,
                   string& parametro1,
                   string& parametro2,
                   int& contador_mal_comportamiento,
                   function<void()> update_objects,
                   function<void()> update_exits)
    : continuar_loop_(continuar_loop),
      escena_actual_(escena_actual),
      invocador_comandos_(invocador_comandos),
      comando_(comando),
      parametro1_(parametro1),
      parametro2_(parametro2),
      contador_mal_comportamiento_(contador_mal_comportamiento),
      update_objects_(update_objects),
      update_exits_(update_exits) {}

void GameLoop::run() {
    bool primera_entrada = true;

    while(continuar_loop_) {
        ///DIBUJAR ESCENARIO///
        if(primera_entrada) {
            cout << endl;
            escena_actual_->pintar();
            cout << endl;
            cout << get_descripcion_estado_actual() << endl;
            primera_entrada = false;
        }

        ///RECOGIDA DE COMMANDOS CONSOLA///
        cout << ">>>";

        processInput();

        ///TRATAMIENTO DE COMANDOS
        int ret_val = invocador_comandos_.exec(comando_, parametro1_, parametro2_);
        if(ret_val == 1) {
            contador_mal_comportamiento_++;
        }

        //Actualizar Objetos
        update_objects_();

        //Actualizar Salidas
        update_exits_();
    }

    //SALIDA DEL JUEGO
    if(contador_mal_comportamiento_ < 3) {
        string goodbye_message = "GRACIAS POR JUGAR! :),TE ESPERO PRONTO DE VUELTA.";
        cout << endl << goodbye_message << endl << endl;
    } else {
        cout << endl << endl <<
            "Eres una desgracia humana mentalmente o no tienes" <<
            " la sufiente madurez, así que vuelve tan sólo cuando hayas soluciodado ese asunto. ADIOS!.";
        cout << endl << "ERES UN MALEDUCADO, NECESITAS CLASES DE MODALES." << endl << endl;
    }
}

void GameLoop::processInput() {
    string entrada_consola;
    getline(cin, entrada_consola);

    // Clear previous command parameters
    comando_ = "";
    parametro1_ = "";
    parametro2_ = "";

    list<string> lista_comandos;
    istringstream iss(entrada_consola);
    string sub;
    while(iss >> sub) {
        lista_comandos.push_back(sub);
    }

    if(!lista_comandos.empty()) {
        comando_ = lista_comandos.front();
        lista_comandos.pop_front();
    }

    if(!lista_comandos.empty()) {
        parametro1_ = lista_comandos.front();
        lista_comandos.pop_front();
    }

    if(!lista_comandos.empty()) {
        parametro2_ = lista_comandos.front();
        lista_comandos.pop_front();
    }
}

string GameLoop::get_descripcion_estado_actual() {
    string descripcion = escena_actual_->examine();
    descripcion += "\n";
    if(escena_actual_->get_objetos_disponibles() != "") {
        descripcion += "Puedes ver : \n";
        descripcion += escena_actual_->get_objetos_disponibles();
    }
    return descripcion;
}
