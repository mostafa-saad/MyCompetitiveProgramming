#include <stdio.h>

#define DEBUG 0

#define MAXN 1000
#define MAXM 10

#define na11 180000

int p[MAXN+2][MAXM+2];      // papier: 0-diera, 1-papier
int M,N,K;

int s[na11],t[na11],u[na11];
int na[12] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147};

int nohole(int x1,int y1,int x2,int y2)
{
	for (int i=x1; i<=x2; i++) for (int j=y1; j<=y2; j++) if (!p[i][j]) return 0;
	return 1;
}

//       stlpec  riadok index1   index2    pridane 3x2
void srot(int x, int y, int low, int high, int plus)
{
DEBUG && printf("> Srot(x=%d, y=%d, low=%d, high=%d, plus=%d)\n",x,y,low,high,plus);
	if (y < M)
	{
		srot(x, y+1, low+2*na[y], high, plus);
		srot(x, y+1, low+2*na[y], high+na[y], plus);
		srot(x, y+1, low+2*na[y], high+2*na[y], plus);

		if (nohole(x-3,y,x-1,y+1))
		{
			srot(x, y+2, low, high+na[y]+na[y+1], plus+1);
			srot(x, y+2, low, high+2*na[y]+na[y+1], plus+1);
			srot(x, y+2, low, high+na[y]+2*na[y+1], plus+1);
			srot(x, y+2, low, high+2*na[y]+2*na[y+1], plus+1);
		}

		if (nohole(x-2,y,x,y+1))
		{
			srot(x, y+2, low+na[y]+na[y+1], high+2*na[y]+2*na[y+1], plus+1);
		}

		if (nohole(x-2,y,x-1,y+2))
		{
			srot(x, y+3, low+na[y]+na[y+1]+na[y+2], high+na[y]+na[y+1]+na[y+2], plus+1);
			srot(x, y+3, low+na[y]+na[y+1]+na[y+2], high+2*na[y]+na[y+1]+na[y+2], plus+1);
			srot(x, y+3, low+na[y]+na[y+1]+na[y+2], high+na[y]+2*na[y+1]+na[y+2], plus+1);
			srot(x, y+3, low+na[y]+na[y+1]+na[y+2], high+2*na[y]+2*na[y+1]+na[y+2], plus+1);
			srot(x, y+3, low+na[y]+na[y+1]+na[y+2], high+na[y]+na[y+1]+2*na[y+2], plus+1);
			srot(x, y+3, low+na[y]+na[y+1]+na[y+2], high+2*na[y]+na[y+1]+2*na[y+2], plus+1);
			srot(x, y+3, low+na[y]+na[y+1]+na[y+2], high+na[y]+2*na[y+1]+2*na[y+2], plus+1);
			srot(x, y+3, low+na[y]+na[y+1]+na[y+2], high+2*na[y]+2*na[y+1]+2*na[y+2], plus+1);
		}

		if (nohole(x-1,y,x,y+2))
		{
			srot(x, y+3, low+2*na[y]+2*na[y+1]+2*na[y+2], high+2*na[y]+2*na[y+1]+2*na[y+2], plus+1);
		}
	}
	else
	{
DEBUG && printf("| naslo: u[%d] (%d) := s[%d] (%d) + %d\n", high, u[high], low, s[low], plus);
		if (u[high] < s[low]+plus)
//DEBUG && printf("| naslo: u[%d] (%d) := s[%d] (%d) + %d\n", high, u[high], low, s[low], plus),
			u[high] = s[low]+plus;
	}
DEBUG && printf("< Srot(x=%d, y=%d, low=%d, high=%d, plus=%d)\n",x,y,low,high,plus);
}

int main(void)
{
	int D;
	scanf("%d", &D);

	while (D--)
	{
		scanf("%d %d %d", &N, &M, &K);
		for (int i=2; i<N+2; i++) for (int j=0; j<M; j++) p[i][j] = 1;
		for (int i=0; i<N+2; i++) p[i][M] = p[i][M+1] = 0;
		for (int i=0; i<M; i++) p[0][i] = p[1][i] = 0;
		for (int i=0; i<K; i++)
		{
			int x,y;
			scanf("%d %d", &x, &y);
			p[x+1][y-1] = 0;
		}

if (DEBUG) 
  for (int j=0; j<M+2; j++) {
  for (int i=0; i<N+2; i++) printf("%d", p[i][j]);
  printf("\n");}

		for (int i=0; i<na[M]; i++) s[i] = t[i] = 0;
		for (int i=3; i<N+2; i++)
		{
			for (int j=0; j<na[M]; j++) u[j] = 0;
			srot(i,0,0,0,0);
			for (int j=0; j<na[M]; j++) s[j] = t[j], t[j] = u[j];
		}

		printf("%d\n", t[na[M]-1]);
	}

	return 0;
}







