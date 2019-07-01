/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n^3)                                           *
 *   Opis:              Rozwiazanie powolne: naiwne sprawdzanie          *
 *                      rownowaznosci cyklicznej slow                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const int MAXN = 1000005;

int n;
char word[MAXN];

bool cycEq(int len) {
	for(int i=1; i<=len; ++i) {
		bool ok=true;
		for(int j=1; ok && j<=len; ++j) {
			if(word[n-len+j] != word[(i+j-2)%len+1]) ok=false;
		}
		if(ok) return true;
	}
	return false;
}

int main() {
	scanf("%d%s",&n,word+1);
	for(int i=n/2; i>0; --i) {
		if(cycEq(i)) {
			printf("%d\n",i);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
