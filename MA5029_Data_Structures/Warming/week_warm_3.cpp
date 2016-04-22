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
