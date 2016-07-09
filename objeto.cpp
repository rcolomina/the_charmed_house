#include "objeto.h"

Objeto::Objeto(const Entidad &entity,
	       vector<string> names,
	       vector<string> descriptions,
	       vector<pair<string,string> > namesProperties,
	       string pathFileText):
     Entidad(entity)
{
     // TODO: Create an external list of properties by default
     map_pBools[string("used")]=new Bool(string("used"),false);
     map_pBools[string("fix")]=new Bool(string("fix"),false);
     map_pBools[string("visibility")]=new Bool(string("visibility"),true);
     map_pBools[string("tirable")]=new Bool(string("tirable"),false);
     map_pBools[string("alcanzable")]=new Bool(string("alcanzable"),true);
     map_pBools[string("desatascador")]=new Bool(string("desatascador"),true);
	  	  
     vector<pair<string,string> >::iterator it;
     for(it=namesProperties.begin();it!=namesProperties.end();it++)
     {			 
	  pair<string,string> par=*it;

	  if(par.second==string("true") or par.second==string("false"))
	  {
	       bool boolvalue=false;
	       if(par.second==string("true"))
		    boolvalue=true;
					
	       map_pBools[par.first]=new Bool(par.first,boolvalue);
	       mapBool[par.first]=boolvalue;
	  }
	  else
	  {
	       int integerValue=stoi(par.second);
	       map_pInts[par.first]=new Int(par.first,integerValue);
	  }					
     }

     this->pathFileText=pathFileText;
}

/*pBool Objeto::get_property(const string &name){			 
  return map_pBools[name];
  }*/

void Objeto::set_value(string prop,bool value){
     delete map_pBools[prop];
     map_pBools[prop]=new Bool(prop,value);
}

// TODO: Create a generic method to operate do operation with objects, which will accept functors
void Objeto::tirar()
{
     cout<<endl<<descripcion_tirar<<endl;
     if(objeto_rel_tirar!=NULL)
     {
	  objeto_rel_tirar->set_value(string("visibility"),true);
     }
     else
     {
	  cout<<"ERROR: Null object"<<endl;
     }
}

void Objeto::set_tirable(Objeto *objeto,string descrip_tirable)
{
     if(objeto!=NULL)
     {
	  this->objeto_rel_tirar=objeto;
	  objeto_rel_tirar->set_value(string("visibility"),false);
	  this->descripcion_tirar=descrip_tirable;
     }
}


template <typename U>
U Objeto::get_value(const char* pro){
     return U();
}



template<>
bool Objeto::get_value<bool>(const char* pro)
{			 
     pBool pb=map_pBools[string(pro)];
     bool value=false; // TODO: Return false value by default 
     if(pb!=NULL)
     {
	  value=pb->Value();
     }
#ifdef _DEBUG
     cout<<"get_value:"<<pro<<" valueProp:"<<value<<endl;
     cout<<"get_value:"<<pro<<" valueBool:"<<mapBool[string(pro)]<<endl;
#endif			 
     return value;
}


template<>
int Objeto::get_value<int>(const char* pro)
{			 
     pInt pI=map_pInts[string(pro)];
     int value=0; 
     if(pI!=NULL)
     {
	  value=pI->Value();
     }
#ifdef _DEBUG
     cout<<"get_value:"<<pro<<" valueProp:"<<value<<endl;
     cout<<"get_value:"<<pro<<" valueInts:"<<map_pInts[string(pro)]<<endl;
#endif			 
     return value;
}


void Objeto::insert_event(IEvent *event)
{
     eventsToFire.push(event);
}


IEvent* Objeto::activate_event()
{
     if(!eventsToFire.empty())
     {
	  IEvent *event=eventsToFire.front();
	  eventsToFire.pop();
	  return event;					
     }
     return NULL;
}
