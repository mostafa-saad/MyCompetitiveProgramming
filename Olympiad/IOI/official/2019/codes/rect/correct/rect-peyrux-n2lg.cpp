//In the name of God
//Peyman Jabbarzade Ganje
//Border shouldn't be equal with inside

#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> pii;

const int maxn = 3000 + 10, maxx=1e7;
int n,m, fen_t[maxx];
long long ans;
int v[maxn], vlen;
vector<int> will_remove;
short gl[maxn][maxn], gr[maxn][maxn];
short fl[maxn][maxn], fr[maxn][maxn];
vector<pii> sp[2][maxn][maxn];

void fen_add(int x,int val) { for(x++; x > 0; x -= x&-x) fen_t[x]+=val; }
int fen_f(int x) { int ret = 0; for(x++; x < maxx; x += x&-x) ret += fen_t[x]; return ret; }

void add_pair(int type, int lvl, int x, int y) {
	if(abs(x - y) <= 1) return;

	int l = min(x, y), r = max(x, y);

	int tmp = 1;
	if(gr[lvl][l] == r) tmp += fr[lvl][l];
	else if(gl[lvl][r] == l) tmp += fl[lvl][r];


	if(type == 0) sp[type][lvl+1][r].push_back(pii(r-l-1, tmp));
	else sp[type][r][lvl+1].push_back(pii(tmp, r-l-1));

	if(x < y) gr[lvl+1][x] = y, fr[lvl+1][x] = tmp;
	else gl[lvl+1][x] = y, fl[lvl+1][x] = tmp;
}

void extract_pairs(int type, int lvl) {
	int nz[maxn], len = 0;
	for(int i=0;i<vlen;i++) {
		int last=-1;
		while(len > 0 && v[nz[len-1]] < v[i]) {
			if(v[nz[len-1]] > last)
				add_pair(type, lvl, nz[len-1], i);
			last = v[nz[len-1]];
			len--;
		}
		if(len) add_pair(type, lvl, i, nz[len-1]);
		nz[len++] = i;
	}
}

long long count_rectangles(vector<vector<int>> a) {
	n = a.size();
	m = a[0].size();

	memset(gl, -1, sizeof gl);
	memset(gr, -1, sizeof gr);

	vlen = m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) v[j] = a[i][j];
		extract_pairs(0,i);
	}

	memset(gl, -1, sizeof gl);
	memset(gr, -1, sizeof gr);

	vlen = n;
	for(int j=0;j<m;j++) {
		for(int i=0;i<n;i++) v[i] = a[i][j];
		extract_pairs(1,j);
	}

	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			if(sp[0][i][j].size() && sp[1][i][j].size()) {
				sort(sp[0][i][j].begin(), sp[0][i][j].end());
				sort(sp[1][i][j].begin(), sp[1][i][j].end());
				// sp[0].X fix sp[1].X moteghaier
				int p = 0;
				will_remove.clear();
				for(int k=0;k<(int)sp[1][i][j].size();k++)
				{
					while(p<sp[0][i][j].size() && sp[0][i][j][p].X <= sp[1][i][j][k].X)
					{
						fen_add(sp[0][i][j][p].Y, 1);
						will_remove.push_back(sp[0][i][j][p].Y);
						p++;
					}
					ans += fen_f(sp[1][i][j][k].Y);
				}
				for(int k=0;k<(int)will_remove.size();k++)
					fen_add(will_remove[k], -1);
			}
	return ans;
}
