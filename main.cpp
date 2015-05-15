#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "manager.h"

void *hilo_principal( void *ptr );
void *hilo_eventos( void *ptr );

int main(){
	  pthread_t thread1,thread2;

	  Manager *manager=new Manager();

	  pthread_create(&thread1, NULL, hilo_principal, (void*)manager);  //inteface de usuario
	  pthread_create(&thread2, NULL, hilo_eventos, (void*)manager);    //eventos del juego
	  
	  pthread_join( thread1, NULL); //espera hasta que acabe el hilo 1
	  pthread_join( thread2, NULL); //espera hasta que acabe el hilo 2

	  //delete manager;

	  return 0;
}

void *hilo_principal( void *ptr )
{
	  Manager *manager;
	  manager = (Manager *) ptr;
	  manager->run();
	  return 0;
}

void *hilo_eventos( void *ptr )
{
	  Manager *manager;
	  manager = (Manager *) ptr;
	  manager->clock();
	  return 0;
}






