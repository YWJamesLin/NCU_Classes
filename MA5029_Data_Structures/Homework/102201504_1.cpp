/*
學號：102201504
系級：數學2A
姓名：林溢偉
第_次作業：1
編譯環境：ViM with Gnu Compiler Collection in Arch Linux
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std ;

class Wordsize {
  public:
    //constructor
    Wordsize ( int& n ) : count ( n ) {} ;
    //operator() is a filter for string 
    const string operator() ( const string& str ) const {
      if ( str.length() >= count ) { return str ; }
      else { return "" ; }
    }
  private:
    int count ;
};

template<class t0>
//printing words
void print_words ( const t0& begin , const t0& end , const Wordsize& fn ) {
  for ( t0 i = begin ; i != end ; ++i ) {
    if ( fn ( *i ) != "" ) {  
      cout << fn ( *i ) ;
      if ( i != end-1 ) { cout << " "; }
    }
  }
}

int main() {
  int n = 4 ;
  string line, word ;
  istringstream istr ;
  vector<string> strs ;

  do {
    cout << "in > " ;
    getline ( cin , line ) ;
    istr.str ( line ) ;
    while ( istr >> word ) { strs.push_back(word); }
    istr.clear() ;
    
    cout << "out> " ;
    print_words ( strs.begin() , strs.end() , Wordsize ( n ) ) ;
    cout << endl ;
    strs.clear() ;
  } while ( 1 ) ;

  return 0 ;
}

