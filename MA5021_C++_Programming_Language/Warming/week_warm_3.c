#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define S 50000

int main()
{
	int m, n, i, j, indbg;
	char **left, **mid, **right;
	
	scanf("%d", &n);
	left=(char **)malloc(sizeof(char *)*n);
	mid=(char **)malloc(sizeof(char *)*n);
	right=(char **)malloc(sizeof(char *)*n);
	m=n;
	for(i=0; i<n; ++i)
	{
		left[i]=(char *)malloc(sizeof(char)*m);
		right[i]=(char *)malloc(sizeof(char)*m);
		for(j=0; j<m; ++j)
		{
			left[i][j]='/';
			right[i][j]='\\';
		}
		mid[i]=(char *)malloc(sizeof(char)*(2*i+1));
		for(j=0; j<2*i+1; ++j){ mid[i][j]='@'; }
		--m;
	}
	m=n;
	printf("\x1b[2J");
	for(i=0; i<n; ++i)
	{
		printf("\x1b[%d;1H", i+1);
		for(j=0; j<m; ++j){ printf("%c", left[i][j]);  }
		printf("\x1b[%d;1H", n+1); 
		fflush(stdout);
		m--;
		usleep(S);
	}
	m=n;
	indbg=m+4;
	for(i=0; i<n; ++i)
	{
		printf("\x1b[%d;%dH", i+1, indbg);
		for(j=0; j<m; ++j){ printf("%c", right[i][j]); }
		printf("\x1b[%d;1H", n+1); 
		fflush(stdout);
		--m, ++indbg;
		usleep(S);
	}
	m=n;
	indbg=m+2;
	for(i=0; i<n; ++i)
	{
		printf("\x1b[%d;%dH", i+1, indbg);
		for(j=0; j<2*i+1; ++j){ printf("%c", mid[i][j]); }
		printf("\x1b[%d;1H", n+1); 
		fflush(stdout);
		--m, --indbg;
		usleep(S);
	}
	puts("");
	for(i=0; i<n; ++i)
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
