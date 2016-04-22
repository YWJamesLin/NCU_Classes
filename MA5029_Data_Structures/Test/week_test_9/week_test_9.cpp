#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <iomanip>
#include <cassert>

using namespace std;

template <typename T>
T str2num (const string& foo) {
  istringstream istr (foo);
  T num;
  istr >> num;
  return num;
}

template <typename T>
string num2str (const T& num) {
  ostringstream ostr;
  ostr << num;
  return ostr.str ();
}

template <typename T>
struct Node {
  T data;
  Node<string> *left, *right;

  Node () : left (NULL), right (NULL) {}
  Node (const T& d) : data (d), left (NULL), right (NULL) {}

  bool is_leaf_node () const {
    return (left == NULL && right == NULL ? true : false);
  }
};

Node<string>* make_node (const string& d) {
  return new Node<string> (d);
}

template <typename T>
ostream& operator<< (ostream& out, const Node<string>& src) {
  return out << src.data;
}

template <typename T>
class Expression_Tree {
  private :
    Node<string>* root;

    void build_tree (const string& exp) {
      stack< Node<string>* > foo;
      istringstream istr (exp);
      string seq;
      string optr = "+-*/";
      Node<string>* ptr;

      while (istr >> seq) {
        ptr = make_node (seq);

        if (optr.find (seq) != string::npos) {
          ptr -> right = foo.top ();
          foo.pop ();
          ptr -> left = foo.top ();
          foo.pop ();
          foo.push (ptr);
        } else {
          foo.push (ptr);
        }
      }

      root = foo.top ();
      foo.pop ();
      assert (foo.size () == 0);
    }

    T evaluate_subtree (const Node<string>* ptr) const {
      if (ptr -> is_leaf_node ()) {
        return str2num<T> (ptr -> data);
      } else {
        T a, b;

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
    Expression_Tree (const string& exp) : root (NULL) {
      build_tree (exp);
    }

    Expression_Tree (const Expression_Tree<T>& foo) {
      if (foo.root == NULL) {
        root = NULL;
      } else {
        cout << "cpy" << endl;
        root = new Node<string> (foo.root -> data);
        copy_subtree (&root, foo.root);
      }
    }

    Expression_Tree (Node<string>* r) : root(r) {}

    Expression_Tree<T>& operator= (const Expression_Tree<T>& foo) {
      if (root == foo.root) {
        return *this;
      } else {
        erase_subtree (root);
        copy_subtree (&root, foo.root);
        return *this;
      }
    }

    void erase_subtree (Node<string>* ptr) {
      if (ptr) {
        erase_subtree (ptr -> left);
        erase_subtree (ptr -> right);
        delete ptr;
        ptr = NULL;
      }
    }

    T evaluate () const { return evaluate_subtree (root); }

    void copy_subtree (Node<string>** ptr, const Node<string>* q) const {
      if (q == NULL) {
        *ptr = NULL;
      } else {
        ptr = new Node<string> (q -> data);
        copy_subtree (ptr -> left ,q -> left);
        copy_subtree (ptr -> right ,q -> right);
      }
    }

    ~Expression_Tree () { erase_subtree (root); }

    void print_subtree (ostream& out, const Node<string>* ptr, int depth = 1) const {
      if (ptr == NULL) {
        out << setw ((depth - 1) * 5) << "|--> " << setw (5) << left << "." << right << endl;
      } else {
        if (depth > 1) { out << setw ((depth - 1) * 5) << "|--> "; }
        out << setw (5) << left << ptr -> data << right << endl;
        if ( ! (ptr -> is_leaf_node ())) {
          print_subtree (out, ptr -> right, depth + 1);
          print_subtree (out, ptr -> left, depth + 1);
          if (ptr -> left == NULL || (ptr -> left != NULL && ptr -> left -> is_leaf_node ())) { out << endl; }
        }
      }
    }

    friend ostream& operator<< (ostream& out, const Expression_Tree<T>& src) {
      src.print_subtree (out, src.root);
      return out;
    }

    friend Expression_Tree<T> operator+ (const Expression_Tree<T>& b, const int& a) {
      Node<string>* r;
      string str = "+";

      r = make_node (str);
      r -> left = make_node (num2str<int> (a));
      r -> right = b.root;

      return Expression_Tree<T> (r);
    }

    friend Expression_Tree<T> operator* (const int& a, const Expression_Tree& b) {
      Node<string>* root;
      string str = "*";

      root = make_node (str);
      root -> left = make_node (num2str<int> (a));
      root -> right = b.root;

      return Expression_Tree<T> (root);
    }
};


int main () {
  string exp = "4 6 + 5 /";

  Expression_Tree<int> foo (exp);

  cout << foo << "> " << foo.evaluate () << "\n\n";

  Expression_Tree<int> bar(6 * foo + 4);

cout << bar << endl;
  //cout << 6 * foo + 4 << "> " << bar.evaluate () << endl;

  return 0;
}
