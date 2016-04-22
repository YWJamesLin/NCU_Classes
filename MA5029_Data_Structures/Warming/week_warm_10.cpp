#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

template <typename S, typename T>
struct Node {
  S num;
  T data;

  Node<S, T> *right, *left;
  Node () {}
  Node (const S& a) : num (a), data (), right (NULL), left (NULL) {}
  Node(const S& a, const T& b) : num (a), data (b), right (NULL), left (NULL) {}
  bool is_leaf () const {
    return (left == NULL && right == NULL) ? true : false;
  }
};

template <typename S, typename T>
Node<S, T>* new_node (const S& n, const T& d = T()) {
  return new Node<S, T> (n, d);
}

template <typename S, typename T>
ostream& operator<< (ostream& out, const Node<S, T>& src) {
  out << src.num;
  return out;
}

// mainpulator {
struct Show_Data {
  ostream* out;
};

Show_Data& operator<< (ostream& out, Show_Data& src) {
  src.out = &out;
  return src;
}

template <typename S, typename T>
ostream& operator<< (const Show_Data& manip, const Node<S, T>& src) {
  *(manip.out) << src.num << " [" << src.data << ']';
  return *(manip.out);
}

Show_Data show;
// }

template <typename S, typename T>
void copy_tree (Node<S, T>*& a, const Node<S, T>* b) {
  if (b == NULL) {
    a = NULL;
  } else {
    a = new_node<S, T> (b -> num, b -> data);
    copy_tree (a -> left, b -> left);
    copy_tree (a -> right, b -> right);
  }
}

template <typename S, typename T>
void delete_tree (Node<S, T>*& ptr) {
  if (ptr != NULL) {
    if (! (ptr -> is_leaf ())) {
      delete_tree (ptr -> left);
      delete_tree (ptr -> right);
    }
    delete ptr;
  }
}

template <typename S, typename T>
void print_tree (ostream& out, const Node<S, T>* ptr, int depth = 1) {
  if (ptr == NULL) {
    out << setw ((depth - 1) * 5) << "|--> " << setw (5) << left << '.' << right << "\n";
  } else {
    if (depth > 1) { out << setw ((depth - 1) * 5) << "|--> "; }
    
    if (ptr -> is_leaf ()) {
      out << left << show << *ptr << right << endl;
    } else {
      out << left << *ptr << right << endl;
    }

    if ( ! ptr -> is_leaf ()) {
      print_tree (out, ptr -> right, depth + 1);
      print_tree (out, ptr -> left, depth + 1);
      if (ptr -> left == NULL || (ptr -> left != NULL && ptr -> left -> is_leaf ())) { out << endl; }
    }
  }
}

template <typename S, typename T>
Node<S, T>* join (const Node<S, T>* a, const Node<S, T>* b) {
  Node<S, T> *ptr = new_node (a -> num + b -> num);
  ptr -> left = a;
  ptr -> right = b;
  return ptr;
}

template <typename S, typename T>
class Huffman_Tree {
  private :
    Node<S, T>* root;
    
  public :
    Huffman_Tree (const S& n, const T& d) : root (new_node (n, d)) {}

    Huffman_Tree (Node<S, T>* ptr = NULL, bool need_new = true) {
      if (need_new) { copy_tree (root, ptr); }
      else { root = ptr; }
    }

    Huffman_Tree (const Huffman_Tree<S, T>& foo) {
      copy_tree (root, foo.root);
    }

    Huffman_Tree<S, T>& operator= (const Huffman_Tree<S, T>& foo) {
      if (this == &foo) { return *this; }
      delete_tree (root);
      copy_tree (root, foo.root);
      return *this;
    }

    ~Huffman_Tree () { delete_tree (root); }

  template <typename A, typename B>
  friend Huffman_Tree<A, B> operator+ (const Huffman_Tree<A, B>& a, const Huffman_Tree<A, B>& b) {
    Node<S, T> *aptr, *bptr;

    copy_tree (aptr, a.root);
    copy_tree (bptr, b.root);

    Node<S, T> *ptr = new_node<S, T> (a.root -> num + b.root -> num);
    
    ptr -> left = a.root;
    ptr -> right = b.root;

    return Huffman_Tree<S, T> (ptr, false);
  }

  template <typename A, typename B>
  friend bool operator< (const Huffman_Tree<A, B>& a, const Huffman_Tree<A, B>& b);

  template <typename A, typename B>
  friend ostream& operator<< (ostream& out, const Huffman_Tree<A, B>& src) {
    print_tree<A, B> (out, src.root);
    return out;
  }
};

template <typename S, typename T>
bool operator< (const Huffman_Tree<S, T>& a, const Huffman_Tree<S, T>& b) {
  return (a.root -> num) > (b.root -> num);
}

template <typename S, typename T>
ostream& operator<< (ostream& out, priority_queue< Huffman_Tree<S, T> > src) {
  out << ">> elements in priority_queue : \n\n";
  while (src.size ()) {
    out << src.top ();
    src.pop ();
  }
  return out;
}

int main () {
  int i, j;
  const int N = 8;
  vector<int> nos (N);
  vector<char> chs (N);

  for (i = 0; i < nos.size (); ++ i) {
    nos[i] = 1 + i;
    chs[i] = 'a' + i;
  }

  priority_queue< Huffman_Tree <int, char> > foo;

  Huffman_Tree <int, char> htree1, htree2;

  for (i = 0; i < nos.size (); ++ i) {
    foo.push (Huffman_Tree<int, char> (nos[i], chs[i]));
  }


  while (foo.size () > 1) {
    cout << foo << endl;
    htree1 = foo.top ();
    cout << htree1 << endl;
    cout << "pushing" << endl;
    foo.pop ();
    htree2 = foo.top ();
    foo.pop ();
    foo.push (htree1 + htree2);
  }

  cout << foo << endl;

  return 0;
}
