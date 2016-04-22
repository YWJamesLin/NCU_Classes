#include <iostream>

using namespace std;

template <class T>

struct Node {
  T item;
  Node<T> *fptr;
};

template <class T>
class List {
  private:
    Node<T> *head, *tail;
    int len;

    //delete head and redirect the head and tail, but the length will not be changed
    void delete_head () {
      if (len == 0) { return; }
      else if (len == 1) {
        delete head;
        head = tail = NULL;
      } else {
        Node<T>* tmp = head -> fptr;
        delete head;
        head = tmp;
      }
    }
    
    void delete_list () {
      if (len == 0) { return; }
      else {
        while (head != NULL) { delete_head (); }
        len = 0;
      }
    }

  public:
    List () : head (NULL), tail (NULL), len(0) {}

    List (const List<T>& src) {
      if (src.len == 0) {
        head = tail = NULL;
        len = 0;
      } else {
        Node<T> *sItr, *cNode;
        
        cNode = new Node<T>;
        cNode -> item = src.head -> item;
        head = cNode;
        
        sItr = src.head -> fptr;

        while (sItr != NULL) {
          cNode -> fptr = new Node<T>;
          cNode -> fptr -> item = sItr -> item;
          
          cNode = cNode -> fptr;
          sItr = sItr -> fptr;
        }
        cNode -> fptr = NULL;
        tail = cNode;

        len = src.len;
      }
    }

    ~List () { delete_list(); }

    List<T> operator= (const List<T>& src) {
      if (this == &src) {
        return src;
      } else if (src.len == 0) {
        return List<T>();
      } else {
        Node<T> *sItr, *cNode;
        
        cNode = new Node<T>;
        cNode -> item = src.head -> item;
        head = cNode;
        
        sItr = src.head -> fptr;

        while (sItr != NULL) {
          cNode -> fptr = new Node<T>;
          cNode -> fptr -> item = sItr -> item;
          
          cNode = cNode -> fptr;
          sItr = sItr -> fptr;
        }
        cNode -> fptr = NULL;
        tail = cNode;

        len = src.len;

        return *this;
      }
    }

    Node<T>* begin () { return head; }
    int size () { return len; }

    void push_back (const T& data) {
      if (len == 0) {
        head = new Node<T>;
        head -> item = data;
        head -> fptr = NULL;
        tail = head;
      } else if (len == 1) {
        tail = new Node<T>;
        tail -> item = data;
        tail -> fptr = NULL;
        head -> fptr = tail;
      } else {
        tail -> fptr = new Node<T>;
        tail -> fptr -> item = data;
        tail -> fptr -> fptr = NULL;
        tail = tail -> fptr;
      }
      ++ len;
    }

    void pop_back () {
      if (len == 0) { return; }
      else if (len == 1) {
        delete tail;
        head = tail = NULL;
      } else {
        Node<T>* i = head;
        for (; i -> fptr != tail; i = i -> fptr) {}
        delete tail;
        i -> fptr = NULL;
        tail = i;
      }
      -- len;
    }

    void insert (Node<T>* node, const T& data) {
      Node<T>* i = head;
      for (; i -> fptr != node; i = i -> fptr) {}
        
      Node<T> *tmp = new Node<T>;
      tmp -> item = data;
      tmp -> fptr = node;
      i -> fptr = tmp;
      ++ len;
    }

    template <class S>
    friend ostream& operator<< (ostream& out, const List<S>& in) {
      for (Node<T>* i = in.head; i != NULL; i = i -> fptr) { out << i -> item << " "; }
      return out;
    }
};

int main () {
  List<int> foo;

  for (int i = 0; i < 5; ++ i) { foo.push_back(i); }
  cout << foo.size() << " : " << foo << endl;

  foo.pop_back () ;
  cout << foo.size() << " : " << foo << endl;

  Node<int> *p ;
  p = foo.begin();
  p = p -> fptr;
  foo.insert(p, 7);
  p = p -> fptr;
  foo.insert(p, 8);
  cout << foo.size() << " : " << foo << endl;

  return 0;
}
