#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>

using namespace std;

class Grade
{
  private:
    vector< list<int> > num;

  public:
    Grade(int n)
    {
      int rn;
      srand(static_cast<unsigned>(time(NULL)));
      for(int i=0; i<10; ++i){ num.push_back( list<int>() ); }
      for(int i=0; i<n; ++i)
      {
        rn = static_cast<int>(101. * rand() / (1. + RAND_MAX));
        num[(rn == 100)?9:(rn/10)].push_back(rn);
      }
    }
    friend ostream& operator<<(ostream& out, const Grade& foo)
    {
      for(int i=0; i<10; ++i)
      {
        out << setw(2) << i << '~' << setw(3) << ((i==10)?100:i*10) << "   :";
        for(list<int>::const_iterator j = foo.num[i].begin(); j != foo.num[i].end(); ++j){ out << setw(5) << *j; }
        out << endl;
      }
      return out;
    }
    void sort_erase(int a)
    {
      int count = 0;
      bool found = false;
      for(int i=0; i<10; ++i)
      {
        num[i].sort();
        if(!found)
        {
          for(list<int>::iterator j = num[i].begin(); j != num[i].end(); ++j)
          {
            ++count;
            if(count == a)
            { 
              num[i].erase(j);
              found = true;
              break;
            }
          }
        }
      }
    }
};

int main()
{
  Grade foo(50);
  cout << foo << endl;
  foo.sort_erase(10);
  cout << foo << endl;
  return 0;
}
