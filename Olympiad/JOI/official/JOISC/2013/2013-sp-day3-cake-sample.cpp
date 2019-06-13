#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cassert>

using namespace std;

#define MAXN 300000
#define LOGN 20
#define MAXA 1000000000

typedef long long ll;
typedef pair<int,int> pint;

#define repp(i,a,b) for(int i=(int)(a);i<=(b);++i)
#define rep(i,n) repp(i,0,(n)-1)

#define mp make_pair

int n;
int a[3*MAXN+10];
ll ans[MAXN+10];
int minv=MAXA+1,minp;

int depth=0;

pint rmqdata[MAXN][LOGN];
void buildrmq(){
	for(int i=0; i<n-1; ++i) rmqdata[i][0]=mp(a[i],i);
	for(int sz=1,j=1; 2*sz<=n-1; sz*=2,++j){
		for(int i=0; i<=n-1-2*sz; ++i){
			rmqdata[i][j] = min(rmqdata[i][j-1], rmqdata[i+sz][j-1]);
		}
	}
}
pint rmq(int le,int ri){
	int j=0, sz=1;
	while(ri-le+1 >= sz*2){
		sz *= 2;
		++j;
	}
	return min(rmqdata[le][j], rmqdata[ri-sz+1][j]);
}

ll ruisekiwa[MAXN+10];
void buildruiseki(){
	ruisekiwa[0] = 0LL;
	ruisekiwa[1] = 0LL;
	repp(i, 0, n-2){
		ruisekiwa[i+2] = ruisekiwa[i] + a[i];
	}
}
ll kogoruiseki(int st, int en, int par){
	par %= 2;
	ll res;
	if(st < en){
		if(par==0){
			if((en-st)%2)
				res = ruisekiwa[en+1] - ruisekiwa[st];
			else
				res = ruisekiwa[en+2] - ruisekiwa[st];
		}else{
			if((en-st)%2)
				res = ruisekiwa[en+2] - ruisekiwa[st+1];
			else
				res = ruisekiwa[en+1] - ruisekiwa[st+1];
		}
	}else{
		if(par==0){
			if((en-st)%2)
				res = ruisekiwa[st+2] - ruisekiwa[en+1];
			else
				res = ruisekiwa[st+2] - ruisekiwa[en];
		}else{
			if((en-st)%2)
				res = ruisekiwa[st+1] - ruisekiwa[en];
			else
				res = ruisekiwa[st+1] - ruisekiwa[en+1];
		}
	}
	return res;
}

void add(int le, int ri, ll v){
	assert(0 <= le && ri <= n-2);
	ans[le] += v;
	ans[ri+1] -= v;
}

void midsolve(int le, int ri, int mi){
	while(le < mi && mi < ri){
		int l = rmq(le, mi-1).second;
		int r = rmq(mi+1, ri).second;
		if(a[l] < a[r]){
			add(mi, mi, kogoruiseki(l, le, ri-l));
			le = l+1;
		}else{
			add(mi, mi, kogoruiseki(r, ri, r-le));
			ri = r-1;
		}
	}
	if(le == mi){
		add(mi, mi, kogoruiseki(mi, ri, 0));
	}else{
		add(mi, mi, kogoruiseki(mi, le, 0));
	}
}
void solve(int le, int ri){
	if(ri-le < 0) {
		return;
	}
	pint mid = rmq(le,ri);
	int mi = mid.second;
++depth;
	if(ri-le == 0){
		add(le, ri, a[le]);
--depth;
		return;
	}else if(ri-le == 1){
		add(le, le, a[le]);
		add(ri, ri, a[ri]);
--depth;
		return;
	}
	solve(le, mi-1);
	add(le, mi-1, kogoruiseki(mi, ri, mi-le));
	solve(mi+1, ri);
	add(mi+1, ri, kogoruiseki(mi, le, ri-mi));
	midsolve(le, ri, mi);
--depth;
}

ll saishou(){
	ll res = minv;
	int le=0, ri=n-2, cnt=0;
	while(le<=ri){
		if(a[le] < a[ri]){
			if(cnt%2) res += a[ri];
			--ri; ++cnt;
		}else{
			if(cnt%2) res += a[le];
			++le; ++cnt;
		}
	}
	return res;
}

int main(){
	cin >> n;
	rep(i,n){
		scanf("%d",&a[n+i]);
	}
	rep(i,n){
		if(a[n+i] < minv) {
			minv = a[n+i];
			minp = i;
		}
	}
	int i,j=0;
	for(i=minp+1; i<n; ++i,++j){
		a[j] = a[n+i];
	}
	for(i=0; j<n-1; ++i,++j){
		a[j] = a[n+i];
	}


	buildrmq();
	buildruiseki();
	solve(0,n-2);

	if(n%2) ans[0] += minv;
	repp(i,1,n-2) ans[i] += ans[i-1];

	for(int i=n-1-minp; i<n-1; ++i){
		printf("%lld\n", ans[i]);
	}
	printf("%lld\n", saishou());
	for(int i=0; i<n-1-minp; ++i){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
