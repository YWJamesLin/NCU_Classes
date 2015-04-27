#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#define S 50000

int main(void)
{
  wchar_t poem[]=L"寒泉漱玉清音好，好處深居近翠巒。"
                 L"巒秀聳岩飛澗水，水邊松竹檜宜寒。"
                 L"寒窗淨室親邀客，客待閒吟恣取歡。"
                 L"歡宴聚陪終宴喜，喜來歸興酒闌殘。";
  int ind[]={2, 5, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1};
  int rV[]={0, 1, 0, -1}, cV[]={2, 0, -2, 0};
  int poemn, dirn, indn, x, y;
  int i, j;

  x=5, y=6;
  dirn=2, poemn=0;
  setlocale(LC_ALL, "zh_TW.UTF-8");
  printf("\x1b[2J");
  for(i=0; i<14; ++i)
  {
    for(j=0; j<ind[i]; ++j)
    {
      if(((poemn+1)%8==7 || (poemn+1)%8==0) && (poemn!=0 && poemn!=62))
      {
        --j;
        ++poemn;
        usleep(S);
        continue;
      }
      x+=cV[dirn], y+=rV[dirn];
      printf("\x1b[%d;%dH%lc", y, x, poem[poemn]);
      printf("\x1b[8;1H");
      fflush(stdout);
      usleep(S);
      ++poemn;
    }
    dirn=(dirn+1)%4;
  }
  
  return 0;
}
