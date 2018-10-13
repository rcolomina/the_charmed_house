#ifndef _entidad_H_
#define _entidad_H_

#include <string>

using namespace std;

class Entidad {
 public:
 Entidad():
  id(0){}
 Entidad(const int id,const string name,const string description):
  id(id),
    name(name),
    description(description){}

 Entidad(const string sid,const string name,const string description):
  sid(sid),
    id(1),  //todo
    name(name),
    description(description){}

 Entidad(const Entidad &other):id(other.id),
    name(other.name),
    description(other.description){}

  const string sId(){return sid;}
  const int Id(){return id;}
  const string Name(){return name;}
  const string examine(){return description;}

 protected:
  const string sid;
  const int id; 
  const string name;
  const string description;
};


#endif
