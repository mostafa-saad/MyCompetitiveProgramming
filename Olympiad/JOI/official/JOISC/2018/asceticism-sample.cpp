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
#include<cassert>
using namespace std;
const long long mod=1000000007;
const long long inf=mod*mod;
const long long d2=500000004;
const double EPS=1e-6;
const double PI=acos(-1.0);
int ABS(int a){return max(a,-a);}
long long ABS(long long a){return max(a,-a);}
long long finv[110000];
long long inv[110000];
long long fact[110000];
long long C(int a,int b){
	if(a<b)return 0;
	return fact[a]*finv[b]%mod*finv[a-b]%mod;
}
long long pw(long long a,long long b){
	long long ret=1;
	while(b){
		if(b%2)ret=ret*a%mod;
		a=a*a%mod;
		b/=2;
	}
	return ret;
}
long long f(int a,int b){
	long long ret=0;
	for(int i=0;i<=b;i++){
		long long t=pw(b-i,a)*finv[a]%mod*C(a,i)%mod;
		if(i%2)ret=(ret+mod-t)%mod;
		else ret=(ret+t)%mod;
	}
	return ret;
}
long long calc(int a,int b){
	long long ret=f(a,b+1);
	ret=(ret+mod-f(a,b))%mod;
	return ret;
}
int main(){
	fact[0]=1;
	for(int i=1;i<110000;i++)fact[i]=fact[i-1]*i%mod;
	inv[1]=1;
	for(int i=2;i<110000;i++){
		inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod;
	}
	finv[0]=1;
	for(int i=1;i<110000;i++){
		finv[i]=finv[i-1]*inv[i]%mod;
	}
	int N,K;scanf("%d%d",&N,&K);
	K--;
	printf("%lld\n",calc(N,K)*fact[N]%mod);
	
}