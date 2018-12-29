/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie bledne, losowanie                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N=1000010, OP = 20000000;
int l[2*MAX_N], r[2*MAX_N], w[2*MAX_N], sum[MAX_N], in[MAX_N];
char c[MAX_N], us[2*MAX_N];

int main(void) {
	int n, m, i, j, k, t, M=0, rozne=0; srand(39875);
	scanf("%d%d%s", &n, &m, c);
	for(i=0; i<n; ++i)
		c[i]=(c[i]=='T'?2:1);
	memset(w, -1, sizeof w);
	for(i=0; i<n; ++i) {
		M+=c[i]; sum[i]=M;
		w[M]=i;
	}
	for(i=0; i<m; ++i) {
		scanf("%d", &in[i]);
		if(!us[in[i]]) {
			++rozne;
			us[in[i]]=1;
		}
	}
	memset(us, 0, sizeof us);
	int ile = OP;
	for(t=0; t<m; ++t) {
		k=in[t];
		if(!us[k]) {
			us[k]=1; l[k]=-1;
			if(w[k]!=-1) {
				l[k]=1; r[k]=w[k]+1;
			}
			else if(w[k+1]!=-1) {
				int mod=(n-w[k+1])/(ile/(m-t)), y;
				for(y=1; y<=mod; y<<=1); mod=max(1,(y>>1));
				for(i=w[k+1], j=0; i<n; ++j, --ile) {
					if(w[sum[i]-k]!=-1) {
						l[k]=w[sum[i]-k]+2;
						r[k]=i+1;
						break;
					}
					i+=mod+(rand()&(mod-1));
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
