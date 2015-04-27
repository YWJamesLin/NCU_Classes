#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

enum{ NO=52 };

class Card
{
  public:
    Card()
    {
      data.clear();
      for(i=0; i<NO; ++i){ data.push_back(i); }
    }
    void shuffle()
    {
      for(i=0; i<NO/2; ++i)
      {
        for(j=NO-1; j>0; --j)
        {
          tmp=1.*rand()*j/(1.+RAND_MAX);
          data[tmp]+=data[j];
          data[j]=data[tmp]-data[j];
          data[tmp]-=data[j];
        }
      }
    }
    int getbegin()
    {
      return data[0];
    }
    void delbegin()
    {
      data.erase(data.begin());
    }
  private:
    int i, j, tmp;
    vector<int> data;
};

class Gambler
{
  public:
    Gambler()
    {
      data.clear();
      sorted=false;
    }
    friend Card& operator>>(Card& in, Gambler& out)
    {
      out.data.push_back(in.getbegin());
      out.sorted=false;
      in.delbegin();
      return in;
    }
    friend Gambler& operator>>(Gambler& in, Gambler& out)
    {
      out.data.push_back(in.data[0]);
      out.sorted=false;
      in.data.erase(in.data.begin());
      in.sorted=false;
      return in;
    }
    friend ostream& operator<<(ostream& out, Gambler& in)
    {
      int i;
      if(!in.sorted){ in.card_sort(); }
      for(i=0; i<in.sdata.size(); ++i)
      { 
        switch(in.sdata[i]/13)
        {
          case 0:
            out << "C" << in.sdata[i]%13+1 << " ";
            break;
          case 1:
            out << "D" << in.sdata[i]%13+1 << " ";
            break;
          case 2:
            out << "H" << in.sdata[i]%13+1 << " ";
            break;
          case 3:
            out << "S" << in.sdata[i]%13+1 << " ";
            break;
        }
      }
      return out;
    }
  private:
    vector<int> data;
    vector<int> sdata;
    bool sorted;
    void card_sort()
    {
      sdata.clear();
      sdata=data;
      sort(sdata.begin(), sdata.end());
      sorted=true;
    }
};

int main()
{
  int i;
  Card card;
  Gambler Amy, Jane, John;

  card.shuffle();
  for(i=0; i<5; ++i){ card >> Amy >> Jane >> John; }
  cout << "Before:" << endl;
  cout << Amy << endl;
  cout << Jane << endl;
  cout << John << endl << endl;
  Amy >> Jane;
  Jane >> John;
  John >> Amy;
  cout << "After:" << endl;
  cout << Amy << endl;
  cout << Jane << endl;
  cout << John << endl << endl;

  return 0;
}
