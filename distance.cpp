
#include "distance.h"


int DistLevenshtein::calculate()
{
    const char *s=s1.c_str();
    const char *t=s2.c_str();
    const int len_s = s1.size();
    const int len_t = s2.size();
			
    return this->LevenshteinDistance(s,len_s,t,len_t);

}


int DistLevenshtein::LevenshteinDistance(const char *s, const int len_s, const char *t, const int len_t)
{
    int cost;

    /* base case: empty strings */
    if (len_s == 0)
        return len_t;
    if (len_t == 0)
        return len_s;

    /* test if last characters of the strings match */
    if (s[len_s-1] == t[len_t-1])
        cost = 0;
    else
        cost = 1;

    /* return minimum of delete char from s, delete char from t, and delete char from both */
    return min(this->LevenshteinDistance(s,len_s-1,t,len_t)+1, min(
                   this->LevenshteinDistance(s,len_s,t,len_t-1)+1,
                   this->LevenshteinDistance(s,len_s-1,t,len_t-1)+cost));
}
