/*
學號：102201504
系級：數學2A
姓名：林溢偉
第_次作業：7
編譯環境：ViM with Gnu Compiler Collection in Arch Linux
*/
#include <iostream>
#include <stack>
#include <sstream>

using namespace std ;

//get gcd of two numbers
int gcd ( int a , int b ) {
  if ( a < b ) {
    a += b ;
    b = a - b ;
    a -= b ;
  }

  int tmp ;
  while ( a % b ) {
    tmp = a % b ;
    a = b ;
    b = tmp ;
  }
  return b ;
}

class Frac {
  private:
    int child, mother ;

  public:
    Frac () : child (0) , mother (0) {}
    Frac (int c, int m) : child (c) , mother (m) {}
    //string type Fraction initializor
    Frac ( string& in ) {
      if ( in.length () > 3 ) {
        child = - ( in[1] - 48 ) ;
        mother = in[3] - 48 ;
      } else {
        child = in[0] - 48 ;
        mother = in[2] - 48 ;
      }
    }

    friend Frac operator+ ( const Frac& a, const Frac& b ) {
      int c = a.child * b.mother + b.child * a.mother ;
      int m = a.mother * b.mother ;
      int g = gcd ( c , m ) ;
      return Frac ( c / g , m / g ) ;
    }

    friend Frac operator- ( const Frac& a , const Frac& b ) {
      int c = a.child * b.mother - b.child * a.mother ;
      int m = a.mother * b.mother ;
      int g = gcd ( c , m ) ;
      return Frac ( c / g , m / g ) ;
    }

    friend Frac operator* ( const Frac& a , const Frac& b ) {
      int c = a.child * b.child ;
      int m = a.mother * b.mother ;
      int g = gcd ( c , m ) ;
      return Frac ( c / g , m / g ) ;
    }

    friend Frac operator/ ( const Frac& a , const Frac& b ) {
      int c = a.child * b.mother ;
      int m = a.mother * b.child ;
      int g = gcd ( c , m ) ;
      return Frac ( c / g , m / g ) ;
    }

    friend ostream& operator<< ( ostream& out , const Frac& in ) {
      out << in.child << '/' << in.mother ;
      return out ;
    }
};

template <class T>
T evalua ( const string& in ) {
  T num1 , num2 ;
  stack<T> num ;
  stack<char> oper ;
  string tmp ;
  istringstream istr ;

  istr.str ( in );
  while ( istr >> tmp ) {
    if ( tmp[0] > 47 && tmp[0] < 58 ) {
      num.push ( Frac ( tmp ) ) ;
    } else {
      if ( tmp.length () > 1 ) {
        num.push ( Frac ( tmp ) ) ;
      } else {
        if ( tmp[0] == ')' ) {
          while ( oper.top () != '(' ) {
            num2 = num.top () ;
            num.pop () ;
            num1 = num.top () ;
            num.pop () ;
            
            switch ( oper.top () ) {
              case '+' :
                num.push ( num1 + num2 ) ;
                break ;
              case '-' :
                num.push ( num1 - num2 ) ;
                break ;
              case '*' :
                num.push ( num1 * num2 ) ;
                break ;
              case '/' :
                num.push ( num1 / num2 ) ;
                break ;
            }
            oper.pop () ;
          }
          oper.pop () ;
        } else {
          oper.push ( tmp[0] ) ;
        }
      }
    }
  }
  return num.top ();
}

int main () {
  string in ;

  getline ( cin , in ) ;
  cout << evalua<Frac> ( in ) << endl ;

  return 0 ;
}
