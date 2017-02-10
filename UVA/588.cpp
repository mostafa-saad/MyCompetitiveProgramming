/*
 * Another buggy code by mostafa_saad
 *
 *  Created on: Oct 5, 2008
 * 
 * This problem can be solved directly using simple geometry utilities.
 * For sake of practice, one can apply polygon cut algorithm.
 * 
 * The idea is pretty simple. Think of the visbility from edges perspective.
 * If we have edge A, which point makes every point of this line visible? A point a bove (left) of this line. 
 * Then, everything below is useless and shouldn't be our target point area.
 *
 * So solution is, for every edge, cut the polygon part that doesn't see this edge. IF we are done, if there is still
 * a polygon (area > 0), then any point anside this sub-polygon can see everything.
 */

#include<set>
#include<map>
#include<list>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<complex>
#include<sstream>
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;

#define all(v)				((v).begin()), ((v).end())
#define sz(v)				((int)((v).size()))
#define clr(v, d)			memset(v, d, sizeof(v))
#define repi(i, j, n) 		for(int i=(j);i<(int)(n);++i)
#define repd(i, j, n) 		for(int i=(j);i>=(int)(n);--i)
#define repa(v)				repi(i, 0, sz(v)) repi(j, 0, sz(v[i]))
#define rep(i, v)			repi(i, 0, sz(v))
#define lp(i, cnt)			repi(i, 0, cnt)
#define lpi(i, s, cnt)		repi(i, s, cnt)
#define P(x)				cout<<#x<<" = { "<<x<<" }\n"
#define pb					push_back
#define MP					make_pair

typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<vi> vvi;
typedef vector<vd> vvd;
typedef vector<string> vs;
typedef long long ll;
typedef long double ld;

const int OO = (int) 1e8; //Small -> WRONG, Large -> OVERFLOW

const double PI = acos(-1.0);
const double EPS = (1e-7);

int dcmp(double x, double y) {
	return fabs(x - y) <= EPS ? 0 : x < y ? -1 : 1;
}

typedef complex<double> point;
#define X real()
#define Y imag()
#define cp(a,b)                 ( (conj(a)*(b)).imag() )

bool intersectSegments(point a, point b, point c, point d, point & intersect)
{
	double d1 = cp(a-b, d-c), d2 = cp(a-c, d-c), d3 = cp(a-b, a-c);
	if(fabs(d1) < EPS) return false; // Parllel || identical
	double t1 = d2/d1, t2 = d3/d1;
	intersect = a+(b-a)*t1;
	if(t2 < -EPS || t2 > 1+EPS)
		return false;
    return true;
}

// Cut polygon P(anti-clock) by line AB
// If polygon is clockwise, swap first, last lines
// right is the right polygon on right hand side of AB
// Make sure from polygon and line directions
pair<vector<point>, vector<point> > polygonCut(vector<point> &p, point A, point B) {
	vector<point> left, right;
	point intersect;

	for (int i = 0; i < sz(p); ++i) {
		point cur = p[i], nxt = p[(i+1)%sz(p)];

		if ( cp(B-A, cur-A) >= 0)	right.push_back(cur);

		if(intersectSegments(A, B, cur, nxt, intersect)) {
			right.push_back(intersect);
			left.push_back(intersect);
		}

		if ( cp(B-A, cur-A) <= 0)	left.push_back(cur);
	}
	return make_pair(left, right);
}



int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in","rt",stdin);
#endif

	int x, y;

	int n, cases = 1;

	while (scanf("%d", &n) && n)
	{
		vector<point> p;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", &x, &y);
			p.push_back( point(x, y) );
		}

		vector<point> pts = p;
		lp(i, n)
			p = polygonCut(p, pts[i], pts[(i+1) % n]).first;


		cout<<"Floor #"<<cases++<<"\n";
		if(p.size() == 0)
			cout<<"Surveillance is impossible.\n";
		else
			cout<<"Surveillance is possible.\n";

		cout<<"\n";
	}
	return 0;
}

