#include "lib/property/property.h"

#include <iostream>
#include <string>

using namespace std;

int main(){

    cout << "\033[1;31m TESTING BOOLEAN PROPERTIES \033[0m\n";

	  
    pBool pb_visible=new Property<bool>(string("visible"),true);
    pBool pb_fix=new Property<bool>(string("fix"),true);
	  
    cout<<"Value of pb_visible is "<<*pb_visible<<endl;
    cout<<"Value of pb_fix is "<<*pb_fix<<endl;

    Property<bool> propBool("helloProp",true);

    //cout<<"propBool before bool assignation: "
    cout<<"I can get value from a bool -> propBool=false;"<<endl;
    cout<<"prop is named as:"<<propBool.Name();
    cout<<"propBool before bool assignation: propBool -> "<<propBool<<endl;
    propBool=false;	  	  
    cout<<"propBool after bool assignation: propBool  ->"<<propBool<<endl;

    // Imitating a standard Bool
    Property<bool> pBool("standard bool",true);

//	  cout<<"This is a replica of an standard bool using class Property<bool> pBool; :"<<endl;
//	  cout<<"Can assign value to a bool -> bool bolean=pBool;";
//	  bool sbool;
//	  sbool=pBool;
//	  cout<<"sbool has value "<<sbool;
//	  cout<<"pBool has value "<<pBool;
//   cout<<"Can extract value -> cout<<\"Extracting value \"<<pBool<<endl;"<<endl;	  
    /*	  cout<<"Can get a valuee from bool -> pBoolbool bolean=pBool;"<<endl;
	  sbool=true;
	  pBool=sbool;
	  cout<<"sbool has value "<<sbool;
	  cout<<"pBool has value "<<pBool;
    */

    bool sBool;
    sBool=pBool.Value();

    cout<<"sBool with value coming from pBool:"<<sBool<<endl;

    cout << "\033[1;31m TESTING INTEGER PROPERTIES \033[0m\n";


	  
//	  cout<<
	  
    return 0;
}
