#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

const int Inf = 2000000007;
const int Maxn = 100005;
const int Maxr = 4;

int n;
ii p[Maxn];
ii a[Maxn], b[Maxn];
int alen, blen;
int x, y1, y2;

void Rotate(ii p[], int len)
{
	for (int i = 0; i < len; i++)
		p[i] = ii(p[i].second, -p[i].first);
}

void Move(ii p[], int len, int &nil)
{
	nil = 0;
	for (int i = 1; i < len; i++)
		if (p[i] < p[nil]) nil = i;
	ii add = ii(-p[nil].first, -p[nil].second);
	for (int i = 0; i < len; i++)
		p[i] = ii(p[i].first + add.first, p[i].second + add.second);
}

void Reflect(ii p[], int len)
{
	for (int i = 0; i < len; i++)
		p[i].second = -p[i].second;
}

bool trivialCompare(ii a[], int alen, int anil, ii b[], int blen, int bnil)
{
	for (int i = 0; i < alen; i++)
		if (a[(anil + i) % alen] != b[(bnil + i) % blen])
			return false;
	return true;
}

bool spinAround(ii a[], int alen, int anil, ii b[], int blen)
{
	int bnil;
	for (int r = 0; r < Maxr; r++) {
		Rotate(b, blen);
		Move(b, blen, bnil);
		if (trivialCompare(a, alen, anil, b, blen, bnil))
			return true;
	}
	return false;
}

bool complexCompare(ii a[], int alen, ii b[], int blen)
{
	int anil; Move(a, alen, anil);
	if (spinAround(a, alen, anil, b, blen)) return true;
	Reflect(b, blen);
	reverse(b, b + blen);
	return spinAround(a, alen, anil, b, blen);
}

bool inLine(ii a[], int i, int j, int k)
{
	return a[i].first == a[j].first && a[j].first == a[k].first ||
		   a[i].second == a[j].second && a[j].second == a[k].second;
}

void addPoint(ii a[], int &alen, int x, int y)
{
	a[alen++] = ii(x, y);
	if (alen >= 2 && a[alen - 2] == a[alen - 1]) { alen--; return; }
	if (alen >= 3 && inLine(a, alen - 3, alen - 2, alen - 1)) alen--;
}

void Construct(ii p[], int len, int s1, int s2, int x, int y1, int y2, ii a[], int &alen)
{
	alen = 0;
	addPoint(a, alen, x, y1);
	do {
		s1 = (s1 + 1) % len;
		addPoint(a, alen, p[s1].first, p[s1].second);
	} while (s1 != s2);
	addPoint(a, alen, x, y2);
	if (alen >= 3 && inLine(a, alen - 2, alen - 1, 0)) alen--;
	if (alen >= 3 && inLine(a, alen - 1, 0, 1)) {
		alen--;
		for (int i = 0; i < alen; i++)
			a[i] = a[i + 1];
	}
	/*printf("Constructed\n");
	for (int i = 0; i < alen; i++)
		printf("a[%d] = (%d, %d)\n", i, a[i].first, a[i].second);
	printf("\n");*/
}

void Split(ii p[], int len, int x, int y1, int y2, ii a[], int &alen, ii b[], int &blen)
{
	int s1 = 0, s2 = 0;
	while (!(p[s1].second == y1 && p[(s1 + 1) % len].second == y1 && 
			p[(s1 + 1) % len].first <= x && x <= p[s1].first)) s1 = (s1 + 1) % len;
	while (!(p[s2].second == y2 && p[(s2 + 1) % len].second == y2 &&
		 	p[s2].first <= x && x <= p[(s2 + 1) % len].first)) s2 = (s2 + 1) % len;
	Construct(p, len, s1, s2, x, y1, y2, a, alen);
	Construct(p, len, s2, s1, x, y2, y1, b, blen);
}

ll getPerimeter(ii a[], int alen)
{
	ll res = 0;
	for (int i = 0; i < alen; i++)
		res += abs(a[i].first - a[(i + 1) % alen].first) + 
			   abs(a[i].second - a[(i + 1) % alen].second);
	return res;
}

int Status(ii p[], int len, int x, int &y1, int &y2)
{
	y1 = Inf, y2 = -Inf;
	for (int i = 0; i < len; i++)
		if (p[i].first == x && p[(i + 1) % len].first == x) {
			y1 = min(y1, max(p[i].second, p[(i + 1) % len].second));
			y2 = max(y2, min(p[i].second, p[(i + 1) % len].second));
		} else if (min(p[i].first, p[(i + 1) % len].first) < x &&
					x < max(p[i].first, p[(i + 1) % len].first)) {
			y1 = min(y1, p[i].second);
			y2 = max(y2, p[i].second);
		}
	Split(p, len, x, y1, y2, a, alen, b, blen);
	ll Pa = getPerimeter(a, alen), Pb = getPerimeter(b, blen);
	if (Pa < Pb) return -1;
	if (Pa > Pb) return 1;
	return 0;
}

bool getVertical(ii p[], int len, int &x, int &y1, int &y2)
{
	//printf("vert\n");
	/*for (int i = 0; i < len; i++)
		printf("p[%d] = (%d, %d)\n", i, p[i].first, p[i].second);
	printf("\n");*/
	int lx = Inf, rx = -Inf;
	for (int i = 0; i < len; i++) {
		lx = min(lx, p[i].first); 
		rx = max(rx, p[i].first);
	}
	lx++; rx--;
	while (lx <= rx) {
		x = lx + rx >> 1;
		int st = Status(p, len, x, y1, y2);
		if (st == -1) lx = x + 1;
		else if (st == 1) rx = x - 1;
		else { //printf("x = %d\n", x); printf("alen = %d, blen = %d\n", alen, blen);
			/*for (int i = 0; i < alen; i++)
				printf("%d %d\n", a[i].first, a[i].second);
			printf("\n");
			for (int i = 0; i < blen; i++)
				printf("%d %d\n", b[i].first, b[i].second);*/
		 return complexCompare(a, alen, b, blen); 
		}
	}
	return false;
}

void Init()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &p[i].first, &p[i].second);
	int sm = 0;
	for (int i = 0; i < n; i++)
		if (p[i] < p[sm]) sm = i;
	if (p[sm].first != p[(sm + 1) % n].first)
		reverse(p, p + n);
}

int main()
{
	Init();
	if (getVertical(p, n, x, y1, y2))
		printf("%d %d %d %d\n", x, y1, x, y2);
	else {
		Rotate(p, n);
		if (getVertical(p, n, x, y1, y2))
			printf("%d %d %d %d\n", -y1, x, -y2, x);
		else printf("NO\n");
	}
	return 0;
}