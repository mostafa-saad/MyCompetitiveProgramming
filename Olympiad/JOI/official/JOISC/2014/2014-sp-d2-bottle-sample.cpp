#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXH = 2010;
const int MAXW = 2010;
const int MAXP = 200010;
const int HEIGHT = 20;
const int INF = 1000000000;

int H, W, P, Q;
int field[MAXH][MAXW];
char in[MAXW + 10];

int ax[] = {-1, 0, 0, 1}, ay[] = {0, -1, 1, 0};
pair<int, int> reg[MAXH][MAXW];

int uf[MAXP];
vector<int> tree[MAXP], dist[MAXP];
int depth[MAXP], up[MAXP][HEIGHT], upd[MAXP][HEIGHT];

int root(int p)
{
	return uf[p] < 0 ? p : (uf[p] = root(uf[p]));
}

bool join(int p, int q)
{
	p = root(p); q = root(q);
	if(p == q) return false;

	uf[p] += uf[q];
	uf[q] = p;

	return true;
}

void bfs()
{
	queue<pair<int, int> > qu;

	for(int i=0;i<H;i++) for(int j=0;j<W;j++){
		if(field[i][j] < 0) reg[i][j] = make_pair(-1, -1);
		else{
			reg[i][j] = make_pair(0, field[i][j]);
			qu.push(make_pair(i, j));
		}
	}

	while(!qu.empty()){
		pair<int, int> tmp = qu.front(); qu.pop();
		int y = tmp.first, x = tmp.second;

		for(int i=0;i<4;i++){
			int y2 = y + ay[i], x2 = x + ax[i];
			if(y2 < 0 || x2 < 0 || y2 >= H || x2 >= W) continue;
			if(reg[y2][x2].first != -1 || field[y2][x2] == -2) continue;

			reg[y2][x2] = make_pair(reg[y][x].first + 1, reg[y][x].second);
			qu.push(make_pair(y2, x2));
		}
	}
}

void add_edge(int x, int y, int d)
{
	tree[x].push_back(y);
	tree[y].push_back(x);
	dist[x].push_back(d);
	dist[y].push_back(d);
}

void visit(int p, int r, int d)
{
	if(r == -1){
		for(int i=0;i<HEIGHT;i++){
			up[p][i] = -1;
		}
		depth[p] = 0;
	}else{
		up[p][0] = r; upd[p][0] = d;
		depth[p] = depth[r] + 1;
		for(int i=1;i<HEIGHT;i++){
			if(up[p][i-1] == -1) up[p][i] = -1;
			else{
				up[p][i] = up[up[p][i-1]][i-1];
				upd[p][i] = max(upd[p][i-1], upd[up[p][i-1]][i-1]);
			}
		}
	}

	for(int i=0;i<tree[p].size();i++) if(tree[p][i] != r) visit(tree[p][i], p, dist[p][i]);
}

void make_MST()
{
	vector<pair<int, pair<int, int> > > cand;
	for(int i=0;i<H;i++){
		for(int j=0;j<W;j++){
			if(field[i][j] == -2) continue;

			if(i < H-1 && field[i+1][j] != -2 && reg[i][j].second != reg[i+1][j].second)
				cand.push_back(make_pair(reg[i][j].first + reg[i+1][j].first, make_pair(reg[i][j].second, reg[i+1][j].second)));

			if(j < W-1 && field[i][j+1] != -2 && reg[i][j].second != reg[i][j+1].second)
				cand.push_back(make_pair(reg[i][j].first + reg[i][j+1].first, make_pair(reg[i][j].second, reg[i][j+1].second)));
		}
	}

	sort(cand.begin(), cand.end());

	for(int i=0;i<P;i++) uf[i] = -1;

	for(int i=0;i<cand.size();i++){
		int x=cand[i].second.first, y=cand[i].second.second, d=cand[i].first;

		if(join(x, y)){
			add_edge(x, y, d);
		}
	}

	for(int i=1;i<P;i++){
		if(join(i-1, i)) add_edge(i-1, i, INF);
	}

	visit(0, -1, 0);
}

int solve(int p, int q)
{
	if(depth[p] > depth[q]) swap(p, q);

	int ret = 0;
	for(int i=HEIGHT-1;i>=0;i--) if(depth[q] - (1<<i) >= depth[p]){
		ret = max(ret, upd[q][i]);
		q = up[q][i];
	}

	if(p == q) return ret;

	for(int i=HEIGHT-1;i>=0;i--){
		if(up[p][i] != up[q][i]){
			ret = max(ret, max(upd[p][i], upd[q][i]));
			p = up[p][i];
			q = up[q][i];
		}
	}

	ret = max(ret, max(upd[p][0], upd[q][0]));
	return ret;
}

int main()
{
	scanf("%d%d%d%d", &H, &W, &P, &Q);
	for(int i=0;i<H;i++){
		scanf("%s", in);
		for(int j=0;j<W;j++){
			if(in[j] == '.') field[i][j] = -1;
			else field[i][j] = -2;
		}
	}

	for(int i=0;i<P;i++){
		int a, b;
		scanf("%d%d", &a, &b);
		--a; --b;

		field[a][b] = i;
	}

	bfs();
	make_MST();

	for(int i=0;i<Q;i++){
		int s, t;
		scanf("%d%d", &s, &t);
		--s; --t;

		int ret = solve(s, t);
		if(ret == INF) ret = -1;
		printf("%d\n", ret);
	}

	return 0;
}
