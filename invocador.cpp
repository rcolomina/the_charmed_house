#include "invocador.h"

void Invocador::exec(string command){
     ICommand *icommand=mapComandos[command];
     if(icommand!=0){
          icommand->execute();
     }
     else
          cout<<"Error!: Comando "<<command<<" no inicializado"<<endl;

}

void Invocador::set_command(ICommand *command){
     // exit=command;
}

// Iteration 
void Invocador::examinar_comando(string parametro1){
     if(mapComandos[s_examinar]!=0){
          //cout<<"Entrando en Invocador: Metodo ver_comandor"<<endl;
					
          mapComandos[s_examinar]->execute();
     }
     else
          cout<<"Error!: Comando ver no inicializado"<<endl;
}



/*
void Invocador::salir(){
	       ICommand* icommand=mapComandos[s_exit];
			 if(icommand!=0){
					//cout<<"Entrando en Invocador: Metodo salir"<<endl;
					icommand->execute();
			 }
			 else
					cout<<"Error!: Comando exit no inicializado"<<endl;
	  }

void Invocador::ayuda_comandos(){
			 ICommand* icommand=mapComandos[s_ayuda];
			 //cout<<"Ayuda_comandos"<<endl;
			 if(icommand!=0){		
					//	cout<<"Entrando en Invocador: Metodo ayuda_comandos"<<endl;
					icommand->execute();
			 }
			 else
					cout<<"Error!: Comando exit no inicializado"<<endl;
	  }

void Invocador::ver_comando(){
		 if(mapComandos[s_ver]!=0){
				//cout<<"Entrando en Invocador: Metodo ver_comandor"<<endl;
					
					mapComandos[s_ver]->execute();
			 }
			 else
					cout<<"Error!: Comando ver no inicializado"<<endl;
	  }
*/

	 
	 
	 


