/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tess1.c                                          *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie powolne.                             *
 *   Złożoność czasowa: O(m + l * log m + |A|)                           *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define MAX_M 1000000 // maksymalna długość ciągu a_i
#define MAX_A 1000000 // maksymalny wyraz ciągu

int m, n, k, b, p, a[MAX_M], emp, ok;
int cou[MAX_A], ind[MAX_A], beg[MAX_A];

int main()
{
    int i, j, l, c, r;

    for(i = 0; i < MAX_A; ++i)
    {
        cou[i] = 0;
        beg[i] = -1;
    }

	scanf("%d", &m);    
	for(i = 0; i < m; ++i) {
		scanf("%d", &a[i]);
        --a[i];
        ++cou[a[i]];
	}

    emp = 0;
    for(i = 0; i < MAX_A; ++i) {
        if(cou[i] > 0)
            beg[i] = emp;
        emp += cou[i];
        cou[i] = 0;
    }

    for(i = 0; i < m; ++i) {
        ind[beg[a[i]] + cou[a[i]]] = i;
        cou[a[i]]++;
    }

	scanf("%d", &n);
	for(i = 0; i < n; ++i) {
		scanf("%d", &k);
		p = -1;
		ok = 1;
		for(j = 0; j < k; ++j) {
			scanf("%d", &b);
			--b;
			if(!ok || beg[b] == -1) {
				ok = 0;
				continue;
			}
			l = beg[b];
            r = beg[b] + cou[b];
			while(l < r) {
				c = (l + r) / 2;
				if(ind[c] <= p)
					l = c + 1;
				else
					r = c;
			}
			if(l == (beg[b] + cou[b]))
				ok = 0;
			else
				p = ind[l];
		}
		printf("%s\n", (ok ? "TAK" : "NIE"));
	}

	return 0;
}
