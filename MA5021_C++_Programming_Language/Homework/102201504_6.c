#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int chkwd (int y, int m, int d) {
  if (m >= 3) { m -= 2; }
  else { 
    -- y;
    m += 10;
  }
  return (y + y / 4 - y / 100 + y / 400 + (int)(2.6 * m - 0.2) + d) % 7;
}

int chkleap (int y) {
  if (y % 4) { return 0; }
  else {
    if (! (y % 100)) { return (! (y % 400)) ? 1 : 0; }
    else { return 1; }
  }
}

void printcal (int y, int m, int bd, int ed) {
  int wd, i, nd;

  wd = chkwd (y, m, bd);
  nd = bd;
  if (wd) { printf ("%*lc", 4 * wd, L' '); }
  while (nd <= ed) {
    printf ("%3d ", nd);
    ++ nd;
    wd = (wd + 1) % 7;
    if (! wd) { puts (""); }
  }
  puts ("\n");
}

int main (void) {
  int by, bm, bd, ey, em, ed;
  int i, j, k;
  int ubm, lbd, ubd, wd;
  int dem[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  wchar_t *cm[] = {L"一", L"二", L"三", L"四", L"五", L"六", L"七", L"八", L"九", L"十", L"十一", L"十二"};
  char *ws[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  setlocale (LC_ALL, "zh_TW.UTF-8");
  printf ("%ls", L">輸入前後兩日期：");
  scanf ("%d%d%d%d%d%d", &by, &bm, &bd, &ey, &em, &ed);
  puts ("");
  for (i = by; i <= ey; ++ i) {
    (i != by) ? (j = 1) : (j = bm);
    (i != ey) ? (ubm = 12) : (ubm = em);
    for (; j <= ubm; ++ j) {
      printf ("%7lc%i%ls%ls%ls\n", L' ', i, L" 年 ", cm[j-1], L" 月");
      for (k = 0; k < 7; ++ k) { printf ("%s ", ws[k]); }
      puts ("");
      lbd = 1;
      (chkleap (i) && j == 2) ?  (ubd = 29) : (ubd = dem[j-1]);
      if (i == by && j == bm) { lbd = bd; }
      if (i == ey && j == em) { ubd = ed; } 
      printcal (i, j, lbd, ubd);
    }
  }

  return 0;
}
