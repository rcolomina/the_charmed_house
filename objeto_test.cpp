#include "objeto.h"
#include <cassert>

int main(){

    cout<<">Testing Item class<"<<endl;
    cout<<"--------------------"<<endl;
    cout<<"Creating and Entity"<<endl;
    int id=1;
    string name="device";
    string descrip="This is a piece of juck";	  
    Entidad entity(id,name,descrip);
	  
    cout<<"entity name is:"<<entity.Name()<<endl;
    cout<<"entity description is:"<<entity.examine()<<endl;
	  
    cout<<"Defining properties as pairs (string,string)"<<endl;
    pair<string,string> par;
    vector<pair<string,string> > props;
	  
    par.first="visibility";
    par.second="true";
    cout<<"Declaring visibility as true"<<endl;
    props.push_back(par);
	  
    par.first="visualizer";
    par.second="false";
    cout<<"Declaring visualizer as false"<<endl;
    props.push_back(par);
	  
    par.first="tirable";
    par.second="true";
    cout<<"Declaring tirable as true"<<endl;
    props.push_back(par);
	  
    par.first="reacher";
    par.second="true";
    cout<<"Declaring reacher as true"<<endl;
    props.push_back(par);
	  
    vector<string> names;
    vector<string> descr;
    string fileNameText;
	  
    Objeto item(entity,names,descr,props,fileNameText);


    cout<<"TESTING GET VALUE METHOD "<<endl;
    cout<<"Is "<<item.Name()<<" visible? : "<<"get_value<bool>(\"visibility\") is " <<item.get_value<bool>("visibility")<<endl;
    assert(item.get_value<bool>("visibility")==true);
    cout<<"Test PASS"<<endl;
	  
    cout<<"Is "<<item.Name()<<" a visualizer? : "<<"get_value<bool>(\"visualizer\") is "<<item.get_value<bool>("visualizer")<<endl;
    assert(item.get_value<bool>("visualizer")==false);
    cout<<"Test PASS"<<endl;
	  
    cout<<"Is "<<item.Name()<<" a tirable? : "<<"get_value<bool>(\"tirable\") is "<<item.get_value<bool>("tirable")<<endl;
    assert(item.get_value<bool>("tirable")==true);
    cout<<"Test PASS"<<endl;

    cout<<"Is "<<item.Name()<<" a reacher? : "<<"get_value<bool>(\"reacher\") is "<<item.get_value<bool>("reachero")<<endl;
    assert(item.get_value<bool>("reacher")==true);
    cout<<"Test PASS"<<endl;


    cout<<"TESTING RELATED OBJECTS"<<endl;


    Entidad ent2(2,"hidden","hidden object");
    Objeto item2(ent2,names,descr,props,fileNameText);
    cout<<"New object item2 created"<<endl;
    item2.set_value("visibility",false);
    cout<<"Item2 visibiblity:"<<item2.get_value<bool>("visibility")<<endl;

    cout<<"We attach item2 to item as a hidden object"<<endl;
    item.set_tirable(&item2,"A hidden object appears");
    
	  
    cout<<"Exec the action 'tirar' of item"<<endl;
    item.tirar();

    cout<<"Item2 visibiblity:"<<item2.get_value<bool>("visibility")<<endl;

	  
//	  Objeto item
	  
}
