#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 2000
#define MAXN2 4000
#define pb push_back
using namespace std;

int N,M;
int Pa,Qa;
int Rb,Sb;
vector<int> ioi[MAXN];
vector<int> joi[MAXN];
int bgni[MAXN];
int bgnj[MAXN];
int endi[MAXN];
int endj[MAXN];
int counti=0;
int countj=0;
int shachoi;
int shachoj;
int imos[MAXN2][MAXN2];
void dfs(int v,bool is_joi){
	if(is_joi){bgnj[v]=countj++;}else{bgni[v]=counti++;}
	for(int i=0;i<(is_joi?joi[v].size():ioi[v].size());i++){
		if(is_joi){dfs(joi[v][i],true);}
		else{dfs(ioi[v][i],false);}
	}
	if(is_joi){endj[v]=countj++;}else{endi[v]=counti++;}
}

int main()
{
	scanf("%d %d\n",&N,&M);
	for(int a=0;a<N;a++){
		scanf("%d %d\n",&Pa,&Qa);
		if(Pa!=0){
			Pa--;
			joi[Pa].pb(a);
		}else{shachoj=a;}
		if(Qa!=0){
			Qa--;
			ioi[Qa].pb(a);
		}else{shachoi=a;}
	}
	
	dfs(shachoj,true);
	dfs(shachoi,false);
	
	for(int b=0;b<M;b++){
		scanf("%d %d",&Rb,&Sb);
		Rb--;Sb--;
		imos[bgnj[Rb]][bgni[Sb]]+=1;
		imos[bgnj[Rb]][endi[Sb]]-=1;
		imos[endj[Rb]][bgni[Sb]]-=1;
		imos[endj[Rb]][endi[Sb]]+=1;
	}
	
	int cnt;
	for(int i=0;i<MAXN2;i++){
		cnt=0;
		for(int j=0;j<MAXN2;j++){
			cnt+=imos[j][i];
			imos[j][i]=cnt;
		}
	}
	for(int j=0;j<MAXN2;j++){
		cnt=0;
		for(int i=0;i<MAXN2;i++){
			cnt+=imos[j][i];
			imos[j][i]=cnt;
		}
	}
	
	for(int a=0;a<N;a++){
		printf("%d\n",imos[bgnj[a]][bgni[a]]);
	}
}