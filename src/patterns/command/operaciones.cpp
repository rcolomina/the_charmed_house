#include <cassert>

#include "operaciones.h"
#include "lib/logger/logger.h"
#include "lib/colormod/colormod.h"


void Exit::execute(){
    continuar_loop=false;
}

// Muestra los comandos disponibles
void Ayuda::execute(){

    cout<<"Comandos disponibles:"<<endl;
				 
    for(vector<string>::iterator it=v_comandos.begin();
        it!=v_comandos.end();
        it++)
    {
        cout<<*it<<" ";
    }
}

void Ver::execute(){

    Logger::instance().log("Entering into Ver::execute() method ", Logger::kLogLevelInfo);

    cout<<"escenario actual address: "<<escena_actual<<endl;
    //cout<<escena_actual->
        
        
    string descripcion=(*escena_actual)->examine();
    descripcion+="\n";
    if((*escena_actual)->get_objetos_disponibles()!="")
    {
        descripcion+="Puedes ver los siguiente: ";
        descripcion+=(*escena_actual)->get_objetos_disponibles();
    }
    cout<<Color::cyan<<descripcion<<Color::def;	 
}

void Examinar::execute(){

    // This shows user a description of objects examinated
    // recorrer objetos del scene actual y del inventario
    if(string(parametro)==string(""))
        cout<<"Examinar que?"<<endl;
    else if(inventario.get_existe_objeto(parametro))
        cout<<(inventario.get_objeto(parametro))->examine()<<endl;
    else if((*scene)->get_existe_objeto_escenario(parametro))
        cout<<((*scene)->get_objeto(parametro))->examine()<<endl;		  
    else 
        cout<<Color::red<<"No hay nada llamado '"<<parametro<<"'"<<Color::def<<endl;
}


void CommandInventario::execute(){
    cout<<endl<<Color::cyan<<"En tu inventario posees lo siguiente: "<<Color::def<<endl;
    cout<<Color::yellow<<inventario.listar()<<Color::def<<endl;
}


void Cardinal::execute(){
    //cout<<"existeSalida "<<existeSalida<<endl;
    Logger::instance().log("Entering into Cardinal::execute() method ", Logger::kLogLevelInfo);
	  
    pScene psce=*escena_actual;
     

     
    bool existeSalida=(psce->get_salida(cardinal)!=nullptr);
    bool estadoSalida=psce->get_estado_salida(cardinal);


    if(existeSalida and estadoSalida)
    {			
        *escena_actual = (*escena_actual)->get_salida(cardinal);
        primera_entrada=true;
        // cout<<"cambiando de escena"<<endl;
    } 
    else
        cout<<Color::red<<"No puedes ir: "<<cardinal<<Color::def<<endl;					

}

// Si es "tirable", se puede tirar del mismo.
void Tirar::execute(){

    Logger::instance().log("Entering into Tirar::execute() method ", Logger::kLogLevelInfo);

	  
    // Analisis sintactico parametros en entrada
    string objTirar;
    // parametro1 es una preposicion 
    bool param1Articulo=parametro=="de" or parametro=="del";
    // parametro2 no es vacio
    bool param2NotVoid=parametro2!="";

    if(param1Articulo and param2NotVoid)
        objTirar=parametro2;
    else 
        objTirar=parametro;
			
	 
    bool existeObjTirar=(*scene)->get_existe_objeto_escenario(objTirar);
    // Existe el objeto especificado en objTirar
    if(existeObjTirar)
    {
        Objeto *objeto=(*scene)->get_objeto(objTirar);
        //Si se puede tirar del objeto pasado por objTirar
		  		  
        if(objeto->get_value<bool>("tirable"))
        {
            if(objeto->get_value<bool>("stucked"))
            {					
                bool desatascador=false;
                desatascador=inventario.posee_desatascador();


                if(desatascador)
                {
                    Logger::instance().log("Bool desatascador es true", Logger::kLogLevelDebug);
                    Objeto *objDesatascador=inventario.tomar_desatascador();											  
                    string desatascador;
                    if(objDesatascador!=0){
                        Logger::instance().log("Existe objeto desatascador", Logger::kLogLevelDebug);
								 
                        desatascador=objDesatascador->Name();
                        inventario.eliminar(desatascador);
                    }
                    //TODO: Determinar genero del objeto desatascador para poner "del" o "de la" (determinar genero de la palabra)


                    cout<<Color::yellow<<"Has conseguido tirar del "<<objTirar<<" con ayuda de "<<objDesatascador->Name()<<Color::def<<endl;

                    objeto->tirar();
                    (*scene)->eliminar(objeto);					
                }
                else
                {
                    cout<<Color::magenta<<"Esta atascado"<<Color::def<<endl;
                }
            }						
            else
            {
                objeto->tirar();
                (*scene)->eliminar(objeto);					
            }
        }
        else
            cout<<Color::red<<"No puedes tirar de "<<objTirar<<Color::def<<endl;
    }
    else
    {
        if(objTirar!="")
            cout<<Color::red<<"No puedo tirar de '"<<objTirar<<"'."<<Color::def<<endl;
        else
            cout<<Color::magenta<<"Tirar de que?."<<Color::def<<endl;
    }
}


void Coger::execute()
{

//	  cout<<(*escenario)->Name()<<endl;
//	  cout<<"Parametro "<<parametro<<endl;
    // Existe el objeto especificado en parametro 1
    if((*scene)->get_existe_objeto_escenario(parametro))
    {			 
        Objeto *objeto=(*scene)->get_objeto(parametro);
        //Si se puede tirar del objeto pasado por parametro
        if(!objeto->get_value<bool>("fix"))
        {
            if(objeto->get_value<bool>("alcanzable"))
            {
                inventario.insertar_objeto(objeto);
                (*scene)->eliminar(objeto);
                cout<<Color::yellow<<"Has cogido "<<parametro<<Color::def<<endl;
            }
            else
                cout<<Color::red<<"No se puedes coger porque no es alcanzable "<<Color::def<<endl;
        }
        else
            cout<<Color::red<<"No puedes cogerlo porque esta fijado."<<parametro<<Color::def<<endl;			 
    }
    else
    {
        if(parametro!="")
            cout<<""<<parametro<<" no se puede coger."<<endl;
        else
            cout<<Color::magenta<<"Coger que?"<<Color::def<<endl;
    }
}

void Alcanzar::execute()
{
    Logger::instance().log("Entering into Alcanzar::execute() method ", Logger::kLogLevelInfo);
	  
    // Si tienes algo para alcanza	
    if((*scene)->get_existe_objeto_escenario(parametro))
    {
        Objeto *objeto=(*scene)->get_objeto(parametro);
//		  if(objeto->get_value<bool>(""))
        //TODO: There is an error, this code should avoid that items "alcanzables" may be disappear
			 
        if(inventario.posee_alcanzador() )
        {
            Objeto *objAlcanzador=inventario.tomar_alcanzador();
					
            string alcanzador;
            if(objAlcanzador!=0)
            {
                alcanzador=objAlcanzador->Name();
                inventario.eliminar(alcanzador);
            }

            //Determinar genero del objeto alcanzador para poner "del" o "de la"
            cout<<Color::yellow<<"Has cogido "<<parametro<<" con ayuda del "<<alcanzador<<Color::def<<endl;			 

            inventario.insertar_objeto(objeto);
            (*scene)->eliminar(objeto);

        }
        else
            cout<<Color::red<<"No tienes nada con que alcanzar eso."<<Color::def<<endl;
    }
    else
    {
        if(parametro!="")
            cout<<Color::red<<""<<parametro<<" no se puede alcanzar."<<Color::def<<endl;
        else
            cout<<Color::magenta<<"Alcanzar que?"<<Color::def<<endl;
    }

    // y quieres coger algo no alcanzable
    // puedes cogerlo

}




void Dejar::execute(){
	  
/*
// Existe el objeto especificado en parametro 1
if((*escenario)->get_existe_objeto_escenario(parametro))
{			 
Objeto *objeto=(*escenario)->get_objeto(parametro);
//Si se puede tirar del objeto pasado por parametro
if(!objeto->get_fijo())
inventario.insertar_objeto(objeto);
else
cout<<"No puedes coger de "<<parametro<<endl;

}
else
{
if(parametro!="")
cout<<"No puedes coger '"<<parametro<<"'."<<endl;
else
cout<<"Coger que?."<<endl;
}
*/

        }

// This operation uses two parameters and determine whether
// the first can be 'inserted' over the second.
// In that case, check out whether an action must be trigger or not
// e.g. a key and a lock should have same codes to trigger the action
// to open a door or a gate
void Colocar::execute(){

    bool existOrigin  = inventory.get_existe_objeto(parametro);	 
    bool existDestiny = (*scene)->get_existe_objeto_escenario(parametro2);
    bool p1void = (parametro=="");
    bool p2void = (parametro2=="");

    if(p1void)
    {
        // TODO: Parametrise this phrase
        cout<<Color::magenta<<"Colocar que?"<<Color::def<<endl;
    }

    if(not p1void and p2void)
    {
        // TODO: Parametrise this phrase
        cout<<Color::magenta<<"Colocar "<<parametro<<" sobre que?"<<Color::def<<endl;
    }

    if(not p1void and not p2void)
    {
        if(existOrigin)
        {			 
            if(existDestiny)
            {
                Objeto *obj1=inventory.get_objeto(parametro);
                Objeto *obj2=(*scene)->get_objeto(parametro2);

                assert(obj1!=nullptr);
                assert(obj2!=nullptr);								 
						  
                bool isKey  =  true;//obj1->get_value<bool>("key");
                bool isLock =  true;//obj2->get_value<bool>("lock");
                if(isKey and isLock)
                {								
                    int code1 = obj1->get_value<int>("code");
                    int code2 = obj2->get_value<int>("code");
                    if(code1==code2)
                    {
                        // TODO: Parametrise this phrase										
                        cout<<Color::yellow<<"Has colocado "<<parametro<<" sobre "<<parametro2;
                        cout<<". Un mecanismo se ha activado."<<Color::def<<endl;			
                        IEvent* event=obj2->activate_event();	
                        if(event!=nullptr)
                            eventsQueue.push(event);
                    }
                    else
                    {
                        // TODO: Parametrise this phrase
                        cout<<Color::magenta<<"Has colocado "<<parametro<<" sobre "<<parametro2;
                        cout<<Color::magenta<<", pero nada sucede."<<Color::def<<endl;
                    }
										
                }						  
                else
                {
                    // TODO: Parametrise this phrase							      
                    cout<<Color::red<<"No puedes hacer eso."<<Color::def<<endl;
                }								 
						  
            }
            else
            {

                // TODO: Parametrise this phrase								 
                cout<<Color::red<<"No hay nada parecido a "<<parametro2<<Color::def<<endl;
            }
        }
        else
        {
            // TODO: Parametrise this phrase								 
            cout<<Color::red<<"No puedes colocar "<<parametro<<" sobre "<<parametro2<<Color::def<<endl;
        }
    }
}






