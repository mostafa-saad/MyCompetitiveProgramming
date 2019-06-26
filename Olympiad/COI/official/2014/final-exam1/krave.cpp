#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 1e+9;

struct rect {
	int x1, y1, x2, y2;
	rect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0):
		x1(x1), y1(y1), x2(x2), y2(y2) {}
	long long area(void) {
		return (long long)(x2 - x1) * (y2 - y1);
	}
};

bool operator < (rect A, rect B) {
	return A.x1 != B.x1 ? A.x1 < B.x1 : A.y1 < B.y1;
}

struct tournament {
	int offset;
	int from, to, y;
	vector<set<int, greater<int>>> tree;

	tournament(int size) {
		for(offset = 1; offset <= size; offset *= 2);
		tree.resize(2 * offset);
	}
	
	void _add(int t, int lo, int hi) {
		if(lo >= to || hi <= from) return;
		if(lo >= from && hi <= to) {
			tree[t].insert(y);
			return;
		}
		int mid = (lo + hi) / 2;
		_add(2 * t, lo, mid);
		_add(2 * t + 1, mid, hi);
	}

	int query(int pos, int y) {
		int ret = -INF;
		for(pos += offset; pos > 0; pos /= 2) {
			auto it = tree[pos].lower_bound(y);
			if(it == tree[pos].end()) continue;
			ret = max(ret, *it);
		}
		return ret;
	}

	void add(int l, int r, int v) {
		from = l; to = r + 1; y = v;
		_add(1, 0, offset);
	}
};

int main(void) {

	int A, B, N;
	scanf("%d%d%d", &A, &B, &N);

	tournament down(A), left(B);
	down.add(0, A, 0);
	left.add(0, B, 0);

	set<rect> rectangles;
	rectangles.insert(rect(0, 0, A, B));

	for(int i = 0; i < N; ++i) {
		int nx, ny, d; scanf("%d%d%d", &nx, &ny, &d);
		int py = down.query(nx, ny);
		int px = left.query(ny, nx);
		
		auto it = rectangles.lower_bound(rect(px, py, -1, -1));
		int x1 = it -> x1, x2 = it -> x2, y1 = it -> y1, y2 = it -> y2;
		rectangles.erase(it);

		rect A, B;
		if(d == 1) {
			A = rect(x1, y1, x2, ny);
			B = rect(x1, ny, x2, y2);
			down.add(x1, x2, ny);
		} else {
			A = rect(x1, y1, nx, y2);
			B = rect(nx, y1, x2, y2);
			left.add(y1, y2, nx);
		}
		printf("%lld %lld\n", min(A.area(), B.area()), max(A.area(), B.area()));
		rectangles.insert(A);
		rectangles.insert(B);
	}

	return 0;

}
