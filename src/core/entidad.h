#ifndef _entidad_H_
#define _entidad_H_

#include <string>

// This class provides identification methods for its derived classes
// Each object

class Entidad {
public:
    Entidad():
        sid("-1"),
        name("no name"),
        description("no description"){}

    Entidad(const std::string sid,const std::string name,const std::string description):
        sid(sid),
        name(name),
        description(description){}

    Entidad(const Entidad &other):
        sid(other.sid),
        name(other.name),
        description(other.description){}

    virtual ~Entidad() = default;

    const std::string& id() const { return sid; }
    const std::string& sId() const { return sid; }  // Deprecated: use id() instead
    const std::string& Name() const { return name; }
    const std::string& examine() const { return description; }

protected:
    const std::string sid;
    const std::string name;
    const std::string description;
};


#endif
