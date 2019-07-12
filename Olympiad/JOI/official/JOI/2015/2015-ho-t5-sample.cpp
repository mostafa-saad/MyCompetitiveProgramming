#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int H, W, L;

char in[4010][4010];
int ul[4010][4010], dr[4010][4010];

struct BIT
{
	static const int N = 4010;
	int val[N];

	void Init() { for (int i = 0; i < N; ++i) val[i] = 0; }
	void Add(int i, int x) { ++i; while (i <= N) { val[i] += x; i += i & -i; } }
	int Sum(int i) { int s = 0; while (i > 0) { s += val[i]; i -= i & -i; } return s; }
	int Query(int L, int R) { return (R > L) ? (Sum(R) - Sum(L)) : 0; }
};

void Precalc()
{
	for (int i = 0; i < H; ++i) for (int j = 0; j < W; ++j) ul[i][j] = dr[i][j] = 10000;

	int c = 0;

	for (int i = 0; i < H; ++i) {
		c = 0;
		for (int j = 0; j < W; ++j) {
			dr[i][j] = min(dr[i][j], c = (in[i][j] == '.' ? (c + 1) : 0));
		}

		c = 0;
		for (int j = W - 1; j >= 0; --j) {
			ul[i][j] = min(ul[i][j], c = (in[i][j] == '.' ? (c + 1) : 0));
		}
	}

	for (int j = 0; j < W; ++j) {
		c = 0;
		for (int i = 0; i < H; ++i) {
			dr[i][j] = min(dr[i][j], c = (in[i][j] == '.' ? (c + 1) : 0));
		}

		c = 0;
		for (int i = H - 1; i >= 0; --i) {
			ul[i][j] = min(ul[i][j], c = (in[i][j] == '.' ? (c + 1) : 0));
		}
	}
}

vector<int> lef, rig;
vector<pair<int, int> > eve;

BIT sl, sr;

long long sol = 0;

void Solve(int tx, int ty)
{
	int id = 0;
	lef.clear(); rig.clear(); eve.clear();
	sl.Init(); sr.Init();

	while (tx < H && ty < W) {
		lef.push_back(ul[tx][ty]);
		rig.push_back(dr[tx][ty]);

		if (ul[tx][ty] > 0) eve.push_back(make_pair(ul[tx][ty], id * 2));
		if (dr[tx][ty] > 0) eve.push_back(make_pair(dr[tx][ty], id * 2 + 1));

		++tx; ++ty; ++id;
	}

	sort(eve.begin(), eve.end());

	for (int i = eve.size() - 1; i >= 0; --i) {
		int v = eve[i].second, w = eve[i].first;

		if (v % 2 == 0) {
			v /= 2;
			sol += sr.Query(v + L - 1, v + w);

			sl.Add(v, 1);
		} else {
			v /= 2;
			sol += sl.Query(v - w + 1, v - L + 2);

			sr.Add(v, 1);
		}
	}
}

int main()
{
	int P;
	scanf("%d%d%d%d", &H, &W, &L, &P);
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) in[i][j] = '.';
	}
	for (int i = 0; i < P; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		--x; --y;
		in[x][y] = '#';
	}

	Precalc();
	sol = 0;
	for (int i = 0; i < W; ++i) Solve(0, i);
	for (int i = 1; i < H; ++i) Solve(i, 0);

	printf("%lld\n", sol);
	return 0;
}
