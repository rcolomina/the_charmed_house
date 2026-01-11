#ifndef _escenario_
#define _escenerio_

#include <fstream> 
#include <string>
#include <map>
#include <queue>

#include "objeto.h"

using namespace parametros;
using namespace std;

class Escenario;
typedef Escenario* pScene;
typedef Escenario** ppScene;

extern void connect(Escenario* scenA,cardinal carA,Escenario* scenB,cardinal carB);

//Clase que describe un escenario: Salidas, Objetos, Descripción, Imagen
class Escenario : public Entidad {
public:
    //constructores
    Escenario(){}
    Escenario(int id,string nombre,string descripcion,string observacion);
    Escenario(const Entidad &ent,const string &observacion,const string &path);
     
    //////getters//////
    string get_description();
    string salidas();     
    string get_observacion(){return observacion;}
    map<string,pScene> get_salidas(){return escenarioSalidas;} //devuelve lista de escenarios salidas
    string salidasDisponibles();	 
    pScene get_salida(string coordenada){return escenarioSalidas[coordenada];} // return null if does not exist
    pScene conexion(cardinal car);
    bool get_estado_salida(string coordenada);
    map<string,pItem> get_objetos(){return objetos;} // what objects are availables
    string get_objetos_disponibles();	  
    pItem get_objeto(string nombre){return objetos[nombre];}
    bool get_existe_objeto_escenario(string nombre);
    string get_path_image(){return pathFileImageText;}
	  
    //////setters/////
    void set_salidas(map<string,pScene> salidas); //se invocará en la construcción del mundo	  	  
    void set_salida(pScene escenario,string coordenada,bool estado);
    void set_estado_salida(string coordenada,bool new_estado);
    void set_objeto(pItem obj);
    void eliminar(pItem obj);

    // procedures
    void pintar(); // allow to draw a scene
private:	
    string observacion;	  
    map<string,pScene> escenarioSalidas;       // guarda par (cardinal, pScene)
    map<string,bool>   estadoSalidas; // salida abierta o cerrada
    map<string,pItem>  objetos;       // nombre y referenca a objeto	 
    const string pathFileImageText;	  
    map<cardinal,pScene> conexions;
    friend void connect(Escenario* scenA,cardinal carA,Escenario* scenB,cardinal carB);
};

#endif


