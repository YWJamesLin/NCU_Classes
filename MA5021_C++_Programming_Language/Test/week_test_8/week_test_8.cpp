#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Random_Shuffle
{
  public:
    Random_Shuffle(int l, int u, int n)
    {
      srand(static_cast<unsigned>(time(NULL)));
      lbound=l;
      ubound=u;
      nlst=n;
      data.clear();
      list=new int [n];
      for(i=0; i<n; ++i){ list[i]=0; }
      check=false;
    }
    ~Random_Shuffle()
    {
      delete [] list;
    }
    int size()
    {
      return ubound-lbound+1;
    }
    int get()
    {
      if(data.empty()){ gen(); }
      tmp=data[0];
      data.erase(data.begin());
      return tmp;
    }
  private:
    int lbound, ubound, nlst;
    int i, j, tmp;
    int *list;
    bool check;
    vector<int> data;
    void gen()
    {
      for(i=lbound; i<=ubound; ++i){ data.push_back(i); }
      i=0;
      while(i<(ubound-lbound+2)/2 || check==false)
      {
        for(j=ubound-lbound; j>0; --j)
        {
          tmp=1.*rand()*j/(1.+RAND_MAX);
          data[tmp]+=data[j];
          data[j]=data[tmp]-data[j];
          data[tmp]-=data[j];
        }
        check=true;
        for(j=0; j<nlst; ++j)
        {
          for(tmp=j; tmp<nlst; ++tmp)
          {
            if(data[j]==list[tmp])
            { 
              check=false;
              break;
            }
          }
        }
        ++i;
      }
      for(i=0; i<nlst; ++i){ list[i]=data[ubound-nlst+i]; }
    }
};

int main()
{
  Random_Shuffle foo(1,5,2);

  int i, j;
  for(i=0; i<4; ++i)
  {
    for(j=0; j<foo.size(); ++j)
    {
      cout << foo.get() << " ";
    }
    cout << endl;
  }

  return 0;
}
