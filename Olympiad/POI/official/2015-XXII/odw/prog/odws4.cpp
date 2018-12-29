/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Odwiedziny                                         *
 *   Zlozonosc czasowa:    O(nq)                                              *
 *   Autor programu:       Marek Sommer                                       *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/

#include <bits/stdc++.h>

using namespace std;

int n;
int ojc[50005];
int pre[50005]; int pre_l = 0;
int pos[50005];
vector<int> graf[50005];

bool ojciec(int a, int b) {
	return pre[a] <= pre[b] && pre[b] <= pos[a];
}

void dfs(int w, int o)
{
	pre[w] = ++pre_l;
	ojc[w] = o;
	for(auto & i : graf[w])
		if(i != o)
			dfs(i, w);
	pos[w] = pre_l;
}

int c[50005];

void idz(int a, int b, int k)
{
	if(ojciec(b, a))
		swap(a, b);
	int ra = 0, rb = 0;
	int wyn = 0;
	while(!ojciec(a, b))
	{
		if(ra == 0)
			wyn += c[a];
		ra = (ra + 1) % k;
		a = ojc[a];
	}
	while(a != b)
	{
		if(rb == 0)
			wyn += c[b];
		rb = (rb + 1) % k;
		b = ojc[b];
	}
	if(rb == 0)
		wyn += c[b];
	printf("%d\n", wyn);
}

int t[50005];
int k[50005];

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", c + i);
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		graf[a].emplace_back(b);
		graf[b].emplace_back(a);
	}
	dfs(1, -1);
	for(int i = 1; i <= n; i++)
		scanf("%d", t + i);
	for(int i = 1; i < n; i++)
		scanf("%d", k + i);
	for(int i = 1; i < n; i++)
		idz(t[i], t[i + 1], k[i]);
	return 0;
}
