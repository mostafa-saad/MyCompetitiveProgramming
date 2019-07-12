#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

const int INF=5e8;
const int MAX_N=1000005;
int app[MAX_N];

int d[MAX_N],ans[MAX_N];
int N,C;

pi ps[500005];
int pscnt[500005];
void chmin(int& a,int b){
  a=min(a,b);
}

void solve(int n,int* ar,int L,int R){
  if(n&1) return;
  if(n==0){
    for(int i=0;i<C;++i) ans[i]=0;
    return;
  }

  int m=0;
  for(int i=0;i<n;i+=2){
    int a=ar[i],b=ar[i+1];
    if(a>b) swap(a,b);
    ps[m++]={a,b};
  }
  sort(ps,ps+m);
  m=unique(ps,ps+m)-ps;
  memset(pscnt,0,sizeof(pscnt));
  for(int i=0;i<n;i+=2){
    int a=ar[i],b=ar[i+1];
    if(a>b) swap(a,b);
    ++pscnt[lower_bound(ps,ps+m,make_pair(a,b))-ps];
  }
  for(int i=0;i<m;++i) {
    int a=ps[i].first,b=ps[i].second;
    if(a==b) continue;
    int val=N-(app[a]+app[b]-pscnt[i]);
    chmin(ans[a],val);
    chmin(ans[b],val);
  }
  for(int i=0;i<C;++i) d[i]=i;
  sort(d,d+C,[&](int a,int b){
    return app[a]>app[b];
  });
  for(int i=0;i<C;++i) {
    int j;
    for(j=0;(i==j) || (j<C && binary_search(ps,ps+m,make_pair(min(d[i],d[j]),max(d[j],d[i]))));++j);
    if(j<C){
      int val=N-(app[d[i]]+app[d[j]]);
      chmin(ans[d[i]],val);
      chmin(ans[d[j]],val);
    }
  }
}
int n;
int ar[MAX_N];

int main(){
  cin>>n>>C;
  if(C==1){
    puts("0");
    return 0;
  }
  for(int i=0;i<n;++i) scanf("%d",&ar[i]),--ar[i];
  for(int i=0;i<C;++i) ans[i]=INF;

  for(int i=0;i<n;++i) app[ar[i]]++;
  N=n;
  solve(n,ar,-1,-1);
  solve(n-1,ar+1,ar[0],-1);
  solve(n-1,ar,-1,ar[n-1]);
  solve(n-2,ar+1,ar[0],ar[n-1]);
  for(int i=0;i<C;++i) printf("%d\n",ans[i]);
  return 0;
}



