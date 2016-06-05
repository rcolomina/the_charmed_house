

/*template<class T> class Distance{
	public:
	  virtual double calculate(T e1,T e2)=0;
	protected:
	  T e1,e2;
};
*/

/*class DistanceEuclidenan : public Distance{

};*/

/*
class DLevenshtein : public Distance{
public DLevenshtein():

};*/


// Reference: https://en.wikipedia.org/wiki/Levenshtein_distance

#include <string>

using namespace std;

class DistLevenshtein{
	public:
	  DistLevenshtein(const string s1,const string s2):s1(s1),s2(s2){}
	  int calculate();

	  //Todo: overloading equal and cout operators asociated with calculate
	private:
	  int LevenshteinDistance(const char *s, const int len_s, const char *t, const int len_t);
	  const string s1,s2;
};

