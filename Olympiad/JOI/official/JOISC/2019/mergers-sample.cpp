#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

int n,K;
vector<vector<int> > e,id;
vector<int> s,pr,c,N,rN,X,Y,liv;

void eulertour()
{
  stack<pair<int,int> > S;
  S.push(make_pair(0,0));
  while(!S.empty()){
    int i=S.top().first,x=S.top().second;
    S.pop();
    if(x==0){
      N[i]=rN.size();
      rN.push_back(i);
    }
    if(x<e[i].size()){
      S.push(make_pair(i,x+1));
      int j=e[i][x];
      if(j!=pr[i]){
	pr[j]=i;
	X.push_back(N[i]);
	S.push(make_pair(j,0));
      }
    }
    else{
      X.push_back(N[i]);
      Y[i]=X.size();
    }
  }
}

const int TINF=1000000000;

template<class T> class segmintree
{
private:
  T ragin(int i,int j,int k,int a,int b)
  {
    return a<=j&&k<=b?seg[i]:k<=a||b<=j?TINF:min(ragin(2*i,j,(j+k)/2,a,b),ragin(2*i+1,(j+k)/2,k,a,b));
  }
public:
  T *seg;
  int S;
  segmintree(vector<T> a)
  {
    int n=a.size();
    S=0;
    while((1<<S)<=n)S++;
    seg=(T *)calloc(sizeof(T),1<<(S+1));
    for(int i=0;i<1<<S;i++){
      seg[i+(1<<S)]=(i<n?a[i]:TINF);
    }
    for(int i=(1<<S)-1;i>0;i--){
      seg[i]=min(seg[2*i],seg[2*i+1]);
    }
  }
  T rag(int a,int b){
    return ragin(1,0,1<<S,a,b);
  }
};

void dfs()
{
  stack<pair<int,int> > S;
  vector<int> r(n);
  S.push(make_pair(0,0));
  while(!S.empty()){
    int i=S.top().first,x=S.top().second;
    S.pop();
    if(x==0){
      r[i]=c[i];
    }
    else{
      int j=e[i][x-1];
      if(j!=pr[i]){
	liv[id[i][x-1]]=(r[j]>0);
	r[i]+=r[j];
      }
    }
    if(x<e[i].size()){
      S.push(make_pair(i,x+1));
      int j=e[i][x];
      if(j!=pr[i]){
	S.push(make_pair(j,0));
      }
    }
  }
}

int main()
{
  scanf("%d%d",&n,&K);
  e=vector<vector<int> >(n);
  id=vector<vector<int> >(n);
  for(int i=0;i<n-1;i++){
    int a,b;
    scanf("%d%d",&a,&b);
    a--,b--;
    e[a].push_back(b);
    id[a].push_back(i);
    e[b].push_back(a);
    id[b].push_back(i);
  }
  pr=vector<int>(n);
  pr[0]=-1;
  N=vector<int>(n);
  Y=vector<int>(n);
  eulertour();
  segmintree<int> seg(X);
  s=vector<int>(n);
  for(int i=0;i<n;i++){
    scanf("%d",&s[i]);
    s[i]--;
  }
  vector<vector<int> > is(K);
  for(int i=0;i<n;i++){
    is[s[i]].push_back(i);
  }
  c=vector<int>(n);
  for(int j=0;j<K;j++){
    for(int x=0;x+1<is[j].size();x++){
      int a=is[j][x],b=is[j][x+1];
      int an=rN[seg.rag(min(Y[a],Y[b]),max(Y[a],Y[b]))];
      c[an]-=2;
      c[a]++,c[b]++;
    }
  }
  liv=vector<int>(n-1);
  dfs();
  int cnt=0;
  vector<bool> b(n,false);
  for(int i=0;i<n;i++){
    if(b[i])continue;
    b[i]=true;
    queue<int> Q;
    Q.push(i);
    int d=0;
    while(!Q.empty()){
      int j=Q.front();
      Q.pop();
      for(int x=0;x<e[j].size();x++){
	int k=e[j][x];
	if(!liv[id[j][x]]){
	  d++;
	}
	else if(!b[k]){
	  b[k]=true;
	  Q.push(k);
	}
      }
    }
    if(d==1){
      cnt++;
    }
  }
  printf("%d\n",(cnt+1)/2);
  return 0;
}
