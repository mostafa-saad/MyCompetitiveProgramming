#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <stack>
#include <ctime>
#include <iterator>
using namespace std;

#define ALL(c) (c).begin(),(c).end()
#define IN(x,c) (find(c.begin(),c.end(),x) != (c).end())
#define REP(i,n) for (int i=0;i<(int)(n);i++)
#define FOR(i,a,b) for (int i=(a);i<=(b);i++)
#define INIT(a,v) memset(a,v,sizeof(a))
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
template<class A, class B> A cvt(B x) { stringstream ss; ss<<x; A y; ss>>y; return y; }

typedef pair<int,int> PII;
typedef long long int64;

#define N 100000

int n;
int64 h[N],w[N];

int64 sqr(int64 x) { return x*x; }

struct line {
	char type;
	double x;
	int64 k, n;
};

bool operator<(line l1, line l2) {
	if (l1.type+l2.type>0) return l1.x<l2.x;
	else return l1.k>l2.k;
}

set<line> env;
typedef set<line>::iterator sit;

bool hasPrev(sit it) { return it!=env.begin(); }
bool hasNext(sit it) { return it!=env.end() && next(it)!=env.end(); }

double intersect(sit it1, sit it2) {
	return (double)(it1->n-it2->n)/(it2->k-it1->k);
}

void calcX(sit it) {
	if (hasPrev(it)) {
		line l = *it;
		l.x = intersect(prev(it), it);
		env.insert(env.erase(it), l);
	}
}

bool irrelevant(sit it) {
	if (hasNext(it) && next(it)->n <= it->n) return true; // x=0 cutoff
	return hasPrev(it) && hasNext(it) && intersect(prev(it),next(it)) <= intersect(prev(it),it);
}

void add(int64 k, int64 a) {
	sit it;
	// handle collinear line
	it=env.lower_bound({0,0,k,a});
	if (it!=env.end() && it->k==k) {
		if (it->n <= a) return;
		else env.erase(it);
	}
	// erase irrelevant lines
	it=env.insert({0,0,k,a}).first;
	if (irrelevant(it)) { env.erase(it); return; }
	while (hasPrev(it) && irrelevant(prev(it))) env.erase(prev(it));
	while (hasNext(it) && irrelevant(next(it))) env.erase(next(it));
	// recalc left intersection points
	if (hasNext(it)) calcX(next(it));
	calcX(it);
}

int64 query(int64 x) {
	auto it = env.upper_bound((line){1,(double)x,0,0});
	it--;
	return it->n+x*it->k;
}

int64 g[N];

int64 solve() {
	int64 a=0;
	REP (i,n) a+=w[i];
	g[0]=-w[0];
	FOR (i,1,n-1) {
		add(-2*h[i-1],g[i-1]+sqr(h[i-1]));
		int64 opt=query(h[i]);
		g[i]=sqr(h[i])-w[i]+opt;
	}
	return a+g[n-1];
}

int main() {
	cin >> n;
	REP (i,n) cin >> h[i];
	REP (i,n) cin >> w[i];
	cout << solve() << endl;
	return 0;
}
