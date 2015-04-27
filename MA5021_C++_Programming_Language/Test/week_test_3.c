#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define S 100000

int main()
{
	char **left, **mid, **right;
	int in, tmp, indbg, i, j;

	scanf("%d", &in);
	left=(char **)malloc(sizeof(char *)*in);
	mid=(char **)malloc(sizeof(char *)*in);
	right=(char **)malloc(sizeof(char *)*in);
	tmp=in;
	for(i=0; i<in; ++i)
	{
		left[i]=(char *)malloc(sizeof(char)*tmp);
		right[i]=(char *)malloc(sizeof(char)*tmp);
		for(j=0; j<tmp; ++j)
		{
			left[i][j]='/';
			right[i][j]='\\';
		}
		mid[i]=(char *)malloc(sizeof(char)*(2*i+1));
		for(j=0; j<2*i+1; ++j){ mid[i][j]='@'; }
		--tmp;
	}
	tmp=in;
	printf("\x1b[2J");
	for(i=0; i<in; ++i)
	{
		printf("\x1b[%d;1H", i+1);
		for(j=0; j<tmp; ++j){ printf("%c", left[i][j]); }
		fflush(stdout);
		--tmp;
		usleep(S);
	}
	indbg=in+4;
	tmp=in;
	for(i=0; i<in; ++i)
	{
		printf("\x1b[%d;%dH", i+1, indbg);
		for(j=0; j<tmp; ++j){ printf("%c", right[i][j]); }
		fflush(stdout);
		++indbg;
		--tmp;
		usleep(S);
	}
	tmp=in;
	for(i=0; i<in; ++i)
	{
		for(j=0; j<tmp; ++j)
		{
			left[i][j]='\\';
			right[i][j]='/';
		}
		--tmp;
	}
	tmp=1;
	for(i=in-1; i>=0; --i)
	{
		printf("\x1b[%d;1H", 2*in-i);
		for(j=0; j<tmp; ++j){ printf("%c", left[i][j]); }
		fflush(stdout);
		++tmp;
		usleep(S);
	}
	indbg=2*in+3;
	tmp=1;
	for(i=in-1; i>=0; --i)
	{
		printf("\x1b[%d;%dH", 2*in-i, indbg);
		for(j=0; j<tmp; ++j){ printf("%c",right[i][j]); }
		fflush(stdout);
		--indbg;
		++tmp;
		usleep(S);
	}
	indbg=in+2;
	for(i=0; i<in; ++i)
	{
		printf("\x1b[%d;%dH", i+1, indbg);
		for(j=0; j<2*i+1; ++j){ printf("%c",mid[i][j]); }
		fflush(stdout);
		--indbg;
		usleep(S);
	}
	indbg=3;
	tmp=in-1;
	for(i=in-1; i>=0; --i)
	{
		printf("\x1b[%d;%dH", 2*in-i, indbg);
		for(j=0; j<2*tmp+1; ++j){ printf("%c",mid[i][j]); }
		fflush(stdout);
		++indbg;
		--tmp;
		usleep(S);
	}
	printf("\x1b[%d;1H", 2*in+1);
	for(i=0; i<in; ++i)
	{
		free(left[i]);
		free(mid[i]);
		free(right[i]);
	}
	free(left);
	free(mid);
	free(right);

	return 0;
}
