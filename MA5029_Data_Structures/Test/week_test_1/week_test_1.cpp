#include <iostream>
#include <algorithm>

using namespace std;

class Power
{
  private:
    int base, exp;

  public:
    Power(int c, int m): base(c), exp(m){}
    int getbase() const{ return base; }
    int getexp() const{ return exp; }
    friend Power operator*(const Power& a, const Power& b)
    {
      Power foo(a.base, a.exp);
      foo.exp += b.exp;
      return foo;
    }
    friend bool operator<(const Power& a, const Power& b)
    {
      int suma=1 , sumb=1;
      for(int i=0; i < a.exp; ++i){ suma *= a.base; }
      for(int i=0; i < b.exp; ++i){ sumb *= b.base; }
      return suma < sumb;
    }
    friend ostream& operator<<(ostream& out, const Power& in)
    {
      out << in.base << '^' << in.exp;
      return out;
    }
};

struct MyRule
{
  bool operator()(const Power& a, const Power& b)
  {
    if(a.getbase() > b.getbase() || a.getbase() < b.getbase()){ return a.getbase() >= b.getbase(); }
    else
    {
      return a.getexp() >= b.getexp();
    }
  }
};

void print_items(const Power* a, const Power* b)
{
  bool second = false;
  for(const Power* i = a; i != b; ++i)
  {
    if(second){ cout << " , "; }
    cout << *i;
    second = true;
  }
  cout << endl;
}

int main()
{
  const int n = 4;

  Power foo[n] = { Power(2, 3), Power(3, 5), Power(7, 5), Power(7, 3)};
  Power bar[n] = { Power(2, 5), Power(3, 10), Power(7, 2), Power(7, 2)};

  for(int i=0; i<n; ++i){ foo[i] = foo[i] * bar[i]; }

  print_items(foo, foo+n);

  sort(foo, foo+n);

  print_items(foo, foo+n);
  
  sort(foo, foo+n, MyRule());

  print_items(foo, foo+n);

  return 0;
}
