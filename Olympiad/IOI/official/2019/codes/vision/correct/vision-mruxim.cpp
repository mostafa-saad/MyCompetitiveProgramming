// ... ... .. ....!
// ... ....... .... ...!

#include<bits/stdc++.h>
#include "vision.h"
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

const int maxn = 1000 + 10;

vector<int> row[maxn], column[maxn];
vector<int> diag1[2*maxn], diag2[2*maxn];
int row_or[maxn], column_or[maxn];
int diag1_or[2*maxn], diag2_or[2*maxn];
vector<int> diag_pair;
vector<int> rowcol_pair;

void construct_network(int n, int m, int k) {
	assert(1 <= k && k <= n+m-2);

	rep(i, n) rep(j, m) {
		int id = i * m + j;
		row[i].pb(id);
		column[j].pb(id);
		diag1[i+j].pb(id);
		diag2[i+(m-1-j)].pb(id);
	}

	rep(i, n) row_or[i] = (m > 1) ? add_or(row[i]) : row[i][0];
	rep(i, m) column_or[i] = (n > 1) ? add_or(column[i]) : column[i][0];
	rep(i, n+m-1)
		diag1_or[i] = (sz(diag1[i]) == 1) ? diag1[i][0] : add_or(diag1[i]),
		diag2_or[i] = (sz(diag2[i]) == 1) ? diag2[i][0] : add_or(diag2[i]);

	rep(i, n+m-1-k)
		diag_pair.pb(add_and({diag1_or[i], diag1_or[i+k]})),
		diag_pair.pb(add_and({diag2_or[i], diag2_or[i+k]}));

	int diag_pairs_or = (sz(diag_pair) == 1) ? diag_pair[0] : add_or(diag_pair);

	int rows_prefix_or, columns_prefix_or;

	rep(i, n-k-1) {
		rows_prefix_or = (i == 0) ? row_or[0] : add_or({rows_prefix_or, row_or[i]});
		rowcol_pair.pb(add_and({rows_prefix_or, row_or[i+k+1]}));
	}

	rep(i, m-k-1) {
		columns_prefix_or = (i == 0) ? column_or[0] : add_or({columns_prefix_or, column_or[i]});
		rowcol_pair.pb(add_and({columns_prefix_or, column_or[i+k+1]}));
	}

	if(sz(rowcol_pair) == 0)
		return;

	int rowcol_pairs_or = (sz(rowcol_pair) > 1) ? add_or(rowcol_pair) : rowcol_pair[0];

	int not_rowcol_pairs = add_not(rowcol_pairs_or);

	add_and({diag_pairs_or, not_rowcol_pairs});
}

