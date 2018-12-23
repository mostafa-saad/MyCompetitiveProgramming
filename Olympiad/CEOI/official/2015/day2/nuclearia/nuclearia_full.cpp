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

NUCLEARIA Nuclearia, PosDiag, NegDiag;
PLANT Plant[MAXN];
QUERY Query[MAXQ];
huge Row[MAXWH];
huge Col[MAXWH];

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void UpdatePosDiag(int x1, int y1, int x2, int y2, int b)
{
	if((x1 < 0) && (y1 < 0))
	{
		int m = -max(x1, y1);
		Nuclearia(0, 0) += m * b;
		x1 += m;
		y1 += m;
	}
	
	if(x1 < 0)
	{
		int m = -x1;
		Col[y1] += b;
		Col[y1 + m] -= b;
		x1 += m;
		y1 += m;
	}
	
	if(y1 < 0)
	{
		int m = -y1;
		Row[x1] += b;
		Row[x1 + m] -= b;
		x1 += m;
		y1 += m;
	}
	
	PosDiag(x1, y1) += b;
	
	if((x2 + 1 < w) && (y2 + 1 < h)) PosDiag(x2 + 1, y2 + 1) -= b;
}

void UpdateNegDiag(int x1, int y1, int x2, int y2, int b)
{
	if(y2 > h - 1)
	{
		int m = y2 - (h - 1);
		x1 += m;
		y2 -= m;
	}
	
	if(x1 < 0)
	{
		int m = -x1;
		Col[(y2 - m) + 1] -= b;
		if(y2 + 1 < h) Col[y2 + 1] += b;
		x1 += m;
		y2 -= m;
	}
	
	if((x1 < w) && (y2 >= 0)) NegDiag(x1, y2) -= b;
	
	if(x2 > w - 1)
	{
		int m = x2 - (w - 1);
		x2 -= m;
		y1 += m;
	}
	
	if(y1 < 0)
	{
		int m = -y1;
		Row[(x2 - m) + 1] -= b;
		if(x2 + 1 < w) Row[x2 + 1] += b;
		x2 -= m;
		y1 += m;
	}
	
	if((x2 + 1 >= 0) && (x2 + 1 < w) && (y1 - 1 >= 0) && (y1 - 1 < h)) NegDiag(x2 + 1, y1 - 1) += b;
}

void SummarizeDiags()
{
	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < h; y++)
		{
			if((x) && (y)) PosDiag(x, y) += PosDiag(x - 1, y - 1);
			if((x) && (y != h - 1)) NegDiag(x, y) += NegDiag(x - 1, y + 1);
		}
	}
}

void AddDiags()
{
	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < h; y++)
		{
			Nuclearia(x, y) += PosDiag(x, y);
			Nuclearia(x, y) += NegDiag(x, y);
		}
	}
}

void SummarizeLines()
{
	for(int x = 1; x < w; x++)
	{
		Row[x] += Row[x - 1];
	}
	
	for(int y = 1; y < h; y++)
	{
		Col[y] += Col[y - 1];
	}
}

void AddLines()
{
	for(int x = 0; x < w; x++)
	{
		Nuclearia(x, 0) += Row[x];
	}
	
	for(int y = 0; y < h; y++)
	{
		Nuclearia(0, y) += Col[y];
	}
}

void Summarize()
{
	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < h; y++)
		{
			if(x) Nuclearia(x, y) += Nuclearia(x - 1, y);
			if(y) Nuclearia(x, y) += Nuclearia(x, y - 1);
			if((x) && (y)) Nuclearia(x, y) -= Nuclearia(x - 1, y - 1);
		}
	}
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
		Query[i].x1 -= 2;
		Query[i].y1 -= 2;
		Query[i].x2--;
		Query[i].y2--;
	}
	
	for(int i = 0; i < n; i++)
	{
		PLANT& P = Plant[i];
		int d = (P.a - 1) / P.b;
		int x1 = P.x - d;
		int y1 = P.y - d;
		int x2 = P.x + d + 1;
		int y2 = P.y + d + 1;
		int r = P.a % P.b;
		
		if(r)
		{
			Nuclearia(max(0, x1), max(0, y1)) += r;
			if(x2 < w) Nuclearia(x2, max(0, y1)) -= r;
			if(y2 < h) Nuclearia(max(0, x1), y2) -= r;
			if((x2 < w) && (y2 < h)) Nuclearia(x2, y2) += r;
			
			x1++;
			y1++;
			x2--;
			y2--;
		}
		
		if(P.a >= P.b)
		{
			UpdatePosDiag(x1, y1, x2, y2, P.b);
			UpdateNegDiag(x1, y1, x2, y2, P.b);
		}
	}
	
	SummarizeDiags();
	AddDiags();
	SummarizeLines();
	AddLines();
	Summarize();
	Summarize();
	
	for(int i = 0; i < q; i++)
	{
		QUERY& Q = Query[i];
		huge rsl = Nuclearia(Q.x2, Q.y2);
		if(Q.x1 >= 0) rsl -= Nuclearia(Q.x1, Q.y2);
		if(Q.y1 >= 0) rsl -= Nuclearia(Q.x2, Q.y1);
		if((Q.x1 >= 0) && (Q.y1 >= 0)) rsl += Nuclearia(Q.x1, Q.y1);
		
		Print(rsl, (Q.x2 - Q.x1) * (Q.y2 - Q.y1));
	}
	
	return 0;
}
