/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tess6.cpp                                        *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie powolne.                             *
 *   Złożoność czasowa: O(m * n + l)                                     *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

#define MAX_M 1000000 // maksymalna długość ciągu a_i
#define MAX_A 1000000 // maksymalny wyraz ciągu

int m, n, k, b[MAX_M], p, a[MAX_M], emp;
int cou[MAX_A][2], ind[MAX_A], beg[MAX_A], pos[MAX_A];
bool ok;

int main()
{
    for(int i = 0; i < MAX_A; ++i)
    {
        cou[i][0] = cou[i][1] = pos[i] = 0;
        beg[i] = -1;
    }

	scanf("%d", &m);    
	for(int i = 0; i < m; ++i) {
		scanf("%d", &a[i]);
        --a[i];
        ++cou[a[i]][0];
	}

    emp = 0;
    for(int i = 0; i < MAX_A; ++i) {
        if(cou[i] > 0)
            beg[i] = pos[i] = emp;
        emp += cou[i][0];
        cou[i][0] = 0;
    }

    for(int i = 0; i < m; ++i) {
        ind[beg[a[i]] + cou[a[i]][0]] = i;
        cou[a[i]][0]++;
    }

	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &k);
		p = -1;
		ok = true;
		for(int j = 0; j < k; ++j) {
			scanf("%d", &b[j]);
			--b[j];
            ++cou[b[j]][1];
            if(cou[b[j]][0] < cou[b[j]][1])
                ok = false;
        }
		for(int j = 0; j < k; ++j) {
			if(!ok || beg[b[j]] == -1) {
				ok = false;
				break;
			}
			int l = pos[b[j]], r = beg[b[j]] + cou[b[j]][0];
			while(l < r && ind[l] <= p)
                l++;
            pos[b[j]] = l + 1;
			if(l == r)
				ok = false;
			else
				p = ind[l];
		}
		printf("%s\n", (ok ? "TAK" : "NIE"));
        for(int j = 0; j < k; ++j) {
            pos[b[j]] = beg[b[j]];
            cou[b[j]][1] = 0;
        }
	}

	return 0;
}
