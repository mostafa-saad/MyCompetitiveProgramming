// ... ... .. ....!
// ... ....... .... ...!

#include<bits/stdc++.h>
using namespace std;

#define rep(i, n) for(int i = 0, i##__n = (int)(n); i < i##__n; ++i)
#define fer(i, a, b) for(int i = (int)(a), i##__b = (int)(b); i < i##__b; ++i)
#define rof(i, b, a) for(int i = (int)(b), i##__a = (int)(a); i-- > i##__a; )
#define sz(x) (int((x).size()))
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define X first
#define Y second
//#define endl '\n'

template<class P, class Q> inline void smin(P &a, Q b) { if (b < a) a = b; }
template<class P, class Q> inline void smax(P &a, Q b) { if (a < b) a = b; }

typedef long long ll;
typedef pair<int, int> pii;

////////////////////////////////////////////////////////////////////////////////

const int maxn = 3000 + 10;


int n, m;
vector<vector<int>> H;

short L[maxn][maxn], R[maxn][maxn], U[maxn][maxn], D[maxn][maxn];
short UL[maxn][maxn], DL[maxn][maxn], LU[maxn][maxn], RU[maxn][maxn];

vector<ll> v;

void precalc() {
	short st[maxn];
	
	rep(i, n) {
		int t = 0;
		rep(j, m) {
			while(t && H[i][j] > H[i][st[t-1]]) t--;
			L[i][j] = (t ? st[t-1] : -1);
			st[t++] = j;
		}
	}
	rep(i, n) {
		int t = 0;
		rof(j, m, 0) {
			while(t && H[i][j] > H[i][st[t-1]]) t--;
			R[i][j] = (t ? st[t-1] : -1);
			st[t++] = j;
		}
	}
	rep(j, m) {
		int t = 0;
		rep(i, n) {
			while(t && H[i][j] > H[st[t-1]][j]) t--;
			U[i][j] = (t ? st[t-1] : -1);
			st[t++] = i;
		}
	}
	rep(j, m) {
		int t = 0;
		rof(i, n, 0) {
			while(t && H[i][j] > H[st[t-1]][j]) t--;
			D[i][j] = (t ? st[t-1] : -1);
			st[t++] = i;
		}
	}

	rep(j, m) rep(i, n) {
		if(U[i][j] != -1) {
			if(j > 0 && U[i][j] == U[i][j-1]) UL[i][j] = UL[i][j-1];
			else if(j > 0 && i == D[U[i][j]][j-1]) UL[i][j] = DL[U[i][j]][j-1];
			else UL[i][j] = j;
		}
		if(D[i][j] != -1) {
			if(j > 0 && D[i][j] == D[i][j-1]) DL[i][j] = DL[i][j-1];
			else if(j > 0 && i == U[D[i][j]][j-1]) DL[i][j] = UL[D[i][j]][j-1];
			else DL[i][j] = j;
		}
	}

	rep(i, n) rep(j, m) {
		if(L[i][j] != -1) {
			if(i > 0 && L[i][j] == L[i-1][j]) LU[i][j] = LU[i-1][j];
			else if(i > 0 && j == R[i-1][L[i][j]]) LU[i][j] = RU[i-1][L[i][j]];
			else LU[i][j] = i;
		}
		if(R[i][j] != -1) {
			if(i > 0 && R[i][j] == R[i-1][j]) RU[i][j] = RU[i-1][j];
			else if(i > 0 && j == L[i-1][R[i][j]]) RU[i][j] = LU[i-1][R[i][j]];
			else RU[i][j] = i;
		}
	}
}

void check(int i1, int i2, int j1, int j2) {
	if(i2 < i1 || j2 < j1) return;
	if(!((R[i2][j1-1]-1 == j2 && RU[i2][j1-1] <= i1) || (L[i2][j2+1]+1 == j1 && LU[i2][j2+1] <= i1))) return;
	if(!((D[i1-1][j2]-1 == i2 && DL[i1-1][j2] <= j1) || (U[i2+1][j2]+1 == i1 && UL[i2+1][j2] <= j1))) return;
	v.pb((((ll)i1 * maxn + i2) * maxn + j1) * maxn + j2);
}

int count_rectangles(vector<vector<int>> _H) {
	H = _H;
	n = sz(H);
	m = sz(H[0]);

	precalc();

	fer(i, 1, n-1) fer(j, 1, m-1) {
		if(U[i+1][j] != -1 && L[i][j+1] != -1) check(U[i+1][j]+1, i, L[i][j+1]+1, j);
		if(U[i+1][j] != -1 && R[i][j-1] != -1) check(U[i+1][j]+1, i, j, R[i][j-1]-1);
		if(D[i-1][j] != -1 && L[i][j+1] != -1) check(i, D[i-1][j]-1, L[i][j+1]+1, j);
		if(D[i-1][j] != -1 && R[i][j-1] != -1) check(i, D[i-1][j]-1, j, R[i][j-1]-1);
		if(D[i-1][j] != -1 && R[D[i-1][j]-1][j-1] != -1) check(i, D[i-1][j]-1, j, R[D[i-1][j]-1][j-1]-1);
		if(D[i-1][j] != -1 && L[D[i-1][j]-1][j+1] != -1) check(i, D[i-1][j]-1, L[D[i-1][j]-1][j+1]+1, j);
	}
	
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());

	return sz(v);
}
