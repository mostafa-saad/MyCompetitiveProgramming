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

int main() {
	int n,m;
	string sa,sb;
	cin >> n >> m >> sa >> sb;
	if (sa[0]=='0' || sb[0]=='0') {
		cout << 0 << endl;
		return 0;
	}
	int k=9;
	int p10[k+1];
	p10[0]=1;
	FOR (i,1,k) p10[i]=p10[i-1]*10;
	vector<int64> a(n/k+1),b(m/k+1);
	REP (i,n) a[i/k]+=(sa[n-1-i]-'0')*p10[i%k];
	REP (i,m) b[i/k]+=(sb[m-1-i]-'0')*p10[i%k];
	n=a.size(); m=b.size();
	vector<int64> c(n+m);
	REP (i,n) {
		int carry=0;
		REP (j,m) {
			int64 x=c[i+j]+a[i]*b[j]+carry;
			c[i+j]=x%p10[k];
			carry=x/p10[k];
		}
		c[i+m]=carry;
	}
	reverse(ALL(c));
	bool z=true;
	REP (i,n+m) {
		if (z) {
			if (c[i]!=0) {
				printf("%lld",c[i]);
				z=false;
			}
		} else {
			printf("%09lld",c[i]);
		}
	}
	printf("\n");
	return 0;
}
