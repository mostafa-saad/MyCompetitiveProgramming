// O(N logN) solution
#include <cstdio>

int main()
{
  int n;
  scanf("%d",&n);
  static int A[1000000];
  long long AA=0;
  for(int i=0;i<n;i++){
    scanf("%d",A+i);
    AA+=A[i];
  }
  long long l=0,r=AA+1;
  while(l+1<r){
    long long m=(l+r)/2;
    static long long S[1000000];
    static int P[1000000];
    for(int i=0;i<n;i++){
      if(i>0){
	P[i]=P[i-1]-1;
	S[i]=S[i-1]-A[i-1];
      }
      else{
	P[i]=0;
	S[i]=0;
      }
      while(S[i]<m){
	S[i]+=A[(i+P[i])%n];
	P[i]++;
      }
    }
    bool B=0;
    for(int i=0;i<n;i++){
      if(AA-S[i]-S[(i+P[i])%n]>=m){
	B=1;
      }
    }
    if(B){
      l=m;
    }
    else{
      r=m;
    }
  }
  printf("%lld\n",l);
  return 0;
}
