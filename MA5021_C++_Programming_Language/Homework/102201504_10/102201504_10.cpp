/*
學號:102201504
系級:數學2A
姓名:林溢偉
第_次作業:10
編譯環境:Arch Linux with Vim + GNU C++ compiler
*/
#include <iostream>
#include <unistd.h>
#include <fstream>
#define S 50000

using namespace std;

int main() {
  int i , j , k , ind ;//ind是indent
  //用Unsigned Int 來存Bitmap較不容易產生錯誤，data為拆分小單位，compdata為大單位
  unsigned int data[32] , compdata[8] ;
  ifstream in ;//in用來讀取檔案
  ofstream out ;//out用來輸出檔案

  in.setf ( ios_base::hex , ios_base::basefield ) ;//先設定十六進位旗標
  in.open ( "hex" , ios_base::in ) ;//開啟檔案，hex是十六進位數字（文字檔）
  //讀取檔案中的每個十六進位碼
  for ( i = 0 ; i < 32 ; ++ i ) {
    in >> data[i];
  }
  in.close() ;//關閉檔案
  in.setf ( ios_base::dec , ios_base::basefield ) ;//將旗標設定回原樣
  out.open ( "comp" , ios_base::in | ios_base::binary ) ;//開啟檔案，comp為壓縮(compress)過後的數字（二進位）
  for ( i = 0 ; i < 8 ; ++ i ) {
    compdata[i] = ( data[i*4] << 21 ) + ( data[i*4+1] << 14 ) + ( data[i*4+2] << 7 ) + data[i*4+3] ;
    out.write ( reinterpret_cast<char *> ( compdata + i ) , sizeof ( int ) ) ;//寫入檔案
  }
  out.close() ;//關閉檔案
  in.open ( "comp" , ios_base::in | ios_base::binary ) ;//開啟欲讀取的二進位檔
  for ( i = 0 ; i < 8 ; ++ i ) {
    in.read(reinterpret_cast<char *> ( compdata + i ) , sizeof ( int ) ) ;//讀取檔案
  }
  in.close();//關閉檔案
  //分解每個compdata
  for( i = 0 ; i < 8 ; ++ i ) {
    data[i*4] = ( compdata[i] >> 21 ) ;
    data[i*4+1] = ( ( compdata[i] << 11 ) >> 25 ) ;
    data[i*4+2] = ( ( compdata[i] << 18 ) >> 25 ) ;
    data[i*4+3] = ( ( compdata[i] << 25 ) >> 25 ) ;
  }
  //組合為以row為基準的Bitmap，這樣輸出調整時比較方便，另外直接把每個字的空白囊括進去
  for ( i = 0 ; i < 8 ; ++ i ) { 
    compdata[i] = ( data[i] << 24 ) + ( data[i+8] << 16 ) + ( data[i+16] << 8 ) + data[i+24] ;
  }
  while ( 1 ) {
    //位移向量(indent)
    for ( ind = 0 ; ind < 32 ; ++ ind ) {
      cout << "\x1b[2J" ;//清空螢幕
      //shift向量
      for ( i = 31 ; i >= 0 ; -- i ) {
        for ( j = 0 ; j < 8 ; ++ j ) {
          cout << "\x1b[" << j+1 << ";" << ( 32 - i ) * 2 - 1 << "H" ;
          //%32部份是讓位元位移可以rotate
          if ( ( compdata[j] >> ( ( i - ind + 32 ) %32 ) ) % 2 ) {
            cout << "  " ;
          }
          else {
            cout << "\x1b[47m  \x1b[0m" ;
          }
        }
      }
      cout << "\x1b[9;1H" << flush ;
      usleep ( S ) ;
    }
  }

  return 0 ;
}
