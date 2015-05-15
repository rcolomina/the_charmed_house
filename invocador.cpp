#include "invocador.h"


void Invocador::salir(){
			 if(mapComandos[s_exit]!=0){
					//cout<<"Entrando en Invocador: Metodo salir"<<endl;
					mapComandos[s_exit]->execute();
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
			 
void Invocador::set_command(ICommand *command){
			 // exit=command;
 }
