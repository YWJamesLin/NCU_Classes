#include <stdio.h>

int main()
{
	int n, i, j;

	scanf("%d", &n);
	for(i=1; i<=n; ++i)
	{
		if(i==1){ printf("%*c", 2*n+1, '_'); }
		else{ printf("%*c", 4*n+1, '_'); }
	}
	puts("");
	for(i=1; i<=n; ++i)
	{
		for(j=1; j<=n; ++j)
		{
			if(j==1){ printf("%*c%c", 2*(n-i)+1, '_', '|');  }
			else{ printf("%*c%c", 4*(n-i)+1, '_', '|'); }
			printf("%*c%c", i*4-2, '|', '_');
		}
		puts("");
	}

	return 0;
}
