#include "factory.h"
#include "game.h"
#include <string>


using namespace std;

int main(){

	  cout<<"Starting with Factory class test"<<endl;

	  string xmlSpecs("gamesInfo.xml");
	  FactoryGame fac(xmlSpecs);
	  
	  cout<<"Building Items"<<endl;
	  cout<<"Building Item item01"<<endl;
	  fac.buildItemById("item01");
	  
	  
}
