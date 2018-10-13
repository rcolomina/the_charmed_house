#include "invocador.h"

// Return: -1 Error, 0 Ok, 1 Bad Behaviour
void Invocador::exec(string command,
		     string parametro1,
		     string parametro2){
     //,list<string> params){    
     
     //TODO: Create string command's preprocessor to select which comand to invoke by command invoker	  
     //Tratamiento del command mal deletrado
     //How to know that command is in a list of strings
     bool info=(command==s_exit or
		command==s_salir or
		command==s_ayuda or
		command==s_ver or
		command==s_inventario or
		command==s_examinar);
     
     bool norte=(command=="norte" or command=="n");
     bool sur  =(command=="sur" or command=="s");
     bool este =(command=="este" or command=="e");
     bool oeste=(command=="oeste" or command=="o");     
     bool colocar=(command=="colocar");
     
     if(info)  mapComandos[command]->execute();

     if(norte) this->exec(s_norte);
     if(sur)   this->exec(s_sur);
     if(este)  this->exec(s_este);
     if(oeste) this->exec(s_oeste);
     
     bool tirar = command==s_tirar;

     if(tirar) this->exec(s_tirar);

     bool coger = command==s_coger;

     if(coger) this->exec(s_coger);

     bool alcanzar = command==s_alcanzar;

     if(alcanzar) this->exec(s_alcanzar);

     if(colocar) this->exec("colocar");
	 

     
     if(command=="arriba");
     else if(command=="abajo");			
     else if(command=="entrar");
     else if(command=="salir");					
     else if(command=="salidas")
     {
	  pScene escena_actual=mapComandos[s_norte]->getCurrentScene();
	  string salidas_disponibles = escena_actual->salidasDisponibles();
	  cout<<endl<<"Las salidas disponibles son:"<<salidas_disponibles<<endl;
     }
     else if(command=="tiempo")
	  cout<<endl<<"Han pasado "<<tiempo<<" segundos desde que comenzó la partida."<<endl;
     else if(command=="");
     else 
     {
	  // TODO: Use regular expresion instead/
	  bool hijo=(command=="hijo" or command=="Hijo");
	  
	  bool puta=(parametro1=="puta" or parametro1=="Puta") or (parametro2=="puta" or parametro2=="Puta");
	  
	  bool idiota=(command=="Idiota" or command=="idiota") or 
	       (parametro1=="Idiota" or parametro1=="idiota") or 
	       (parametro2=="Idiota" or parametro2=="idiota");
	  
	  bool maricon=(command=="maricón" or command=="Maricón") or (command=="maricon" or command=="Maricon") or
	       (parametro1=="maricón" or parametro1=="Maricón") or (parametro1=="maricon" or parametro1=="Maricon") or
	       (parametro2=="maricón" or parametro2=="Maricón") or (parametro2=="maricon" or parametro2=="Maricon");


	  bool cabron=(command=="cabron" or command=="Cabron") or (command=="Cabrón" or command=="cabrón") or
	       (parametro1=="cabron" or parametro1=="Cabron") or (parametro1=="Cabrón" or parametro1=="cabrón") or
	       (parametro2=="cabron" or parametro2=="Cabron") or (parametro2=="Cabrón" or parametro2=="cabrón");		 

	  
	  if(hijo and puta){
	       cout<<"Hijo puta lo serás tu, se un poco más serio, o morirás.";
	       return 1;
	  }
	  else if(idiota){
	       cout<<"La idiotez de persigue, vas a morir.";
	       return 1;
	  }
	  else if(maricon){
	       cout<<"¿Te gusta la sodomía?.";
	       return 1; 
	  }
	  else if(cabron){
	       cout<<"¿Consientes que tu mujer se acueste con otro?";
	       return 1; 
	  }
     }    
     
     
     if(command!="")
	  cout<<endl;
	
     else
          cout<<"Error!: Command "<<command<<" no inicializado"<<endl;

     return -1;
}





	 
	 


