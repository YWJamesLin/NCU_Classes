/*
學號：102201504
系級：數學2A
姓名：林溢偉
第_次作業：4
編譯環境：ViM with Gnu Compiler Collection in Arch Linux
*/
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std ;

// Use "typedef" to alias some types
typedef vector< vector<wchar_t> >::const_iterator vvcitr ;
typedef vector<wchar_t>::iterator vitr ;
typedef vector<wchar_t>::const_iterator vcitr ;
typedef set<wchar_t>::const_iterator scitr ;

int main() {
  //locale configuration
  locale uzh("zh_TW.UTF-8") ;
  setlocale(LC_ALL, "zh_TW.UTF-8") ;

  wifstream in ;
  wstring wstr ;
  vector< vector<wchar_t> > poems ;
  //tmpset is to temp and compute intersection sets
  vector<wchar_t> tmpset[2] ;
  // c == compare, one of the sets to compute intersections
  vcitr cbegin, cend ;
  // intsec is to save our final intersection sets
  set<wchar_t> intsec ;
  int now ;

  in.open("data") ;
  in.imbue(uzh) ;
  while ( in >> wstr ) {
    vector<wchar_t> poem ;
    for ( int i = 0 ; i < wstr.length() ; ++ i ) {
      // get rid of some punctuations
      if ( wstr[i] != L',' && wstr[i] != L'。' ) {
        poem.push_back ( wstr[i] ) ;
      }
    }
    sort ( poem.begin(), poem.end() ) ;
    poems.push_back ( poem ) ;
  }
  in.close() ;

  // now is to record which tmpset to use
  now = 0 ;
  // first to compute the first and second poem
  // first
  cbegin = poems[0].begin(), cend = poems[0].end() ;
  //second
  vvcitr i = poems.begin() ;
  ++i;
  for(; i != poems.end() ; ++ i ) {
    set_intersection( cbegin , cend , i->begin() , i->end() , back_inserter ( tmpset[now] ) ) ;
    // now, we only need to compute the result and the next poem
    cbegin = tmpset[now].begin() ;
    cend = tmpset[now].end() ;
    // use another tmpset and clean when computed
    now = !now ;
    tmpset[now].clear() ;
  }
  for ( vcitr i = tmpset[!now].begin() ; i != tmpset[!now].end() ; ++ i ) {
    if ( intsec.find(*i) == intsec.end() ) {
      intsec.insert(*i) ; 
    }
  }
  for ( scitr i = intsec.begin() ; i != intsec.end() ; ++ i ) {
    wcout << *i << L'　' ;
  }
  wcout << endl ;

  return 0 ;
}
