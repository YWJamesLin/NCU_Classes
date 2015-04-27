#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <unistd.h>
#include <locale.h>
#define S 50000
 
wchar_t linec[6]={L'─', L'┘', L'┐', L'│', L'┌', L'└'};
int firph[2]={-1, 1};
int phase[2][3]={{1, 3, 4}, {2, 3, 5}};

int pwhite(int x, int beg)
{
  printf("\x1b[47m");
  for(; beg<=20; ++beg){ printf("\x1b[%d;%dH ", beg, x); }
  printf("\x1b[0m");
  printf("\x1b[21;1H");
  fflush(stdout);
  usleep(S);
}

int printc(int i, int j, int k, int l)
{
  printf("\x1b[%d;%dH%lc", i, j, linec[phase[k][l]]);
  printf("\x1b[21;1H");
  fflush(stdout);
  usleep(S);
}

int printv(int *x, int *y, int cst)
{
  int ph=0, cs, i;

  printc(*y, *x, cst, ph);
  if(cst==0){ pwhite(*x, *y+1); }
  *y+=firph[cst];
  ++ph;
  while(1)
  {
    cs=(int)(3.*rand()/(1.+RAND_MAX));
    if(*y==20 || *y==1 || !cs)
    {
      ++ph;
      break;
    }
    else
    {
      printc(*y, *x, cst, ph);
      if(cst){ ++*y; }
      else{ --*y; }
    }
  }
  printc(*y, *x, cst, ph);
  if(cst==1){ pwhite(*x, *y+1); }
  *x+=1;
}

int main(void)
{
  int x, y;
  int cs, st;

  srand((unsigned)(time(NULL)));
  setlocale(LC_ALL, "zh_TW.UTF-8");
  while(1)
  {
    x=1, y=1+(int)(20.*rand()/(1.+RAND_MAX));
    printf("\x1b[2J");
    while(x<=70)
    {
      cs=(int)(2.*rand()/(1.+RAND_MAX));
      if(cs)
      {
        st=(int)(2.*rand()/(1.+RAND_MAX));
        if(y==20){ st=0; }
        else if(y==1){ st=1; }
        printv(&x, &y, st);
      }
      else
      {
        printf("\x1b[%d;%dH%lc", y, x, linec[0]);
        pwhite(x, y+1);
        x+=1;
      }
    }
  }

  return 0;
}
