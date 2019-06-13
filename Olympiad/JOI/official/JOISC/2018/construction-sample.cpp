#include <bits/stdc++.h>
using namespace std;

const int NMAX=100000;
const int BS=17;

int Par[NMAX],Dep[NMAX],X[NMAX],dep[NMAX],par[NMAX],S[NMAX];

int n;
vector<vector<int> > e;

void dfs(int i)
{
  S[i]=0;
  for(int x=0;x<e[i].size();x++){
    int j=e[i][x];
    dep[j]=dep[i]+1;
    par[j]=i;
    dfs(j);
    S[i]+=S[j];
  }
}

void HLD()
{
  dep[0]=0;
  par[0]=-1;
  dfs(0);
  int NX=0;
  Par[0]=0;
  Dep[0]=0;
  stack<int> ST;
  ST.push(0);
  while(!ST.empty()){
    int i=ST.top();
    ST.pop();
    X[i]=NX;
    NX++;
    int K=-1;
    for(int j=0;j<e[i].size();j++){
      int k=e[i][j];
      if(K==-1||S[K]<S[k]){
	K=k;
      }
    }
    if(K==-1)continue;
    Par[K]=Par[i];
    Dep[K]=Dep[i]+1;
    for(int j=0;j<e[i].size();j++){
      int k=e[i][j];
      if(k==K)continue;
      Par[k]=k;
      Dep[k]=0;
      ST.push(k);
    }
    ST.push(K);
  }
}

stack<pair<int,int> > St[NMAX];

long long bit[1<<BS];
void bitadd(int N,int i,long long v)
{
  int p=i+1;
  while(p<1<<N){
    bit[p]+=v;
    p+=p&-p;
  }
}
long long bitsum(int N,int i)
{
  int p=i+1;
  long long ret=0;
  while(p>0){
    ret+=bit[p];
    p-=p&-p;
  }
  return ret;
}

long long cal_inv(vector<pair<int,int> > &V)
{
  int n=V.size(),N=0;
  while((1<<N)<=n)N++;
  vector<int> X(n);
  for(int i=0;i<n;i++)X[i]=V[i].first;
  sort(X.begin(),X.end());
  for(int i=0;i<n;i++)V[i].first=lower_bound(X.begin(),X.end(),V[i].first)-X.begin();
  for(int i=0;i<(1<<N);i++)bit[i]=0;
  long long ret=0ll;
  for(int t=0;t<n;t++){
    ret+=bitsum(N,V[t].first-1)*V[t].second;
    bitadd(N,V[t].first,V[t].second);
  }
  return ret;
}

int main()
{
  scanf("%d",&n);
  vector<int> C(n);
  for(int i=0;i<n;i++){
    scanf("%d",&(C[i]));
  }
  vector<int> A(n-1),B(n-1);
  for(int i=0;i<n-1;i++){
    scanf("%d%d",&(A[i]),&(B[i]));
    A[i]--,B[i]--;
  }
  e=vector<vector<int> >(n);
  for(int i=0;i<n-1;i++){
    e[A[i]].push_back(B[i]);
  }
  HLD();
  for(int T=0;T<n-1;T++){
    int p=B[T],c=C[p];
    vector<pair<int,int> > V;
    while(p!=-1){
      int d=Dep[p]+1,t=0;
      p=Par[p];
      stack<pair<int,int> > &S=St[p];
      vector<pair<int,int> > V2;
      while(!S.empty()&&S.top().second<=d){
	pair<int,int> pr=S.top();
	S.pop();
	V2.push_back(make_pair(pr.first,pr.second-t));
	t=pr.second;
      }
      if(!S.empty()){
	V2.push_back(make_pair(S.top().first,d-t));
      }
      S.push(make_pair(c,d));
      for(int x=V2.size()-1;x>=0;x--)V.push_back(V2[x]);
      p=par[p];
    }
    printf("%lld\n",cal_inv(V));
  }
  return 0;
}
