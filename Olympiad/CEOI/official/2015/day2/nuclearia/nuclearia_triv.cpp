#include <stdio.h>
#include <stdlib.h>

#define MAXWH 10000000
#define MAXN 1000000
#define MAXQ 1000000

typedef long long int huge;

int w, h, n, q;

typedef struct NUCLEARIA
{
	huge Info[MAXWH];
	huge& operator () (int x, int y) {return Info[(y * w) + x];}
}
NUCLEARIA;

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

NUCLEARIA Nuclearia;
PLANT Plant[MAXN];
QUERY Query[MAXQ];

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int abs(int a)
{
	return (a < 0) ? -a : a;
}

int dist(int x1, int y1, int x2, int y2)
{
	return max(abs(x1 - x2), abs(y1 - y2));
}

void Print(huge sum, int area)
{
	huge rsl = sum / area;
	if((sum % area) * 2 >= area)
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
		Plant[i].y--;
	}
	
	scanf("%d", &q);
	for(int i = 0; i < q; i++)
	{
		scanf("%d%d%d%d", &(Query[i].x1), &(Query[i].y1), &(Query[i].x2), &(Query[i].y2));
		Query[i].x1--;
		Query[i].y1--;
	}
	
	for(int i = 0; i < n; i++)
	{
		PLANT& P = Plant[i];
		for(int x = 0; x < w; x++)
		{
			for(int y = 0; y < h; y++)
			{
				int d = dist(x, y, P.x, P.y);
				if(P.a > huge(d) * P.b)
				{
					Nuclearia(x, y) += P.a - (d * P.b);
				}
			}
		}
	}
	
	for(int i = 0; i < q; i++)
	{
		QUERY& Q = Query[i];
		huge rsl = 0;
		
		for(int x = Q.x1; x < Q.x2; x++)
		{
			for(int y = Q.y1; y < Q.y2; y++)
			{
				rsl += Nuclearia(x, y);
			}
		}
		
		Print(rsl, (Q.x2 - Q.x1) * (Q.y2 - Q.y1));
	}
	
	return 0;
}
