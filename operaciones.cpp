#include "operaciones.h"



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

    string descripcion=(*escena_actual)->examine();
    descripcion+="\n";
    if((*escena_actual)->get_objetos_disponibles()!="")
    {
        descripcion+="Puedes ver los siguiente: ";
        descripcion+=(*escena_actual)->get_objetos_disponibles();
    }
    cout<<descripcion;	 
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
        cout<<"No hay nada llamado '"<<parametro<<"'"<<endl;

}


void CommandInventario::execute(){
    cout<<endl<<"En tu inventario posees lo siguiente: "<<endl<<inventario.listar()<<endl;
}


void Cardinal::execute(){

    if((*escena_actual)->get_salida(cardinal))
    {
        *escena_actual = (*escena_actual)->get_salida(cardinal);
        primera_entrada=true;
        // cout<<"cambiando de escena"<<endl;
    } 
    else
        cout<<"No puedes ir al "<<cardinal;					


}

// Si es "tirable", se puede tirar del mismo.
void Tirar::execute(){

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
        if(objeto->get_tirable())
        {
            if(objeto->get_atascado())
            {
                bool desatascador=inventario.posee_desatascador();
									 
                if(desatascador)
                {
                    Objeto *objDesatascador=inventario.tomar_desatascador();											  
                    string desatascador;
                    if(objDesatascador!=0){
                        desatascador=objDesatascador->Name();
                        inventario.eliminar(desatascador);
                    }
                    //TODO: Determinar genero del objeto desatascador para poner "del" o "de la"
                    cout<<"Has conseguido tirar del "<<objTirar<<" con ayuda de "<<objDesatascador->Name()<<endl;

                    objeto->tirar();
                    (*scene)->eliminar(objeto);					
                }
                else
                {
                    cout<<"Esta atascado"<<endl;
                }
            }						
            else
            {
                objeto->tirar();
                (*scene)->eliminar(objeto);					
            }
        }
        else
            cout<<"No puedes tirar de "<<objTirar<<endl;
    }
    else
    {
        if(objTirar!="")
            cout<<"No puedo tirar de '"<<objTirar<<"'."<<endl;
        else
            cout<<"Tirar de que?."<<endl;
    }
}


void Coger::execute(){

//	  cout<<(*escenario)->Name()<<endl;
//	  cout<<"Parametro "<<parametro<<endl;
    // Existe el objeto especificado en parametro 1
    if((*scene)->get_existe_objeto_escenario(parametro))
    {			 
        Objeto *objeto=(*scene)->get_objeto(parametro);
        //Si se puede tirar del objeto pasado por parametro
        if(!objeto->get_fijo())
        {
            if(objeto->get_alcanzable()){
                inventario.insertar_objeto(objeto);
                (*scene)->eliminar(objeto);
                cout<<"Has cogido "<<parametro<<endl;
            }
            else
                cout<<"No se puedes coger porque no es alcanzable "<<endl;
        }
        else
            cout<<"No puedes cogerlo porque esta fijado."<<parametro<<endl;			 
    }
    else
    {
        if(parametro!="")
            cout<<""<<parametro<<" no se puede coger."<<endl;
        else
            cout<<"Coger que?"<<endl;
    }
}

void Alcanzar::execute(){
    // Si tienes algo para alcanza	
    if((*scene)->get_existe_objeto_escenario(parametro))
    {
        if(inventario.posee_alcanzador())
        {
            Objeto *objAlcanzador=inventario.tomar_alcanzador();

            string alcanzador;
            if(objAlcanzador!=0)
            {
                alcanzador=objAlcanzador->Name();
                inventario.eliminar(alcanzador);
            }

            //Determinar genero del objeto alcanzador para poner "del" o "de la"
            cout<<"Has cogido "<<parametro<<" con ayuda del "<<alcanzador<<endl;			 

            Objeto *objeto=(*scene)->get_objeto(parametro);
            inventario.insertar_objeto(objeto);
            (*scene)->eliminar(objeto);

        }
        else
            cout<<"No tienes nada con que alcanzar eso."<<endl;
    }
    else
    {
        if(parametro!="")
            cout<<""<<parametro<<" no se puede alcanzar."<<endl;
        else
            cout<<"Alcanzar que?"<<endl;
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
