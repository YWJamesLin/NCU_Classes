#include <iostream>
#include <iterator>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

const string nWord[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char vowel[5] = {'a', 'e', 'i', 'o', 'u'};

template<class S, class T, class F>
void copy_to(S begin, S end, T out, F func)
{
  for(S i = begin; i != end; ++i)
  {
    *out = func(*i);
  }
}

template<class S, class F1, class F2>
void convert(S begin, S end, F1 If, F2 Then)
{
  for(S i = begin; i != end; ++i)
  {
    if(If(*i)){ *i = Then(*i); }
  }
}

struct Eng_Num
{
  string operator()(const string& str)
  {
    if(str[0] < 48 || str[0] > 57){ return str; }
    else{ return nWord[str[0] - 48]; }
  }
};

struct VOWEL
{
  int loc;
  VOWEL(int l): loc(l){}
  bool operator()(const string& str)
  {
    for(int i=0; i<5; ++i)
    {
      if(str[loc-1] == vowel[i]){ return true; }
    }
    return false;
  }
};

struct To_Upper
{
  string operator()(const string& str)
  {
    string tmp = str;
    for(int i=0; i < str.length(); ++i){ tmp[i] = toupper(str[i]); }
    return tmp;
  }
};

int main()
{
  string foo = "there are 3 apples, 2 pencils, and 8 rulers on my desk.";

  istringstream istr(foo);
  istream_iterator<string> iter(istr);
  
  vector<string> bar;

  copy_to(iter, istream_iterator<string>(), back_inserter(bar), Eng_Num());

  convert(bar.begin(), bar.end(), VOWEL(2), To_Upper());

  copy(bar.begin(), bar.end(), ostream_iterator<string>(cout, " "));

  cout << endl;

  return 0;
}
