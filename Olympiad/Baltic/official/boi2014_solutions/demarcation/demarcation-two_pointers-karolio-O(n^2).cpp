#include <cstdio>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

const int Maxn = 100005;    // Max number of points
const int Maxr = 4;         // Max number of rotations

int n;               // Number of points
ii p[Maxn];          // Points of polygon
ii a[Maxn], b[Maxn]; // Candidates to compare
int alen, blen;      // Number of points of candidates
ll P;                // Perimeter
int E, F;            // Selected edges
ll A, B;             // Lengths between E and F edges

void Move(ii p[], int len, int &nil)
{
	nil = 0;
	for (int i = 0; i < len; i++)
		if (p[i] < p[nil]) nil = i;
	ii d = ii(-p[nil].first, -p[nil].second);
	if (d == ii(0, 0)) return;
	for (int i = 0; i < len; i++)
		p[i] = ii(p[i].first + d.first, p[i].second + d.second);
}

void Rotate(ii p[], int len)
{
	for (int i = 0; i < len; i++)
		p[i] = ii(p[i].second, -p[i].first);
}

void Reflect(ii p[], int len)
{
	for (int i = 0; i < len; i++)
		p[i].second = -p[i].second;
	reverse(p, p + len);
}

bool trivialCompare(ii a[], int alen, int anil, ii b[], int blen, int bnil)
{
	for (int i = 0; i < alen; i++) // alen = blen
		if (a[(anil + i) % alen] != b[(bnil + i) % blen])
			return false;
	return true;
}

bool spinAround(ii a[], int alen, int anil, ii b[], int blen)
{
	int bnil;   // The leftmost (the lowest) point
	for (int i = 0; i < Maxr; i++) {
		Rotate(b, blen);
		Move(b, blen, bnil);
		if (trivialCompare(a, alen, anil, b, blen, bnil))
			return true;
	}
	return false;
}

bool complexCompare(ii a[], int alen, ii b[], int blen)
{
	if (alen != blen) return false;
	int anil;   // The leftmost (the lowest) point
	Move(a, alen, anil);
	if (spinAround(a, alen, anil, b, blen)) return true;
	Reflect(b, blen);
	return spinAround(a, alen, anil, b, blen);
}

ll crossProduct(ll ax, ll ay, ll bx, ll by) { return ax * by - ay * bx; }

ll inLine(ii a, ii b, ii c)
{
	return crossProduct(b.first - a.first, b.second - a.second, 
						c.first - a.first, c.second - a.second) == 0;
}

void addPoint(ii p[], int &len, ii toadd)
{
	if (len == 0) p[len++] = toadd;
	else if (toadd != p[len - 1]) {
			if (len >= 2 && inLine(p[len - 2], p[len - 1], toadd))
				len--;
			p[len++] = toadd;
		}

}

void Construct(ii p[], int len, ii a[], int &alen, int s1, int s2, int x, int y1, int y2)
{
	alen = 0;
	addPoint(a, alen, ii(x, y1));
	int pnt = s1;
	do {
		pnt = (pnt + 1) % len;
		addPoint(a, alen, p[pnt]);
	} while (pnt != s2);
	addPoint(a, alen, ii(x, y2));
	if (alen >= 3 && inLine(a[alen - 2], a[alen - 1], a[0]))
		alen--;
	if (alen >= 3 && inLine(a[alen - 1], a[0], a[1])) {
		alen--;
		for (int i = 0; i < alen; i++)
			a[i] = a[i + 1];
	}
}

void Split(ii p[], int len, int x, int y1, int y2, ii a[], int &alen, ii b[], int &blen)
{
	int s1 = 0;
	while (!(p[s1].second == y1 && p[(s1 + 1) % len].second == y1 && 
		   p[(s1 + 1) % len].first <= x && x <= p[s1].first))
		s1 = (s1 + 1) % len;
	int s2 = 0;
	while (!(p[s2].second == y2 && p[(s2 + 1) % len].second == y2 && 
		   p[s2].first <= x && x <= p[(s2 + 1) % len].first))
		s2 = (s2 + 1) % len;
	Construct(p, len, a, alen, s1, s2, x, y1, y2); 
	Construct(p, len, b, blen, s2, s1, x, y2, y1);
}

ll edgeLen(int pnt)
{
	return abs(p[pnt].first - p[(pnt + 1) % n].first) + abs(p[pnt].second - p[(pnt + 1) % n].second);
}

int nextHorizontal(ii p[], int len, int pnt, ll &toinc, ll &todec)
{
	do {
		toinc += edgeLen(pnt);
		pnt = (pnt + 1) % len;
		todec -= edgeLen(pnt);
	} while (p[pnt].second != p[(pnt + 1) % len].second);
	return pnt;
}

int prevHorizontal(ii p[], int len, int pnt, ll &toinc, ll &todec)
{
	do {
		todec += edgeLen(pnt);
		pnt = (pnt - 1 + len) % len;
		toinc -= edgeLen(pnt);
	} while (p[pnt].second != p[(pnt + 1) % len].second);
	return pnt;
}

bool Check(ii p[], int len, int x, int y1, int y2)
{
	for (int i = 0; i < len; i++)
		if (p[i].first == x && p[(i + 1) % len].first == x) {
			int Y1 = min(p[i].second, p[(i + 1) % len].second);
			int Y2 = max(p[i].second, p[(i + 1) % len].second);
			Y1 = max(Y1, y1); Y2 = min(Y2, y2);
			if (Y1 < Y2) return false;
		} else if (p[i].first != p[(i + 1) % len].first &&
				   y1 < p[i].second && p[i].second < y2 && 
				   min(p[i].first, p[(i + 1) % len].first) <= x && x <= max(p[i].first, p[(i + 1) % len].first))
				return false;
	Split(p, len, x, y1, y2, a, alen, b, blen);
	return complexCompare(a, alen, b, blen);
}

bool getVerticalSplit(ii p[], int len, int &x, int &y1, int &y2)
{
	int begin = nextHorizontal(p, len, 0, B, A);
	E = F = begin;
	A = -edgeLen(E); B = P - edgeLen(E);
	do {
		while (edgeLen(E) + edgeLen(F) >= A - B) {
			if (edgeLen(E) + edgeLen(F) >= abs(A - B)) {
				int or1 = p[E].first < p[(E + 1) % len].first? 1: -1;
		   		int or2 = p[F].first < p[(F + 1) % len].first? 1: -1;
		   		if (or1 != or2 && (or1 == 1 && p[E].second > p[F].second || or1 == -1 && p[E].second < p[F].second)) {
			   		ll num = p[E].first + p[(E + 1) % len].first;
			   		num += p[F].first + p[(F + 1) % len].first;
			   		num += or1 == 1? A - B: B - A;
			   		if (num % 4ll == 0) {
			   			ll X = num / 4ll;
			   			ll Y1 = min(p[E].second, p[F].second), Y2 = max(p[E].second, p[F].second);
			   			bool inE = min(p[E].first, p[(E + 1) % len].first) <= X && X <= max(p[E].first, p[(E + 1) % len].first);
			   			bool inF = min(p[F].first, p[(F + 1) % len].first) <= X && X <= max(p[F].first, p[(F + 1) % len].first);
			   			if (inE && inF && Check(p, len, X, Y1, Y2)) {
							x = X; y1 = Y1; y2 = Y2;
							return true;
			   			}
			   		}
			   	}
			}
			F = nextHorizontal(p, len, F, A, B);
		}
		F = prevHorizontal(p, len, F, A, B);
		E = nextHorizontal(p, len, E, B, A);
	} while (E != begin);
	return false;
}

void Init()
{
	scanf("%d", &n);
	int lm = 0; // leftmost
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &p[i].first, &p[i].second);
		if (p[i] < p[lm]) lm = i;
	}
	if (!(p[lm].second < p[(lm + 1) % n].second))
		reverse(p, p + n); // Make clockwise
	for (int i = 0; i < n; i++)
		P += edgeLen(i);
}

int main()
{
	Init();
	int x, y1, y2;
	if (getVerticalSplit(p, n, x, y1, y2))
		printf("%d %d %d %d\n", x, y1, x, y2);
	else {
		Rotate(p, n);
		if (getVerticalSplit(p, n, x, y1, y2))
			printf("%d %d %d %d\n", -y2, x, -y1, x); // Rotating back
		else printf("NO\n");
	}
	return 0;
}