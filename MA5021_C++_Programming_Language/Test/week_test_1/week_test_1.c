#include <stdio.h>

int main()
{
	int N, i, j;
	
	putchar('>');
	scanf("%d", &N);
	for(i=1; i<=N+1; ++i)
	{
		for(j=1; j<=N; ++j)
		{
			if(i==N+1)
			{
				if(j==1){ printf("%*s", 2*N+2, "| |"); }
				else{ printf("%*s", 4*N+1, "| |"); }
			}
			else if(i==1){ printf("%s%*s", "_", 4*N, "_"); }
			else
			{
				if(j==1){ printf("%*s", 2*i-1, "|_"); }
				else{ printf("%*s", 4*(i-1), "|_"); }
				printf("%*s", 4*(N-i)+5, "_|");
			}
		}
		printf("\n");
	}
	for(i=N; i>=1; --i)
	{
		for(j=1; j<=N; ++j)
		{
			if(j==1){ printf("%*s", 2*i, "_|"); }
		  else{ printf("%*s", 4*i-2, "_|"); }
			printf("%*s", 4*(N-i)+3, "|_");
		}
		printf("\n");
	}

	return 0;
}
