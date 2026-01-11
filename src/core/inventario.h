#ifndef _inventario_
#define _inventario_

#include <map>
#include <string>

#include "objeto.h"

class Inventario{
public:
    Inventario();

    //GETTERS
    Objeto* get_objeto(std::string nombre_objeto);
    bool get_existe_objeto(std::string nombre);
    Objeto extraer_objeto();
    std::string listar();

    bool posee_alcanzador();
    Objeto* tomar_alcanzador();

    bool posee_desatascador();
    Objeto* tomar_desatascador();

    //SETTERS
    void insertar_objeto(Objeto *objeto);
    void eliminar(std::string nombre);

private:
    std::map<std::string,Objeto*> objetos_inventario;
};

#endif

