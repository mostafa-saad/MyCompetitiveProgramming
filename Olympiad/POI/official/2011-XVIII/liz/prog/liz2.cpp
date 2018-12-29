/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *          pamieciowa: O(n)                                             *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N=1000010;
char c[MAX_N]; int gdzie[2*MAX_N], e[2];

int main(void) {
	int n, m, i, j=0, k, mx=0;
	assert(scanf("%d%d%s", &n, &m, c)==3);
	for(i=0; i<n; ++i)
		c[i]=(c[i]=='T'?2:1);
	for(j=0; j<n; ++j) {
		if(c[j]==1)
			break;
	}
	memset(gdzie, -1, sizeof(int)*2*(n+1));
	for(i=j; i<n; ++i) {
		mx+=c[i]; gdzie[mx]=i;
		e[mx&1]=max(e[mx&1], mx);
	}
	while(m--) {
		assert(scanf("%d", &k)==1);
		if(j==n) {
			if((k&1) || k>(n<<1))
				puts("NIE");
			else
				printf("%d %d\n", 1, k>>1);
		}
		else {
			if(!(k&1) && k<=2*j)
				printf("%d %d\n", 1, k>>1);
			else if(k<=mx) {
				if(gdzie[k]!=-1)
					printf("%d %d\n", j+1, gdzie[k]+1);
				else
					printf("%d %d\n", j+2, gdzie[k+1]+1);
			}
			else {
				if(k<=(j<<1)+e[k&1])
					printf("%d %d\n", j-((k-e[k&1])>>1)+1, gdzie[e[k&1]]+1);
				else
					puts("NIE");
			}
		}
	}
	return 0;
}
