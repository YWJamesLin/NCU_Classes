/*
學號：102201504
系級：數學2A
姓名：林溢偉
第_次作業：2
編譯環境：ViM with Gnu Compiler Collection in Arch Linux
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std ;

class Color {
  private:
    string name ;
    int rgb[3] ;

  public:
    Color ( string str , int* r ) : name(str) {
      for ( int i = 0 ; i < 3 ; ++ i ) {
        rgb[i] = r[i] ;
      }
    }
    //operator[] is to fetch data directly from object
    int operator[] ( int n ) const {
      return rgb[n] ;
    }
    //compare operator
    friend bool operator< ( const Color& a , const Color& b ) {
      //色碼大者放前面，相同時名稱長度小者放前面
      if ( ( ( a[0] << 16 ) | ( a[1] << 8 ) | a[2] ) == ( ( b[0] << 16 ) | ( b[1] << 8 ) | b[2] ) ) {
        return a.name.length() < b.name.length() ;
      }
      else {
        return ( ( a[0] << 16 ) | ( a[1] << 8 ) | a[2] ) > ( ( b[0] << 16 ) | ( b[1] << 8 ) | b[2] ) ;
      }
    }

    friend ostream& operator<< ( ostream& out , const Color& in ) {
      out << setw(15) << in.name << " :" ;
      for ( int i = 0 ; i < 3 ; ++ i ) {
        out << setw(4) << in.rgb[i] ;
      }
      return out ;
    }
};

int main() {
  ifstream in ;
  vector<Color> colorList ;
  string tmpstr ;
  int tmprgb[3] ;
  char tmpc ;
  
  in.open("data") ;
  while(1)
  {
    if ( in.eof() ) {
      break;
    }
    in >> tmpstr ;
    for ( int i = 0 ; i < 3 ; ++ i ) {
      in >> tmprgb[i] ;
    }
    //generate color object 
    colorList.push_back ( Color( tmpstr, tmprgb ) ) ;
  }
  in.close() ;

  sort ( colorList.begin() , colorList.end() ) ;
  for ( int i = 0 ; i < colorList.size() ; ++ i ) {
    cout << colorList[i] << endl ;
  }

  return 0 ;
}
