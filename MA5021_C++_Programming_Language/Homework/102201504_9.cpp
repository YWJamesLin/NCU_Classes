/*
學號:102201504
系級:數學2A
姓名:林溢偉
第_次作業:9
編譯環境:Arch Linux with ViM + GNU C++ Compiler
*/
#include <iostream>
#include <cstdlib>

using namespace std;

//定義SSP_Game類別
class SSP_Game {
  private:
    int i , j , tmp ;//流程變數
    int *narr , *rnd ;//narr存construct時的random shuffle array，rnd存遊戲進行時的亂數
    int np , nw , win ;//np==number of players, nw=number of winners, win是用來確認有無結果
    bool *status ;//status用來存取每位玩家的輸贏狀態
    wstring *name , winname ;//name用來存每位玩家的名子，winname是贏家的名字
    
  public:
    //建構子
    SSP_Game ( wstring *namearr , int num ) {
      srand ( static_cast<unsigned> ( time ( NULL ) ) ) ;//取亂數種子
      narr = new int[num] ;//動態建立陣列
      rnd = new int[num] ;
      name = new wstring[num] ;
      status = new bool[num] ;
      for ( i = 0 ; i < num ; ++ i ) {
        narr[i] = i ;
      }
      //洗牌
      for ( i = 0 ; i < num ; ++ i ) {
        for ( j = num - 1 ; j > 0 ; -- j ) {
          tmp = 1. * rand () * j / ( 1. + RAND_MAX ) ;
          narr[j] += narr[tmp] ;
          narr[tmp] = narr[j] - narr[tmp] ;
          narr[j] -= narr[tmp] ;
        }
      }
      for ( i = 0 ; i < num ; ++ i ) { 
        name[i] = namearr[ narr[i] ] ;
        status[i] = true ;
      }
      np = num ;
      nw = num ;
      
      delete [] narr ;//這個空間可以回收了
    }

    //解構時，將動態空間回收
    ~SSP_Game () {
      delete [] name;
      delete [] rnd;
      delete [] status;
    }
    
    //遊戲進行一輪
    void play () {
      int exist ;

      exist = 0 ;//exist是狀態變數，用位元存取:xyz，x表布，y表石頭，z表剪刀
      for ( i = 0 ; i < np ; ++ i ) {
        //輸的就不用猜拳了
        if ( status[i] == false ) {
          continue ;
        }
        rnd[i] = 3. *rand() / ( 1. * RAND_MAX ) ;
        switch ( rnd[i] ) {
          //剪刀
          case 0:
            exist |= 1 ;
            break ;
          //石頭
          case 1:
            exist |= 2 ;
            break ;
          //布
          case 2:
            exist |= 4 ;
            break ;
        }
      }
      //三種都有或都出一樣就是無勝負
      if ( exist == 7 || exist == 1 || exist == 2 || exist == 4 ) {
        //3表無勝負
        win = 3 ;
      }
      else { 
        switch ( exist ) {
          //101，win=0是剪刀
          case 5:
            win = 0 ;
            break ;
          //011，win=1是石頭
          case 3:
            win = 1 ;
            break ;
          //110，win=2是布
          case 6:
            win = 2 ;
            break ;
        }
      }
    }
    
    //結束與否
    bool over () {
      if ( nw == 1 ) {
        return true;
      }
      else {
        return false;
      }
    }

    //輸出贏家姓名
    wstring winner () {
      return winname ;
    }

    //自定義SSP_Game輸出運算子，用來輸出結果
    friend wostream& operator<< ( wostream& out , SSP_Game& src ) {
      int i;

      //輸出姓名
      for ( i = 0 ; i < src.np ; ++ i ) {
        //上一輪輸的不用印
        if ( src.status[i] == false ) { 
          continue ; 
        }
        out << src.name[i] << L"　" ;
      }
      out << endl ;
      //印出玩家出的拳
      for ( i = 0 ; i < src.np ; ++ i ) {
        //一樣，輸的不用印
        if ( src.status[i] == false ) { 
          continue ;
        }
        switch ( src.rnd[i] ) {
          case 0 :
            out << L"剪刀　" ;
            break ;
          case 1 :
            out << L"石頭　" ;
            break ;
          case 2 :
            out << L"布　　" ;
            break ;
        }
      }
      //如果非無勝負，先進行淘汰
      if ( src.win != 3 ) {
        for ( i = 0 ; i < src.np ; ++ i ) {
          //非贏即輸
          if ( src.status[i] == true && src.rnd[i] !=  src.win ) {
            src.status[i] = false ;
            -- src.nw ;
          }
        }
      }
      //如果出現贏家，決定贏家是誰
      if ( src.nw == 1 ) {
        for ( i=0 ; i < src.np ; ++ i ) {
          if ( src.status [i] == true ) {
            src.winname = src.name[i] ;
            break ;
          }
        }
      }
      //印結果
      out << endl ;
      out << L"-->" ;
      if ( src.nw != 1 ) {
        out << L"無勝負" ; 
      }
      else {
        switch ( src.win ) {
          case 0 :
            out << L"剪刀" ;
            break ;
          case 1 :
            out << L"石頭" ;
            break ;
          case 2 :
            out << L"布" ;
            break ;
        }
      }
      out << endl ;
      return out ;
    }
} ;

int main() {
  int n ;
  wstring names[] = { L"小華" , L"小明" , L"小民" , L"花花" , L"小玟" , L"阿泰" , L"小杰" , L"阿凡" , L"莉莉" , L"阿新" } ;
  setlocale ( LC_ALL , "zh_TW.UTF-8" ) ;
  cin >> n ;
  SSP_Game game ( names , n ) ;

  do
  {
    game.play () ;
    wcout << game << endl; 
  }while( ! game.over () ) ;
  wcout << game.winner () << endl ;

  return 0 ;
}
