#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Frac
{
  private:
    int child, mother;

  public:
    Frac(int c, int m = 1): child(c), mother(m){}
    friend ostream& operator<<(ostream& out, const Frac& in)
    {
      out << in.child;
      if(in.mother != 1){ out << '/' << in.mother; }
      return out;
    }
};

class Cfrac
{
  private:
    vector<int> data;

  public:
    Cfrac(int* begin, int* end)
    {
      for(int* i = begin; i != end; ++i){ data.push_back(*i); }
    }

    string cfrac(int i)
    {
      stringstream sstr;
      string str;

      sstr << '[';
      for(int j = 1; j <= i; ++j)
      {
        sstr << data[j-1];
        if(j != i)
        {
          if(j == 1){ sstr << ';'; }
          else{ sstr << ','; }
        }
      }
      sstr << ']';
      sstr >> str;
      return str;
    }

    Frac frac(int i)
    {
      int child = data[i-1], mother = 1, j=i-1;
      while(j>=1)
      {
        //inverse
        child += mother;
        mother = child - mother;
        child -= mother;

        //operation
        child += data[j-1] * mother;
        --j;
      }
      return Frac(child, mother);
    }
};

int main()
{
  const int M = 9;
  int no[M] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  Cfrac foo(no, no+M);
  for(int i=1; i<=M; ++i)
  {
    cout << foo.cfrac(i) << " = " << foo.frac(i) << endl;
  }
  return 0;
}
