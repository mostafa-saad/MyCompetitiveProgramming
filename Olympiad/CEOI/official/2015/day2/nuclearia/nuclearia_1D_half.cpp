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

int abs(int a)
{
	return (a < 0) ? -a : a;
}

int dist(int x1, int x2)
{
	return abs(x1 - x2);
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
		
		for(int x = P.x, cur = P.a; (x >= 0) && (cur > 0); x--, cur -= P.b)
		{	
			Nuclearia[x] += cur;
		}
		
		for(int x = P.x + 1, cur = P.a - P.b; (x < w) && (cur > 0); x++, cur -= P.b)
		{
			Nuclearia[x] += cur;
		}
	}
	
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
