#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Grade
{
  private:
    vector< list<int> > num;

  public:
    Grade(int n)
    {
      srand(static_cast<unsigned>(time(NULL)));
      for(int i=0; i<10; ++i){ num.push_back(list<int>()); }
      for(int i=0, tmp; i<n; ++i)
      {
        tmp = static_cast<int>(101. * rand() / (1. + RAND_MAX));
        num[(tmp/10 == 10)?9:(tmp/10)].push_back(tmp);
      }
    }
    friend ostream& operator<<(ostream& out, const Grade& in)
    {
      list<int>::const_iterator j;
      for(int i=0; i<10; ++i)
      {
        out << setw(2) << i*10 << "~" << setw(3) << ((i==9)?100:((i+1)*10-1)) << " : ";
        for(j = ((in.num[i]).begin()); j != ((in.num[i]).end()); ++j){ out << setw(3) << *j << " "; }
        out << endl;
      }
      return out;
    }
};

int main()
{
  Grade foo(50);

  cout << foo << endl;

  return 0;
}
