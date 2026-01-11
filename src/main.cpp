#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <fstream>
#include <iostream>
#include <string>

#include "manager/manager.h"

#include <tinyxml.h>

// Thread used for main game
void *main_thread(void *ptr);

// Thread used for time event
void *events_thread(void *ptr);


int main(int argc,char **n_args){

    // Language selection
    std::string language = "es";  // Default to Spanish

    // Check for command line argument
    if (argc > 1) {
        std::string arg = n_args[1];
        if (arg == "--lang=en" || arg == "-l=en" || arg == "en") {
            language = "en";
        } else if (arg == "--lang=es" || arg == "-l=es" || arg == "es") {
            language = "es";
        }
    } else {
        // Interactive language selection
        std::cout << "\n==================================" << std::endl;
        std::cout << "  THE CHARMED HOUSE / LA CASA ENCANTADA" << std::endl;
        std::cout << "==================================" << std::endl;
        std::cout << "\nSelect language / Seleccione idioma:" << std::endl;
        std::cout << "  1. English" << std::endl;
        std::cout << "  2. Español" << std::endl;
        std::cout << "\nEnter your choice (1 or 2): ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();  // Clear the input buffer

        if (choice == 1) {
            language = "en";
        } else {
            language = "es";
        }
    }

    std::cout << "\nLanguage selected: " << (language == "en" ? "English" : "Español") << std::endl;
    std::cout << std::endl;

    pthread_t thread1,thread2;

    /*	   TiXmlDocument doc("gamesInfo.xml");
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
           cout<<child2->GetText()<<endl;*/
		
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

    Manager *manager=new Manager(language);

    pthread_create(&thread1, NULL, main_thread, (void*)manager);  //inteface de usuario
    //pthread_create(&thread2, NULL, events_thread, (void*)manager);    //eventos del juego
	  
    pthread_join( thread1, NULL); //espera haeeesta que acabe el hilo 1
    //pthread_join( thread2, NULL); //espera hasta que acabe el hilo 2

    //Trying to save manager object.
/*	  std::ofstream file("./saved.bin");

//	  ofs << manager; // store the object to file
//	  ofs.close();
//
int beginning,end;

beginning = file.tellg();
file.seekg(0, ios::end);
end = file.tellg();

ifstream::pos_type size = (end - beginning);
	  

file.seekg(0,ios::beg);
file.read((char*)&memblock,size);
file.close();
*/

	  	  
    delete manager;

    return 0;
}

void *main_thread( void *ptr )
{
    Manager *manager = (Manager *) ptr;
    manager->run();
    return 0;
}

void *events_thread( void *ptr )
{
    Manager *manager = (Manager *) ptr;
    manager->clock();
    return 0;
}






