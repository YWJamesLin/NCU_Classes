#include <stdio.h>

int main (void) {
  int in, i, j;
  
  putchar ('>');
  scanf ("%d", &in);
  for (i = 0; i < in; ++ i) { printf ("%*c%*c\\\n", (in + 1) * 5, '|', (i + 1), '\\'); }
  for (i = 0; i < 2 * (in + 1); ++ i) {
    printf ("%*c", 4 * in + 3 - 2 * i, '-');
    for (j = 0; j < in + 1; ++ j) { putchar ('-'); }
    if (i == 0) {
      printf ("%*c", in + 3, '-');
      for (j = 0; j < in; ++ j) { putchar ('-'); }
      for (j = 0; j < in + 4; ++ j) { putchar ('_'); }
      putchar ('@');
    }
    else if (i <= in) {
      if (i == 1) { printf ("%*c%*c", in + 2, '@', 2 * in + 7, '/'); }
      else { printf ("%*c", in * 3 + i + 8, '/'); }
    }
    else if (i == in + 1) {
      printf ("%*c", in * 3 + 6, '-');
      for (j = 0; j < in + 2; ++ j) { putchar ('-'); }
      putchar (',');
    }
    else { printf ("%*c", in * 2 + 4 + i, '/'); }
    puts ("");
  }
  return 0;
}
