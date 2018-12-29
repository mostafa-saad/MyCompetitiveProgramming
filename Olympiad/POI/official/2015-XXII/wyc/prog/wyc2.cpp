/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wycieczki                                          *
 *   Zlozonosc czasowa:    O(n^3 * log k)                                     *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include<cstdio>
#include<assert.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int nax = 125;
ll INF = 2E18;
#define REP(i, n) for(int i = 0; i < n; ++i)

ll mnoz(ll a, ll b) {
	if(b == 0) return 0;
	if(a > INF / b) return INF;
	return a * b;
}

struct Mat {
	ll t[nax][nax];
	int n;
	Mat() {}
	Mat(int _size) {
		n = _size;
		assert(n < nax);
		REP(i, n) REP(j, n) t[i][j] = 0;
	}
	Mat operator * (Mat & b) const {
		Mat c(n);
		REP(i, n) REP(j, n) REP(k, n)
			c.t[i][k] = min(c.t[i][k] + mnoz(t[i][j], b.t[j][k]), INF);
		return c;
	}
	ll liczbaSciezek() {
		ll a = -(n/3);
		REP(i, n - 1) if(i % 3 == 0) a = min(a + t[n-1][i], INF);
		return a;
	}
	void wypisz() {
		REP(i, n) {
			REP(j, n) printf("%lld ", t[i][j]);
			puts("");
		}
	}
};

Mat M[80]; // 80 > log(1e18)

int main() {
	int N, m;
	ll K;
	scanf("%d%d%lld", &N, &m, &K);
	M[0] = Mat(3*N+1);
	REP(i, N) REP(j, 2) M[0].t[3*i+j][3*i+j+1]++;
	for(int i = 0; i < m; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		M[0].t[3*(a-1)+c-1][3*(b-1)]++;
	}
	REP(i, N) M[0].t[3*N][3*i] = 1;
	M[0].t[3*N][3*N] = 1;
	int i = 0;
	long long wyn = 0;
	while(true) {
		M[i+1] = M[i] * M[i];
		if(M[i+1].liczbaSciezek() >= K)
			break;
		if(i > 2 && M[i].liczbaSciezek() == M[i+1].liczbaSciezek()) {
			puts("-1");
			return 0;
		}
		wyn += (1LL << i);
		++i;
	}
	Mat ja = M[i];
	for(int j = i - 1; j >= 0; --j)
		if((ja * M[j]).liczbaSciezek() < K) {
			ja = ja * M[j];
			wyn += (1LL << j);
		}
	printf("%lld\n", wyn+1);
	
	
	return 0;
}
