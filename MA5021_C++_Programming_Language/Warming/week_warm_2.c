#include <stdio.h>
#include <unistd.h>
#define S 50000 

int main()
{
	int h, w, inh, inw, i, j;

	scanf("%d%d", &h, &w);
	printf("\x1b[2J");
	fflush(stdout);
	for(inh=1, inw=1; inw<=w; inw+=4)
	{
		for(i=inh, j=inw; j>=1 && i<=h; ++i, --j){ printf("\x1b[%d;%dH/", i, j); }
		fflush(stdout);
		usleep(S);
	}
	for(inh+=inw-w, inw=w; inh<=h; inh+=4)
	{
		for(i=inh, j=inw; j>=1 && i<=h; ++i, --j){ printf("\x1b[%d;%dH/", i, j); }
		fflush(stdout);
		usleep(S);
	}
	for(inh=1, inw=w; inw>=1; inw-=4)
	{
		for(i=inh, j=inw; j<=w && i<=h; ++i, ++j){ printf("\x1b[%d;%dH\\", i, j); }
		fflush(stdout);
		usleep(S);
	}
	for(inh+=(1-inw), inw=1; inh<=h; inh+=4)
	{
		for(i=inh, j=inw; j<=w && i<=h; ++i, ++j){ printf("\x1b[%d;%dH\\", i, j); }
		fflush(stdout);
		usleep(S);
	}
	printf("\x1b[%d;1H", h+1);

	return 0;
}
