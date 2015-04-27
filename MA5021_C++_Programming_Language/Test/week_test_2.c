#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define S 10000

int main(void)
{
	int pth, ptw, h, w, i, j, tmph, tmpw, rnd;

	scanf("%d%d", &h, &w);
	printf("\x1b[2J");
	srand((unsigned)time(NULL));
	while(1)
	{
		for(pth=1, ptw=1; ptw<=w; ptw+=4)
		{
			for(i=pth, j=ptw; j>=1 && i<=h; ++i, --j)
			{
				rnd=(int)(28.*rand()/(1.+RAND_MAX));
				printf("\x1b[%d;3%dm", rnd/7, rnd%7+1);
				printf("\x1b[%d;%dH/", i, j);
				fflush(stdout);
				printf("\x1b[%d;1H", h+1);
				fflush(stdout);  
				usleep(S);
			}
		}
		for(pth+=ptw-w, ptw=w; pth<=h; pth+=4)
		{
			for(i=pth, j=ptw; j>=1 && i<=h; ++i, --j)
			{
				rnd=(int)(28.*rand()/(1.+RAND_MAX));
				printf("\x1b[%d;3%dm", rnd/7, rnd%7+1);
				printf("\x1b[%d;%dH/", i, j);
				fflush(stdout);
				printf("\x1b[%d;1H", h+1);
				fflush(stdout);
				usleep(S);
			}
		}
		tmph=i-1, tmpw=j+1;
		printf("\x1b[33m");
		for(pth=1, ptw=w; ptw>=1; ptw-=4)
		{
			for(i=pth, j=ptw; j<=w && i<=h; ++i, ++j)
			{
				rnd=(int)(28.*rand()/(1.+RAND_MAX));
				printf("\x1b[%d;3%dm", rnd/7, rnd%7+1);
				printf("\x1b[%d;%dH\\", i, j);
				fflush(stdout);
				printf("\x1b[%d;1H", h+1);
				fflush(stdout);
				usleep(S);
			}
		}
		for(pth+=1-ptw, ptw=1; pth<=h; pth+=4)
		{
			for(i=pth, j=ptw; j<=w && i<=h; ++i, ++j)
			{
				rnd=(int)(28.*rand()/(1.+RAND_MAX));
				printf("\x1b[%d;3%dm", rnd/7, rnd%7+1);
				printf("\x1b[%d;%dH\\", i, j);
				fflush(stdout);
				printf("\x1b[%d;1H", h+1);
				fflush(stdout);
				usleep(S);
			}
		}	
		for(pth=i-1, ptw=j-1; ptw<=w; ptw+=4)
		{
			for(i=pth, j=ptw; j>=1 && i>=1; --i, --j)
			{
				printf("\x1b[%d;%dH ", i, j);
				fflush(stdout);
				printf("\x1b[%d;1H", h+1);
				fflush(stdout);
				usleep(S);
			}
		}
		for(pth-=ptw-w, ptw=w; pth>=1; pth-=4)
		{
			for(i=pth, j=ptw; j>=1 && i>=1; --i, --j)
			{
				printf("\x1b[%d;%dH ", i, j);
				fflush(stdout);
				printf("\x1b[%d;1H", h+1);
				fflush(stdout);
				usleep(S);
			}
		}
		for(pth=tmph, ptw=tmpw; ptw>=1; ptw-=4)
		{
			for(i=pth, j=ptw; j<=w && i>=0; --i, ++j)
			{
				printf("\x1b[%d;%dH ", i, j);
				fflush(stdout);
				printf("\x1b[%d;1H", h+1);
				fflush(stdout);
				usleep(S);
			}
		}
		for(pth-=1-ptw, ptw=1; pth>=0; pth-=4)
		{
			for(i=pth, j=ptw; j<=w && i>=0; --i, ++j)
			{
				printf("\x1b[%d;%dH ", i, j);
				fflush(stdout);
				printf("\x1b[%d;1H", h+1);
				fflush(stdout);
				usleep(S);
			}
		}	
	}

	return 0;
}
