/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Gra w dzielniki                                *
 *   Plik:                gra.cpp                                        *
 *   Autor:               Marcin Stefaniak                               *
 *************************************************************************/

#include <vector>

#include "maja.h"

using namespace std;

const int MAX_N = 1000000;

vector<bool> prime(MAX_N);

void sito_eratostenesa(int n) {
	for(int i=1; i<=n; i++) prime[i]=true;
	prime[1]=false;
	for(int i=2; i*i <= n; i++) {
		if (prime[i]) 
			for(int j=i+i; j <= n; j+=i) 
				prime[j]=false;
	}
}

int main(void) {
	int n;
	while ((n=gramy_dalej())) {
		sito_eratostenesa(n);
		int k=1;
		for (int p=1;p<=n;p++) if (prime[p]) { 
			int q=p;
			while (p<=n && czy_podzielna_przez(q)) { q*=p; n/=p; k*=p; }
		}
		zgaduj(k);
	}
	return 0;
}
