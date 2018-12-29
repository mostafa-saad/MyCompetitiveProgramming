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
#include<set>
#include<stack>
#include<bits/stdc++.h>

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
		while(a){
			D[a]--;
			a/=2;
		}
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
	set<int> S;
	FORI(i,n) S.insert(i*2);
	S.insert(-MMM);
	S.insert(MMM);
	FORI(q,n-1){
		int i = col[q];
		if(Next[q] == 0){
			set<int>::iterator it = S.insert(first[i]*2+1).fi;
			while((*it) <= q*2){
				if(*it % 2 == 0)
					Tree.rm(*it/2);
				set<int>::iterator jt = it;
				it++;
				S.erase(jt);
			}
		}
		ans += Tree.sum(t1[q]+1,q);
		int x = max(q - (n/2),t1[q]+1);
		x = (x*2-1);
		set<int>::iterator it = S.insert(x).fi;
		set<int>::iterator ip1 = it;
		set<int>::iterator im1 = it;
		ip1++;
		im1--;
		S.erase(it);
		if(*im1/2 <= q && *im1/2 >= t1[q]+1){
			MMM = min(MMM,abs(n-(2*q-*im1)-2));
		}
		if(*ip1/2 <= q && *ip1/2 >= t1[q]+1){
			MMM = min(MMM,abs(n-(2*q-*ip1)-2));
		}
	}
	printf("%lld %d\n", ans,MMM);
}
