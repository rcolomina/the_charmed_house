#include "manager.h"
#include "logger.h"


using namespace parametros;

const double freq=1.0/60.0; 

Manager::Manager():dt(freq),
                   tiempo(0),
                   continuar_loop(true),
                   contador_mal_comportamiento(0),
						 fac("gamesInfo.xml")
{	  
	  //CONSTRUIMOS LA PRIMERA ESCENA: TODO:Cargar desde fichero
	  // TODO: Build automatically all these objects running over its ids.
	  pScene esc1 = fac.buildScenarioById("game.scenes.scene.sce001");
	  pScene esc2 = fac.buildScenarioById("game.scenes.scene.sce002");
	  pScene esc3 = fac.buildScenarioById("game.scenes.scene.sce003");
	  pScene esc4 = fac.buildScenarioById("game.scenes.scene.sce004");
	  pScene esc5 = fac.buildScenarioById("game.scenes.scene.sce005");
	  pScene esc6 = fac.buildScenarioById("game.scenes.scene.sce006");
	  
	  //CONSTRUIR OBJETOS
	  // TODO: Build automatically all these objects running over its ids.	  
	  pItem o_baston    = fac.buildItemById("game.items.item.item01");
	  pItem o_ladrillo  = fac.buildItemById("game.items.item.item02");
	  pItem o_cerradura = fac.buildItemById("game.items.item.item03");
	  pItem o_palanca   = fac.buildItemById("game.items.item.item04");
	  pItem o_figurita  = fac.buildItemById("game.items.item.item05");
	  pItem o_hueco     = fac.buildItemById("game.items.item.item06");
	 
//Continuar con el bucle principal del juego
//	  continuar_loop=true;
//   configurar reloj
//	  tiempo=0; //segundos	  
//   variables del jugador
//	  contador_mal_comportamiento=0;
  	 	  	  	 
    // Setear la escena de comienzo del juego
    escena_actual=esc1;

    //insertar escenario en mundo
/*    mundo[nombre1]=esc1;
    mundo[nombre2]=esc2;
    mundo[nombre3]=esc3;
    mundo[nombre4]=esc4;*/
	 
    // Enlaces entre escenas
    //Id: 1->[2(o),3(e)] ,2->[1(e),4(i)), 3->[1(o)], 4->[2(e)]
	 connect(esc1,west,esc2,east);
	 connect(esc1,east,esc3,west);
	 connect(esc2,west,esc4,east);

	 
    esc1->set_salida(esc2,oeste,true);	 
	 esc2->set_salida(esc1,este,true);
		  
    esc1->set_salida(esc3,este,true);
    esc3->set_salida(esc1,oeste,true);
	 
    esc2->set_salida(esc4,oeste,true);
	 esc4->set_salida(esc2,este,true);

	 esc4->set_salida(esc5,oeste,true);
	 esc5->set_salida(esc4,este,true);

	 esc5->set_salida(esc6,oeste,false);
	 esc6->set_salida(esc5,este,true);
	 
    //RELACIONAR OBJETOS
	 // Ladrillo con llave
    string descrip_tirar_ladrillo="Tiras con fuerza del ladrillo de la pared, y parece que comienza a ceder. Una vez sacado el ladrillo, tras el, aparece una cerradura escondida.";
    o_ladrillo->set_tirable(o_cerradura,descrip_tirar_ladrillo);

	 //o_hueco->subscribed(
	 
    //INSERTAR OBJETOS EN ESCENARIOS
    esc1->set_objeto(o_ladrillo);
    esc1->set_objeto(o_cerradura);
    esc2->set_objeto(o_baston);
    esc3->set_objeto(o_figurita);
    esc4->set_objeto(o_palanca);
	 esc5->set_objeto(o_hueco);
    //CONSTRUIR INVENTARIO
    //inventario.insertar_objeto(objeto);
	 
    // CONSTRUIR COMMANDOS E INVOCADOR
	 //Crear vector de comandos
	
	 // TODO: Create ICommands from a list automatically
    comandos_disponibles="Comandos disponibles:";
	 for(int i=0;i<NUMBER_COMMANDS;++i)
        v_comandos.push_back(comandos[i]);

    //Construir los comandos y conectarlos al invocador
    ICommand *c_exit  = new Exit(continuar_loop);
    ICommand *c_ayuda = new Ayuda(v_comandos);
    ICommand *c_ver   = new Ver(&escena_actual); //pasar direccion del puntor a una escena
    ICommand *c_examinar = new Examinar(&escena_actual,inventario,parametro1); //pasamos direccion al escenario actual y al inventario
    ICommand *c_inventario = new CommandInventario(inventario);
//	  const Escena& escena_actual=escena_actual;
    ICommand *c_norte = new Cardinal(&escena_actual,s_norte,primera_entrada);
    ICommand *c_sur   = new Cardinal(&escena_actual,s_sur,primera_entrada);
    ICommand *c_oeste = new Cardinal(&escena_actual,s_oeste,primera_entrada);
    ICommand *c_este  = new Cardinal(&escena_actual,s_este,primera_entrada);
    ICommand *c_tirar = new Tirar(&escena_actual,inventario,parametro1,parametro2);
    ICommand *c_coger = new Coger(&escena_actual,inventario,parametro1);
    ICommand *c_dejar = new Dejar(&escena_actual,inventario,parametro1);
    ICommand *c_alcanzar = new Alcanzar(&escena_actual,inventario,parametro1);
	 ICommand *c_colocar = new Colocar(&escena_actual,inventario,eventsQueue,parametro1,parametro2);

	 
    map<string,ICommand*> mapComandos;
	 
    mapComandos[s_exit]=c_exit;
    mapComandos[s_salir]=c_exit;
    mapComandos[s_ayuda]=c_ayuda;
    mapComandos[s_ver]=c_ver;
    mapComandos[s_examinar]=c_examinar;
    mapComandos[s_inventario]=c_inventario;
    mapComandos[s_norte]=c_norte;
    mapComandos[s_sur]=c_sur;
    mapComandos[s_este]=c_este;
    mapComandos[s_oeste]=c_oeste;
    mapComandos[s_tirar]=c_tirar;
    mapComandos[s_coger]=c_coger;
    mapComandos[s_dejar]=c_dejar;
    mapComandos[s_alcanzar]=c_alcanzar;
	 mapComandos[s_colocar]=c_colocar;

    // Construir invocador de comandos con mapComandos
    invocador_comandos=Invocador(mapComandos);


	 // Events on objects
	 IEvent *eventOpenConnection1 = new EventOpenConnection(esc5,
																			  s_oeste,
																			  postMessageActivationToEventOpenConnection1);

	 o_hueco->insert_event(eventOpenConnection1);
	 
}

void Manager::prologo(){

	  // TODO: Get data from sceneario object
	  
    cout<<endl<<"¡BIENVENIDO QUERIDO JUGADOR! \n\nLA CASA ENCANTADA v1.0"<<endl<<endl;
    cout<<tituloPreludio<<endl;

    string my_string=textoPreludio1;
    string::iterator my_iter;
    for(my_iter = my_string.begin(); my_iter != my_string.end(); my_iter++)
    {
        usleep(50000);
        cout<<*my_iter<<flush;
    }

    cout<<endl;
//	  cout<<textoPreludio1<<endl;
    sleep(2);

    my_string=textoPreludio2;
    for(my_iter = my_string.begin(); my_iter != my_string.end(); my_iter++)
    {
        usleep(50000);
        cout<<*my_iter<<flush;
    }
	  
    sleep(3);
    cout<<endl;
    cout<<textoComienzo<<endl;
    cout<<endl;
    sleep(4);

}

void Manager::run(){

    //Marcar la primera entrada al metodo
    primera_entrada=true;

//	 prologo();

    while(continuar_loop){

        ///DIBUJAR ESCENARIO///
        if(primera_entrada)
        {
            cout<<endl;
				dibujar();
				cout<<endl;
            cout<<get_descripcion_estado_actual()<<endl;
            primera_entrada=false;
        }

        ///RECOGIDA DE COMMANDOS CONSOLA///
//	     cout<<"[Escena: "<<escena_actual->get_nombre()<<"]"
//				  <<"[Objetos: "<<escena_actual->get_objetos_disponibles()<<"]"
//				  <<"[Salidas: "<<escena_actual->
//				  <<endl<<">>>";

        cout<<">>>";

        //EXTRACCION DEL COMANDOS Y LOS PARAMETROS
        string entrada_consola;
        getline(cin,entrada_consola);
        //cout<<"Se ha introducido: "<<comando;
        list<string> lista_comandos;
        istringstream iss(entrada_consola);
        do{string sub;
            iss >> sub;
            //					  cout<< "Substring: " << sub << endl;
            lista_comandos.push_back(sub);
        }while(iss);

        if(!lista_comandos.empty()){
            comando=lista_comandos.front();
            lista_comandos.pop_front();
		  }

        if(!lista_comandos.empty()){
            parametro1=lista_comandos.front();
            lista_comandos.pop_front();
        }

        if(!lista_comandos.empty()){
            parametro2=lista_comandos.front();
            lista_comandos.pop_front();
        }

        ///TRATAMIENTO DE COMANDOS
        tratamiento_comandos(comando);

        //Actualizar Objetos
        actualizar_objetos();

        //Actualizar Salidas
        actualizar_salidas();
    }

    //TODO: GUARDAR LA PARTIDA CON TODOS SUS ESTADOS

    //SALIDA DEL JUEGO
    if(contador_mal_comportamiento < 3 )
        cout<<endl<<"GRACIAS POR JUGAR! :),TE ESPERO PRONTO DE VUELTA."<<endl<<endl;
    else
        cout<<endl<<"ERES UN MALEDUCADO, NECESITAS CLASES DE MODALES."<<endl<<endl;
}

string Manager::get_comandos_disponibles()
{
    return comandos_disponibles;
}

string Manager::get_descripcion_estado_actual(){
    string descripcion=escena_actual->examine();
    descripcion+="\n";
    if(escena_actual->get_objetos_disponibles()!="")
    {
        descripcion+="Puedes ver : \n";
        descripcion+=escena_actual->get_objetos_disponibles();
    }
    return descripcion;
}

string Manager::get_salidas_estado_actual(){
	  
    string lista_salidas;

    //map<string,Escenario*> salidas=escena_actual->get_salidas();

	 map<string,pScene> salidas=escena_actual->get_salidas();

    for(map<string,pScene>::iterator it=salidas.begin();
        it!=salidas.end();it++)
    {
        lista_salidas+=it->first;
        lista_salidas+=" ";
    }
    return lista_salidas;
}


//Tratamiento de la línea de comandos 
void Manager::tratamiento_comandos(string comando){

	  //TODO: Create string command's preprocessor to select which comand to invoke by command invoker
	  
    //Tratamiento del comando mal deletrado
    //How to know that comando is in a list of strings
    bool info=(comando==s_exit or
					comando==s_salir or
					comando==s_ayuda or
					comando==s_ver or
					comando==s_inventario or
					comando==s_examinar);
    bool norte=(comando=="norte" or comando=="n");
    bool sur  =(comando=="sur" or comando=="s");
    bool este =(comando=="este" or comando=="e");
    bool oeste=(comando=="oeste" or comando=="o");

	 bool colocar=(comando=="colocar");
	 
    if(info)
        invocador_comandos.exec(comando);
    if(norte)
        invocador_comandos.exec(s_norte);
    if(sur)
        invocador_comandos.exec(s_sur);
    if(este)
        invocador_comandos.exec(s_este);
    if(oeste)
        invocador_comandos.exec(s_oeste);

    bool tirar=comando==s_tirar;

	 if(tirar)
        invocador_comandos.exec(s_tirar);

    bool coger=comando==s_coger;

	 if(coger)
        invocador_comandos.exec(s_coger);

    bool alcanzar=comando==s_alcanzar;

    if(alcanzar)
        invocador_comandos.exec(s_alcanzar);

	 if(colocar)
			invocador_comandos.exec("colocar");
	 
			 			 
    if(comando=="arriba");
    else if(comando=="abajo");			
    else if(comando=="entrar");
    else if(comando=="salir");					
    else	if(comando=="salidas")
			cout<<endl<<"Las salidas disponibles son:"<<escena_actual->salidasDisponibles()<<endl;
    else if(comando=="tiempo")
        cout<<endl<<"Han pasado "<<tiempo<<" segundos desde que comenzó la partida."<<endl;
    else if(comando=="");
    else 
    {
			// TODO: Use regular expresion instead/
        bool hijo=(comando=="hijo" or comando=="Hijo");

        bool puta=(parametro1=="puta" or parametro1=="Puta") or (parametro2=="puta" or parametro2=="Puta");

        bool idiota=(comando=="Idiota" or comando=="idiota") or 
            (parametro1=="Idiota" or parametro1=="idiota") or 
            (parametro2=="Idiota" or parametro2=="idiota");

        bool maricon=(comando=="maricón" or comando=="Maricón") or (comando=="maricon" or comando=="Maricon") or
            (parametro1=="maricón" or parametro1=="Maricón") or (parametro1=="maricon" or parametro1=="Maricon") or
            (parametro2=="maricón" or parametro2=="Maricón") or (parametro2=="maricon" or parametro2=="Maricon");


        bool cabron=(comando=="cabron" or comando=="Cabron") or (comando=="Cabrón" or comando=="cabrón") or
            (parametro1=="cabron" or parametro1=="Cabron") or (parametro1=="Cabrón" or parametro1=="cabrón") or
            (parametro2=="cabron" or parametro2=="Cabron") or (parametro2=="Cabrón" or parametro2=="cabrón");		 


        if(hijo and puta){
            cout<<"Hijo puta lo serás tu, se un poco más serio, o morirás.";
            contador_mal_comportamiento++;
        }
        else if(idiota){
            cout<<"La idiotez de persigue, vas a morir.";
            contador_mal_comportamiento++;
        }
        else if(maricon){
            cout<<"¿Te gusta la sodomía?.";
            contador_mal_comportamiento++;
        }
        else if(cabron){
            cout<<"¿Consientes que tu mujer se acueste con otro?";
            contador_mal_comportamiento++;
        }
        else 
        {
				 
            ;}		
        //cout<<endl<<"Comando inválido, escribe (ayuda)";}
    }


    if(contador_mal_comportamiento>3)
	 {
        cout<<endl<<endl<<"Eres una desgracia humana mentalmente o no tienes la sufiente madurez, así que vuelve tan sólo cuando hayas soluciodado ese asunto. ADIOS!.";				
        continuar_loop=false;
    }

	 	 
	 if(comando!="")
			cout<<endl;
			 
} //

void Manager::clock(){

    while(continuar_loop)
	 {
        int itime = (int) tiempo;
        if( itime % (5*60) == 0 )
        {
            cout<<"\nHan pasado "<<tiempo<<" segundos desde el inicio del juego\n"<<">>>";
        }

        sleep(1); //detiene el hilo durante 1 segundo
        tiempo++;
    }
}

//Actualizar atributos de objetos
//Definir las reglas y relaciones entre objetos
void Manager::actualizar_objetos(){

	  // Compsume events
	  eventsQueue.fire();

/*	  IEvent *event;
	  if(!eventsQueue.empty())
	  {
			 cout<<"Size eventsQueue:"<<eventsQueue.size()<<endl;
			 event=eventsQueue.front();
  	
			 cout<<"Size eventsQueue:"<<eventsQueue.size()<<endl;
			 assert(event!=NULL);
			 Logger::instance().log("actualizar_objetos", Logger::kLogLevelInfo);
			 //cout<<event->message()<<endl;
			 cout<<event->activate()<<endl;
			 eventsQueue.pop();
	  }*/
	  
}
	  
	  
//Genericos: Si un objeto esta usado, hacerlo invisible, para que no se liste en su escenario
//SEGURO??

// Escenario 1: La entrada de la mansion
//    if(escena_actual->Id()==id_escena1)
//	 {
        //Chequear el ladrillo de la puerta
/*			 Objeto *ladrillo=mundo[escena1]->get_objeto(o_ladrillo);
			 Objeto *llave=mundo[escena1]->get_objeto(o_cerradura);
			 if(llave!=NULL and ladrillo!=NULL)
                         if(not llave->get_visible() and ladrillo->get_usado()){
                         cout<<"Una llave dorada aparece ante tu vista."<<endl;
                         llave->set_visible(true);
                         }*/
        //
			
//    }
//}

//Actualizar salidas del escenario
void Manager::actualizar_salidas(){
    //Establecer reglas de activacion de salidas
}

void Manager::dibujar(){
	  escena_actual->pintar();
}
