#include<bits/stdc++.h>
using namespace std;

template<class T> void chmin(T& a,const T& b) { if(a>b) a=b; }
template<class T> void chmax(T& a,const T& b) { if(a<b) a=b; }

typedef pair<int,int> pi;

const int INF=5e8;
const int MAX_N=500005;

struct uf{
  int par[MAX_N];
  int size[MAX_N];
  void init(){
    memset(par,-1,sizeof(par));
    for(int i=1;i<MAX_N;++i) size[i]=1;
  }
  int root(int a){
    if(par[a]==-1) return a;
    return par[a]=root(par[a]);
  }
  void unite(int a,int b){
    a=root(a);b=root(b);
    if(a==b) return;

    par[b]=a;
    size[a]+=size[b];
  }
  bool same(int a,int b){
    return root(a)==root(b);
  }
};
uf u;

int n,q;
int ar[MAX_N];
vector<int> keys[MAX_N];

pi query[MAX_N];

bool vis[MAX_N];
pi memo[MAX_N];
vector<int> pos[MAX_N];
bool open(int id,int l,int r){
  return (*lower_bound(pos[id].begin(),pos[id].end(),l)<=r);
}
pair<int,pi> rec(int p){//(id,(l,r))
  if(vis[p]){
    return {p,{p,p}};
  }
  if(memo[p].first>=0){
    return {-1,memo[p]};
  }
  if(u.root(p)!=p){
    return rec(u.root(p));
  }
  vis[p]=1;
  int l=p,r=p;
  while(1){
    if(l>0 && open(ar[l-1],l,r)){
      auto range=rec(l-1);
      chmin(l,range.second.first);
      chmax(r,range.second.second);
      if(range.first>=0 && range.first!=p){
        u.unite(range.first,p);
        vis[p]=false;
        return {range.first,{l,r}};
      }
      continue;
    }
    if(r+1<n && open(ar[r],l,r)){
      auto range=rec(r+1);
      chmin(l,range.second.first);
      chmax(r,range.second.second);
      if(range.first>=0 && range.first!=p){
        u.unite(range.first,p);
        vis[p]=false;
        return {range.first,{l,r}};
      }
      continue;
    }
    break;
  }
  vis[p]=0;
  return {-1, memo[p]={l,r} };
}
int main(){
  u.init();
  cin>>n;
  for(int i=0;i<n-1;++i) scanf("%d",&ar[i]),--ar[i];
  int sum=0;
  for(int i=0;i<n;++i){
    int K;scanf("%d",&K);
    keys[i].resize(K);
    sum+=K;
    for(int j=0;j<K;++j){
      scanf("%d",&keys[i][j]);
      --keys[i][j];
      pos[keys[i][j]].push_back(i);
    }
  }
  for(int i=0;i<n;++i) pos[i].push_back(INF);
  memset(memo,-1,sizeof(memo));
  for(int i=0;i<n;++i) rec(i);
  for(int i=0;i<n;++i) if(u.root(i)!=i){
    memo[i]=memo[u.root(i)];
  }
  cin>>q;
  for(int i=0;i<q;++i){
    int l,r;scanf("%d%d",&l,&r);--l;--r;
    if(memo[l].first<=r && r<=memo[l].second) puts("YES");
    else puts("NO");
  }
  return 0;
}



