#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <wchar.h>
#define S 50000

int main(void)
{
	wchar_t *foo= L"春眠不覺曉處處聞啼鳥夜來風雨聲花落知多少";
	int in, i, j, bound;

	setlocale(LC_ALL, "zh_TW.UTF-8");
	printf("%c", '>');
	scanf("%d", &in);
	printf("\x1b[2J");
	fflush(stdout);
	i=(20%in!=0)?20/in+1:20/in;
	bound=i;
	for(; i>=1; --i)
	{
		for(j=1; j<=in; ++j)
		{
			if((bound-i)*in+j-1>20){ break; }
			printf("\x1b[%d;%dH%lc", j, 2*i-1, foo[(bound-i)*in+j-1]);
			printf("\x1b[%d;1H", in+1);
			fflush(stdout);
			usleep(S);
		}
	}

	return 0;
}
