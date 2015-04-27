#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum{ NO=52 };

class Card
{
  private:
    int i, j, tmp;
    vector<int> card;
  public:
    Card()
    {
      card.clear();
      for(i=0; i<NO; ++i){ card.push_back(i); }
    }
    void shuffle()
    {
      for(i=0; i<NO/2; ++i)
      {
        for(j=NO-1; j>0; --j)
        {
          tmp=1.*rand()*j/(1.+RAND_MAX);
          card[tmp]+=card[j];
          card[j]=card[tmp]-card[j];
          card[tmp]-=card[j];
        }
      }
    }
    int get(int foo)
    {
      return card[foo];
    }
    void delbegin()
    {
      card.erase(card.begin());
    }
};

class Gambler
{
  private:
    bool sorted;
    int tmp;
    vector<int> card;
    vector<int> srtarr;
    void cardsort()
    {
      srtarr.clear();
      for(tmp=0; tmp<card.size(); ++tmp){ srtarr.push_back(card[tmp]); }
      sort(srtarr.begin(), srtarr.end());
      sorted=true;
    }
  public:
    Gambler()
    {
      card.clear();
      srtarr.clear();
      sorted=false;
    }
    friend Card& operator>>(Card& in, Gambler& tg)
    {
      tg.sorted=false;
      tg.card.push_back(in.get(0));
      in.delbegin();
      return in;
    }
    friend ostream& operator<<(ostream& out, Gambler& src)
    {
      int i;
      if(src.sorted==false){ src.cardsort(); }
      for(i=0; i<src.srtarr.size(); ++i)
      {
        switch(src.srtarr[i]/13)
        {
          case 0:
            out << "C";
            break;
          case 1:
            out << "D";
            break;
          case 2:
            out << "H";
            break;
          case 3:
            out << "S";
            break;
        }
        out << (src.srtarr[i]%13+1) << " ";
      }
      return out;
    }
};

int main()
{
  srand(static_cast<unsigned>(time(NULL)));
  int i;
  Card card;
  card.shuffle();
  Gambler Tom, Mary, Jane;

  for(i=0; i<5; ++i){ card >> Tom >> Mary >> Jane; }
  cout << Tom << endl;
  cout << Mary << endl;
  cout << Jane << endl;

  return 0;
}
