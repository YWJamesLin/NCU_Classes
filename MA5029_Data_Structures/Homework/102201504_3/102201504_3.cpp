/*
學號：102201504
系級：數學2A
姓名：林溢偉
第_次作業：3
編譯環境：ViM with Gnu Compiler Collection in Arch Linux
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std ;

typedef multimap<int, int>::const_iterator mmItr ;

struct cntNode {
  int index , count ;
  cntNode ( int i , int c ) : index(i) , count(c) {}
} ;

struct compare {
  bool operator() ( const cntNode& a , const cntNode& b ) {
    return a.count > b.count ;
  }
} ;

int max_stroke = 50 ;//max number of strokes

int main() {
  multimap<int, int> tStroke ;
  //to map #{strokes} to those characters
  vector<cntNode> cntMap ;
  //to restore counts and sort it easily
  ifstream in ;
  int ncode , ccnt , opcount ;
  //ncode is the char. code of the character, ccnt is the stroke of that char., opcount is to count output
  istringstream listr, manipStr ;
  //listr is to save line input, manipStr is to manipulate the U+XXXX string
  string lineStr, cstr, tstr ;

  setlocale(LC_ALL, "zh_TW.UTF-8") ;
  in.open("data") ;
  while ( getline ( in, lineStr ) ) {
    listr.str ( lineStr ) ;
    listr >> cstr ;
    //filter the "#"-begined string
    if ( cstr == "#" ) {
      listr.clear() ;
      continue ;
    }
    manipStr.str ( cstr.substr(2) ) ;
    manipStr >> hex >> ncode ;
    manipStr.clear() ;
    listr >> tstr ;
    //only need the stroke data
    if ( tstr != "kTotalStrokes" || ncode < 0x4e00 || ncode > 0x9fa5 ) {
      listr.clear() ;
      continue ;
    }
    listr >> ccnt ;
    listr.clear() ;
    tStroke.insert ( make_pair<int, int>( ccnt, ncode ) ) ;
  }
  in.close() ;

  for ( int i=1 ; i < max_stroke + 1 ; ++ i ) {
    wcout << i << L"畫︰" << tStroke.count(i) << endl ;
    //put the counting number in this container
    cntMap.push_back ( cntNode ( i, tStroke.count(i)) ) ;
    //enumerate the characters
    pair<mmItr, mmItr> mmitrs ;
    mmitrs = tStroke.equal_range(i) ;
    opcount = 0 ;
    if ( mmitrs.first != mmitrs.second ) {
      for ( mmItr j = mmitrs.first ; j != mmitrs.second ; ++ j ) {
        wcout << static_cast<wchar_t> ( j -> second ) << " " ;
        ++opcount ;
        if( opcount == 25 ) {
          wcout << endl ;
          opcount = 0 ;
        }
      }
      wcout << endl ;
    }
  }
  wcout << endl ;
  sort ( cntMap.begin() , cntMap.end() , compare() ) ;
  for ( vector<cntNode>::iterator i = cntMap.begin() ; i != cntMap.end() ; ++ i ) {
    wcout << i->index << L"畫 ： " << i->count << L"個" << endl ;
  }

  return 0 ;
}
