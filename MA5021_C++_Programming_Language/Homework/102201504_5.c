#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#define S 250000

int main (void) {
  wchar_t *poems = L"起看山色拂雲開，萬壑千重紫翠來。"
                   L"開戶鄭真芳草遙，閉關許謹落花誰。"
                   L"醉醒只向書倉坐，醒醉惟從夢境回。"
                   L"塵世簪纓從不問，浮雲難上釣魚台。"

                   L"問誰花裡掩松關，有客新從塵市還。"
                   L"來去燕當簾際舞，去來鷗在水濱間。"
                   L"人言行已在皆濁，吾謂持身良獨艱。"
                   L"濁世市交多惡客，但令無得近雲山。"

                   L"自憐衣褐老隆中，憶自童年倏作翁。"
                   L"湖海氣消年亦謝，煙霞情重癖難改。"
                   L"謝山雲臥輸陶令，蔣遙花香勝鄭公。"
                   L"將寄愁懷對明月，只將琴拂弄三終。";
  int ind[] = {2, 2, 6, 2, 2, 6, 2, 2, 6, 6, 6}, nind, cloc;
  int rV[] = {1, 0, -1, 0}, cV[] = {0, -2, 0, 2}, row, col, dir;
  int i, j;

  setlocale( LC_ALL, "zh_TW.UTF-8");
  nind = 4, cloc = 1, row = 1, col = 15*2, dir = 0;
  printf ("\x1b[2J");
  printf ("\x1b[%d;%dH%lc", row, col, poems[0]);
  fflush (stdout);
  usleep (S);
  while (cloc < wcslen (poems)) {
    for (i = 0; i < ind[nind]; ++ i) {
      if (poems[cloc] == L'，' || poems[cloc] == L'。') { ++ cloc; }
      row += rV[dir], col += cV[dir];
      printf ("\x1b[%d;%dH%lc", row, col, poems[cloc]);
      printf ("\x1b[16;1H");
      fflush (stdout);
      usleep (S);
      ++ cloc;
    }
    dir = (dir + 1) % 4;
    nind = (nind + 1) % 11;
  }

  return 0;
}
