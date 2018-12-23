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

int n=0;
double a[100000],b[100000];

int main() {
	cin >> n;
	REP (i,n) {
		cin >> a[i] >> b[i];
		a[i]-=1; b[i]-=1;
	}
	sort(a,a+n); reverse(a,a+n);
	sort(b,b+n); reverse(b,b+n);
	int i=0,j=0;
	double r=0;
	double sa=0,sb=0;
	while (i<n) {
		sa+=a[i];
		i++;
		while (j<n && min(sa-j,sb-i)<min(sa-(j+1),(sb+b[j])-i)) {
			sb+=b[j];
			j++;
		}
		r=max(r, min(sa-j,sb-i));
	}
	printf("%.4f\n",r);
	return 0;
}
