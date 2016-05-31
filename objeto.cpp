#include "objeto.h"

Objeto::Objeto()
{
	  usado=false;
	  fijo=false;
	  visible=true;
	  tirable=false;
	  alcanzable=true;
}

Objeto::Objeto(int id,
					string nombre,
					string descripcion):Entidad(id,nombre,descripcion)
{
	  usado=false;
	  fijo=false;
	  visible=true;
	  tirable=false;
	  alcanzable=true;
}

void Objeto::tirar()
{
	  cout<<endl<<descripcion_tirar<<endl;
	  if(objeto_rel_tirar!=0)
			 objeto_rel_tirar->set_visible(true);
	  else
			 cout<<"ERROR: Null object"<<endl;			 
}

void Objeto::set_tirable(Objeto *objeto,string descrip_tirable)
{
	  tirable=true;
	  this->objeto_rel_tirar=objeto;
	  this->descripcion_tirar=descrip_tirable;
}





