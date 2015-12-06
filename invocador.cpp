#include "invocador.h"

void Invocador::exec(string command){

     ICommand *icommand=mapComandos[command];
     if(icommand!=0){
          icommand->execute();
     }
     else
          cout<<"Error!: Comando "<<command<<" no inicializado"<<endl;

}





	 
	 


