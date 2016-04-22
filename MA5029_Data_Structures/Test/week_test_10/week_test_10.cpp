#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

unsigned int decbin (string str) {
  int bin = 0;
  for (int i = 0; i < 8; ++ i) {
    bin = bin * 2 + (str.length () > i && str[i] == '1' ? 1 : 0);
  }

  return bin;
}

vector<unsigned int> compress (const string& orgstr, const map<char, string>& chpath) {
  unsigned int a;
  int cnt;
  char c;
  vector<unsigned> cmp;
  string str;
  istringstream istr (orgstr);
  ostringstream ostr;
  stringstream sstr;
  map<char, string>::const_iterator mitr;
  for (int i = 0; i < orgstr.length (); ++ i) {
    mitr = chpath.find (orgstr[i]);
    ostr << mitr -> second;
    istr.clear ();
  }

  istr.str (ostr.str ());
  ostr.str ("");
  cnt = 0;
  istr.clear ();
  while (istr >> c) {
    ++ cnt;
    ostr << c;
    if (cnt == 8) {
      ostr << " ";
      cnt = 0;
    }
    istr.clear ();
  }
  
  istr.str (ostr.str ());
  ostr.str ("");
  istr.clear ();
  cnt = 0;
  a = 0;
  while (istr >> str) {
    a = ((a << 8) + decbin (str));
    ++ cnt;
    if (cnt == 4) {
      cnt = 0;
      cmp.push_back (a);
      a = 0;
    }
    istr.clear ();
  }
  if (cnt != 4) { cmp.push_back(a << 8); }
  
  
  return cmp;
}

int main () {
  string str = "to boldly go where no one has gone before";

  string chs = " abdefghlnorstwy";
  string path[] = {"01", "00010", "1000", "100111", "101",
                 "10010", "11111", "11110", "0011", "1110",
                 "110", "0010", "00001", "100110", "00011",
                 "00000"};

  int i;
  map<char, string> chpath;

  for (i = 0; i < chs.size (); ++ i) {
    chpath[chs[i]] = path[i];
  }

  vector<unsigned int> bar = compress (str, chpath);

  cout << str << endl;

  for (i = 0; i < bar.size (); ++ i) {
    cout << setw (8) << setfill ('0') << hex << bar[i] << " ";
  }

  cout << endl;

  return 0;
}
