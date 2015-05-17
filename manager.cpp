#include "manager.h"

using namespace parametros;

Manager::Manager():dt(1.0/60.0),tiempo(0),continuar_loop(true),contador_mal_comportamiento(0)
	  

{
	  //Crear vector de comandos
	  comandos_disponibles="Comandos disponibles:";
	  for(int i=0;i<10;++i)
			 v_comandos.push_back(comandos[i]);

	  //Continuar con el bucle principal del juego
//	  continuar_loop=true;

	  //configurar reloj
//	  tiempo=0; //segundos	  
	  //variables del jugador
//	  contador_mal_comportamiento=0;
	  int id_escena;

	  //CONSTRUIMOS LA PRIMERA ESCENA: TODO:Cargar desde fichero 
	  string nombre="La entrada principal de la mansion";
	  //string escena=nombre;
     //creamos la escena 
	  Escenario *escena=new Escenario(id_escena1,nombre1,descripcion1,observacion1);

	  //insertar escenario en mundo
	  mundo[nombre1]=escena;

	  //selecionamos la escena de arranque del juego. TODO: Cargar desde fichero de salvaguarda
	  escena_actual=escena;

	  //SEGUNDA ESCENA
	  id_escena=2;
	  nombre="El monumento de piedras";
     string escena2=nombre;

	  escena=new Escenario(2,nombre,descripcion2,observacion2);

	  //insertar escenario en mundo
	  mundo[nombre]=escena;


	  //TERCENRA ESCENA: Lapida
	  id_escena=3;
	  nombre="EL cementerio";
     string escena3=nombre;

	  escena=new Escenario(3,nombre,descripcion3,observacion3);
	  
	  //insertar escenario en mundo
	  mundo[nombre]=escena;

	  //ENLAZAR ESCENARIOS ENTRE SI
	  //Id: 1->(2,3) ,2<->1, 3<->1
     mundo[escena1]->set_salida(mundo[escena2],oeste);
     mundo[escena1]->set_salida(mundo[escena3],este);
	  mundo[escena2]->set_salida(mundo[escena1],este);
	  mundo[escena3]->set_salida(mundo[escena1],oeste);

	  //CONSTRUIR OBJETOS
	  int id_obj=1;
	  string nombre_obj="bastón alargado";
	  string descripcion_obj="Es un batón de madera bastante largo, con una empuñadura en su extremo.";
	  Objeto *o_baston=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_baston->set_visible(true); o_baston->set_usado(false); o_baston->set_fijo(false);

	  id_obj=2;
	  nombre_obj="ladrillo";
	  descripcion_obj="Ladrillo saliente en la pared de la casa. Es posible que se puede tirar de él.";
	  Objeto *o_ladrillo=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_ladrillo->set_visible(false);
	  o_ladrillo->set_fijo(true);

	  id_obj=3;
	  nombre_obj="llave dorada";
	  descripcion_obj="Una llave dorada y antigua.";
	  Objeto *o_llave=new Objeto(id_obj,nombre_obj,descripcion_obj);
	  o_llave->set_visible(false);
	  o_llave->set_fijo(false);


	  //INSERTAR OBJETOS EN ESCENARIOS
	  
	  mundo[escena2]->set_objeto(o_baston);

	  //entrada de la mandion
	  mundo[escena1]->set_objeto(o_ladrillo);
	  mundo[escena1]->set_objeto(o_llave);

	  //CONSTRUIR INVENTARIO
	  //inventario.insertar_objeto(objeto);

	  //Construir los comandos y conectarlos al invocador
     ICommand *exit=new Exit(continuar_loop);
	  ICommand *ayuda=new Ayuda(v_comandos);
	  ICommand *ver=new Ver(&escena_actual); //pasar direccion del puntor a una escena
	  ICommand *examinar=new Examinar(*escena_actual,inventario,parametro1); //pasamos direccion al escenario actual y al inventario

	  mapComandos[s_exit]=exit;
	  mapComandos[s_ayuda]=ayuda;
	  mapComandos[s_ver]=ver;
	  mapComandos[s_examinar]=examinar;
	  
	  //construir invocador de comandos
	  invocador_comandos=Invocador(mapComandos);

	  

}

void Manager::prologo(){

	  cout<<endl<<"¡BIENVENIDO QUERIDO JUGADOR! \n\nLA CASA ENVANTADA v1.0"<<endl<<endl;
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

//	  prologo();


	  while(continuar_loop){

			 ///DIBUJAR ESCENARIO///
			 if(primera_entrada)
			     {
						 cout<<endl;dibujar();cout<<endl;
						 cout<<get_descripcion_estado_actual()<<endl;
						 primera_entrada=false;
				  }

			 ///RECOGIDA DE COMMANDOS CONSOLA///
//			 cout<<"[Escena: "<<escena_actual->get_nombre_escenario()<<"]"
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
					lista_comandos.pop_front();}

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
	  if(contador_mal_comportamiento<3)
			 cout<<endl<<"GRACIAS POR JUGAR! :),TE ESPERO PRONTO DE VUELTA."<<endl<<endl;
	  else
	 		 cout<<endl<<"ERES UN MALEDUCADO, NECESITAS CLASES DE MODALES."<<endl<<endl;


}

string Manager::get_comandos_disponibles()
{
	  return comandos_disponibles;
}

string Manager::get_descripcion_estado_actual(){
	  string descripcion=escena_actual->get_descripcion();
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
	  map<string,Escenario*> salidas=escena_actual->get_salidas();

	  for(map<string,Escenario*>::iterator it=salidas.begin();
		  it!=salidas.end();it++)
	  {
			 lista_salidas+=it->first;
			 lista_salidas+=" ";
	  }

	  return lista_salidas;

}





//Tratamiento de la línea de comandos 
void Manager::tratamiento_comandos(string comando){

	        if(comando==s_exit)
					 invocador_comandos.salir();

			  if(comando==s_ayuda)
				    invocador_comandos.ayuda_comandos();

			  if(comando==s_ver)
					invocador_comandos.ver_comando();

			  if(comando==s_examinar)
					 invocador_comandos.examinar_comando(parametro1);

//			  if(comando==s_ver))
//			  invocador_comandos.ver_descripcion();

//			 if(comando=="exit")
//					continuar_loop=false;

//			 else if(comando=="ayuda")
//					cout<<endl<<get_comandos_disponibles();

//					cout<<endl<<get_descripcion_estado_actual();
/*
			 else if(comando=="examinar"){
					if(parametro1=="")
						  cout<<escena_actual->get_observacion()<<endl;
					else 
					   {
						//OBJETO DEL MUNDO

						//Si está en el inventario, lo describes
						  if(inventario.get_existe_objeto(parametro1))
								cout<<inventario.get_objeto(parametro1)->get_descripcion(); 			  		   	   
						//Si está en el escenario actual, lo describes
  					     else if(escena_actual->get_existe_objeto_escenario(parametro1))
							  cout<<escena_actual->get_objeto(parametro1)->get_descripcion();
 					   
						  else
							  cout<<"No se puede examinar eso.";
						}
						  
			      }*/

			 if(comando=="inventario" or comando=="i")
				  cout<<endl<<"Posees lo siguiente: "<<endl<<inventario.listar()<<endl;

			 else if(comando=="norte" or comando=="n")
               {
					  if(escena_actual->get_salida("norte"))
					     {
						  escena_actual=(escena_actual->get_salida("norte"));
						  primera_entrada=true;
				    	  } 
					  else
						  cout<<"No puedes ir al norte.";					
               }

	        else if(comando=="sur" or comando=="s")
               {
					if(escena_actual->get_salida("sur"))
					     {
						  escena_actual=(escena_actual->get_salida("sur"));
						  primera_entrada=true;
				    	  } 
					else
						  cout<<"No puedes ir al sur.";
					
              }

			 else if(comando=="oeste" or comando=="o"){
					if(escena_actual->get_salida("oeste"))
					     {
						  escena_actual=(escena_actual->get_salida("oeste"));
						  primera_entrada=true;
				    	  } 
					else
						  cout<<"No puedes ir al oeste.";
					}

			 else if(comando=="este" or comando=="e"){
					if(escena_actual->get_salida("este"))
					     {
								 escena_actual=(escena_actual->get_salida("este"));
						  primera_entrada=true;
				    	  } 
					else
						  cout<<"No puedes ir al este.";
					}
			 
			 else if(comando=="arriba");
			 else if(comando=="abajo")	;			
			 else if(comando=="entrar");
			 else if(comando=="salir");					
			 else	if(comando=="salidas")
					cout<<endl<<"Las salidas disponibles son:"<<get_salidas_estado_actual()<<endl;
			 else if(comando=="tiempo")
					cout<<endl<<"Han pasado "<<tiempo<<" segundos desde que comenzó la partida."<<endl;
			 else if(comando=="");
			 else 
			      {
					//
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


			 if(contador_mal_comportamiento>3){
					cout<<endl<<endl<<"Eres una desgracia humana mentalmente o no tienes la sufiente madurez, así que vuelve tan sólo cuando hayas soluciodado ese asunto. ADIOS!.";				
					continuar_loop=false;
			 }


			 if(comando!="")
					cout<<endl;
			 
}



void Manager::clock(){

	  while(continuar_loop){

			 int itime=(int)tiempo;
			 if(itime%(5*60)==0)
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

//Genericos: Si un objeto esta usado, hacerlo invisible, para que no se liste en su escenario
//SEGURO??

// Escenario 1: La entrada de la mansion
	  if(escena_actual->get_id()==id_escena1){
			 //Chequear el ladrillo de la puerta
/*			 Objeto *ladrillo=mundo[escena1]->get_objeto(o_ladrillo);
			 Objeto *llave=mundo[escena1]->get_objeto(o_llave);
			 if(llave!=NULL and ladrillo!=NULL)
					if(not llave->get_visible() and ladrillo->get_usado()){
						  cout<<"Una llave dorada aparece ante tu vista."<<endl;
						  llave->set_visible(true);
					}*/

			 //



	  }

	  //if(



}

//Actualizar salidas del escenario
void Manager::actualizar_salidas(){

	  //Establecer reglas de activacion de salidas

}



void Manager::dibujar(){

	  int id_esc=escena_actual->get_id();

	  if(id_esc==1){

 cout<<" .0000000000000000000KKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXXNNNXXWNNWWMMMWNNNNNNNNWWMMMMMMM"<<endl;
 cout<<" .0000000000000000KKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXNXXNXNNNWWWWWWMMMWNWNNWWWWNWWMMMMMM"<<endl;
 cout<<" .00000000000000KKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXXNWWMWNNWMMMMMMMMMMMWNWMMMMWMMMMMMMMM"<<endl;
 cout<<" .0000000000000KKKKKKKKKKKKKKKKKKKKXXXXNWXKXXXXXNNNNWWNNWMMMMMMMMMMMMWWMMMMMMMMMMMMMM"<<endl;
 cout<<" .0000000000KKKKKKKKKKKKKKKKKKKKKKXXXXXXXK0XXXNNXXXNNNNNWMWWMMMMMMMMMWWWWMWMMMMMMMMMM"<<endl;
 cout<<" .000000KKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXXKkOKXXWWWNNWWWWNNWMMMMMMMMMMMWWNNWNWMMMMMWWMW"<<endl;
 cout<<" .xdkkkxxOKKKKKKKKKKKKKKKKKKKKKXXOOOkkxkdollclO0OOKNNNNNNNNWWMMMMMMMMWWWWWXKXKXKK0000"<<endl;
 cout<<" .00KKKKKKKKKKKKKKKKKKKKKKKKKKXXXXX0oc::;,'''loOKXXNWNNNNNNWWWMMMMMMMMMWWWWWWWWWWWWWW"<<endl;
 cout<<" .KKKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXXK:........oklkXXXXXNNNNNWWMMMWMMWWMMMWWWWWWWNNWWWW"<<endl;
 cout<<" .KKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXXKc..',.....,kkoKXXXNNNNNNNWWWWWMMMMMMMMMMMMMMMWWWMM"<<endl;
 cout<<" .KKKKKKKKKKKKKKKKKKKKKKKXXXXXXXX0;...','.....,l:dxNNNNNNNNNNWMWWMMMMMMMMMMMMMMMMMMMM"<<endl;
 cout<<" .KKKKKKKKKKKKKKKKKKKKKXXXXXXXXXx'............',;xoXNNNNNNNWWWMMMMMMMMMMMMMMMMMMMWMMM"<<endl;
 cout<<" .KKKKKKKKKKKKKKKKKKXXXXXXXXXXk:....''..''....'..:xNNNNNNWWWWWMMMMMMMMMMMMMMMMMMMMMWM"<<endl;
 cout<<" .KKKKKKKKKKKKKKKXXXXXXXXXXXx,'...................,xXNNWWMMMMMMMMWWWMMMMMMMMMMMMMMMMM"<<endl;
 cout<<" .XXXXXNNXKKXXXXXNNWWNNWWNNNN0:..,,;,;;:l:ccc;,ol:''lKWWNWN0kkKWWXWWWWWWWWWWWWWMMMMMM"<<endl;
 cout<<" .KXXXXXNXXXXXNNNWWWWMMMMMWWWWX....':::;::;;::,dxc;.'lkNKKl;,,o0XkXMWWWWWWWWWMMMMMMMW"<<endl;
 cout<<" .XNXXXXXXXXNNNNNNWWWMMMMMMWWMK,:lc:''','.,::c,kKxo,.',cl:;,,','':dKXWWWWWWWWWWWMMMMM"<<endl;
 cout<<" .XXXXXXXXXNNXXXNNWWWWWWWNWNWWx;ll'.':ox:.':cc,xo.......',,'.....'dokNWWWWWWWWWMMMMMM"<<endl;
 cout<<" .XXXXXXXXXXXXXNNWWWK0kkkxdool;:cc'..lod;.':::,c'......'cdo,......'ooONWWWWWWWMMMMMMM"<<endl;
 cout<<" .XXXXNNNNXNNXXXNNNd,'''.......;::..'ccc,.':c:,,'.......:cc'........coOWWNK0NWWWMMMMM"<<endl;
 cout<<" .NWWWMMMMMMMWWWNNk,.,ol'......,:;...llo,.',,,'.........'''.........',oOKo''oWWWWWWMM"<<endl;
cout<<"...XNNNWWWWWWWWWW0:...;dl.......'''...''....................'''''''''''''',,;;0WWWWWWW"<<endl;
cout<<"...kkK00OkKNNNN0c.....,c'.......................  .........................;::kK0KOO0O"<<endl;
cout<<"...WMMMMMMWWNk:......................................................''''...;lNWWWWWWW"<<endl;
cout<<"...NNNNNNOxl,'............ .....''.'',,,,;,:;;;''...''',,,,;;;;;;:;::::,;....:xOOWWWWW"<<endl;
cout<<".'.XXXXXNXkc,...............':::::::;,,;;:ccccc,''.;::::;,,',,;::c:c::;;o,.......c0WWW"<<endl;
cout<<"'..XXXNNNNNN0''',,,,,,,,,;;,,:;;;;,,;cc;,,,',;:,'..;:;''';:::,;;;::;:;::xd...'''',,xWW"<<endl;
cout<<".'.NNNNNNNNNK,::::;;'''''',;','',,''cdd:',;c;,,''..;:;..'odod,,,,c:::;:;xl'.....',.,kW"<<endl;
cout<<"...NNNNNNNNNO,::::'..;co,..,,,,oo;''ldl:,'coc,:''..,;,...llcl,'',;,;:;;:dc,.....';.';O"<<endl;
cout<<"...NNNNNNNNNx;::::...oox'..,,;,ol,,.;;,.'.,;,.'.'..,,'...lolo,,',:;;;;;;l:;.....';,'.;"<<endl;
cout<<"...NNNNNNWNNl::::;..'lcl.....'''..,'c:;';;coo:,'::::;;.',loco,'',::;;;;;l::;:,,::col;o"<<endl;
cout<<"  .NNNNNNNNW:::::'..'dll...'''','''',,'';,,;;;,;,,,'''',:lc,,'',;:;::::;l:c,;''oolco,l"<<endl;
cout<<",..NXkxxdddo,;,,,''',,''''''.............................,;;,,;;;;;;;;;,ldl''',co,,;''"<<endl;
cout<<"...KKo'......................................................'',;;;;;;;'lxd;;,,:l';','"<<endl;
cout<<".. ............  .....................................'........',,,,',,':ko'','.'.;:,'"<<endl;
cout<<".  ...  ......    ........  .....................  ..,.......'......',,':d;..'.......'"<<endl;
cout<<";. c'..  .. ..... .......  ..........................,.....''.......'';';l;..........."<<endl;
cout<<".. l;. ...........................,,''''......'......c,.'..'''',',;',,,',:;'......'..."<<endl;
cout<<".. ... ........'.c......o;...........................ll,''','''l;cd,,;;,,:;'....'....."<<endl;
cout<<"'. ,'.......''.:'x'..'.,d;....,,.        ..;.........ll;'',,,''c;:l,',,';:;,....'..'.."<<endl;
cout<<".. ;;.;lc..''.';,o..''.,l,.''.;,.        .':.''.'....cc;'',,,''ccco;';;,,;;;.''.;'.,.."<<endl;
cout<<".. ...  ......'',:..''.:l;.,o,;,.       ...'.........,c,..,,,''llcd;';;,.;;:....;,.,.."<<endl;
cout<<"'' ....... .....,,..'..:c,.,c:'..  .. .',............,,.....'..;;;:,.';;',;:....',.,.."<<endl;
cout<<" . '.......,'.''''...'.....;,lc:. .',,,,'............;,...............',.;:;.......','"<<endl;
cout<<"'. ,...'..';;',.,,...,..'.';;0;,c;:c,,',:; ..........';;.....'''',,,,,',':xd,.',....,'"<<endl;
cout<<".. ',''''''',';;.'.''''''''';xc::;,c:::,:d:,'..:;....,;,,''...';:d:......;dx..'''..:od"<<endl;
cout<<".. ,;:;;,,''..','.............';cl;:,':;:k;:;;,;d'''.'c;,'',,c:c;cd......:cl'',;;':okk"<<endl;
cout<<".. ;l:;c:;'.,lood;...............':cc;:odKko:c:;O,,::co;,'';,c;',lx',loc..lc:;c::c:::l"<<endl;
cout<<".' ','',,''.ldkOX,................',c:ldx0xc::,'x;,:ooll:'.';;:;:ccc;;ld'.;::;::;:cc:l"<<endl;
cout<<".' ;,'.',.'',odxo''..,:llo:lc,.';::cccloxxooo:;:c::;lodllccclodxxkxkoclxxxxxxdooooc,:c"<<endl;
cout<<".. ::ccl:::c::cooolc;'.,,;colc;;,'';cccldxddddddddddddddddollooodxxxdodddddddddooo;;cl"<<endl;
cout<<".. :::::lc:clc::c:ll::cllloollccclc::llllodoooooooooooooodoc:codxOkxoccloooolooooc,,::"<<endl;
cout<<".  ;;,:lcllodddddxxcc::cllllcc:c:ccc:;,,,;codoooodooooooooc:;:ldk0OOdccclccol:cclc,,::"<<endl;
cout<<".. c:c:;'coooddxxkl,;','.,:cllllcccoollccccclooololooddlcclc:cllxkkko:;;c:;;cc::c:'.,;"<<endl;
cout<<";::;,,;:lcloooo;;c:,;:cclllcccodxdoollllllcllc:ldoll:loll;coodkkOxlcclllooooc:;,,,."<<endl;

	  }
	  else if(id_esc==3)
	  {

cout<<"xkkdl'cOx'   ...  .okxdlllooooxxOOOkOK0x0KKOKXKxX0ooodddO0kdxOOO0OdldoxxxxkkxodxkOxxx0KkKXKNNWWMWNWNK0O0KXXX0O0KKKXXXXXKkxO0KKKKKXKKKKKKKKKK0OkkOO0OO00000N"<<endl;
cout<<"o00OO:;k:.  ...  .:KXX0kk0O0KKXNWMMNNXN0k0NNNNNKKWNKNNNK000K0o:dxk00kok0kkdoxkOOxdxkkO0koxO000OO0O0KKXNWWWWNKKXNNXXXX0OOKXXXKKKKKKKKKKKKKKKKK00OO000KKK00KW"<<endl;
cout<<"'0KXKc...  ...   .lkOOkdxxdddxO0KKXXXWWNX0O00XXWKO0NNNXKK00KX0kdONNKKXK0kdk0KXXXNK000KXKKOxKNXNNXNNNNWMWMWWNK0NNNXKOOKXKKXKKKKKKKKKKKKKKKKKKKKKKK0XWWWNXXXW"<<endl;
cout<<" 'k0Xd.   .x:..  .loodc'OKKKKKKKKKK0O0OkxOOkxdxkxclxodkOOO0K000kclodxollcxxkxddxxkkxO000KXKOO0KXNWWMWNXNWNX0Odxkxkk0XXXXKKKKKKKKKKKKKKKKKKKKKXXKKNWMMWWWWWW"<<endl;
cout<<"  lNNl    d0,.   .xNK0k:;dOKXXKXK000kOKKO000kkkxdxoooc;:lllllodccoccocd0OOXNNXKXXXKKOdkO000K0OdoOOOOOkkkxdxkkO0XXXXXNNXXXXXXXKKKKKKKKKKKKKXNWNXXNNWMMMWWWWW"<<endl;
cout<<"  .ll.   ,Od.     .'''....''''.',:clc..,;llooloddddokOOOKK0OxOKO0KKOdkKOkxOKKXXNNNNNNNKKXNNNNWW00NWWWWNNNNWWNNNNNNNNNNNNNXXXXXXXXKKKKKXXXNWWWWNNNWWWWWWWWWN"<<endl;
cout<<"        .kx'     .'ldxdcxxoldl;lcdkkdd:,l0KNNNXXNWN00NXXXKKKK00OOXXKKdx0KkoxOOkOXXNNNNNKNNNNWWWWKKWWWWNWWWWWWWWWNNNNWWWWNNNXXXXXXXXXXXXNNNWNNNWWWWWWWWWWWWX"<<endl;
cout<<"       ,0x'.     ,ooxoldxxkkxoldlodlccc;.oO0KK0XNNNXOKKKKKKKKKXX0XNNKO0kx0K0kxxkO0KKKKKKKKKKNWNNN0XNNNNNNWWWMWWWNNNNWWWWNNNNNNNNNNNNNXXNNNWNNNNWWNNNNNNNNNK"<<endl;
cout<<"      .::...   .;0XKkxKXK00KK0OKKKKKOxxko.ldxdx0KKXX0k0KKKKKKKKXK0XXXK0KK0OO0KOod0XXXXXXNNXXWWWWNXONNNNNNNNNWWWNNNNNNNNNNNNNWWWWWNNNNNNNNNNNNNNNNNNNNNNNNNO"<<endl;
cout<<"      ....    .o0kOxdKK0O00XKKkKKKKKKKKO0l,xKKKKK00Okkk0KKK00KKKKkKKKKKKXXXKkkk00xkk0KXXNNWWNNNNNXK0KKXWNWNNNNNNNNNNNNNWWWWWWWWWWWNNNNXNNNNNNXXXXXXXNNNNXXk"<<endl;
cout<<"            ..xNNKkdxk00KXXKKKO0KKKKKKKK0OklcoxO0000kOOOO000O0000OOKKKKKKKKK000OOOO0kxxk0KXNNWWWXKXNXXXNWWWWNNNNNNNNNNNWWWWWWMMMMMWWNNXXXXNNXXXXXXXXXXXXXXO"<<endl;
cout<<".          .'k0KKXKKXNXKXXXKKK0O0K00KKKK0000Okdlc,:l:codokkkkkO0KKOOKKKKKKKKKKKKXX0O00O00000KK00XNNNNNWXXXKKXKXNXXXNWWWWWWWWWMMMMWWWWNNXXKXXXXXXXXXXXXXXXK0"<<endl;
cout<<"           .dWWWNXXXNNXXKKK0KK00OO0KKKKKKKKK0K0K0ldxkxO0xldox0K000OkO00000000KKKKXNNNXXK0000KXXXNMWWWWWNNNXNNNXNXXXNWWWWWWWWWWWWWNNNNNXXXKKKKKKKKKKXKKXXKKx"<<endl;
cout<<"          :KNNWWWWNNNNNXXXXKXXKKKO0KKKKKKKKKKKK0OdKK0kk0OO0000000000Oxk000000KKKKKXNWWWMMWWWWWWWWWWWWNNNNNXXXXXXXXXXNNWWNNNNNNNNNNNNNXXXKKK0000KKK0KK000OkO"<<endl;
cout<<". .      .xXXXNNNNNNNWWWWWWWWWWWNNXKKKKXXXKKKKKKOk000OkO00000000000OOOOkkO000KKKKXNWMMMMMMMMMMMWWWNNNNNNNXXXXKKKKKKKKKKKKKKKXXXXXKKKKKK00000000000OO0Okxxox"<<endl;
cout<<"....      oXXXXXXNNNNNNNNNNNNNNNNNNNNNNXXNNNNXXXXKKK000000000000000KKKKKK00000KKKXXWMMMMMMMMMMMWWNNNXXXXXXKKKKKKK00000000000000000000000000000000OOkxkxolll"<<endl;
cout<<",..       ,0XXXXXXNNNNNNNNNNNNNNNNNNNNNNWWNNNNNNXXXXXXXXXXXXXXXXNNNNWWWWMWWWWWWMMMMMMMWWWWWWWWWNNNNNXXXKKXXKK0000000000OOOOOOOOO000000000OOO0OOOOOkxdoddc:c"<<endl;
cout<<":,'.      .cKXXXXXNXNNNNNNNNNNNWNNNNNNNNNNNNNNNNNNWWWMMMMMMMMMWMMMWWWWWWMMMMMMMMWWWWWNNNNNNNXXXXXXXXXKKK000000OOOOOOkkxdooOOOOOOOOOOO000000OO00OOOkdlcc:ccc"<<endl;
cout<<"x;,.      ..kKKKKKNNNNNNNNNNNNNWWWNNNNNNNNNNNNWWNNWWMMMMMMMMMMMWWNNNNXNNNNNNNNNNNNNNNXXXXKKKKKKK00000000OOOOOOOOOOOc..   .xOOOOOOOOOOO00000000OOOOkdo:;;,,:"<<endl;
cout<<"0c;.       .lNNXNNNNNNNNNNNNNNNNWWNNNNNNNNNNNNNNNNNNNWWWWWMMMWWWNNNXXXXXXXXNNNXNXXXXXXXXXKKKKK00000000OOOOOOOOOOOOOo     .oOOOOOOOO00000OOOOOOOkkkxoloc,;;;"<<endl;
cout<<"Xkc,. .    .,XNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNXXXXXXXXXNNNNNNNNNNNNNNXXXXXXXXKKKKKKKKKKKKKKKKKKx.     .lO0O000000000OOOOOOOOkxxdodlc;,,"<<endl;
cout<<"X0o;...    ..kNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNKkKNNNNNNNNNNNNNNNNNNNNNNNNNWWWX:.       '':KKKKKKKKKK000000OOkkOkxoolc,"<<endl;
cout<<"NNk:'...    .,KNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNKkXNNNNNNNNNNKl0NNWNNNNNX0kOXNNNNNXXXXNNNNk;,.          .OKKKKKKKKK00000OOkkxxxxxxoc;"<<endl;
cout<<"NNXl,...    ..lXNNNNNNNNNNNNNNNNNNNNNNWWWNNNNNNNNNNNNNNNNNNNNNNNNNNNNNKxXNNNNNNNNNNXoKNNNNNN0o;...,o0NNNNXXNNNNNk...          .dKKK0000000000OOkkkxoolll,.'"<<endl;
cout<<"NNNk;...     ..kNNNNNNWWWWWWWWWWWWNNWWMWWNNNNNNNNNNNNNNNNNNNNOlKNNNNNNKdXNNNNNNNNNNXdKNNNWXx:.......,dXNNNNNNNWWK'..        .k0KKKKKKKKK0KKKKK000Okdoc;.. ."<<endl;
cout<<"NNNXc,..     ..cNNWNNWWWWWWWNNNNNNNNNNNNXKXNNNNNNNNNNNNNNNWWO;.;ONWWWWXdXNNWWWWWWWWXlOWNNXl,..........dNNNNNNWWWW0Ox'       dXXKKKKKKK000000000OOkdxx;..  '"<<endl;
cout<<"NNNNx'....   ...ONNWWWWWWWWWWWWNNXXXXXk:'..,cxKNNXNNNNNWWWWNl,..,XNNNNKc0NNNNNNNWWWKcxNNXc......   ....kNNNNNNNNNNNNXo      xXXKKKKKKKKKK00000Okkxxo:..   '"<<endl;
cout<<"NNNN0;,...   ...cNNNNWWWWWWWNNNNNXXN0c.........l0XXXXNNNWNNNc,..xNNNNN0;ONNNNNNNNXN0cdNNk;. .... .  ...;WWNNNNNNNNNXXO...   cKKXXXXXNNNXKKKKOOkko::'...   '"<<endl;
cout<<"XNNNKc:,..     .'KNN0dk0NNNNNNNNXNN0:...........'OKKKXXNNNNNl,..kXNNNN0;xNNNNNXOkKN0loNNd,.  ...    .. .kNNNNNNNXXXXX0'..   '0KKXXXXXXXXXXKK0kxl;'....    ."<<endl;
cout<<"KXXXOc;'...  .  .xNNNO;oNWNNNNNNNNNo....  .  ..  ,KNNNNNNNNO;,...;0NNNO;cOokNK:..'O0llN0;...  ... ...   :0NXKXOo;;lKXX;      OXXXXXXNX0dlxKXKXk:'....     ;"<<endl;
cout<<"0KKkc::,..      .'l0NK:cokNNNNNWNW0;......       .cXNNNNNOl;;......;kNk:,;;:d;....,occKK;..    ......    'cdKk,....'ONo      oNNNO;o0l'...;OOxc,....      ;"<<endl;
cout<<"OOd:.:l;'.       .,dOl',.,loONNWNNO,..  ...   .   .'o0KKd..',..   .dXNk:;::c'......'c:dXc::.               :Oc......,Xk.     ;XNO, ,;.........,,....       "<<endl;
cout<<"x,,'.lo:'.       .,;','.. ..,clKNNO;. ....... ...    .:c;..,;;... .,Okc,..,.........'''d:::. .         .. .:d,.......k0..    .OXKl.;. ....   .''....       "<<endl;
cout<<":.;,.cc:..       ....,'.   .....ll,,. ............    ..;;.:::'.....:cc;'',...........'''cl.           ,o..oo........cK,      ,lOxc................        "<<endl;
cout<<",:,'';c:..        .':,.'. .,'...',';' ........  ..     .,;.ccc,..'....;'',:'. .....,;,,:;lc.           ,l..xk........kK'.       ;oc.........,.':'..        "<<endl;
cout<<";:.'.,lc'.       .''cc,;. .'...'''';; .... ..          .,'.ccc,';.......;:c........,,';',lc.. .        .. .dOc......'k:.       .cc;.........,.'c,.         "<<endl;
cout<<",;.'',ol,..      .':cc,;. .c,...,,,,:..... .. .        .'.'ccc,;........,cc.. .   .,c,;,;lc.           ..  .,c.......:c.        ':,.........;.'c'.         "<<endl;
cout<<",;';''ol;.  ..   ..,:c,:' .,'.  .''';'.........  .     ....cc:';.......,',:....... 'l,;;;o:.           ...  .:...........       ...........',.',.          "<<endl;
cout<<",;;:.'ol;. .... ....'.,:, .... .....,:....  ....       ..;:ccc;,.......;.,'.       'l'..;l;            ...  ''................      ..........'..          "<<endl;
cout<<";,:;.,oc,.....    ....;:'    .......'c'.........  ..   ..cclccc'.......::'.        .:...;l,             ....''............           .........'.           "<<endl;
cout<<":,:,.;oc'....    ...c:'.      .......:;............. ...,,,,,;:.........'..        ..;'.:o;  ...  ... . .,..;'..''......              ..........           "<<endl;
cout<<"::c;.co:,,...    ...',...........,,,;::................':;;;;:;',..                .;c..:c,...... .......'..,'.''..........            .....''.            "<<endl;
cout<<":cc:,ol:c,..     ..''''.'''''''',,',,,c'...............''',,c;...               ... ...,lc'...... .......'..,:;c,..........            .   ....            "<<endl;
cout<<"::::co:c:..      ..''''''''''''''''''':,...............',',,;..             .. ........;l,. ..... ..  ....',:lll............                 .            ."<<endl;
cout<<"''',ll:l;.       .'''''''''''''''''''',;...............,;;,'.             ........,,,,,:c' .,cc:,....  ...',clll.  ........                 ..            '"<<endl;
cout<<"..',:::,.         .'',,''','',,,'''',,,;.. ...........'::;;,.......          .....',''':c, .:l;,'....'''...',,,,'.........                  ..            '"<<endl;
cout<<"'''.'....         ............''...''..'. ............,;;;,;'.....            .. ..',,,:c,.,oc;'....lxoc,....................              ..              "<<endl;
cout<<"....'..........................................'.....'';;,,,'..            .      ...',,;;'','.   .cxdo:'............';;,,.   ...............             ."<<endl;
cout<<".....''..........................''.'''..'''''.''.....';,,,,,...............          ....',;:c'..,lc:;;;..   ..    .         .....'''''''..              ."<<endl;
cout<<"................................'''''''''',',''',,'''',,'',,,',,,,,,,'',,,''',',,;,,..',,,;,;;;,,;,',;;,,.            .... ........',,::;,'.              ."<<endl;
cout<<".......''.'.'''','''''',,''''''''''''''''''''.'.''''''''''''''''''''''',''','''''''''''''',,,,,,,'','''''....''..''''',''',''''''',:::cccc;...            ."<<endl;
cout<<".........'',''''''''''',','''..'.'''''''',''''..'',''''''''''''''''''',,,,'''''''.''''''.'',,',''''''''''',''''''''''''''''''.....';;;;;;;;;'.            ."<<endl;
cout<<"....''''''''''''''''','''''.''''''''','','''',,',,,,,,,,,,,,,,,,,,,,,,,::,,,,,,''''','''.'','''',',''',,,,,,,,,,'''''''''''''''''''''''''''''.............."<<endl;

	  }
	  else if(id_esc==2)
	  {

cout<<"..........................      ......................................................................................                             "<<endl;                       
cout<<"........................................................................................................................                           "<<endl;                       
cout<<"''.....................................................................................................................                            "<<endl;                       
cout<<",''''....................................................................................................................                          "<<endl;                        
cout<<",,,''''....................................................................................................................                        "<<endl;                        
cout<<";,,,,'''''..................................................................................................................                       "<<endl;                        
cout<<";;;,,,,''''''................................................................................................................                      "<<endl;                        
cout<<";;;;;,,,,,''''''.............................................................................................................                      "<<endl;                        
cout<<"::;;;;;;,,,,''''''''.....................................',;:::;;,,''.......................................................                       "<<endl;                        
cout<<":::::;;;;,,,,,,,,,'''''.............................,coxkOkxdol::;;,,,,,''........................................:looollc::;,,''....              "<<endl;                        
cout<<"c::::::clllcc:;;;,,,'''''''......................'lkKKK0Okdolc:;,,,,,;;;;,,'....................................;XXKKOOxdoc::;;;;,,,,,'.           "<<endl;                        
cout<<"cc:coxxdl:;;;;;;,,,,,''''''''''''''''''''''''''''kXXXK0Okdlc:;,,,,,,,,,;;;,,....................................;XXKK0kxol::;;;;;;;;;;;,.          "<<endl;                        
cout<<",cxOkdc:;;;;;;;,,,,''.''''''''''''''''''''''''''lXXXK0Okdol:;,,,,,,,,,,,,,,''....................................,dOOkxol:;,,,,,,,,,,''.           "<<endl;                        
cout<<"o0Oxl:;;;;;;;,,,''....',,,,'''''''''''''''''''''lXXKK0kxdoc:;;,,,'''''''''''..................................;lxkO00Okxdl:;,''.......             "<<endl;                        
cout<<"0Oxl:::::;;,,'......'',,,,,,'',,,,,,,''''''''''',o0K00Okxdocc:;,,,''........................................;0NXXXXKK00Okdol:;,,''',,'.            "<<endl;                        
cout<<"Okdllcc::;,''''',,,,,,,,,,,''',,,,,,,,,,'''''''''';lxkOOkxdlc;,'............................................kNNNNXXXK00kxdolc::;;;;;;;;'           "<<endl;                        
cout<<"ldddddollc::::;;;,,,'''.....',,,,,,,,,,,,,,,,,,;;:clloxxxxdolc:;,,''''''''''''..............................:KNNXXXKK0Okdolc:::;::::::;'           "<<endl;                        
cout<<"ccccokOkdolc::;,'........'',,,,,,,,,,,,,,,:ldxOOOOkkxxdoolcc:::;;;;;;;;,,,,,,,,,,,,,''........................:x0KK0Okxdlc::;;;;;;;;;,..           "<<endl;                        
cout<<",;;o00kxdolc;;;,,,,,,,,,,,,,,,,,,,,,,,;ox0KK00OOkxxdolcc:::;;;;;;;;;;;;;;;;;;;;;;;;;;;,'...................';:clok0Okxdolc:;;,,,''''...            "<<endl;                        
cout<<"'''ckOOkkxxxxddol::;;,,,,;;;;;;,,,'',dKXXKK00Okkdollc:;;;;;,;;;;;;;;;;;;;;;;;;;;;;;;;;;,,...............ckKXKKKKK000OOkxdoc:;,,''',,,,,,.          "<<endl;                        
cout<<",,'';okOOOkdlc:;;;;;;;;;;;;;;;;;,,''xNXXKK0OOkddlc::;;,,,,,,,,,,,,,;;;;;;;;;;;;;;;;;,,,,'..............lXNXXXKKK00OOkkxdolcc:;;,,;;;;;;;;.         "<<endl;                        
cout<<"',cx00Okxoc:;,,,,;;;;;;;;;;;;;,,''.cXXXKKOkkxdlc:;;,,,'''''''''',,,,,,,,,,,,,,,,,,,,,'''...............'x0KK000Okkxddoolc::;;,,,,,,,,,'..          "<<endl;                        
cout<<":OKKOkdoc;,,,,,,,,;;;;;;,,,,,''..',lXXK0Okxxolc:;,,'''''''.''''''''''''''''''''''''.......................';::clodoolcc:;;,'''.......              "<<endl;                        
cout<<"OK0kdlc;,''''''',,,,,,''''....',,;;;xKK0Oxdolc:;,,''''.....................................................,coxOOkkxdoolc:;;,'''........           "<<endl;                        
cout<<"xOxo:;,''..''''''...........''',,,,,,cxOkxdolc::;;,,,'''''''............................................'o0XKKKKK00OOOkkxdoolc::;;,,,,,,'..        "<<endl;                        
cout<<",ccc;;;,,,,,'.....   .................',:loddoolcc::;;,,,,'''..........................................;KXXXXXKKKK00OOkkxdoolcc::;;;;,,,,,,'       "<<endl;                        
cout<<"'''''',,;::;,'..........'''''''''''''''''..'''',,,;;::;;,'...........................''''''........    kXXXXXXXKKK00Okkxddolcc::;;;;;,,,,,,,'      "<<endl;                        
cout<<"'''';ldkkxdolc:;;,,,,,,,,,,,,,;;;,,,,,,,''.',;:loxxxdoc:;;,'''...............''''''''',,,,,,,,,,''..   oXXXXXXXKK00Okkxdollc::;;;,,,,,,,,,,,,.     "<<endl;                        
cout<<"'';oO000Okxdolc::;;;,,,,,,;;;;;;;;;;;,,;cokO000OOkkxddollc:;;,,'''''''''''''''''',,,,,,,,,,,,,,,,,,'.  .xKKKKKKK00Okxxdolcc:;;,,,,,,,,,,,,,,'      "<<endl;                        
cout<<".:OKK00Okxdolc::;;;;,,,,,;;;;;;;;;;;:ok0KK000OOkkkxddoollc::;;,,,,'''''''''',,,,,,,,,,,,,''''','''''..   ;x00000Okkxdollc:;;,,,''''''''''''.       "<<endl;                        
cout<<".xKK0OOkxdol:;;;,,,,,,,,,,;;;;;;;;oOKKKKK00OOkkxxddoollcc::;;;,,,,'''',,,',,,,,,,,,,'''''''''''''.....    .,dkkkkxxdollc:;;,,'''''''''''...        "<<endl;                        
cout<<".d00Okxdolc:;,,'''''''''',,,,,,,l0XKKKK00OOkkxxddoolcc:::;;,,,,,,'''','',''''''''''''.................';cooddddddddoolcc:;;;,,,,''''....           "<<endl;                        
cout<<" .dkkxoll:;,''............'..',xXXXKKK00OOkxxdoolcc::;;;,,,''''''''''''''''''''.................. .;oxkkkkkkkkkkkxxxdoolc:;;,''...........         "<<endl;                        
cout<<"   ,lll::,'...................lXXXKKK00Okxxdoolc::;;,,,'''''''...'''.'................            ckOOOOO0OO0OOOOkkkxxxddollc:;;,'''..........     "<<endl;                        
cout<<"     ..'''.........           oXXKK00Okkxdolc:;;;,,'''............................               .kO000000000000OOOkkkkxxxddoollcc::;;,,'''''''..  "<<endl;                        
cout<<"                              .OK00Okxddol:;;,,''..........................                       oO000KKKK0000000OOOOOkkkkxxddooollcc::;,,,,,''''. "<<endl;                       
cout<<"                                ckkxdolc:;,'''................                                    .lkO00000000000000OOOOOkkkkxxddoollc::;;,,,,,,,,, "<<endl;
cout<<"                                 .,cc::;,''...........                                              .:oxkkkOOOOO000OOOOOOOOkkxxddoolc:;;;,,,,,,,,'''"<<endl;                      
cout<<"                                     ...........                                                       .';coodxxxxkkkkkkkkxxxdddolc:;;,,'''''''''..."<<endl;                      
cout<<"                                                                                                            ..',;cllloooooooollc::;,''............  "<<endl;                       
cout<<"            .                                                                                                  p     ....'',,,,,,''.......           "<<endl;                       
cout<<"                                                                                                                                                    "<<endl;                       
cout<<"                                                                                                                                                    "<<endl;                       
cout<<"                                                                                                                                                   "<<endl;                        
cout<<"                     .   ..                                                                                                                        "<<endl;                        


}



};

