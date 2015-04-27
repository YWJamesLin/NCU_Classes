#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

struct Eng_Word
{
  bool operator()(const string& str) const
  {
    bool iA = true;
    for(int i=0; i<str.length(); ++i)
    {
      if(!isalpha(str[i]))
      {
        iA = false;
        break;
      }
    }
    return iA;
  }
};

struct By_Length
{
  bool operator()(const string& a, const string& b) const
  {
    return a.length() < b.length();
  }
};

template<class S, class T, class Fn>
void copy_if(S begin, S end, T out, Fn f)
{
  for(S i = begin; i != end; ++i)
  {
    if(f(*i))
    {
      *out = *i;
      ++out;
    }
  }
}

int main()
{
  string foo = "be right back in 10 mins";

  istringstream istr(foo);
  istream_iterator<string> iter(istr);

  vector<string> bar;

  copy_if(iter, istream_iterator<string>(), back_inserter(bar), Eng_Word());

  stable_sort(bar.begin(), bar.end(), By_Length());

  copy(bar.begin(), bar.end(), ostream_iterator<string>(cout," "));

  cout << endl;

  return 0;
}
