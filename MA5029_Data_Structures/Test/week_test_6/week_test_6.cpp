#include <iostream>
#include <stack>
#include <deque>
#include <sstream>

using namespace std;

template<typename T>
string to_prefix (const string& l) {
  T temp;
  stack<string> inverse, oper;
  deque<string> prefix;
  string tmp;
  istringstream istr;
  ostringstream ostr;

  istr.str (l);

  while (istr.peek () != '\n' && istr >> tmp) {
    inverse.push (tmp);
    istr.clear ();
  }
  
  while ( ! inverse.empty ()) {
    if (inverse.top () == ")") {
      oper.push (")");
    } else if (inverse.top () == "(") {
      while (oper.top () != ")") {
        prefix.push_front (oper.top ());
        oper.pop ();
      }
      oper.pop ();
    } else if (inverse.top ().length () < 2) {
      switch ((inverse.top ())[0]) {
        case '+':
          oper.push ("+");
          break;
        case '-':
          oper.push ("-");
          break;
        case '*':
          oper.push ("*");
          break;
        case '/':
          oper.push ("/");
          break;
        default:
          prefix.push_front (inverse.top ());
      }
    } else {
      prefix.push_front (inverse.top ());
    }

    inverse.pop ();
  }
  
  for (int i = 0; i < prefix.size (); ++ i) {
    ostr << prefix[i] << " ";
  }

  return ostr.str ();
}

template<typename T>
T eval_prefix (const string& prefix) {
  T first, second, tmpT;
  stack<char> oper;
  stack<T> num;
  stack<string> inverse;
  istringstream istr, tmpist;
  string tmp;

  istr.str (prefix);
  while (istr.peek () != '\n' && istr >> tmp) {
    inverse.push (tmp);
    istr.clear ();
  }

  while ( ! inverse.empty ()) {
    if ((inverse.top ()).length() < 2) {
      if ((inverse.top ())[0] > 47 && (inverse.top ())[0] < 58) {
        num.push (static_cast<int>((inverse.top ())[0]) - 48);
      } else {
        first = num.top ();
        num.pop ();
        second = num.top ();
        num.pop ();

        switch ((inverse.top ())[0]) {
          case '+':
            num.push (first + second);
            break;
          case '-':
            num.push (first - second);
            break;
          case '*':
            num.push (first * second);
            break;
          case '/':
            num.push (first / second);
        }
      }
    } else {
      tmpist.str (inverse.top ());
      tmpist >> tmpT;
      tmpist.clear();
      num.push (tmpT);
    }
    inverse.pop ();
  }
  return num.top ();
}
int main () {
  string line;
  
  cout << ">> ";
  while (getline (cin, line)) {
    cout << endl;
    cout << "<< " << to_prefix<double> (line) << endl;
    cout << "<< " << eval_prefix<double> (to_prefix<double> (line)) << endl;
  }
  return 0;
}
