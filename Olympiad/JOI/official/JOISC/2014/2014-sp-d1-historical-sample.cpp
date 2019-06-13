#include<stdio.h>
#include<vector>
#include<algorithm>
#define SQ 100
/*

bucket size: 100

*/
using namespace std;
int c[110000];
int d[110000];
int z[110000];
vector<int>v[110000];
long long e[110000];
long long f[3000][3000];
int main(){
	int a,b;
	scanf("%d%d",&a,&b);
	for(int i=0;i<a;i++)scanf("%d",c+i);
	for(int i=0;i<a;i++){
		z[i]=c[i];
	}
	std::sort(z,z+a);
	for(int i=0;i<a;i++){
		d[i]=lower_bound(z,z+a,c[i])-z;
		v[d[i]].push_back(i);
	}
	for(int i=0;i<a/SQ;i++){
		for(int j=0;j<a;j++)e[j]=0LL;
		long long val=0LL;
		for(int j=i*SQ;j<=a;j++){
			if(j%SQ==0){
				f[i][j/SQ]=val;
			}
			e[d[j]]+=z[d[j]];
			val=max(val,e[d[j]]);
		}
	}
	for(int i=0;i<b;i++){
		int p,q;
		scanf("%d%d",&p,&q);
		p--;
		long long ret=f[(p+SQ-1)/SQ][q/SQ];
		for(int j=p;j%SQ;j++){
			ret=max(ret,(long long)z[d[j]]*(lower_bound(v[d[j]].begin(),v[d[j]].end(),q)-lower_bound(v[d[j]].begin(),v[d[j]].end(),p)));
		}
		for(int j=q-1;(j+1)%SQ;j--){
			ret=max(ret,(long long)z[d[j]]*(lower_bound(v[d[j]].begin(),v[d[j]].end(),q)-lower_bound(v[d[j]].begin(),v[d[j]].end(),p)));
		}
		printf("%lld\n",ret);
	}
}