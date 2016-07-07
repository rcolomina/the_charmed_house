#include "conceal.h"


int main(){

	  pItem hidden=new Objeto(1,"manzana","Es una fruta muy rica");
	  pItem visible=new Objeto(2,"rama","Es una rama muy frondosa");

	  ConcealItem* cItem=new ConcealItem(visible,hidden,"Descubres una rica manzana");


	  cout<<"ConcealItem examine() "<<cItem->examine()<<endl;	  	  
	  cout<<"ConcealItem discover() "<<cItem->discover()<<endl;
	  cout<<"ConcealItem examine() "<<cItem->examine()<<endl;

	  delete cItem;

	  cout<<"Hi, my object name is '"<<visible->Name()<<"', and I am still living after ConcealItem has been deleted"<<endl;
			 
	  delete hidden;
	  delete visible;




}
