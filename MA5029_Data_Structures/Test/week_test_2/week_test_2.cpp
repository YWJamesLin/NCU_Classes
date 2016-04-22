#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;

class Grade
{
  private:
    vector< list<int> > num;
  public:
    Grade(int n)
    {
      srand(static_cast<unsigned>(time(NULL)));
      for(int i=0; i<10; ++i){ num.push_back( list<int>() ); }
      for(int i=0, temp; i<n; ++i)
      {
        temp = 101. * rand() / (1. + RAND_MAX);
        num[(temp/10==10)?9:(temp/10)].push_back(temp);
      }
    }
    friend ostream& operator<<(ostream& out, const Grade& in)
    {
      list<int>::const_iterator j;
      for(int i=0; i<10; ++i)
      {
        int k;
        out << i*10 << " ~ " << ((i==10)?100:(i+1)*10-1) << " : ";
        for(j=in.num[i].begin(); j!=in.num[i].end(); ++j)
        { 
          cout << setw(3) << *j << " "; 
        }
        out << endl;
      }
      return out;
    }
    void sort_erase(int a)
    {
      list<int>::iterator j, k, tmp;
      int tmpn;
      for(int i=0; i<10; ++i)
      {
        for(j=num[i].begin(); j != num[i].end(); ++j)
        {
          tmp = j;
          for(k=j; k != num[i].end(); ++k)
          {
            if(k==j){ continue; }
            if(*tmp > *k){ tmp = k; }
          }
          if(tmp != j)
          {
            tmpn = *j;
            *j = *tmp;
            *tmp = tmpn;
          }
        }
      }
      
      for(int i=0, temp=0; i<10; ++i)
      {
        for(j=num[i].begin(); j!=num[i].end(); ++j)
        { 
          ++temp;
          if(temp == a)
          {
            num[i].erase(j);
            break;
          }
        }
        if(temp == a){ break; }
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
