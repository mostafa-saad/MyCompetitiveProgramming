#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<deque>
#include<string>
#include<string.h>
#include<vector>
#include<set>
#include<map>
#include<stdlib.h>
#include<complex>
using namespace std;

const int MN=30000,MQ=100000,BS=15,RQ=300;


typedef complex<long long> point;

long long op(point P1,point P2)
{
  return imag((conj(P1)*P2));
}

namespace std{
  bool operator<(point P1,point P2)
  {
    return op(P1,P2)>0;
  }
};



template<class T> class sumBIT
{
private:
  T *bit;
  int S;
public:
  sumBIT(int S0){
    S=S0;
    bit=(T *)calloc(sizeof(T),1<<S);
  }
  void add(int i,T k){
    int p=i+1;
    while(p<1<<S){
      bit[p]+=k;
      p+=p&-p;
    }
  }
  T sum(int p){
    T ret=0;
    while(p>0){
      ret+=bit[p];
      p-=p&-p;
    }
    return ret;
  }
  T rag(int a,int b){
    return sum(b)-sum(a);
  }
};


int main()
{
  int n,m;
  scanf("%d%d",&n,&m);
  static point P[MN];
  static int C[MN];
  for(int i=0;i<n;i++){
    long long x,y;
    scanf("%lld%lld%d",&x,&y,C+i);
    P[i]=point(x,y);
    C[i]--;
  }
  long long d1,e1,d2,e2;
  scanf("%lld%lld%lld%lld",&d1,&e1,&d2,&e2);
  point X=point(d1,e1),Y=point(d2,e2);
  static bool F[MN];
  for(int i=0;i<n;i++){
    F[i]=(op(Y-X,P[i]-X)>0);
  }
  static point A[MN];
  static pair<int,point> AA[MN];
  for(int i=0;i<n;i++){
    A[i]=(F[i]?P[i]-Y:Y-P[i]);
    AA[i]=make_pair(C[i],A[i]);
  }
  sort(AA,AA+n);
  static int D[MN];
  for(int i=0;i<n;i++){
    D[i]=lower_bound(AA,AA+n,make_pair(C[i],A[i]))-AA;
  }
  static int T[MN+1];
  for(int i=0;i<=m;i++){
    T[i]=lower_bound(AA,AA+n,make_pair(i,Y-X))-AA;
  }
  static pair<point,int> Pr[MN];
  for(int i=0;i<n;i++){
    Pr[i]=make_pair(F[i]?P[i]-X:X-P[i],i);
  }
  sort(Pr,Pr+n);
  int Q;
  scanf("%d",&Q);
  static int as[MQ],bs[MQ];
  for(int i=0;i<Q;i++){
    scanf("%d%d",as+i,bs+i);
    as[i]--,bs[i]--;
  }
  static vector<int> V[MN],VN[MN];
  for(int i=0;i<Q;i++){
    V[as[i]].push_back(bs[i]);
    VN[as[i]].push_back(i);
  }
  static vector<int> V2[MN],VN2[MN];
  for(int i=0;i<Q;i++){
    if(V[as[i]].size()>=RQ){
      V2[bs[i]].push_back(as[i]);
      VN2[bs[i]].push_back(i);
    }
  }
  static long long ans[MQ]={0};
  sumBIT<int> seg0(BS),seg1(BS);
  for(int i=0;i<n;i++){
    if(!F[i]){
      seg1.add(D[i],1);
    }
  }
  for(int t=0;t<n;t++){
    int i=Pr[t].second;
    int a=C[i];
    if(F[i]){
      if(V[a].size()<RQ){
	for(int k=0;k<V[a].size();k++){
	  int b=V[a][k],l=VN[a][k];
	  int L=lower_bound(AA,AA+n,make_pair(b,A[i]))-AA;
	  ans[l]+=seg0.rag(L,T[b+1])+seg1.rag(T[b],L);
	}
      }
      seg0.add(D[i],1);
    }
    else{
      if(V[a].size()<RQ){
	for(int k=0;k<V[a].size();k++){
	  int b=V[a][k],l=VN[a][k];
	  int L=lower_bound(AA,AA+n,make_pair(b,A[i]))-AA;
	  ans[l]+=seg0.rag(L,T[b+1])+seg1.rag(T[b],L);
	}
      }
      seg1.add(D[i],-1);
    }
  }
  sumBIT<int> seg2(BS),seg3(BS);
  for(int i=0;i<n;i++){
    seg2.add(D[i],1);
  }
  for(int t=0;t<n;t++){
    int i=Pr[t].second;
    int b=C[i];
    if(F[i]){
      for(int k=0;k<V2[b].size();k++){
	int a=V2[b][k],l=VN2[b][k];
	int L=lower_bound(AA,AA+n,make_pair(a,A[i]))-AA;
	ans[l]+=seg2.rag(T[a],L);
      }
      seg2.add(D[i],-1);
      seg3.add(D[i],1);
    }
    else{
      for(int k=0;k<V2[b].size();k++){
	int a=V2[b][k],l=VN2[b][k];
	int L=lower_bound(AA,AA+n,make_pair(a,A[i]))-AA;
	ans[l]+=seg3.rag(L,T[a+1]);
      }
      seg2.add(D[i],-1);
      seg3.add(D[i],1);
    }
  }
  for(int t=0;t<Q;t++){
    printf("%lld\n",ans[t]);
  }
  return 0;
}
