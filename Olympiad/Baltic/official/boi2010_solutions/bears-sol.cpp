#include <cstdio>
#include <algorithm>

using namespace std;

#define MAXN 501

struct street {
	int x1, y1, x2, y2;
	int minx() { return min(x1, x2); }
	int maxx() { return max(x1, x2); }
	int miny() { return min(y1, y2); }
	int maxy() { return max(y1, y2); }
};

int a, b;
int n;
street mstreet[MAXN];

void input() {
	scanf("%d %d\n%d", &a, &b, &n);
	for (int i = 0; i < n; ++i)
		scanf("%d %d %d %d", &mstreet[i].x1, &mstreet[i].y1, &mstreet[i].x2, &mstreet[i].y2);
}

inline bool inRange(int left, int right, int x) { return left < x && x < right; }
inline bool inside(int left, int right, int bottom, int top, int x, int y) { return inRange(left, right, x) && inRange(bottom, top, y); }
inline bool inside(int left, int right, int bottom, int top) { return inside(left, right, bottom, top, a, b); }

bool canReach(int k) {
	int left = -k, right = k;
	int bottom = -k, top = k;
	bool any = true;
	while (any && !inside(left, right, bottom, top)) {
		any = false;
		for (int i = 0; i < n; ++i) {
			bool fullInside = inside(left, right, bottom, top, mstreet[i].x1, mstreet[i].y1) &&
				inside(left, right, bottom, top, mstreet[i].x2, mstreet[i].y2);
			if (fullInside)
				continue;
			bool outside = mstreet[i].maxx() <= left || mstreet[i].minx() >= right ||
				mstreet[i].maxy() <= bottom || mstreet[i].miny() >= top;
			if (outside)
				continue;
			left = min(left, mstreet[i].minx()-1);
			right = max(right, mstreet[i].maxx()+1);
			bottom = min(bottom, mstreet[i].miny()-1);
			top = max(top, mstreet[i].maxy()+1);
			any = true;
		}
	}
	return inside(left, right, bottom, top);
}

int main() {
	freopen("bears.in", "r", stdin);
	freopen("bears.out", "w", stdout);
	
	input();
	
	int low = 0, high = max(abs(a), abs(b))+1;
	while (high - low > 1) {
		int mid = (low + high) / 2;
		(canReach(mid) ? high : low) = mid;
	}
	
	printf("%d\n", low);
	
	return 0;
}
