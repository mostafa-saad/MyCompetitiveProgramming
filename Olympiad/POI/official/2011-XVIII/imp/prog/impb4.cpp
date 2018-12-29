/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Impreza                                          *
 *   Autor:             Bartosz Gorski                                   *
 *   Opis:              Rozwiazanie bledne                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

#define MAX_N 3000

int n, m, a, b, k, deg[MAX_N],deg0[MAX_N];
bool del[MAX_N], gra[MAX_N][MAX_N];
vector<pair<int, int> > par;
vector<int> cli;

int main() {
	assert(scanf("%d%d", &n, &m) == 2);
	for(int i = 0; i < m; ++i) {
		assert(scanf("%d%d", &a, &b) == 2);
		--a; --b;
		gra[a][b] = gra[b][a] = true;
		++deg[a];
		++deg[b];
	}
	for(int i=0;i<n;i++) deg0[i]=deg[i];
	for(int ii=0;ii<30;ii++)
	{
		cli.clear();
		k=0;
		for(int i=0;i<n;i++)
		{
			del[i]=false;
			deg[i]=deg0[i];
		}
		int krok=0;
		for(int i = 0; i < n; ++i) {
			par.clear();	
			for(int j = 0; j < n; ++j)
				if(!del[j] && deg[j] > 0)
					par.push_back(make_pair(-deg[j], j));
			sort(par.begin(), par.end());
			if (k >= n / 3) goto hell;
			if(par.empty() || k >= n / 3)
				break;
			if (krok==0) cli.push_back(par[min(ii,(int)par.size())].second); else cli.push_back(par[0].second);
			krok++;
			++k;
			a = cli.back();
			for(int j = 0; j < n; ++j)
				if(!gra[a][j] && !del[j]) {
					del[j] = true;
					for(int l = 0; l < n; ++l)
						if(gra[j][l])
							--deg[l];
				}
			del[a] = true;	
		}
	}
hell:
	//printf("%d\n", k);
	for(int i = 0; i < k; ++i)
		printf("%d ", cli[i] + 1);
	return 0;
}
