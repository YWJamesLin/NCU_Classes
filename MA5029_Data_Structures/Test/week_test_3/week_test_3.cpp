#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef multimap<int, wstring>::const_iterator wmmItr;
typedef multimap<int, int>::const_iterator mmItr;

struct cntNode{
  int index, count;
  cntNode(int i ,int c): index(i) , count(c){}
} ;

struct compare{
  bool operator()(const cntNode& a, const cntNode& b){ return a.count > b.count; }
} ;

int max_stroke = 50;

int main()
{
  multimap<int, int> tStroke;
  multimap<int, int> sTimes;
  multimap<int, wstring> tStrokeNames;
  vector<cntNode> cntMap;
  
  ifstream in;
  wifstream win;
  istringstream listr, manipStr;
  
  int ncode, ccnt, opcount, strokeSum;
  string lineStr, cstr, tstr;
  wstring wstr;

  locale uzh("zh_TW.UTF-8");
  setlocale(LC_ALL, "zh_TW.UTF-8");

  in.open("udata");
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
    if(tstr != "kTotalStrokes" || ncode < 0x4e00 || ncode > 0x9fa5)
    {
      listr.clear();
      continue;
    }
    listr >> ccnt;
    listr.clear();
    tStroke.insert(make_pair<int, int>(ccnt, ncode));
    sTimes.insert(make_pair<int, int>(ncode, ccnt));
  }
  in.close();

  win.open("names");
  win.imbue(uzh);
  while(win >> wstr)
  {
    strokeSum = 0;
    for(int i = 0; i < 3; ++i){ strokeSum += (sTimes.find(wstr[i])) -> second; }
    tStrokeNames.insert(make_pair<int, wstring>(strokeSum, wstr));
  }

  pair<wmmItr, wmmItr> wmmItrs;
  wstring tmpws;
  for(int i = 1; i <= 33; ++i)
  {
    wmmItrs = tStrokeNames.equal_range(i);
    if(wmmItrs.first != wmmItrs.second)
    {
      wcout << i << L"劃：" << endl;
      for(wmmItr j = wmmItrs.first; j != wmmItrs.second; ++j)
      {
        wcout << j->second << L"：" << j->first << L" => ";
        tmpws = (j -> second);
        for(int k = 0; k < 3; ++k)
        {
          wcout << ((sTimes.find(tmpws[k])) -> second);
          if(k != 2){ wcout << L"|"; }
        }
        wcout << endl;
      }
    }
  }

  return 0;
}
