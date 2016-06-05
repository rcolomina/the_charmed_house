#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "manager.h"

#include <tinyxml.h>

// Thread used for main game
void *hilo_principal(void *ptr);

// Thread used for time event
void *hilo_eventos(void *ptr);


int main(int argc,char **n_args){

	   pthread_t thread1,thread2;

 	   TiXmlDocument doc("gamesInfo.xml");
		bool loadOkay = doc.LoadFile();

		if (!loadOkay)
		{
			printf("Could not load test xml file. Error='%s'. Exiting.\n", doc.ErrorDesc());
			exit(1);
		}

		TiXmlNode* node=NULL;

		node = doc.FirstChild("games");
		assert(node);

		TiXmlHandle docHandle(node);
		TiXmlElement* child2 =
			  docHandle.FirstChild("game").FirstChild("scene").FirstChild("description").ToElement();

		if(child2!=0)
			  	cout<<child2->GetText()<<endl;
		
		// ele1->SetAttribute( "id", "gameExample" );
      //	cout<<ele1->Attribute("id")<<endl;

      /*	doc.Print( stdout );
		{
			  printf( "** Printing via TiXmlPrinter **\n" );
			  TiXmlPrinter printer;
			  doc.Accept( &printer );
			  fprintf( stdout, "%s", printer.CStr() );
		}
      */

//	  exit(1);
				
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






