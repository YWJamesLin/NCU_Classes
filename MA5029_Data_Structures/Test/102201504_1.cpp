#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Wordsize
{
  public:
    Wordsize(int& n): count(n){};
    const string operator()(const string& str) const
    {
      if(str.length() >= count){ return str; }
      else{ return ""; }
    }
  private:
    int count;
};

template<class t0>
void print_words(const t0& begin, const t0& end, const Wordsize& fn)
{
  for(t0 i=begin; i!=end; ++i){ cout << fn(*i); }
}

int main()
{
  int n = 4;
  string line, word;
  istringstream istr;
  vector<string> strs;

  do
  {
    cout << "> ";
    getline(cin, line);
    istr.str(line);
    while(istr >> word){ strs.push_back(word); }
    istr.clear();

    print_words(strs.begin(), strs.end(), Wordsize(n));
    strs.clear();
  }while(1);

  return 0;
}
