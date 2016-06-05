
#include <string>

using namespace std;

template<class T> class Property {
	public:
	  Property(){}
	  Property(string name):name(name){}

	  Property & operator=(const Property &rhs);
	private:
	  string name;
	  T value;
};


