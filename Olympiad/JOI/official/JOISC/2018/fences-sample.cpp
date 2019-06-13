#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long i64;
typedef double Double;

typedef pair<Double, Double> Pt;

const int MAXN = 200;
const int INFT = 1001001001;
const Double EPS = 1e-9;

int N, C;
int Ax[MAXN], Ay[MAXN], Bx[MAXN], By[MAXN];
Pt A[MAXN], B[MAXN];
Double cost[MAXN * 2][MAXN * 2];

bool isok(Double xa, Double ya, Double xb, Double yb, Double x, Double ylo, Double yhi)
{
	if (xb < xa) {
		swap(xa, xb);
		swap(ya, yb);
	}
	if (!(EPS < x - xa && EPS < xb - x)) return true;
	Double y = (x - xa) / (xb - xa) * (yb - ya) + ya;
	return !(EPS < y - ylo && EPS < yhi - y);
}

double triangle(Double xa, Double ya, Double xb, Double yb, Double xc, Double yc)
{
	xb -= xa; yb -= ya;
	xc -= xa; yc -= ya;
	return xb * yc - yb * xc;
}

bool cross(Pt a, Pt b, Pt c, Pt d)
{
	return
		triangle(a.first, a.second, b.first, b.second, c.first, c.second) * triangle(a.first, a.second, b.first, b.second, d.first, d.second) < 0
		&& triangle(c.first, c.second, d.first, d.second, a.first, a.second) * triangle(c.first, c.second, d.first, d.second, b.first, b.second) < 0;
}

bool isok(Pt a, Pt b)
{
	Double Cc = C;
	if (cross(a, b, { -Cc, -Cc }, { -Cc, Cc })) return false;
	if (cross(a, b, { -Cc, -Cc }, { Cc, -Cc })) return false;
	if (cross(a, b, { Cc, Cc }, { -Cc, Cc })) return false;
	if (cross(a, b, { Cc, Cc }, { Cc, -Cc })) return false;
	if (cross(a, b, { -Cc, -Cc }, { 0, Cc })) return false;
	if (cross(a, b, { Cc, -Cc }, { 0, Cc })) return false;

	if (-Cc + EPS < a.first && a.first < Cc - EPS && -Cc + EPS < a.second && a.second < Cc - EPS) return false;
	if (-Cc + EPS < b.first && b.first < Cc - EPS && -Cc + EPS < b.second && b.second < Cc - EPS) return false;

	return true;
}
bool cross(Pt a, Pt b)
{
	if (b.first < a.first) swap(a, b);
	if (!(!(EPS < a.first) && EPS < b.first)) return false;
	
	Double y = (0 - a.first) / (b.first - a.first) * (b.second - a.second) + a.second;
	return 0 < y;
}
Double check(Pt a, Pt b)
{
	if (!isok(a, b)) return INFT;

	Double dd = (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);
	return sqrt(dd);
}
Pt sd(Pt a, Pt b, Pt x)
{
	Pt aa(b.first - a.first, b.second - a.second);
	if (fabs(aa.first) < EPS && fabs(aa.second) < EPS) return a;

	Pt xa(x.first - a.first, x.second - a.second);
	Double t = (aa.first * xa.first + aa.second * xa.second) / (aa.first * aa.first + aa.second * aa.second);
	if (t < -EPS || 1 + EPS < t) return a;
	return{ a.first + aa.first * t, a.second + aa.second * t };
}

Double dd[12][12];

void apply(int s, int t, Pt a, Pt b, Pt abase, Pt bbase)
{
	Double dist = check(a, b);
	bool sgn = cross(abase, a) ^ cross(a, b) ^ cross(b, bbase);
	if (sgn) {
		dd[s * 2][t * 2 + 1] = min(dd[s * 2][t * 2 + 1], dist);
		dd[s * 2 + 1][t * 2] = dd[t * 2][s * 2 + 1] = dd[t * 2 + 1][s * 2] = dd[s * 2][t * 2 + 1];
	} else {
		dd[s * 2][t * 2] = min(dd[s * 2][t * 2], dist);
		dd[s * 2 + 1][t * 2 + 1] = dd[t * 2][s * 2] = dd[t * 2 + 1][s * 2 + 1] = dd[s * 2][t * 2];
	}
}
pair<Double, Double> compute(int u, int v)
{
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			dd[i][j] = (i == j ? 0.0 : INFT);
		}
	}
	Pt corner[4] = {
		{-C, -C},
		{-C, C},
		{C, -C},
		{C, C}
	};
	apply(0, 1, A[u], A[v], A[u], A[v]);
	apply(0, 1, A[u], B[v], A[u], A[v]);
	apply(0, 1, B[u], A[v], A[u], A[v]);
	apply(0, 1, B[u], B[v], A[u], A[v]);
	apply(0, 1, A[u], sd(A[v], B[v], A[u]), A[u], A[v]);
	apply(0, 1, B[u], sd(A[v], B[v], B[u]), A[u], A[v]);
	apply(0, 1, A[v], sd(A[u], B[u], A[v]), A[v], A[u]);
	apply(0, 1, B[v], sd(A[u], B[u], B[v]), A[v], A[u]);

	for (int i = 0; i < 6; ++i) {
		for (int j = i + 1; j < 6; ++j) {
			if (i == 0 && j == 1) continue;

			if (i < 2) {
				int n = (i == 0 ? u : v);
				apply(i, j, A[n], corner[j - 2], A[n], corner[j - 2]);
				apply(i, j, B[n], corner[j - 2], A[n], corner[j - 2]);
				apply(i, j, sd(A[n], B[n], corner[j - 2]), corner[j - 2], A[n], corner[j - 2]);
			} else {
				apply(i, j, corner[i - 2], corner[j - 2], corner[i - 2], corner[j - 2]);
			}
		}
	}
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			for (int k = 0; k < 12; ++k) {
				dd[j][k] = min(dd[j][k], dd[j][i] + dd[i][k]);
			}
		}
	}
	return{ dd[0][2], dd[0][3] };
}

int main()
{
	scanf("%d%d", &N, &C);
	for (int i = 0; i < N; ++i) {
		scanf("%d%d%d%d", Ax + i, Ay + i, Bx + i, By + i);
		A[i] = make_pair(Double(Ax[i]), Double(Ay[i]));
		B[i] = make_pair(Double(Bx[i]), Double(By[i]));
	}
	for (int i = 0; i < 2 * N; ++i) {
		for (int j = 0; j < 2 * N; ++j) {
			cost[i][j] = (i == j ? 0 : INFT);
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			auto dist = compute(i, j);
			cost[i * 2][j * 2] = cost[i * 2 + 1][j * 2 + 1] = dist.first;
			cost[i * 2 + 1][j * 2] = cost[i * 2][j * 2 + 1] = dist.second;
		}
	}
	for (int i = 0; i < 2 * N; ++i) {
		for (int j = 0; j < 2 * N; ++j) {
			for (int k = 0; k < 2 * N; ++k) {
				cost[j][k] = min(cost[j][k], cost[j][i] + cost[i][k]);
			}
		}
	}
	Double ret = 8 * C;
	for (int i = 0; i < N; ++i) {
		ret = min(ret, cost[i * 2][i * 2 + 1]);
	}
	printf("%.10f\n", (double)ret);

	return 0;
}
