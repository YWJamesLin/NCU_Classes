#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

const string num[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char Vowel[5] = {'a', 'e', 'i', 'o', 'u'};
struct Eng_Num
{
  string operator()(const string& str)
  {
    bool iN = false;
    for(int i=0; i< str.length(); ++i)
    {
      if(str[i] > 47 && str[i] < 57){ iN = true; }
    }
    if(iN){ return num[static_cast<int>(str[0])-48]; }
    else{ return str; }
  }
};

struct To_Upper
{
  string operator()(string str)
  {
    for(int i=0; i < str.length(); ++i){ str[i] = toupper(str[i]); }
    return str;
  }
};

struct VOWEL
{
  int loc;
  VOWEL(int n): loc(n){}
  bool operator()(const string& str)
  {
    int iV = false;
    for(int i=0; i< 5; ++i)
    {
      if(str[loc-1] == Vowel[i]){ iV = true; }
    }
    return iV;
  }
};

template<class S, class T, class F>
void copy_to(S begin, S end, T out, F f)
{
  for(S i = begin; i != end; ++i)
  {
    *out = f(*i);
    out ++;
  }
}

template<class S, class F1, class F2>
void convert(S begin, S end, F1 iF, F2 then)
{
  for(S i = begin; i != end; ++i)
  {
    if(iF(*i)){ *i = then(*i); }
  }
}
int main()
{
  string foo = "there are 3 apples, 2 pencils, and 8 rulers on my desk.";

  istringstream istr(foo);
  istream_iterator<string> iter(istr);

  vector<string> bar;

  copy_to(iter, istream_iterator<string>(), back_inserter(bar), Eng_Num());

  convert(bar.begin(), bar.end(), VOWEL(3), To_Upper());

  copy(bar.begin(), bar.end(), ostream_iterator<string>(cout, " "));

  cout << endl;

  return 0;
}
