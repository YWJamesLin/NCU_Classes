#include <iostream>

using namespace std;

unsigned getnum (unsigned num, bool ifmax) {
  unsigned tmp, sum = 0;
  for (int i = (ifmax ? 9 : 0); (ifmax ? i >= 0 : i <= 9); (ifmax ? -- i: ++ i)) {
    tmp = num;
    do {
      if (tmp % 10 == i) {
        sum = sum * 10 + i;
      }
      tmp /= 10;
    } while (tmp);
  }
  return sum;
}


void rec (unsigned init, unsigned num, int t) {
  if (! t) { return; }
  unsigned sum, tmp;
  sum = getnum (num, true) - getnum (num, false);
  cout << getnum (num, true) << " - " << getnum (num, false) << " = " << sum << endl;
  if (num <= 9999 && sum == num) { return; }
  else if (num > 9999 && init == sum) { return; }
  rec (init, sum, t-1);
}


int main () {
  unsigned k;

  cout << "> ";
  cin >> k;

  rec (k, k, 100);

  return 0;
}
