#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<deque>
#include<stack>
#include<string>
#include<string.h>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<stdlib.h>
#include<cassert>
#include<time.h>
#include<bitset>
using namespace std;
const long long mod=1000000007;
const long long inf=mod*mod;
const long long d2=(mod+1)/2;
const long double EPS=1e-9;
const long double PI=acos(-1.0);
int ABS(int a){return max(a,-a);}
long long ABS(long long a){return max(a,-a);}
long double ABS(long double a){return max(a,-a);}
int p[110000];
int q[110000];
int A[110000];
int B[110000];
int C[110000];
int z[110000];
int z2[110000];
int bit[110000];
int ans[110000];
pair<int,int> tmp[110000];
int sum(int a,int b){
	if(a>b)return 0;
	if(a)return sum(0,b)-sum(0,a-1);
	int ret=0;
	for(;b>=0;b=(b&(b+1))-1)ret+=bit[b];
	return ret;
}
void add(int a,int b){
	if(a<0)return ;
	for(;a<110000;a|=a+1)bit[a]+=b;
}
int main(){
	int a,b;scanf("%d%d",&a,&b);
	for(int i=0;i<a;i++){
		scanf("%d%d",p+i,q+i);
		tmp[i]=make_pair(p[i],i);
	}
	std::sort(tmp,tmp+a);
	for(int i=0;i<b;i++){
		scanf("%d%d%d",A+i,B+i,C+i);
	}
	for(int i=0;i<a;i++){
		z[i]=q[i];
		z2[i]=p[i];
	}
	std::sort(z,z+a);
	std::sort(z2,z2+a);
	vector<pair<int,int> > ev;
	for(int i=0;i<b;i++){
		if(A[i]+B[i]>=C[i]){
			ev.push_back(make_pair(A[i],i));
		}
	}
	std::sort(ev.begin(),ev.end());
	int at=a-1;
	for(int i=0;i<ev.size();i++){
		int ind=ev[ev.size()-1-i].second;
		int X=A[ind];
		int Y=B[ind];
		
		while(at>=0&&X<=tmp[at].first){
			add(upper_bound(z,z+a,q[tmp[at].second])-z-1,1);
			at--;
		}
		ans[ind]=sum(lower_bound(z,z+a,Y)-z,a);
	}
	ev.clear();
	for(int i=0;i<a;i++)tmp[i]=make_pair(p[i]+q[i],i);
	for(int i=0;i<b;i++){
		if(A[i]+B[i]<C[i]){
			ev.push_back(make_pair(C[i],i));
		}
	}
	std::sort(tmp,tmp+a);
	std::sort(ev.begin(),ev.end());
	for(int k=0;k<2;k++){
		for(int i=0;i<110000;i++)bit[i]=0;
		at=a-1;
		for(int i=0;i<ev.size();i++){
			int ind=ev[ev.size()-1-i].second;
			int T=C[ind];
			while(at>=0&&T<=tmp[at].first){
				if(k==0)add(upper_bound(z,z+a,q[tmp[at].second])-z,1);
				else add(upper_bound(z2,z2+a,p[tmp[at].second])-z2,1);
				at--;
			}
			if(k==0){
				ans[ind]+=a-1-at;
			}
			if(k==0){
				ans[ind]-=sum(0,lower_bound(z,z+a,B[ind])-z);
			}else{
				ans[ind]-=sum(0,lower_bound(z2,z2+a,A[ind])-z2);
			}
		}
	}
	for(int i=0;i<b;i++)printf("%d\n",ans[i]);
}