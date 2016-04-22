#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

multimap<int, int> strokeWord;
multimap<wchar_t, int> wordStroke;

struct by_strokes
{
  bool operator()(const wstring& a, const wstring& b) const
  {
    if(a.length() == b.length())
    {
      for(int i=0; i<3; ++i)
      {
        if(((wordStroke.find(a[i]))->second) != ((wordStroke.find(b[i]))->second))
        {
          return ((wordStroke.find(a[i]))->second) < ((wordStroke.find(b[i]))->second);
        } 
      }
      return true; 
    }
    else{ return a.length() < b.length(); }
  }
};

typedef multimap<wstring, vector<wstring> >::const_iterator mmcitr;
typedef vector<wstring>::const_iterator vcitr;

class Poem
{
  private:
    multimap<wstring, vector<wstring>, by_strokes> poems;

  public:
    Poem(char* fname)
    {
      wifstream win;
      wistringstream wisstr;
      wstring wlstr, poet, poem;

      win.open(fname);
      locale uzh("zh_TW.UTF-8");
      vector<wstring> tmpv;
      int count;
      
      win.imbue(uzh);
      while(getline(win, wlstr))
      {
        tmpv.clear();
        wisstr.str(wlstr);
        wisstr >> poet;
        while(wisstr >> poem)
        {
          tmpv.push_back(poem);
          wisstr.clear();
        }
        wisstr.clear();
        sort(tmpv.begin(), tmpv.end(), by_strokes());
        poems.insert(make_pair<wstring, vector<wstring> >(poet, tmpv));
      }
    }
    friend wostream& operator<<(wostream& out, const Poem& in)
    {
      for(mmcitr i = in.poems.begin(); i != in.poems.end(); ++i)
      {
        out << i->first << L'(' << (i->second).size() << L')' << L" : ";
        for(vcitr j = (i->second).begin(); j != (i->second).end(); ++j)
        {
          out << *j << L" ";
        }
        out << endl;
      }
      return out;
    }
};

int main()
{
  string str;
  int ucode, stroke;

  ifstream in;
  istringstream isstr;

  in.open("strokes.dat");
  setlocale(LC_ALL, "zh_TW.UTF-8");
  while(in >> str >> stroke)
  {
    isstr.str(str.substr(2));
    isstr >> hex >> ucode;
    isstr.clear();
    strokeWord.insert(make_pair<int, int>(stroke, ucode));
    wordStroke.insert(make_pair<wchar_t, int>(ucode, stroke));
  }
  in.close();

  Poem foo("poem.dat");
  wcout << foo << endl;

  return 0;
}
