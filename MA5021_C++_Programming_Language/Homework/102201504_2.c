#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int in, i, j, k;
	
	putchar('>');
	scanf("%d", &in);
	printf("\x1b[30m");
	for(i=1; i<=2*in; ++i) 
	{
		for(j=1; j<=in; ++j) 
		{
			if(i!=1) 
			{
				if(j==1){ printf("%*c", i-1, ' '); }
				else{ printf("\x1b[47m%*c\x1b[40m", 2*(i-1), ' '); }
			}
			if(i%2==0){ printf("|%*c", 4*in-2*i+2, '|'); }
			else{ printf("-%*c", 4*in-2*i+2, '-'); }
		}
		puts("");
	}
	for(i=2*in; i>=1; --i) 
	{
		for(j=1; j<=in; ++j) 
		{
			if(i!=1) 
			{
				if(j==1){ printf("%*c", i-1, ' '); }
				else{ printf("\x1b[47m%*c\x1b[40m", 2*(i-1), ' '); }
			}
			if(i%2==0){ printf("|%*c", 4*in-2*i+2, '|'); }
			else{ printf("-%*c", 4*in-2*i+2, '-'); }
		}
		puts("");
	}

	return 0;
}
