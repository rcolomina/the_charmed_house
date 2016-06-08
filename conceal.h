#ifndef _concealment_h_
#define _concealment_h_

#include "objeto.h"



class ConcealItem{

	public:
	  ConcealItem(pItem visible,pItem hidden,string message):
			 discovered(false),
			 active(visible),
			 visible(visible),
			 hidden(hidden),
			 message(message)
	  {
	  }

	  pItem ItemActive(){return active;}
	  	  
	  string examine(){
			 return active->examine();
	  }

	  string discover(){
			 if(discovered==false){
					discovered=true;
					active=hidden;
					return message;
			 }

			 string mesg;
			 mesg.append(active->Name());
			 return mesg;
	  }

	  
  private:
	  bool discovered;
	  pItem active;
	  pItem visible,hidden;
	  string message;

};


#endif
