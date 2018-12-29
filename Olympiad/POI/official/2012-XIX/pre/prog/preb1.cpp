/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie alternatywne, haszowanie             *
 *                                                                       *
 *************************************************************************/

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int MAXN = 1000005;
const unsigned long long X = 44433321;

int n;
char word[MAXN];
int p[MAXN], s[MAXN];
unsigned long long hash[MAXN];
unsigned long long pw[MAXN];

unsigned long long getHash(int i,int j) {
	return hash[j]-hash[i-1]*pw[j-i+1];
}

const int HASH_TRIES = 5;

bool equal(int a,int b,int c,int d) {
	if (getHash(a,b) == getHash(c,d)) {
		for (int i=0; i<HASH_TRIES; ++i) {
			int j = rand()%(b-a+1);
			if (word[a+j] != word[c+j]) return false;
		}
		return true;
	} else {
		return false;
	}
}

int main() {
	srand(time(NULL));
	scanf("%d%s",&n,word+1);
	if(n%2==0) {
		for(int i=n+1; i>n/2+1; --i) word[i]=word[i-1];
		++n;
	}
	word[n/2+1]='#';
	p[1]=0;
	int k=0;
	for(int i=2; i<=n; ++i) {
		while(k && word[i]!=word[k+1]) {
			k=p[k];
		}
		if(word[i]==word[k+1]) ++k;
		p[i]=k;
	}
	for(int i=1; i<=n; ++i) hash[i]=hash[i-1]*X+word[i]-'a'+1;
	pw[0]=1;
	for(int i=1; i<=n; ++i) pw[i]=pw[i-1]*X;
	int m=n/2+1;
	s[m]=0;
	k=0;
	for(int b=m-1; b>=1; --b) {
		k+=2;
		while(b+k-1>=m) --k;
		while(k && !equal(b,b+k-1,2*m-(b+k-1),2*m-b)) --k;
		s[b]=k;
	}
	int res=0;
	k=p[n];
	while(k) {
		int cur=k+s[k+1];
		assert(cur <= n/2);
		if(cur>res) res=cur;
		k=p[k];
	}
	printf("%d\n",res);
	return 0;
}
