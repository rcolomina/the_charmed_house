#include "invocador.h"
#include "distance.h"

// Return: -1 Error, 0 Ok, 1 Bad Behaviour
int Invocador::exec(string command,
		    string parametro1,
		    string parametro2){

    auto it = this->mapCommands.find(command);
    if (it != this->mapCommands.end()){
        mapCommands[command]->execute();
        return 0;
    }
    
    if(command==""){
        cout<<"Escribe un commando valido para continuar."<<endl;
        return 0;
    }
        
    
    vector<string> commandAvailables;
    for(auto it = mapCommands.begin();
        it != mapCommands.end(); ++it) {
        commandAvailables.push_back(it->first);
    }
        
    int minDistance=100;
    string commandSuggested = "";
    for(auto it=commandAvailables.begin();
        it!= commandAvailables.end();
        ++it){
        DistLevenshtein dist(*it,command);
        int newdist = dist.calculate();
        if(newdist < minDistance){
            minDistance=newdist;
            commandSuggested=*it;
        }
        
    }
    cout<<endl;
    cout<<"Quiza querias escribir el commando '"<<commandSuggested<<"'"<<endl;
        
    
//     // TODO: Move the following ones to new commands
//      if(command=="arriba");
//      else if(command=="abajo");	
//      else if(command=="entrar");
//      else if(command=="salir");					
//      else if(command=="salidas")
//      {
// 	  ICommand *icommand = mapCommands[s_norte];
	  
// 	  Cardinal *cardinal = dynamic_cast<Cardinal*>(icommand);

// 	  pScene escena_actual = cardinal->getCurrentScene();
// 	       //->getCurrentScene();
// 	  string salidas_disponibles = escena_actual->salidasDisponibles();
// 	  cout<<endl<<"Las salidas disponibles son:"<<salidas_disponibles<<endl;
//      }
//      // else if(command=="tiempo")
// //	  cout<<endl<<"Han pasado "<<tiempo<<" segundos desde que comenzó la partida."<<endl;
//      else if(command=="");
//      else 
//      {
// 	  // TODO: Use regular expresion instead/
// 	  bool hijo=(command=="hijo" or command=="Hijo");
	  
// 	  bool puta=(parametro1=="puta" or parametro1=="Puta") or (parametro2=="puta" or parametro2=="Puta");
	  
// 	  bool idiota=(command=="Idiota" or command=="idiota") or 
// 	       (parametro1=="Idiota" or parametro1=="idiota") or 
// 	       (parametro2=="Idiota" or parametro2=="idiota");
	  
// 	  bool maricon=(command=="maricón" or command=="Maricón") or (command=="maricon" or command=="Maricon") or
// 	       (parametro1=="maricón" or parametro1=="Maricón") or (parametro1=="maricon" or parametro1=="Maricon") or
// 	       (parametro2=="maricón" or parametro2=="Maricón") or (parametro2=="maricon" or parametro2=="Maricon");


// 	  bool cabron=(command=="cabron" or command=="Cabron") or (command=="Cabrón" or command=="cabrón") or
// 	       (parametro1=="cabron" or parametro1=="Cabron") or (parametro1=="Cabrón" or parametro1=="cabrón") or
// 	       (parametro2=="cabron" or parametro2=="Cabron") or (parametro2=="Cabrón" or parametro2=="cabrón");		 

	  
// 	  if(hijo and puta){
// 	       cout<<"Hijo puta lo serás tu, se un poco más serio, o morirás.";
// 	       return 1;
// 	  }
// 	  else if(idiota){
// 	       cout<<"La idiotez de persigue, vas a morir.";
// 	       return 1;
// 	  }
// 	  else if(maricon){
// 	       cout<<"¿Te gusta la sodomía?.";
// 	       return 1; 
// 	  }
// 	  else if(cabron){
// 	       cout<<"¿Consientes que tu mujer se acueste con otro?";
// 	       return 1; 
// 	  }
//      }    
          
     return 0;
}





	 
	 


