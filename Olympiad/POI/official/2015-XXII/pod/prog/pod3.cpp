/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Podzial naszyjnika                                 *
 *   Autor programu:       Tomasz Syposz                                      *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include<cstdio>
#include<algorithm>
#include<stack>

using namespace std;
#define REP(i,a,b) for(int i=(a);i<=(b);++i)
#define REPD(i,a,b) for(int i=(a);i>=(b);--i)
#define FORI(i,n) REP(i,1,n)
#define FOR(i,n) REP(i,0,int(n)-1)
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define vi vector<int>
#define ll long long
#define SZ(x) int((x).size())
#define DBG(v) //cerr << #v << " = " << (v) << endl;
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define SORT(X) sort(X.begin(),X.end())
#define fi first
#define se second

int n,k;
int col[1000100];
int t1[1000100];

int last[1000100];
int Next[1000100];
int first[1000100];
stack<pii> Z; //(from,to)
void prep(){
	Z.push(mp(0,100000000));
	FORI(i,n){
		Next[last[col[i]]] = i;
		last[col[i]] = i;
		if(first[col[i]] == 0) first[col[i]] = i;
	}
	FORI(i,n){
		if(Next[i] != 0){
			while(Z.top().se < Next[i]) Z.pop();
			Z.push(mp(i,Next[i]));
		}
		while(Z.top().se <= i) Z.pop();
		t1[i] = Z.top().fi;
	}
}

struct tree{
	int D[1024*2048];
	static const int N = 1024*1024;
	
	tree(){
		FOR(i,N) D[i+N] = 1;
		REPD(i,N-1,1) D[i] = D[i*2]+D[i*2+1];
	}
	
	
	void rm(int a){
		a+=N;
		if(D[a]==0) return;
		while(a){
			D[a]--;
			a/=2;
		}
	}
	
	int right(int a){
		a+=N;
		while(!((a%2==0)&&(D[a+1] != 0))){
			a/=2;
		}
		a++;
		while(a < N){
			a*=2;
			if(D[a]==0) a++;
		}
		return a-N;
	}
	
	int left(int a){
		a+=N;
		while(!((a%2==1)&&(D[a-1] != 0))){
			a/=2;
		}
		a--;
		while(a < N){
			a=(a*2+1);
			if(D[a]==0) a--;
		}
		return a-N;
	}
	
	int sum(int a, int b){
		int rt = 0;
		if( a > b ) return 0;
		a+=N;
		b+=N;
		while(a < b){
			if(a&1){
				rt+=D[a];
			}
			if(!(b&1)){
				rt+=D[b];
			}
			a = (a+1)/2;
			b = (b-1)/2;
		}
		if(a==b){
			rt+=D[b];
		}
		return rt;
	}
};


void read(){
	scanf("%d%d", &n,&k);
	FORI(i,n)
		scanf("%d", &col[i]);
}

typedef long long llg;

tree Tree;

int main(){
	read();
	prep();
	llg ans=0;
	int MMM = 100000000;
	FORI(q,n-1){
		int i = col[q];
		if(Next[q] == 0){
			int x = first[i]+1;
			while(x <= q){
				Tree.rm(x);
				x = Tree.right(x);
			}
		}
		ans += Tree.sum(t1[q]+1,q);
		int x = max(q - (n/2),t1[q]+1);
		int im1 = Tree.left(x);
		int ip1 = Tree.right(x);
		if(im1 <= q && im1 >= t1[q]+1){
			MMM = min(MMM,abs(n-(2*q-2*im1)-2));
		}
		if(ip1 <= q && ip1 >= t1[q]+1){
			MMM = min(MMM,abs(n-(2*q-2*ip1)-2));
		}
		if(x <= q && x >= t1[q]+1 && Tree.D[x+Tree.N] != 0){
			MMM = min(MMM,abs(n-(2*q-2*x)-2));
		}
	}
	printf("%lld %d\n", ans,MMM);
}
