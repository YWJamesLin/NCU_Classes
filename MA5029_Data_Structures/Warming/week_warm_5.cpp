#include <iostream>

using namespace std;

template <class T>
struct Node {
  T item;
  Node<T>* ptr;
};

template <class T>
class List {
  private:
    Node<T> *head, *tail;
    int len;

    bool delete_head () {
      if (len == 0) { return false; }
      else {
        Node<T>* tmp = head -> ptr;
        delete head;
        head = tmp;

        if (len == 1) { tail = NULL; }

        return true;
      }
    }
    
    void delete_list () {
      Node<T>* iter;
      while (head != NULL) {
        iter = head -> ptr;
        delete head;
        head = iter;
      }
      head = tail = NULL;
      len = 0;
    }

  public:
    List (): head (NULL), tail (NULL), len (0) {}

    List (const List<T>& src) {
      if (src.len == 0) {
        head = tail = NULL;
        len = 0;
      } else {
        //sItr is an iterator to iterate the source, cNode means the copy node to copy every node
        Node<T> *sItr, *cNode;

        cNode = new Node<T>;
        cNode -> item = src.head -> item;
        
        //head is the first node
        head = cNode;

        sItr = src.head -> ptr;

        while (sItr != NULL) {
          //copy
          cNode -> ptr = new Node<T>;
          cNode -> ptr -> item = sItr -> item;

          //iterate
          cNode = cNode -> ptr;
          sItr = sItr -> ptr;
        }

        //finish the construction
        cNode -> ptr = NULL;
        tail = cNode;
        len = src.len;
      }
    }

    ~List () { delete_list (); }

    List<T> operator= (const List<T>& src) {
      if (this == &src) {
        return src;
      } else if (src.len == 0) {
        return List<T> ();
      } else {
        Node<T> *cNode, *sItr;

        cNode = new Node<T>;
        cNode -> item = src.head -> item;

        head = cNode;

        sItr = src.head -> ptr;

        while (sItr != NULL) {
          cNode -> ptr = new Node<T>;
          cNode -> ptr -> item = sItr -> item;

          cNode = cNode -> ptr;
          sItr = sItr -> ptr;
        }

        cNode -> ptr = NULL;
        tail = cNode;

        len = src.len;

        return *this;
      }
    }

    bool delete_node (const T& data) {
      if (len == 0) { return false; }
      else {
        int count = 0;
        Node<T> *tmp1, *tmp2;

        tmp1 = head;

        while (tmp1) {
          if (tmp1 -> item == data) {
            ++ count;
            if (tmp1 == head) {
              tmp1 = tmp1 -> ptr;
              delete_head ();
            } else {
              tmp2 -> ptr = tmp1 -> ptr;
              delete tmp1;
              tmp1 = tmp2 -> ptr;
            } 
            continue;
          }
          tmp2 = tmp1;
          tmp1 = tmp1 -> ptr;
        }

        len -= count;
        tail = ((len == 0) ? NULL : tmp2);
        
        return (count ? true : false);
      }
    }

    void push_back (const T& data) {
      Node<T>* bNode = new Node<T>;
      bNode -> item = data;
      bNode -> ptr = NULL;
      if (len == 0) {
        head = tail = bNode;
      } else if (len == 1) {
        tail = bNode;
        head -> ptr = tail;
      } else {
        tail -> ptr = bNode;
        tail = bNode;
      }
      ++ len;
    }

    void push_front (const T& data) {
      Node<T>* fNode = new Node<T>;
      fNode -> item = data;
      fNode -> ptr = head;
      head = fNode;
      if (len == 0) { tail = fNode; }
      ++ len;
    }

    void pop_back () {
      if (len == 0) { return; }
      else if (len == 1) {
        delete head;
        head = tail = NULL;
      }
      else {
        Node<T> *iter = head;
        while (iter -> ptr != tail) { iter = iter -> ptr; }
        delete tail;
        tail = iter;
        tail -> ptr = NULL;
      }
      -- len;
    }

    void pop_front () {
      if (len == 0) { return; }
      else if (len == 1) {
        delete head;
        head = tail = NULL;
      } else {
        Node<T>* tmp = head -> ptr;
        delete head;
        head = tmp;
      }
      -- len;
    }

    template <class S>
    friend ostream& operator<< (ostream& out, const List<S>& in)
    {
      for (Node<T>* i = in.head; i != NULL; i = i -> ptr) { out << i -> item << " "; }
      return out;
    }
};

int main () {
  int i;
  List<int> foo, bar;

  for (i = 0; i < 3; ++ i) { foo.push_front (i); }
  for (i = 4; i < 7; ++ i) { foo.push_back (i); }

  foo.push_back (4);
  foo.push_back (5);
  foo.push_back (4);

  cout << foo << endl;

  foo.delete_node(4);

  cout << foo << endl;

  foo.push_back(2);
  foo.delete_node(2);

  cout << foo << endl;

  bar = foo;

  cout << bar << endl;

  for (i = 0; i < 2; ++ i) { foo.pop_front (); }
  for (i = 0; i < 2; ++ i) { foo.pop_back (); }

  cout << foo << endl;

  bar = foo;

  cout << bar << endl;

  List<int> fbar (foo);
  cout << fbar << endl;

  return 0;
}
