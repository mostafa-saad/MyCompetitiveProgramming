#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int maxn = 444444;
const int sb = maxn / 2;
struct graph {
  int e;
  int beg[maxn], nxt[maxn], to[maxn];
  void aa(int x,int y) {
    ++e; nxt[e]=beg[x]; to[e]=y; beg[x]=e;
  }
  void ae(int x,int y) {
    aa(x,y); aa(y,x);
  }
} g;
 
int n,m;
int dfn[maxn], low[maxn], tme;
vector<int> gd;
bool isgd[maxn];
stack<int> stk;
 
int bkc=sb;
int of[maxn];
int cnt[maxn];
vector<int> tg[maxn];
int decc;
void ae(int x,int y) {
  // cout<<x<<' '<<y<<endl;
  tg[x].push_back(y); tg[y].push_back(x);
  ++decc;
}
void dfs0(int x,int fa) {
  low[x]=dfn[x]=++tme;
  int sonc=0;
  bool ok=false;
  stk.push(x);
  vector<int> sb;
  for(int i=g.beg[x];i;i=g.nxt[i]) {
    int y=g.to[i];
    if(y==fa) continue;
    if(!dfn[y]) {
      dfs0(y,x);
      ++sonc;
      if(low[y]>=dfn[x]) {
        ok=true;
        ++bkc;
        while(stk.top()!=y) {
          int z=stk.top(); stk.pop();
          if(isgd[z]) {
            ae(bkc, z);
          } else {
            of[z]=bkc; ++cnt[bkc];
          }
        }
          int z=stk.top(); stk.pop();
          if(isgd[z]) {
            ae(bkc, z);
          } else {
            of[z]=bkc; ++cnt[bkc];
          }
        if(fa) {
          ae(bkc, x);
        } else {
          sb.push_back(bkc);
        }
      }
      low[x]=min(low[x],low[y]);
    } else {
      low[x]=min(low[x],dfn[y]);
    }
  }
  if(fa ? ok : sonc>=2) {
    gd.push_back(x);
    isgd[x]=1;
  }
  if(!fa) {
    if(sonc>=2) {
      for(int ss:sb) {
        ae(ss, x);
      }
    } else {
      for(int ss:sb) {
        of[x]=ss; ++cnt[ss];
      }
    }
  }
}
ll ans=0;
int sz[maxn];
int gsz;
void dfs2(int x,int f) {
  sz[x]=(x<sb?1:cnt[x]);
  for(int y:tg[x]) {
    if(y==f) continue;
    dfs2(y,x);
    sz[x]+=sz[y];
  }
}
void dfs3(int x,int f) {
  if(x>=sb) {
    ll Bcho=cnt[x];
    // AC in: A(cnt[x]-1,2)
    ans+=Bcho * (cnt[x]-1) * (cnt[x]-2);
    // one in: A:cnt[x]-1, B:gsz-cnt[x]
    ans+=Bcho * (cnt[x]-1) * (gsz-cnt[x]) * 2;
    // both out: as above
    ll P=0,Q=0;
    for(int y:tg[x]) {
      if(y==f) {P+=gsz-sz[x]; Q+=(gsz-sz[x])*(ll)(gsz-sz[x]); continue;}
      P+=sz[y]; Q+=sz[y]*(ll)sz[y];
    }
    ans+=Bcho*(P*P-Q);
    for(int y:tg[x]) {
      ll ga;
      if(y==f) { ga=gsz-sz[x]; }
      else     { ga=sz[y]; }
      P-=ga; Q-=ga*ga;
      ans+=(cnt[x]) * (cnt[x]-1);
      ans+=(cnt[x]) * (gsz-cnt[x]-ga) * 2;
      ans+=P*P-Q;
      P+=ga; Q+=ga*ga;
    }
  } else {
    ll P=0,Q=0;
    for(int y:tg[x]) {
      if(y==f) {P+=gsz-sz[x]; Q+=(gsz-sz[x])*(ll)(gsz-sz[x]); continue;}
      P+=sz[y]; Q+=sz[y]*(ll)sz[y];
    }
    ans+=P*P-Q;
  }
  for(int y:tg[x]) {
    if(y==f) continue;
    dfs3(y,x);
  }
}
 
int main() {
  cin.sync_with_stdio(false); cin.tie(0);
  cin>>n>>m;
  //n=500;m=499;
  for(int i=1;i<=m;++i) {
    int u,v; cin>>u>>v;
    // u=rand()%(i)+1;v=i+1;
    // cerr<<u<<' '<<v<<endl;
    g.ae(u,v);
  }
  int llc=0;
  vector<int> rts;
  for(int i=1;i<=n;++i) {
    if(!dfn[i]) {
      dfs0(i,0), ++llc;
      rts.push_back(i);
    }
  }
  for(int &i:rts) {
    if(!isgd[i]) {
      i=of[i];
    }
  }
  // TODO fix edge
   
  int deled=0;
  for(int i=sb+1;i<=bkc;++i) {
    sort(tg[i].begin(), tg[i].end());
    int ss=unique(tg[i].begin(), tg[i].end())-tg[i].begin();
    deled+=tg[i].size()-ss;
    tg[i].resize(ss);
  }
  for(int i:gd) {
    sort(tg[i].begin(), tg[i].end());
    int ss=unique(tg[i].begin(), tg[i].end())-tg[i].begin();
    deled+=tg[i].size()-ss;
    tg[i].resize(ss);
  }
  // cerr<<deled<<endl;
  decc-=deled/2;
  // assert(decc==((bkc-sb)+gd.size())-llc);
  // return 0;
  for(int i:rts) {
    dfs2(i,0); gsz=sz[i];
    dfs3(i,0);
  }
  cout<<ans<<endl;
  return 0;
}