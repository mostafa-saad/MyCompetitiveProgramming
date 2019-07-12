#include <cstdio>
#include <algorithm>
using namespace std;

int H, W, A[2020][2020];
int gmin, gmax;

bool check(int th)
{
	int sep = 0;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if (A[i][j] < gmax - th) {
				sep = max(sep, j + 1);
			}
		}
		for (int j = 0; j < W; ++j) {
			if (gmin + th < A[i][j]) {
				if (j < sep) return false;
			}
		}
	}
	return true;
}
void flip_row()
{
	for (int i = 0; i < H / 2; ++i) {
		for (int j = 0; j < W; ++j) {
			swap(A[i][j], A[H - 1 - i][j]);
		}
	}
}
void flip_col()
{
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W / 2; ++j) {
			swap(A[i][j], A[i][W - 1 - j]);
		}
	}
}
int solve()
{
	int lo = 0, hi = gmax - gmin;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (check(mid)) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}
	return lo;
}
int main()
{
	scanf("%d%d", &H, &W);
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			scanf("%d", &(A[i][j]));
		}
	}

	gmin = gmax = A[0][0];
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			gmin = min(gmin, A[i][j]);
			gmax = max(gmax, A[i][j]);
		}
	}

	int ret = solve();
	flip_row();
	ret = min(ret, solve());
	flip_col();
	ret = min(ret, solve());
	flip_row();
	ret = min(ret, solve());
	printf("%d\n", ret);
	return 0;
}
