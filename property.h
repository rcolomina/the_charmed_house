
class Property {
	public:
	  Property(string name):name(name){}
	private:
	  string name;
};

class BoleanProperty : public Property{
	public:

	  BoleanProperty(string name,bool value):Property(name),value(value){}
	  bool get_value();
	  void set_value();
	private:
	  bool value;	  
};

class IntegerProperty : public Property {

};

class RealProperty : public Property {

};
