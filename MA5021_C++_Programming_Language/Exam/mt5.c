#include <stdio.h>
#include <unistd.h>

int numbmp[]={0x69996, 0x11111, 0xf1f8f, 0xf171f, 0x99f11, 0xf8f1f, 0xf8f9f, 0xf1244, 0x69696, 0xf9f1f};

void printnum(int num, int ind)
{
  int i, j;

  for(i=0; i<5; ++i)
  {
    for(j=0; j<4; ++j)
    {
      printf("\x1b[%d;%dH", i+1, j+1+ind);
      if((numbmp[num]>>((4-i)*4+(3-j)))%2){ printf("%d", num); }
      else{ putchar(' '); }
    }
  }
}

int gw(int y, int m, int d)
{
  if(m<=2)
  {
    --y;
    m+=10;
  }
  else{ m-=2; }
  return (y+y/4-y/100+y/400+(int)(2.6*m-0.2)+d)%7;
}

int main(void)
{
  int i, tmp, ind;
  int date[4];
  int mask[]={10000, 100, 100, 10};
  
  for(i=0; i<3; ++i){ scanf("%d", date+i); }
  date[3]=gw(date[0], date[1], date[2]);
  ind=0;
  printf("\x1b[2J");
  for(i=0; i<4; ++i)
  {
    while(mask[i]!=1)
    {
      tmp=date[i]%mask[i];
      if(mask[i]/10!=0){ tmp=tmp/(mask[i]/10); }
      printnum(tmp, ind);
      mask[i]/=10;
      ind+=5;
    }
    ind+=5;
  }
  printf("\x1b[6;1H");
  fflush(stdout);

  return 0;
}
