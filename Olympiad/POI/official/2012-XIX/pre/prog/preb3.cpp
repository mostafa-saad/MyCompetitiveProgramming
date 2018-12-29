/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie bardzo bledne, bierzemy maksymalny   *
 *                      prefikso-sufiks                                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const int MAXN = 1000005;

int n;
char word[MAXN];
int p[MAXN];

int main() {
	scanf("%d%s",&n,word+1);
	p[1]=0;
	int k=0;
	for(int i=2; i<=n; ++i) {
		while(k && word[i]!=word[k+1]) k=p[k];
		if(word[i]==word[k+1]) ++k;
		p[i]=k;
	}
	printf("%d\n",p[n]);
	return 0;
}
