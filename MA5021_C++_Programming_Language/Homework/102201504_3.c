#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define S 25000

int main(void)
{
	int *bitmap, i, j;

	bitmap =(int *)malloc(sizeof(int)*14);
	bitmap[0]=0x180;
	bitmap[1]=0x3c0;
	bitmap[2]=0x180;
	bitmap[3]=0x0c0;
	bitmap[4]=0x0f0;
	bitmap[5]=0x0e8;
	bitmap[6]=0x164;
	bitmap[7]=0x264;
	bitmap[8]=0x070;
	bitmap[9]=0x050;
	bitmap[10]=0x08e;
	bitmap[11]=0x081;
	bitmap[12]=0x082;
	bitmap[13]=0x300;
	printf("\x1b[2J\x1b[47m");
	for(i=1; i<=20; ++i)
	{
		for(j=1; j<=15; ++j){ printf("\x1b[%d;%dH ", j, i); }
	}
	fflush(stdout);
	usleep(S);
	while(1) 
	{
		for(i=9; i>=0; --i) 
		{
			for(j=0; j<14; ++j) 
			{
				printf("\x1b[%d;%dH", j+1, 2*(10-i)-1);
				if((*(bitmap+j)>>i)%2!=0){ printf("\x1b[40m  \x1b[47m"); }
				else{ printf("  "); }
				printf("\x1b[15;1H"); 
				fflush(stdout);
				usleep(S);
			}
		}
		for(i=10; i>=1; --i) 
		{
			for(j=1; j<=14; ++j)
			{ 
				printf("\x1b[%d;%dH  ", j, i*2-1); 
				printf("\x1b[15;1H"); 
				fflush(stdout);
				usleep(S);
			}
		}
	}
	free(bitmap);

	return 0;
}
