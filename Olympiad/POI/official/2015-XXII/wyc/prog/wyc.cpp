/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wycieczki                                          *
 *   Zlozonosc czasowa:    O(n^3 * log k)                                     *
 *   Autor programu:       Marcin Andrychowicz                                *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
typedef long long LL;
#define REP(i,n) for(int i=0; i<(n); i++)

/*********************** operacje na macierzach ***********************/

int SIZE;
const LL INF = (LL)(1E18 * 1.5) +1000000;

struct Matrix {
	vector<vector<LL> > t;

  Matrix(){
		t.resize(SIZE, vector<LL>(SIZE, 0));
	}
};

inline LL mnoz(LL a, LL b) {
	if(a == 0)
		return 0;
	if(b > INF/a)
		return INF;
	return a*b;
}

Matrix operator*(Matrix A, Matrix B){
  Matrix res;
  REP(j,SIZE) REP(i,SIZE) REP(k,SIZE) {
    res.t[i][k] += mnoz(A.t[i][j], B.t[j][k]);
		res.t[i][k] = min(res.t[i][k], INF);
	}
  return res;
}
/********************** reszta rozwiazania ***************************/

int N, M;
LL K;
Matrix pow[69];

LL count_paths(Matrix m) {
	LL res = 0;
	REP(i,N) {
		res += m.t[3*N][3*i];
		res = min(res, INF);
	}
	return res;
}

int main(){
	// przygotowanie macierzy sasiedztwa
	cin >> N >> M >> K;
	SIZE = 3*N+1;
	Matrix nei; // macierz sasiedztwa
	nei.t[3*N][3*N] = 1;
	REP(i,N) {
			nei.t[3*N][3*i] = 1;
			nei.t[3*i][3*i+1] = 1;
			nei.t[3*i+1][3*i+2] = 1;
	}
	REP(i,M) {
		int u, v, c;
		cin >> u >> v >> c;
		u--; v--;
		nei.t[3*u+c-1][3*v]++;
	}
	// rozwiazanie
	K += N; // uwzgledniamy sciezki dlugosci 0
	pow[0] = nei;
	int ind = 0;
	while((1LL << ind) <= (long long) (1.5L * K+7) && count_paths(pow[ind]) < K) {
		pow[ind + 1] = pow[ind] * pow[ind];
		ind++;
	}
	LL res = 0; // wynik
	if(count_paths(pow[ind]) >= K) {
		Matrix m = nei;
		for(int i = ind; i >= 0; i--) {
			if(count_paths(m * pow[i]) < K) {
				 m = m * pow[i];
				 res |= (1LL << i);
			}
		}
		res++;
	} else { // brak tylu sciezek
		res = -1;
	}
	// wypisanie wyniku
	cout << res << endl;
	return 0;
}
