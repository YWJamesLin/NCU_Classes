#include <iostream>

using namespace std;

void bk_hole (unsigned init, unsigned num, int t) {
  if ((num == init && t != 100) || t == 0) { return; }
  int tmp = num, mask = 1, sum = 0;
  while (mask * 10 <= tmp) { mask *= 10; }
  while (tmp) {
    cout << (tmp / mask) << "^2";
    sum += (tmp / mask) * (tmp / mask);
    tmp %= mask;
    mask /= 10;
    if (tmp) { cout << " + "; }
  }
  cout << " = " << sum << endl;
  bk_hole (init, sum, t-1);
}

int main () {
  unsigned k;
  
  cout << "> ";
  cin >> k;
  bk_hole(k, k, 100);

  return 0;
}
