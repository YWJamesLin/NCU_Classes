#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main(void)
{
  wchar_t poem[]= L"呆秀才吃長齋鬍鬚滿腮經書揭不開紙筆自己安排明年不請我自來";
  int i, j, bloc, ind, disp;
  int dispind[]={7, 6, 5, 4, 3, 2};

  ind=12, bloc=21;
  setlocale(LC_ALL, "zh_TW.UTF-8");
  for(i=0; i<7; ++i)
  {
    disp=0;
    if(ind>0){ printf("%*c", ind, ' '); }
    for(j=0; j<i+1; ++j)
    {
      if(j>0){ disp+=dispind[j-1]; }
      printf("%5lc", poem[bloc+i-disp]);
    }
    ind-=2;
    puts("");
  }
  return 0;
}
