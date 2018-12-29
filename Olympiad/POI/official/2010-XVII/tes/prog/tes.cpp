/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tes.cpp                                          *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie wzorcowe.                            *
 *                      Rozwiązanie wykorzystuje STLa.                   *
 *   Złożoność czasowa: O(m + l + |A|)                                   *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
using namespace std;

#define MAX_M 1000000 // maksymalna długość ciągu a_i
#define MAX_A 1000000 // maksymalny wyraz ciągu

int m, n, k, a[MAX_M];
vector<int> b[MAX_M], nr[MAX_A], tmp;

int main()
{
	scanf("%d", &m);
	for(int i = 0; i < m; ++i)
		scanf("%d", &a[i]);
    
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &k);
		b[i] = vector<int>(k, 0);
		for(int j = 0; j < k; ++j)
			scanf("%d", &b[i][k - j - 1]);
		nr[b[i].back() - 1].push_back(i);
	}

	for(int i = 0; i < m; ++i)
	{
		tmp.clear();
		swap(tmp, nr[a[i] - 1]);
		for(int j = 0; j < (int)tmp.size(); ++j)
		{
			b[tmp[j]].pop_back();
			if(!b[tmp[j]].empty())
				nr[b[tmp[j]].back() - 1].push_back(tmp[j]);
		}
	}

	for(int i = 0; i < n; ++i)
		printf("%s\n", (b[i].empty() ? "TAK" : "NIE"));

	return 0;
}
