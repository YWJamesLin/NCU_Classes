#include <stdio.h>

int printcal(int y, int m, int d, int w)
{
  int i=1, j=0;

  while(i<=d)
  {
    if(j==14)
    {
      puts("");
      j=0;
    }
    if(w==0 || w==6){ printf("\x1b[31m"); }
    printf("%4d", i);
    if(w==0 || w==6){ printf("\x1b[37m"); }
    ++i, ++j, w=(w+1)%7;
  }
  puts("\n");
}

int chkleap(int y)
{
  if(y%4){ return 0; }
  else
  {
    if(!(y%100)){ return (!(y%400)?1:0); }
    else{ return 1; }
  }
}

int chkwk(int y, int m, int d)
{
  if(m>=3){ m-=2; }
  else
  {
    y--;
    m+=10;
  }
  return (y+y/4-y/100+y/400+(int)(2.6*m-0.2)+d)%7;
}

int main(void)
{
  int y ,m, d, shift, i;
  char ws[][4]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  int dem[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  
  putchar('>');
  scanf("%d", &y);
  puts("");
  for(m=1; m<=12; ++m)
  {
    printf("%d %d\n", y, m);
    shift=chkwk(y, m, 1);
    if(m==2 && chkleap(y)){ d=29; }
    else{ d=dem[m-1]; }
    for(i=0; i<14; ++i)
    {
      if((i+shift)%7==0 || (i+shift)%7==6){ printf("\x1b[31m"); }
      printf("%4s", ws[(i+shift)%7]); 
      if((i+shift)%7==0 || (i+shift)%7==6){ printf("\x1b[37m"); }
    }
    puts("");
    printcal(y, m, d, shift);
  }

  return 0;
}
