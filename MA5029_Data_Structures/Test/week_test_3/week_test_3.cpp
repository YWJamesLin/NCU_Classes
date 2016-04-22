#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

struct data_pair
{
  int count, first;
  data_pair(int c, int f): count(c), first(f){}
};

bool operator<(const data_pair& a, const data_pair& b)
{
  if(a.count < b.count){ return 0; }
  else if(a.count > b.count){ return 1; }
  else
  {
    if(a.first < b.first){ return 0; }
    else{ return 1; }
  }
}

typedef multimap<data_pair, wstring>::const_iterator wmmItr;

int main()
{
  int ncode, stroke, fstroke, total_strokes;
  const int max_stroke = 50;
  bool first;
  multimap<int, int> strokeWchar;
  map<int, int> wcharStroke;
  multimap<data_pair, wstring> nameData;
  ifstream in;
  wifstream win;
  string lstr, cstr, tstr;
  wstring wlstr;
  istringstream listr, cistr;
  wistringstream wcistr;
  wchar_t wch;
  locale uzh("zh_TW.UTF-8");

  setlocale(LC_ALL, "zh_TW.UTF-8");
  in.open("data");
  while(getline(in, lstr))
  {
    listr.str(lstr);
    listr >> cstr;
    if(cstr == "#")
    {
      listr.clear();
      continue;
    }
    cistr.str(cstr.substr(2));
    cistr >> hex >> ncode;
    cistr.clear();
    listr >> tstr;
    if(tstr != "kTotalStrokes")
    {
      listr.clear();
      continue;
    }
    listr >> stroke;
    cout << stroke << endl;
    strokeWchar.insert(make_pair<int, int>(stroke, ncode));
    wcharStroke.insert(make_pair<int, int>(ncode, stroke));
  }
  in.close();
  
  win.open("name");
  win.imbue(uzh);
  while(getline(win, wlstr))
  {
    first = true;
    total_strokes = 0;
    wcistr.str(wlstr);
    while(wcistr >> wch)
    {
      wcout << total_strokes;
      total_strokes += (wcharStroke.find(static_cast<int>(wch))) -> second;
      if(first == true){
        fstroke = total_strokes; 
        first = false;
        }
    }
    wcistr.clear();
    nameData.insert(make_pair(data_pair(total_strokes, fstroke), wlstr));
  }
  win.close();

  pair<wmmItr, wmmItr> wmmItrs;
  wmmItr begin, end, j;
  data_pair kkk(1, 0);
  for(int i=1, k; i < max_stroke+1; ++i)
  {
    wcout << i << L"劃：" << endl;
    kkk.count = i;
    wmmItrs = nameData.equal_range(kkk);
    wcout << ((wmmItrs.first)->first).first;
    if(wmmItrs.first != wmmItrs.second)
    {
      for(j = wmmItrs.first; j != wmmItrs.second; ++j)
      {
        wlstr = j->second;
        wcout << wlstr << L" ： " << (j->first).count << L" => ";
        for(k=0; k < wlstr.length(); ++k)
        {
          wcout << (wcharStroke.find(static_cast<int>(wlstr[k])))->second << L"|";
        }
        wcout << endl;
      }
    }
  }

  return 0;
}


/*




















#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

typedef multimap<int, int>::const_iterator mmItr;
typedef multimap<int, wstring>::const_iterator wmmItr;

int strokeUbound = 50;

int main()
{
  locale uzh("zh_TW.UTF-8");
  multimap<int, int> tStroke;
  multimap<int, wstring> tIdiom;
  map<int, int> charMap;
  ifstream in;
  wifstream win;
  int ncode, ccnt, maxStroke, tmpStroke;
  istringstream listr, manipStr;
  string lineStr, cstr, tstr;
  wchar_t wch;
  wistringstream wlistr;
  wstring wlineStr;

  setlocale(LC_ALL, "zh_TW.UTF-8");
  in.open("data");
  while(getline(in, lineStr))
  {
    listr.str(lineStr);
    listr >> cstr;
    if(cstr == "#")
    {
      listr.clear();
      continue;
    }
    manipStr.str(cstr.substr(2));
    manipStr >> hex >> ncode;
    manipStr.clear();
    listr >> tstr;
    if(tstr != "kTotalStrokes")
    {
      listr.clear();
      continue;
    }
    listr >> ccnt;
    listr.clear();
    tStroke.insert(make_pair<int, int>(ccnt, ncode));
    charMap.insert(make_pair<int, int>(ncode, ccnt));
  }
  in.close();

  win.open("idiom");
  win.imbue(uzh);
  while(getline(win, wlineStr))
  {
    maxStroke=0;
    wlistr.str(wlineStr);
    while(wlistr >> wch)
    {
      tmpStroke = (charMap.find(static_cast<int>(wch))) -> second;
      if(tmpStroke > maxStroke){ maxStroke = tmpStroke; }
    }
    wlistr.clear();
    tIdiom.insert(make_pair<int, wstring>(maxStroke, wlineStr));
  }
  win.close();
  
  pair<wmmItr, wmmItr> wmmItrs;
  wmmItr j;
  for(int i=1; i < strokeUbound+1; ++i)
  {
    wmmItrs = tIdiom.equal_range(i);
    if(wmmItrs.first != wmmItrs.second)
    {
      wcout << i << L"畫：" << endl;
      for(j = wmmItrs.first; j != wmmItrs.second; ++j)
      {
        wcout << j->second << L"　　　";
        wlistr.str(j->second);
        while(wlistr >> wch){ wcout << setw(3) << (charMap.find(static_cast<int>(wch)))->second << "|"; }
        wlistr.clear();
        wcout << endl;
      }
    }
  }

  return 0;
}
*/
