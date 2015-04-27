#include <iostream>
#include <algorithm>

using namespace std;

class Power
{
  public:
    Power(int b, int e): base(b), exp(e){}
    int count() const
    { 
      int sum=base;
      for(int i=0; i<exp; ++i){ sum*=base; }
      return sum;
    }
    friend ostream& operator<<(ostream& out, const Power& in)
    { 
      out << in.base << "^" << in.exp;
      return out;
    }
    friend bool operator<(const Power& a, const Power& b){ return a.count() < b.count(); }
  private:
    int base, exp;
};

template<class t0>
void print_items(const t0 begin, const t0 end)
{
  for(t0 i = begin; i != end; ++i)
  { 
    cout << *i;
    if(i != end-1){ cout << " < "; }
  }
  cout << endl;
}

int main()
{
  Power foo[4] ={Power(2,3), Power(3,5), Power(7,5), Power(7,3)};

  sort(foo ,foo+4);
  print_items(foo, foo+4);

  return 0;
}
