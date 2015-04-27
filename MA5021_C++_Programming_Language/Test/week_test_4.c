#include <stdio.h>
#include <unistd.h>
#define S 50000

int main()
{
	int row, col, ind;
	int RV[]={0, 1, 0, -1}, CV[]={2, 0, -2, 0};
	int iRV[]={0, 1, 0, -1}, iCV[]={-2, 0, 2, 0};
	int in, i, j, k;

	scanf("%d", &in);
	row=1, col=-1, ind=2*in-1;
	printf("\x1b[2J");
	for(i=1; i<=in; ++i)
	{
		for(j=0; j<4; ++j)
		{
			for(k=0; k<ind; ++k)
			{
				row+=RV[j], col+=CV[j];
				printf("\x1b[%d;%dH%d", row, col, i);
				printf("\x1b[%d;1H", 2*in);
				fflush(stdout);
				usleep(S/2);
			}
			if(j==0 || j==2){ --ind; }
		}
	}
	usleep(S);
	printf("\x1b[%d;%dH  ", row, col);
	printf("\x1b[%d;1H", 2*in);
	fflush(stdout);
	usleep(S/2);
	for(i=0; i<=in; ++i)
	{
		for(j=0; j<4; ++j)
		{
			for(k=0; k<ind; ++k)
			{
				row+=iRV[j], col+=iCV[j];
				if(row<1 || col<1){ continue; }
				printf("\x1b[%d;%dH  ", row, col);
				printf("\x1b[%d;1H", 2*in);
				fflush(stdout);
				usleep(S/2);
			}
			if(j==1 || j==3){ ++ind; }
		}
	}

	return 0;
}
