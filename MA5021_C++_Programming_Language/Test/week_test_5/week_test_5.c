#include <stdio.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#define S 250000

int main(void)
{
  wchar_t *poem=L"春眠不覺曉處處聞啼鳥夜來風雨聲花落知多少";
  int in, bound, i, j;
  
  scanf("%d", &in);
  if(20%in){ bound=20/in+1; }
  else { bound=20/in; }
  setlocale(LC_ALL, "zh_TW.UTF-8");
  printf("\x1b[2J");
  while(1)
  {
    i=bound;
    for(; i>=1; --i)
    {
      for(j=0; j<in; ++j)
      {
        if((bound-i)*in+j>19){ break; }
        printf("\x1b[%d;%dH%lc", j+1, 2*i-1, poem[(bound-i)*in+j]);
        printf("\x1b[%d;1H", in+1);
        fflush(stdout);
        usleep(S);
      }
    }
    --j;
    for(i=1; i<=bound; ++i)
    {
      if(j<0){ j=in-1; }
      for(; j>=0; --j)
      {
        printf("\x1b[%d;%dH%lc", j+1, 2*i-1, L'　');
        printf("\x1b[%d;1H", in+1);
        fflush(stdout);
        usleep(S);
      }
    }
  }

  return 0;
}
