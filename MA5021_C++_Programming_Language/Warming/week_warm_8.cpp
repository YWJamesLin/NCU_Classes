#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Random_Shuffle
{
  private:
    int lbound, ubound, ssize;
    vector<int> data;
    int *numarr, tmp;
    int i, j;
    void gen()
    {
      numarr=new int[ssize];
      for(i=lbound; i<=ubound; ++i){ numarr[i-lbound]=i; }
      for(i=0; i<ssize; ++i)
      {
        for(j=ssize-1; j>=1; --j)
        {
          tmp=1.*rand()*j/(1.+RAND_MAX);
          numarr[j]+=numarr[tmp];
          numarr[tmp]=numarr[j]-numarr[tmp];
          numarr[j]-=numarr[tmp];
        }
      }
      for(i=0; i<ssize; ++i){ data.push_back(numarr[i]); }
      delete [] numarr;
    }

  public:
    Random_Shuffle(int l, int u)
    {
      srand(static_cast<unsigned>(time(NULL)));
      lbound=l;
      ubound=u;
      ssize=u-l+1;
      data.clear();
    }
    int size(){ return ssize; }
    int get()
    {
      if(data.empty()){ gen(); }
      tmp=data[0];
      data.erase(data.begin());
      return tmp;
    }
};

int main()
{
  Random_Shuffle foo(1, 5);

  int i, j;
  for(i=0; i<4; ++i)
  {
    for(j=0; j<foo.size(); ++j){ cout << foo.get() << " "; }
    cout << endl;
  }

  return 0;
}
