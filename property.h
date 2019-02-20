#include <string>

using namespace std;

// This is a couple string-generic type
// A soft instronspection can be done with
// strings which is telling what is the purpose
// of the property
template<class T>
class Property {
public:
    Property(){}
    Property(string name):name(name){}
    Property(string name,T value):
        name(name),
        value(value){}

    template <typename U>      // all instantiations of this template are my friends
    U &operator=(Property<U>&)
        {
            return value;
        }

    template <typename U>      // all instantiations of this template are my friends
    friend std::ostream& operator<<( std::ostream&, const Property<U>& );

    template <typename U>
    Property<U>& operator=(U value)
        {
            //Property<U> *out=new Property<U>(string(""),value);
            this->value=value;
            return *this;
        }

    template <typename U>
    U& operator=(const Property<U>& )
        {
            //Property<U> *out=new Property<U>(string(""),value);
            return this->value;					
        }
	  
    string Name()
        {
            return name;
        }

    T Value()
        {
            return value;
        }


private:
    string name;
    T value;
};
/*
  template <typename T>
  std::ostream& operator<<( std::ostream& out, const Property<T>& prop) {
  // Can access all Test<int>, Test<double>... regardless of what T is
  out << prop.value;
  return out;
  }
*/

template <typename U>
std::ostream& operator<<( std::ostream& out, const Property<U>& prop) {
    // Can access all Test<int>, Test<double>... regardless of what T is
    out << prop.value;
    return out;
}



typedef Property<bool>    Bool;
typedef Property<bool>*   pBool;
typedef Property<int>     Int;
typedef Property<int>*    pInt;
typedef Property<double>  Double;
typedef Property<double>* pDouble;

