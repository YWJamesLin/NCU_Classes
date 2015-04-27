#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int *numarr;
  int i, j, ch, mo;

  numarr=(int *)malloc(sizeof(int)*(argc-1));
  for(i=1; i<argc; ++i)
  {
    j=0, numarr[i-1]=0;
    while(argv[i][j]!='\0')
    {
      numarr[i-1]=(numarr[i-1]*10+argv[i][j]-48);
      ++j;
    }
  }
  ch=1, mo=numarr[argc-2];
  for(i=argc-3; i>=0; --i)
  {
    ch+=mo*numarr[i];
    ch+=mo;
    mo=ch-mo;
    ch-=mo;
  }
  printf("%d/%d\n", mo, ch);

  free(numarr);
  return 0;
}
