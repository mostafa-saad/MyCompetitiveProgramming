/*
 * 3562.cpp
 * Another buggy code by mostafa_saad
 *
 *  Created on: Jul 28, 2010
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
#include<algorithm>
#include<numeric>
#include<utility>
#include <functional>
#include<stdio.h>
#include<assert.h>
#include<memory.h>
using namespace std;

#define all(v)				((v).begin()), ((v).end())
#define sz(v)				((int)((v).size()))
#define clr(v, d)			memset(v, d, sizeof(v))
#define rep(i, v)		for(int i=0;i<sz(v);++i)
#define lp(i, n)		for(int i=0;i<(int)(n);++i)
#define lpi(i, j, n)	for(int i=(j);i<(int)(n);++i)
#define lpd(i, j, n)	for(int i=(j);i>=(int)(n);--i)
#define repa(v)				lpi(i, 0, sz(v)) lpi(j, 0, sz(v[i]))
#define P(x)				cout<<#x<<" = { "<<x<<" }\n"
#define pb					push_back
#define MP					make_pair

typedef vector<int>       vi;
typedef vector<double>    vd;
typedef vector< vi >      vvi;
typedef vector< vd >      vvd;
typedef vector<string>    vs;
typedef long long         ll;
typedef long double   	  ld;

const int OO = (int)1e8;	//Small -> WRONG, Large -> OVERFLOW

const double PI  = acos(-1.0);
const double EPS = (1e-7);

int dcmp(double x, double y) {	return fabs(x-y) <= EPS ? 0 : x < y ? -1 : 1;	}

struct edge {
	int from, to;
	int w;

	edge(int from, int to, int w): from(from), to(to), w(w) {}

	bool operator < (const edge & e) const {
		return w > e.w;	// STL priority_queue need it > , or modify data -ve, or use paprmeter less
	}
};

vi buildPath(vector<int> prev, int src) {
	vi path;	// make sure to test case self edge. E.g. 2 --> 2
	for (int i = src; i > -1 && sz(path) <= sz(prev); i = prev[i])	path.push_back(i);
	reverse( all(path) );
	return path;
}

bool BellmanPrcoessing(vector<edge> & edgeList, int n, vi &dist, vi &prev, vi &pos) {
	if(sz(edgeList) == 0)	return false;

	//vi dist(n, OO), prev(n, -1), pos(n);	// To use pos: edgeList[pos[path[i]]].w
	//dist[ edgeList[0].from ] = 0;

	for (int it = 0, r = 0; it < n+1; ++it, r = 0) {
		for (int j = 0; j < sz(edgeList) ; ++j) {
			edge ne = edgeList[j];
			if(dist[ne.from] >= OO || ne.w >= OO)	continue;
			if( dist[ne.to] > dist[ne.from] + ne.w ) {
				dist[ne.to] = dist[ne.from] + ne.w;
				prev[ ne.to ] = ne.from, pos[ ne.to ] = j, r++;
				if(it == n)		return true;
			}
		}
		if(!r)	break;
	}
	return false;
}

pair<double, vi> BellmanFord(vector<edge> & edgeList, int n, int src, int dest)	// O(NE)
{
	vi dist(n, OO);
	vi prev(n, -1), reachCycle(n), path, pos(n);	// To use pos: edgeList[pos[path[i]]].w
	dist[src] = 0;

	BellmanPrcoessing(edgeList, n, dist, prev, pos);
	path = buildPath(prev, dest);
	return make_pair(dist[dest], path);
}

pair<int, int> mcmf(vector< vi > capMax, vector< vector<int> > & costMax, int src, int dest)
{
	int maxFlow = 0;
	double minCost = 0;
	while(true) {
		vector<edge> edgeList;
		repa(capMax) if(capMax[i][j] > 0) edgeList.push_back( edge(i, j, costMax[i][j]) );

		pair<int, vi> p = BellmanFord(edgeList, sz(capMax), src, dest);
		if(p.first <= -OO || p.first >= +OO)	break;

		int bottleNeck = OO;
		lp(i, sz(p.second)-1 ) {
			int f = p.second[i], t = p.second[i+1];
			bottleNeck = min(bottleNeck, capMax[f][t]);
		}

		lp(i, sz(p.second)-1 ) {
			int f = p.second[i], t = p.second[i+1];
			minCost += bottleNeck * costMax[f][t];
			capMax[f][t] -= bottleNeck, capMax[t][f] += bottleNeck;
		}
		maxFlow += bottleNeck;
	}
	return make_pair(maxFlow, minCost);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in", "rt", stdin);
    //freopen("c.txt", "wt", stdout);
#endif

	int r, c, cc =1;
	while(cin>>r>>c) {
		if(!r && !c)
			break;

		vector<int> a(r);
		vector<int> b(c);

		rep(i, a)	cin>>a[i];
		rep(i, b)	cin>>b[i];

		int N = r+c+2;
		vector<vector<int> > cap(N, vector<int>(N, 0));
		vector<vector<int> > cst(N, vector<int>(N, 0));

		lp(i, r)
			cap[0][i+1] = a[i];

		lp(j, c)
			cap[j+r+1][r+c+1] = b[j];

		lp(i, r) lp(j, c) {
			double t;
			cin>>t;
			int x = (int)((t+EPS)*100);
			if(t < 0)	continue;

			cap[i+1][j+r+1] = OO;
			cst[i+1][j+r+1] = x;
			cst[j+r+1][i+1] = -x;
		}

		double c1 = mcmf(cap, cst, 0, r+c+1).second;
		repa(cst)	cst[i][j]*=-1;
		double c2 = -mcmf(cap, cst, 0, r+c+1).second;

		printf("Problem %d: %.2f to %.2f\n", cc++, c1/100.0, c2/100);
	}
	return 0;
}
