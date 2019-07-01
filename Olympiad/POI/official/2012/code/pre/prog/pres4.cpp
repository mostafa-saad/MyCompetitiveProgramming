/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne: sprawdzanie rownowaznosci   *
 *                      cyklicznej slow za pomoca magicznego algorytmu   *
 *                      liniowego                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

const int MAXN = 1000005;

int N;
char word[MAXN];

bool cycEq(int len) {
	char *s1=word+1,*s2=word+N-len+1;
	int n=len,i=0,j=0,k=0;
	while(i<n&&j<n&&k<n) {
		k=1;
		while(k<=n&&s1[(i+k)%n]==s2[(j+k)%n]) k++;
		if(k<=n) {
			if(s1[(i+k)%n]>s2[(j+k)%n]) i+=k;
			else j+=k;
		}
	}
	return k>n;
}

int main() {
	scanf("%d%s",&N,word+1);
	for(int i=N/2; i>0; --i) {
		if(cycEq(i)) {
			printf("%d\n",i);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
