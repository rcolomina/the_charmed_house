#include "objeto.h"

Objeto::Objeto(const int id,
					const string nombre,
					const string descripcion):
	  id(id),nombre(nombre),descripcion(descripcion) 
{
	  usado=false;
	  fijo=false;
	  visible=true;
}



