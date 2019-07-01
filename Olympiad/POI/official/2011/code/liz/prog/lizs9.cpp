/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie powolne, s8 ale od tylu              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAX_N=1000010;
int l[2*MAX_N], r[2*MAX_N], w[2*MAX_N];
char c[MAX_N], us[2*MAX_N];

int main(void) {
	int n, m, i, j, k, M=0;
	scanf("%d%d%s", &n, &m, c);
	for(i=0; i<n; ++i)
		c[i]=(c[i]=='T'?2:1);
	memset(w, -1, sizeof w);
	for(i=0; i<n; ++i) {
		M+=c[i];
		w[M]=i;
	}
	while(m--) {
		scanf("%d", &k);
		if(!us[k]) {
			us[k]=1; l[k]=-1;
			if(w[k]!=-1) {
				l[k]=1; r[k]=w[k]+1;
			}
			else if(w[k+1]!=-1) {
				for(i=n-1, j=M; i>=w[k+1]; --i) {
					if(w[j-k]!=-1) {
						l[k]=w[j-k]+2;
						r[k]=i+1;
						break;
					}
					j-=c[i];
				}
			}
		}
		if(l[k]==-1)
			puts("NIE");
		else
			printf("%d %d\n", l[k], r[k]);
	}
	return 0;
}
