/*
學號：102201504
系級：數學2A
姓名：林溢偉
第_次作業：5
編譯環境：ViM with Gnu Compiler Collection in Arch Linux
*/
#include <iostream>

using namespace std ;

template<typename T>
class Vector {
  private :
    T* inst ;
    int osize , rsize ;

  public :
    //Constructor
    Vector () : inst (NULL) , osize (0) , rsize(0) {}

    Vector ( int n , const T& s = 0 ) : osize (n) , rsize (2 * n) {
      inst = ( n > 0 ? new T[rsize] : NULL ) ;
      for ( int i = 0; i < n; ++ i ) {
        inst[i] = s ;
      }
    }

    Vector ( const T* begin , const T* end ) : inst (NULL) , osize (0), rsize (0) {
      for ( const T* i = begin ; i != end ; ++ i ) {
        push_back ( *i ) ;
      }
    }

    //Copy Constructor
    Vector ( const Vector<T>& src ) {
      osize = src.osize ;
      rsize = src.rsize ;
      inst = ( rsize > 0 ? new T[rsize] : NULL ) ;
      for ( int i = 0; i < osize; ++ i ) {
        inst[i] = src.inst[i] ;
      }
    }

    //Destructor
    ~Vector () {
      if ( rsize > 0 ) {
        delete [] inst ;
      }
    }

    void push_back ( const T& val ) {
      if ( osize == rsize ) {
        rsize = ( rsize ? 2 * rsize : 1 ) ;
        T* tmp = new T[2 * rsize] ;
        for ( int i = 0 ; i < osize ; ++ i) {
          tmp[i] = inst[i] ;
        }
        tmp[osize] = val ;
        delete [] inst ;
        inst = tmp ;
      } else {
        inst[osize] = val ;
      }
      ++ osize ;
    }

    void pop_back () {
      if ( osize > 0 ) {
        -- osize ;
      }
    }

    void resize ( int s ) {
      if ( s > rsize ) {
        //if s is more than twice of rsize, then reserve amount of s
        rsize = ( rsize * 2 > s ? rsize * 2 : s ) ;
        T* tmp = new T[rsize] ;
        for ( int i = 0 ; i < osize ; ++ i ) {
          tmp[i] = inst[i] ;
        }
        delete [] inst ;
        inst = tmp ;
      }
    }

    //print reserved size
    int reserve () const {
      return rsize ;
    }

    //print size
    int size () const {
      return osize ;
    }

    T& operator[] ( int i ) {
      return inst[i] ;
    }

    const T& operator[] ( int i ) const {
      return inst[i] ;
    }

    friend ostream& operator<< ( ostream& out , const Vector<T>& in ) {
      for ( int i = 0 ; i < in.osize ; ++ i ) {
        out << in.inst[i] << " " ;
      }
      out << endl ;
      return out ;
    }

    //Assignment Operator
    Vector& operator= ( const Vector<T>& src ) {
      if ( this == &src ) {
        return *this ;
      }
      if ( src.osize == 0 ) {
        osize = 0 ;
        return *this ;
      }

      int i ;
      if ( src.osize <= rsize ) {
        osize = src.osize ;
        for ( int i = 0 ; i < osize ; ++ i ) {
          inst[i] = src.inst[i] ;
        }
      } else {
        delete [] inst ;
        rsize = src.rsize ;
        osize = src.osize ;
        inst = new T[rsize] ;
        for ( int i = 0 ; i < osize ; ++ i ) {
          inst[i] = src.inst[i] ;
        }
      }
    }
} ;

int main() {
  int x[5] = { 3 , 2 , 4 , 1 , 2 } ;
  Vector<int> a , b(3) , c(5 , 2) ;
  Vector<int> d(c) , e(x , x+5) ;

  cout << d << endl ;

  cout << b << c << e << endl ;

  c.pop_back() ;
  cout << "pop back c then c is:" << endl ;
  cout << c ;
  cout << "size{c} == " << c.size() << endl ;
  cout << "reserve{c} == " << c.reserve() << endl ;

  c.push_back(5) ;
  c.push_back(10) ;
  cout << "push 2 things to c then c is:" << endl ;
  cout << c ;
  cout << "size{c} == " << c.size() << endl ;
  cout << "reserve{c} == " << c.reserve() << endl ;

  c.resize(20) ;
  cout << "resize c to 11 then: " << endl ;
  cout << "reserve{c} == " << c.reserve() << endl ;

  c.resize(41) ;
  cout << "resize c to 31 then: " << endl ;
  cout << "reserve{c} == " << c.reserve() << endl ;

  d = c ;
  cout << "assign c to d then d is: " << endl ;
  cout << d ;
  return 0 ;
}
