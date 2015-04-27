/*
學號:102201504
系級:數學2A
姓名:林溢偉
第_次作業:10
編譯環境:Arch Linux with ViM + GNU C++ Compiler
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>//cctype header可用來判斷char type

using namespace std;

int main() {
  bool next ;//用來判斷有沒有下一個要數的字
  int i , j , count ;
  char alp ;
  string str ;
  ifstream in ;
  istringstream strin ;

  //整支程式的概念是把檔案讀取後，一個字一個字存入istringstream中，再以此istringstream讀進字元判斷並計數
  for ( i = 0 ; i < 10 ; ++ i ) {
    count = 1 ;
    next = false ;
    in.clear() ;
    in.open( "data.txt" , ios_base::in ) ;
    //針對每個case預先讀取不要的string
    for ( j = 0 ; j < i ; ++ j ) {
      in >> str ;
    }
    while ( 1 ) {
      for ( j = 0 ; j < count ; ++ j ) {
        in >> str ;
      }
      //End Of File就跳出
      if ( in.eof() ) {
        in.close() ;
        cout << endl ;
        break ; 
      }
      //有下一個就輸出此字串
      if ( next == true ) { 
        cout << " --> ";
      }
      //count用來數字母用
      count = 0 ;
      strin.str ( str ) ;
      //讀取為"字母"時計數並輸出
      while ( ( strin >> alp ) && isalpha ( alp ) ) {
        cout << alp ;
        ++ count ;
      }
      //清除旗標
      strin.clear() ;
      next = true ;
    }
  }

  return 0 ;
}
