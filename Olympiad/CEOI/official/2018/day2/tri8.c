// Mateusz Radecki
// Queries: O(n*log(n))
// Complexity: O(n*log(n))

#include <stdio.h>
#include <stdlib.h>
#include "trilib.h"

const int nax=40*1007;

struct vector
{
	int *tab;
	int r;
};

int pyt(struct vector * wek, int v)
{
	return (*wek).tab[v];
}

int size(struct vector * wek)
{
	return (*wek).r;
}

int back(struct vector * wek)
{
	return (*wek).tab[(*wek).r-1];
}

void push_back(struct vector * wek, int v)
{
	(*wek).tab[(*wek).r]=v;
	(*wek).r++;
}

void pop_back(struct vector * wek)
{
	(*wek).r--;
}

int *begin(struct vector * wek)
{
	return (*wek).tab;
}

int *end(struct vector * wek)
{
	return (*wek).tab+size(wek);
}

void wloz(struct vector * wek, int v)
{
	int i=(*wek).r;
	while(i>0)
	{
		(*wek).tab[i]=(*wek).tab[i-1];
		i--;
	}
	(*wek).tab[0]=v;
	(*wek).r++;
}

void reverse(int *a, int *b)
{
	b--;
	while(a<b)
	{
		int tmp=(*a);
		(*a)=(*b);
		(*b)=tmp;
		a++;
		b--;
	}
}

int n;
struct vector divide[2], hull[2];

int is_less(const void * a, const void * b)
{
	return 1-2*is_clockwise(1, *(int*)a, *(int*)b);
}

int main()
{
	int h, i;
	n=get_n();
	for (i=0; i<2; i++)
	{
		divide[i].r=0;
		divide[i].tab=(int*)malloc(nax*sizeof(int));
		hull[i].r=0;
		hull[i].tab=(int*)malloc(nax*sizeof(int));
	}
	for (i=3; i<=n; i++)
		push_back(&divide[is_clockwise(1, 2, i)], i);
	for (h=0; h<2; h++)
	{
		push_back(&divide[h], 2);
		qsort(begin(&divide[h]), size(&divide[h]), sizeof(int), is_less);
		for (i=0; i<size(&divide[h]); i++)
		{
			int r=size(&hull[h]);
			while (r>1 && !is_clockwise(pyt(&hull[h], r-2), pyt(&hull[h], r-1), pyt(&divide[h], i)))
			{
				r--;
				pop_back(&hull[h]);
			}
			push_back(&hull[h], pyt(&divide[h], i));
		}
		if (h)
			reverse(begin(&hull[h]), end(&hull[h]));
		wloz(&hull[h], 1);
	}
	for (h=0; h<2; h++)
	{
		pop_back(&hull[0]);
		while (1)
		{
			int out=1;
			int r=size(&hull[0]);
			if (r>1 && !is_clockwise(pyt(&hull[0], r-2), pyt(&hull[0], r-1), back(&hull[1])))
			{
				pop_back(&hull[0]);
				out=0;
			}
			int d=size(&hull[1]);
			if (d>1 && !is_clockwise(back(&hull[0]), pyt(&hull[1], d-1), pyt(&hull[1], d-2)))
			{
				pop_back(&hull[1]);
				out=0;
			}
			if (out)
				break;
		}
		for (i=0; i<2; i++)
			reverse(begin(&hull[i]), end(&hull[i]));
		struct vector tmp=hull[0];
		hull[0]=hull[1];
		hull[1]=tmp;
	}
	give_answer(size(&hull[0])+size(&hull[1]));
	return 0;
}
