#include <stdio.h>
#include <stdlib.h>

#define MAXW 10000000
#define MAXN 1000000
#define MAXQ 1000000

typedef long long int huge;

int w, h, n, q;

typedef struct PLANT
{
	int x;
	int y;
	int a;
	int b;
}
PLANT;

typedef struct QUERY
{
	int x1;
	int y1;
	int x2;
	int y2;
}
QUERY;

huge Nuclearia[MAXW], Piece[MAXW];
PLANT Plant[MAXN];
QUERY Query[MAXQ];

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void Summarize()
{
	for(int x = 1; x < w; x++)
	{
		Nuclearia[x] += Nuclearia[x - 1];
	}
}

void Print(huge sum, int width)
{
	huge rsl = sum / width;
	if((sum % width) * 2 >= width)
	{
		rsl++;
	}
	
	printf("%lld\n", rsl);
}

int main()
{
	scanf("%d%d", &w, &h);
	
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d%d%d", &(Plant[i].x), &(Plant[i].y), &(Plant[i].a), &(Plant[i].b));
		Plant[i].x--;
	}
	
	scanf("%d", &q);
	for(int i = 0; i < q; i++)
	{
		scanf("%d%d%d%d", &(Query[i].x1), &(Query[i].y1), &(Query[i].x2), &(Query[i].y2));
		Query[i].x1 -= 2;
		Query[i].x2--;
	}
	
	for(int i = 0; i < n; i++)
	{
		PLANT& P = Plant[i];
		int d = (P.a - 1) / P.b;
		int x1 = P.x - d;
		int x2 = P.x + d + 1;
		int r = P.a % P.b;
		
		if(r)
		{
			Piece[max(0, x1)] += r;
			if(x2 < w) Piece[x2] -= r;
			
			x1++;
			x2--;
		}
		
		int x = P.x + 1;
		x2++;
		
		if(x1 < 0)
		{
			int m = -x1;
			Piece[0] += P.b * m;
			x1 += m;
		}
		
		Nuclearia[x1] += P.b;
		if(x < w) Nuclearia[x] -= P.b * 2;
		if(x2 < w) Nuclearia[x2] += P.b;
	}
	
	Summarize();
	
	for(int x = 0; x < w; x++)
	{
		Nuclearia[x] += Piece[x];
	}
	
	Summarize();
	Summarize();
	
	for(int i = 0; i < q; i++)
	{
		QUERY& Q = Query[i];
		huge rsl = Nuclearia[Q.x2];
		if(Q.x1 >= 0) rsl -= Nuclearia[Q.x1];
		
		Print(rsl, Q.x2 - Q.x1);
	}
	
	return 0;
}
