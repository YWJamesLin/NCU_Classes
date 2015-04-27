#include <stdio.h>
#include <unistd.h>
#define S 50000

int main(void)
{
	int car[]={0xfff0 ,0x8010 ,0x801f ,0x8001 ,0xcfcf ,0x3030};
	int i, j;
	int ind, max;

	ind=-16, max=16;
	while(1) 
	{
		printf("\x1b[2J");
		fflush(stdout);
		for(i=0; i<6; ++i) 
		{
			for(j=15; j>=0; --j) 
			{
				if(max-j+ind<1 || max-j+ind>60){ continue; }
				printf("\x1b[31m\x1b[%d;%dH", i+1, max-j+ind);
				if((car[i]>>j)%2){ putchar('*'); }
				else{ putchar(' '); }
				printf("\x1b[37m");
			}
		}
		for(i=1; i<=6; ++i)	
		{
			for(j=6; j<=60; j+=8){ printf("\x1b[%d;%dH\x1b[47;30mIII\x1b[40;37m", i, j); }
		}
		for(i=1; i<=60; ++i){ printf("\x1b[7;%dH%d", i, i%10); }
		printf("\x1b[8;1H");
		fflush(stdout);
		++ind;
		if(ind==60){ ind=-16; } 
		usleep(S);
	}

	return 0;
}
