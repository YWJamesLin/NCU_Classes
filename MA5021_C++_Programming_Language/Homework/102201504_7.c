#include <stdio.h>
#include <string.h>
#include <unistd.h>
//usleep for 0.1 second
#define S 100000 

int bitmap[] = {0xf999f, 0x11111, 0xf1f8f, 0xf1f1f, 0x99f11, 0xf8f1f, 0x88f9f, 0xf1111, 0xf9f9f, 0xf9f11};

void printnum (int num) {
  int cnum, lmsk, rmsk, move;
  int i, j, k;

  printf ("\x1b[2J");
  move = 0;
  lmsk = 10000, rmsk = 1000;
  for (i = 0; i < 4; ++ i) {
    if (i == 3) {
      printf ("\x1b[5;16H*");
      move += 2;
    }
    cnum = num % lmsk;
    if (rmsk > 0) { cnum /= rmsk; }
    for (j = 0; j < 5; ++ j) {
      for (k = 0; k < 4; ++ k) {
        printf ("\x1b[%d;%dH", j + 1, move + k + 1);
        if (! ((bitmap[cnum] >> (4 - j) * 4 + (3 - k)) % 2)) { putchar (' '); }
        else {
          if (num <= 50) { printf("\x1b[31m%d\x1b[0m", cnum); }
          else { printf ("%d", cnum); }
        }
      }
    }
    lmsk /= 10, rmsk /= 10, move += 5;
  }
  printf ("\x1b[6;1H");
  fflush (stdout);
}

int main (int argc, char *argv[]) {
  if (argc == 1) { 
    puts ("Error!! No argument.");
    return 1;
  } else if (argc > 2) { 
    puts ("Error!! Too many arguments.");
    return 1;
  } else if (strlen (argv[1]) > 3) {
    puts("Error!! The argument is too large.");

    return 1;
  } else {
    int num=0, i, j;

    for (i = 0; i < strlen (argv[1]); ++ i) { num = (num + argv[1][i] - 48) * 10; }
    for (i = num; i >= 0; -- i) {
      printnum (i);
      usleep (S);
    }

    return 0;
  }
}
