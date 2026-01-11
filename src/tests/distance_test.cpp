
#include "lib/distance/distance.h"

#include <string>
#include <iostream>

using namespace std;


int main(){


    string s1("palanca");
    string s2("palanqueta");
    string s3("Palanca");
    string s4("ladrillo");
 
    DistLevenshtein dl1(s1,s2);
    DistLevenshtein dl2(s1,s3);
    DistLevenshtein dl3(s2,s3);
    DistLevenshtein dl4(s1,s4);

    cout<<"------------------"<<endl;
    cout<<"Levenshte Distances"<<endl;
    cout<<"------------------"<<endl;

	  
    cout<<"Between \""<<s1<<"\" and \""<<s2<<"\" is "<<dl1.calculate()<<endl;
    cout<<"Between \""<<s1<<"\" and \""<<s3<<"\" is "<<dl2.calculate()<<endl;
    cout<<"Between \""<<s2<<"\" and \""<<s3<<"\" is "<<dl3.calculate()<<endl;
    cout<<"Between \""<<s1<<"\" and \""<<s4<<"\" is "<<dl4.calculate()<<endl;


}


