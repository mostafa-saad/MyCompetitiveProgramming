#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

const int Maxn = 100005;    // Max number of points
const int Maxe = 2 * Maxn;  // Max number of events
const int Maxr = 4;         // Max number of rotations

// Element in the set ("Line Sweep")
struct element {
	int y, ind, delt;
	element(int y = 0, int ind = 0, int delt = 0): y(y), ind(ind), delt(delt) {}
	bool operator <(const element &e) const {
		return y < e.y;
	}
};

// Event in "Line Sweep"
struct event {
	int x;
	element el;
	bool en;
	event(int x = 0, element el = element(), bool en = false): x(x), el(el), en(en) { }
	bool operator <(const event &e) const {
		if (x != e.x) return x < e.x;
		return en < e.en;
	}
};

// "Candidate" split line
struct line {
	int x, y1, y2;
	line(int x = 0, int y1 = 0, int y2 = 0): x(x), y1(y1), y2(y2) {}
	bool operator <(const line &l) const {
		if (x != l.x) return x < l.x;
		if (y1 != l.y1) return y1 < l.y1;
		return y2 < l.y2;
	}
};

int n;               // Number of points
ii p[Maxn];          // Points of polygon
ll num[Maxn];        // Enumerated points by perimeter
event E[Maxe];       // Events in "Line Sweep"
int elen;
set <line> Spl;      // Can become split line
ii a[Maxn], b[Maxn]; // Candidates to compare
int alen, blen;      // Number of points of candidates

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
	if (alen >= 3 && inLine(a[len - 1], a[0], a[1])) {
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

bool getVerticalSplit(ii p[], int len, int &x, int &y1, int &y2)
{
	// Prepare perimeter
	num[0] = 0;
	for (int i = 1; i <= len; i++)
		num[i] = num[i - 1] + abs(p[i % len].first - p[i - 1].first) + 
							  abs(p[i % len].second - p[i - 1].second);
	// Prepare events
	elen = 0;
	for (int i = 0; i < len; i++) {
		int ni = (i + 1) % len;
		if (p[i].second == p[ni].second)
			if (p[i].first < p[ni].first) {
				element el = element(p[i].second, i, 1);
				E[elen++] = event(p[i].first, el, false);
				E[elen++] = event(p[ni].first, el, true);
			} else {
				element el = element(p[i].second, ni, -1);
				E[elen++] = event(p[ni].first, el, false);
				E[elen++] = event(p[i].first, el, true);
			}
	}
	sort(E, E + elen);
	// Line Sweep
	set <element> S;
	for (int i = 0, j; i < elen; i = j) {
		j = i;
		int curx = E[i].x;
		if (!Spl.empty()) curx = min(curx, Spl.begin()->x);

		while (curx == E[j].x && !E[j].en)
			S.insert(E[j++].el);

		for (int l = i; l < j; l++) {
			element el = E[l].el;
			ll id1 = num[el.ind] + el.delt * (curx - p[el.ind].first);
			int cangrow = (el.delt == 1? p[(el.ind + 1) % len].first: p[(el.ind - 1 + len) % len].first) - curx;
			set <element>::iterator it = S.find(el);
			if (el.delt == 1)
				if (it == S.begin()) continue;
				else it--;
			else {
				it++;
				if (it == S.end()) continue;
			}
			ll id2 = num[it->ind] + it->delt * (curx - p[it->ind].first);
			cangrow = min(cangrow, (it->delt == 1? p[(it->ind + 1) % len].first: p[(it->ind - 1 + len) % len].first) - curx);
			ll did = el.delt == 1? id1 - id2: id2 - id1;
			if (did < 0) did += num[len];
			ll grow = (num[len] / 2 - did) / 2;
			if (grow >= 0 && grow <= cangrow && 2 * (did + 2 * grow) == num[len])
				Spl.insert(line(curx + grow, min(el.y, it->y), max(el.y, it->y)));
		}
		set <line>::iterator it = Spl.begin();
		while (it != Spl.end() && curx == it->x) {
			set <element>::iterator it2 = S.lower_bound(element(it->y1, 0, 0));
			if (it2 == S.end() || it2->y != it->y1) { Spl.erase(it++); continue; }
			it2++;
			if (it2 == S.end() || it2->y != it->y2) { Spl.erase(it++); continue; }
			Split(p, len, it->x, it->y1, it->y2, a, alen, b, blen);
			if (complexCompare(a, alen, b, blen)) {
				x = it->x; y1 = it->y1; y2 = it->y2;
				return true;
			}
			Spl.erase(it++);
		}

		while (curx == E[j].x)
			S.erase(E[j++].el);
	}
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