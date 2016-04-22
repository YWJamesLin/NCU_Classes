/*
學號：102201504
系級：數學2A
姓名：林溢偉
第_次作業：6
編譯環境：ViM with Gnu Compiler Collection in Arch Linux
*/
#include <iostream>

using namespace std ;

class Point {
  private :
    int x, y ;

  public :
    Point () : x (0) , y (0) {}

    Point ( int a , int b ) : x (a) , y (b) {}

    int getx () const { return x; }

    int gety () const { return y; }

    friend ostream& operator<< ( ostream& out , const Point& in ) {
      out << '(' << in.x << ',' << in.y << ')' ;
      return out ;
    }

    //operator <
    friend bool operator< ( const Point& a , const Point& b ) {
      if ( a.x == b.x ) {
        return a.y <= b.y ;
      } else {
        return a.x < b.x ;
      }
    }
} ;

class by_larger_len {
  private:

  public:
    //compare the length
    bool operator() ( const Point& a , const Point& b ) {
      return a.getx () * a.getx () + a.gety () * a.gety () >= b.getx () * b.getx () + b.gety () * b.gety () ;
    }
} ;

template<class T>
struct Node {
    T data ;
    Node<T> *pre , *post ;

    Node () : pre (NULL) , post (NULL) {}
    Node ( const T& d ) : data (d) , pre (NULL) , post (NULL) {}
} ;

template<class T>
class List {
  private :
    Node<T> *head , *tail ;
    int len ;

  public :
    List () : head(NULL) , tail(NULL) , len(0) {}

    //Constructor for array
    List ( const T* begin , const T* end ) {
      Node<T> *cNode ;
      const T *iter ;
      int count ;

      cNode = new Node<T> ;
      cNode -> data = *begin ;
      cNode -> pre = NULL ;
      head = cNode ;

      iter = begin ;
      ++ iter ;
      ++ count ;
      while ( iter != end ) {
        cNode -> post = new Node<T> ;
        cNode -> post -> data = *iter ;
        cNode -> post -> pre = cNode ;
        cNode = cNode -> post ;
        ++ iter ;
        ++ count ;
      }
      
      cNode -> post = NULL ;
      tail = cNode ;
      len = count ;
    }

    //Copy Constructor
    List ( const List<T>& src ) {
      if ( src.len == 0 ) {
        head = tail = NULL ;
        len = 0 ;
      } else {
        Node<T> *cNode, *iter ;
        int count ;

        cNode = new Node<T> ;
        cNode -> data = src.head -> data ;
        cNode -> pre = NULL ;
        head = cNode ;

        iter = src.head ;
        iter = iter -> post ;
        ++ count ;
        while (iter) {
          cNode -> post = new Node<T> ;
          cNode -> post -> data = *iter ;
          cNode -> post -> pre = cNode ;

          cNode = cNode -> post ;
          iter = iter -> post ;
          ++ count ;
        }
      
        cNode -> post = NULL ;
        tail = cNode ;
        len = count ;
      }
    }

    //Destructor
    ~List () {
      Node<T> *tmp, *iter ;
      iter = head ;
      while ( iter ) {
        tmp = iter ;
        iter = iter -> post ;
        delete tmp ;
      }
    }

    //Assignment Operator
    List<T> operator= ( const List<T>& src ) {
      if ( this == &src ) {
        return src ;
      } else if ( src.len == 0 ) {
        head = tail = NULL ;
        len = 0 ;
      } else {
        Node<T> *cNode , *iter ;
        int count ;

        cNode = new Node<T> ;
        cNode -> data = src.head -> data ;
        cNode -> pre = NULL ;
        head = cNode ;

        iter = src.head ;
        iter = iter -> post ;
        ++ count ;
        while ( iter ) {
          cNode -> post = new Node<T> ;
          cNode -> post -> data = *iter ;
          cNode -> post -> pre = cNode ;

          cNode = cNode -> post ;
          iter = iter -> post ;
        }
        cNode -> post = NULL ;
        tail = cNode ;
        len = count ;
      }
      return *this ;
    }
    
    friend ostream& operator<< ( ostream& out, const List<T>& in ) {
      Node<T> *tmp = in.head ;
      while ( tmp) {
        out << tmp -> data << ' ' ;
        tmp = tmp -> post ;
      }
      return out ;
    }

    void sort () {
      if ( len <= 1 ) { return; }
      
      Node<T> *p, *q, *r ;
      T tmp ;

      //Sort with Insertion Sort
      for ( p = head ; p != tail ; p = p -> post ) {
        r = p ;
        for ( q = p -> post ; q != NULL ; q = q -> post ) {
          if ( q -> data < r -> data ) { r = q ; }
        }
        if (r != p) {
          tmp = r -> data ;
          r -> data = p -> data ;
          p -> data = tmp ;
        }
      }
    }
    
    template <class F>
    void sort (F fn) {
      if (len <= 1) { return ; }

      Node<T> *p, *q, *r ;
      T tmp ;

      //Sort with Insertion Sort
      for ( p = head; p != tail; p = p -> post ) {
        r = p ;
        for ( q = p -> post ; q != NULL ; q = q -> post ) {
          if ( fn ( q -> data, r -> data ) ) { r = q ; }
        }
        if ( r != p ) {
          tmp = r -> data ;
          r -> data = p -> data ;
          p -> data = tmp ;
        }
      }
    }
} ;

int main () {
  Point pts[] = { Point(2, 3), Point(4, 5), Point(1, 2), Point(0, 2) } ;
  List<Point> foo (pts, pts+4) ;
  cout << foo << endl ;

  foo.sort () ;
  cout << foo << endl ;

  foo.sort ( by_larger_len() ) ;
  cout << foo << endl ;

  return 0 ;
}
