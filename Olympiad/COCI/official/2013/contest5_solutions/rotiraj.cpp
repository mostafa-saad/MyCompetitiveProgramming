#include <cstdio>
using namespace std;

typedef long long llint;

const int MAXN = 200000;

int N, K, Q;
int br, uk, id;
int c, w;
int Q1[MAXN], Q2[MAXN];
int A[MAXN]; //niz nakon svih operacija - konacni niz
int how[MAXN]; //za izracunavanje u kojem se pretincu brojevi iz intervala [0,K-1] nalaze
int sol[MAXN]; //trazeni pocetni niz

void dodaj_interval(int poc, int kra) {	
	++how[poc];
	--how[kra];
	if(poc > kra) ++how[0];
	
	return;
}

int main(void) {
	scanf("%d%d%d", &N, &K, &Q);
	br = N/K; //broj pretinaca
	
	for(int i = 0; i < Q; ++i) scanf("%d%d", &Q1[Q-i-1], &Q2[Q-i-1]); //obrnuti ucitane operacije
	for(int i = 0; i < N; ++i) scanf("%d", &A[i]);
	
	for(int i = 0; i < Q; ++i) {
		if(Q1[i] == 1) { //rotacija unutar pretinca
			Q2[i] = ((-Q2[i])%K+K)%K; //pretvaranje u rotaciju udesno
		}
		if(Q1[i] == 2) { //rotacija cijelog niza
			Q2[i] = ((-Q2[i])%N+N)%N; //pretvaranje u rotaciju udesno
			
			w = (w+Q2[i]/K)%br; //prelasci u naredne pretince koji se odnose na svih prvih K brojeva
			Q2[i] %= K; 
			
			dodaj_interval((2*K-c-Q2[i])%K, (2*K-c)%K); //pocetak i kraj intervala koji prelazi u sljedeci pretinac
		}
		
		c = (c+Q2[i])%K; //ukupna opcenita rotacija prvih K brojeva
	}
	
	uk = w;
	for(int i = 0; i < K; ++i) {
		uk = (uk+how[i])%br; //u kojem se pretincu nalazi broj i
		if(uk < 0) uk += br;
		
		id = uk*K+(i+c)%K; //na kojoj se poziciji u nizu nalazi broj i
		
		for(int j = 0; j < br; ++j) { //izracun pozicija za brojeve i+K, i+2*K, ...
			sol[id] = A[i+j*K];
			id = (id+K)%N;
		}
	}
	
	for(int i = 0; i < N; ++i) printf("%d ", sol[i]);
	printf("\n");
	
	return 0;
}
