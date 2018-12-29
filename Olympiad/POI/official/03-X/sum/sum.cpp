/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Sumy                                           *
 *   Plik:                sum.cpp                                        *
 *   Autor:               Marcin Stefaniak                               *
 *************************************************************************/
#include <iostream>
#include <algorithm>

#define REP(i,n) for(int i=0,_LL=(n);i<_LL;++i)
#define FOR(i,a,b) for(int i=(a),_LL=(b);i<=_LL;++i)

using namespace std;

const int MAXN = 100000; 
const int MAXA = 100000;
const int MAXK = 10000;
const int MAXB = 1000000000;

const int INFTY = 2000000000; // musi byæ du¿e, wiêksze od MAXB

int n, a[MAXN];
int k, b[MAXK];

int a0, edges[MAXA], noOfEdges;
int d[MAXA];

bool ustalony[MAXA];

int kopiec[MAXA+1], nKopiec; // w kopcu sa wstawiane wierzcholki w porzadku d[]
int k_ptr[MAXA]; // gdzie w kopcu znajduja sie odpowiednie wierzcholki

void w_dol_kopca(int i) {
	int v=kopiec[i], j;
	while((j=i<<1) <= nKopiec) {
		if (j < nKopiec && d[kopiec[j+1]] < d[kopiec[j]]) j++;
		if (d[v] <= kopiec[j]) break;
		k_ptr[ (kopiec[i] = kopiec[j]) ] = i;
		i=j;
	}
	 k_ptr[ (kopiec[i] = v) ] = i;
}

void zrob_kopiec(int ile) {
	nKopiec=ile;
	for(int i=nKopiec;i>=1;i--) w_dol_kopca(i);
}


void w_gore_kopca(int i) {
	int v=kopiec[i];
	while(i>1) {
		int j=i>>1; 
		if (d[kopiec[j]] < d[v]) break;
		k_ptr[ (kopiec[i] = kopiec[j]) ] = i; 
		i=j;
	}
	k_ptr[ (kopiec[i] = v) ] = i;
}

int dajMin() {
	if (nKopiec < 1) { cerr << "Blad: extractMin(): pusty kopiec\n"; exit(1); }
	int min_v = kopiec[1]; k_ptr[min_v] = 0;
	k_ptr[ (kopiec[1] = kopiec[nKopiec--]) ] = 1;
	w_dol_kopca(1);
	return min_v;
}

void zmniejszono_klucz(int v) {
	// trzeba wiedziec gdzie w kopcu jest v;
	if (k_ptr[v] < 1) { cerr << "Blad: zmniejszono_klucz(): nie znaleziono\n"; exit(1); }
	w_gore_kopca(k_ptr[v]);
}


void sprawdz_ptr() {
	bool ok = true;
	FOR(i,1,nKopiec) if (k_ptr[kopiec[i]] != i) {
		cerr << "zle "<<i<<endl;
		ok=false;
	}
	if (!ok) exit(1);
}


void dijkstra() {
	REP(i, a0) { d[i] = INFTY; ustalony[i] = false; }
	d[0] = 0;
	
	REP(i, a0) { kopiec[i+1] = i; k_ptr[i] = i+1; }
	zrob_kopiec(a0);
	
	REP(ile_razy, a0) {
		// wybieramy najmniejszy z nieustalonych, bez kopca
		int v = dajMin(); 
		
		// ten wierzcholek ustalamy i zmniejszamy odleglosci wzdluz krawedzi
		ustalony[v] = true; 
	
		REP(i, noOfEdges) {
			int w = (v + edges[i]) % a0; // tam dojdziemy
			int new_d = d[v] + edges[i]; // z taka dlugoscia
			if (new_d < d[w]) { 
				d[w] = new_d;	
				zmniejszono_klucz(w);
			}
		}	
	}
}

int main(void) {
	
	cin >> n;
	if (n<1 || n>MAXN) cerr << "UWAGA: n="<<n<<" poza zakresem\n";
	REP(i, n) {
		cin >> a[i];
		if (a[i]<1 || a[i]>MAXA) cerr << "UWAGA: a["<<i<<"]="<<a[i]<<" poza zakresem\n";
		if (i>0 && !(a[i]>a[i-1])) cerr << "UWAGA: a["<<i<<"]="<<a[i]<<" <= "<<a[i-1]<<"=a["<<i-1<<"]\n";
	}	
	
	cin >> k;	
	if (k<1 || k>MAXK) cerr << "UWAGA: k="<<k<<" poza zakresem\n";
	REP(i, k) {
		cin >> b[i];
		if (b[i]<0 || b[i]>MAXB) cerr << "UWAGA: b["<<i<<"]="<<b[i]<<" poza zakresem\n";
	} 

	a0 = a[0]; // najmniejsze a_i
	REP(i, a0) edges[i] = INFTY;

	// sortujemy po resztach modulo a0 i wybieramy najmniejsze
	FOR(i, 1, n-1) edges[a[i] % a0] = min(edges[a[i] % a0], a[i]); 

	// usuwamy puste wpisy
	noOfEdges=0; REP(i,a0) if (edges[i] < INFTY) swap(edges[i], edges[noOfEdges++]);
	
	// znajdujemy algorytmem Dijkstry najmniejsze sumy o danych resztach
	dijkstra();

	// wypisujemy wynik
	REP(i, k) cout << ((b[i] >= d[ b[i] % a0 ]) ? "TAK" : "NIE") << endl;

	return 0;
}

