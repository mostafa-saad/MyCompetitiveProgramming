/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wycieczki                                          *
 *   Zlozonosc czasowa:    O(n^3 * log^2 k)                                   *
 *   Autor programu:       Marcin Andrychowicz                                *
 *   Opis:                 Rozwiazanie dla wag jednostkowych                  *
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
const LL INF = (LL)1E18+1000000;

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
		res.t[i][k] = min(INF, res.t[i][k]);
	}
  return res;
}

Matrix power(Matrix A, LL n){
	Matrix res;
	REP(i,SIZE) res.t[i][i] = 1;
	while(n) {
		if(n%2)
			res = res * A;
		A = A * A;
		n /= 2;
	}
	return res;
}
/********************** reszta rozwiazania ***************************/

int N, M;
LL K;

LL count_paths(Matrix m) {
	LL res = 0;
	REP(i,N) {
		res += m.t[N][i];
		res = min(res, INF);
	}
	return res;
}

int main(){
	//przygotowanie macierzy sasiedztwa
	cin >> N >> M >> K;
	SIZE = N+1;
	Matrix nei; // macierz sasiedztwa
	nei.t[N][N] = 1;
	REP(i,N)
		nei.t[N][i] = 1;
	REP(i,M) {
		int u, v, c;
		cin >> u >> v >> c;
		u--; v--;
		nei.t[u][v]++;
	}
	//wyszukiwanie binarne
	K += N;
	LL low = 1, high = INF;
	while(high > low) {
		LL mid = (low + high) / 2;
		Matrix pow = power(nei, mid + 1);
		if(count_paths(pow) >= K)
			high = mid;
		else
			low = mid + 1;
	}
	//wypisanie wyniku
	if(low == INF)
		low = -1;
	cout << low << endl;
	return 0;
}
