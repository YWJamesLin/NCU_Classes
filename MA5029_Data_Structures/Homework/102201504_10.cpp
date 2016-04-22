#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <iomanip>
#include <cassert>

using namespace std ;

// get a gcd
int gcd ( int a, int b ) {
  int tmp ;
  while ( a %  b) {
    tmp = a % b ;
    a = b ;
    b = tmp ;
  }
  return b ;
}

template<typename T>
T str2num ( const string& foo ) {
  istringstream istr ( foo ) ;
  T num ;
  istr >> num ;
  return num ;
}


template<typename T>
string num2str ( const T& num ) {
  ostringstream ostr ;
  ostr << num ;
  return ostr.str () ;
}

class Fraction {
  private :
    int child , mother ;

  public :
    Fraction () : child (0) , mother (1) {}
    
    Fraction ( const int& c, const int& m ) : child (c) , mother (m) {}

    friend Fraction operator+ ( const Fraction & a , const Fraction& b ) {
      int c , m , g ;

      c = a.child * b.mother + a.mother * b.child ;
      m = a.mother * b.mother ;
      g = gcd ( c , m ) ;
      c /= g ;
      m /= g ;
      return Fraction ( c , m ) ;
    }

    friend Fraction operator- ( const Fraction & a , const Fraction& b ) {
      int c , m , g ;

      c = a.child * b.mother - a.mother * b.child ;
      m = a.mother * b.mother ;
      g = gcd ( c , m ) ;
      c /= g ;
      m /= g ;
      return Fraction ( c , m ) ;
    }

    friend Fraction operator* ( const Fraction & a , const Fraction& b ) {
      int c , m , g ;

      c = a.child * b.child ;
      m = a.mother * b.mother ;
      g = gcd ( c , m ) ;
      c /= g ;
      m /= g ;
      return Fraction ( c , m ) ;
    }

    friend Fraction operator/ ( const Fraction & a , const Fraction& b ) {
      int c, m, g ;

      c = a.child * b.mother ;
      m = a.mother * b.child ;
      g = gcd ( c , m ) ;
      c /= g ;
      m /= g ;
      return Fraction ( c , m ) ;
    }

    friend istream& operator>> ( istream& in , Fraction& obj ) {
      char tmp ;
      in >> obj.child >> tmp >> obj.mother ;
      return in ;
    }

    friend ostream& operator<< ( ostream& out , const Fraction& src ) {
      out << src.child << '/' << src.mother ;
      return out ;
    }
} ;

template<typename T>
struct Node {
  T  data ;
  Node<T>  *left, *right ;

  Node () : left (NULL) , right (NULL) {}
  Node (const T& d) : data (d) , left (NULL) , right (NULL) {}

  // check if this node is a leaf node
  bool  is_leaf_node () const {
    return  ( left == NULL && right == NULL  ? true : false ) ;
  }
} ;

template<typename T>
Node<T>*  make_node ( const T& d ) {
  return  new Node<T> ( d ) ;
}


template<typename T>
ostream& operator<< ( ostream& out , const Node<T>& foo ) {
  return out << foo.data ;
}


template<typename T>
class Expression_Tree {
  private :
    Node<string>  *root ;

    void  build_tree ( const string& exp ) {
      stack< Node<string>* >  foo ;
      istringstream  istr ( exp ) ;

      string   seq ;
      string   optr = "+-*/" ;
      Node<string>  *ptr ;

      
      while ( istr >> seq ) {
        ptr = make_node ( seq ) ;
        if ( optr.find ( seq ) != string::npos ) {
          // if this sequence is an operator
          ptr -> right = foo.top () ;
          foo.pop () ;
          ptr -> left = foo.top () ;
          foo.pop ();
          foo.push ( ptr ) ;
        } else {
          foo.push ( ptr ) ;
        }
      }

      root = foo.top () ;
      foo.pop () ;

      // Assertion
      assert ( foo.size () == 0 ) ;
    }


    T  evaluate_subtree (const Node<string>* ptr) const {
      if (ptr -> is_leaf_node ()) {
        return str2num<T> (ptr -> data);
      } else {
        T  a, b;

        a = evaluate_subtree (ptr -> left);
        b = evaluate_subtree (ptr -> right);

        if (ptr -> data == "+") {
          return a + b;
        } else if (ptr -> data == "-") {
          return a - b;
        } else if (ptr -> data == "*") {
          return a * b;
        } else if (ptr -> data == "/") {
          return a / b;
        }
      }
    }

  public :

    Expression_Tree (Node<string>* r) : root (r) {}

    Expression_Tree (const string& exp) : root (NULL) {
      build_tree(exp);
    }


    // Copy Constructor
    Expression_Tree (const Expression_Tree<T>& foo) {
      if (foo.root == NULL) {
        root = NULL;
      } else {
        root = new Node<string> (foo.root->data);
        copy_subtree (root , foo.root);
      }
    }

    // Assignment Operator
    Expression_Tree<T>& operator= (const Expression_Tree<T>& foo) {
      if (root == foo.root) {
        return *this;
      } else {
        erase_subtree (root);
        copy_subtree (root , foo.root);
        return *this;
      }
    }

    void erase_subtree (Node<string>* ptr) {
      if (ptr) {
        erase_subtree (ptr->left);
        erase_subtree (ptr->right);
        delete ptr;
        ptr = NULL;
      } 
    }

    T evaluate () const { return  evaluate_subtree (root); }



    void copy_subtree (Node<string>* &ptr, const Node<string> *q) const {
      if (q == NULL) {
        ptr = NULL;
      } else {
        ptr = new Node<string> (q -> data);
        copy_subtree (ptr -> left, q -> left);
        copy_subtree (ptr -> right, q -> right);
      }
    }


    ~Expression_Tree () { erase_subtree (root); }


    void  print_subtree (ostream& out, const Node<string>* ptr, int depth = 1) const {
      if (ptr == NULL) {
        out << setw ((depth - 1) * 5) << "|--> " << setw (5) << left << "." << right << "\n";
      } else {
        if (depth > 1) {
          out << setw ((depth - 1) * 5) << "|--> " << setw (5) << left;
        }
        out << ptr -> data << right << endl;
        if ( ! ptr -> is_leaf_node ()) {
          print_subtree (out, ptr->right, depth + 1);
          print_subtree (out, ptr->left, depth + 1);
          if (ptr -> left == NULL || (ptr -> left != NULL && ptr -> left -> is_leaf_node ())) { out << endl; }
        }
      }
    }

    friend ostream& operator<< (ostream& out , const Expression_Tree<T>& foo) {
      foo.print_subtree (out, foo.root);
      return out;
    }

    friend Expression_Tree operator+ (const Expression_Tree<T>& a, const Expression_Tree<T>& b) {
      Node<string>* root;
      string str = "+";
      
      root =  make_node (str);
      root -> left = a.root;
      root -> right = b.root;

      return Expression_Tree<T> (root);
    }
};

int main () {
  string expstr = "3 7 + 5 / 3 5 * 2 3 * 1 + 2 - / * 2 3 6 1 - + - +";

  Expression_Tree<int> foo (expstr);

  cout << foo << "\n"
       << "value : " << foo.evaluate () << "\n\n";

  expstr = "5/8 10/4 / 2/3 * 2 6/8 - +";
  
  Expression_Tree<Fraction> bar (expstr);

  cout << bar << "\n"
       << "value : " << bar.evaluate () << endl;

  return 0;
}
