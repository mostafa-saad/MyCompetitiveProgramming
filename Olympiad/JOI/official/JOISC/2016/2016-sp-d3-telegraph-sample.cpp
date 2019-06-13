#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN=100000;

int main()
{
  int n;
  scanf("%d",&n);
  static int A[MAXN];
  static long long C[MAXN];
  for(int i=0;i<n;i++){
    scanf("%d%lld",A+i,C+i);
    A[i]--;
  }
  static int b[MAXN];
  for(int i=0;i<n;i++){
    b[i]=-1;
  }
  bool F=0;
  for(int i=0;i<n;i++){
    if(b[i]!=-1){
      continue;
    }
    int j=i;
    while(b[j]==-1){
      b[j]=i;
      j=A[j];
    }
    if(b[j]==i){
      int C=0;
      while(b[j]!=-2){
	b[j]=-2;
	j=A[j];
	C++;
      }
      if(C==n){
	F=1;
      }
    }
  }
  long long ans=0ll;
  if(!F){
    for(int i=0;i<n;i++){
      ans+=C[i];
    }
    static long long M1[MAXN]={0},M2[MAXN]={0};
    for(int i=0;i<n;i++){
      M1[A[i]]=max(M1[A[i]],C[i]);
      if(b[i]!=-2){
	M2[A[i]]=max(M2[A[i]],C[i]);
      }
    }
    for(int i=0;i<n;i++){
      ans-=M1[i];
    }
    for(int i=0;i<n;i++){
      if(b[i]!=-2){
	continue;
      }
      long long M=10000000000ll;
      int j=i;
      while(b[j]==-2){
	M=min(M,M1[j]-M2[j]);
	b[j]=-3;
	j=A[j];
      }
      ans+=M;
    }
  }
  printf("%lld\n",ans);
  return 0;
}
