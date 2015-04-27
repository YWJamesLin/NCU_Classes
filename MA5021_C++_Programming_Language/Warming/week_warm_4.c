#include <stdio.h>
#include <unistd.h>
#define S 50000 

int main()
{
	int rVector[]={0, 1, 0, -1}, cVector[]={1, 0, -1, 0};
	int row=1, col=0, time;
	int in, i, j, k;
	
	scanf("%d", &in);
	time=2*in-1;
	printf("\x1b[2J");
	for(i=1; i<=in; ++i)
	{
		for(j=0; j<4; ++j)
		{
			for(k=0; k<time; ++k)
			{
				row+=rVector[j], col+=cVector[j];
				printf("\x1b[%d;%dH%d", row, col, i);
				printf("\x1b[%d;1H", 2*in);
				fflush(stdout);
				usleep(S);
			}
			if(j==0 || j==2){ --time; }
		}
	}
	
	return 0;
}
