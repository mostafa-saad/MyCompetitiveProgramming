/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pustynia                                           *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O((n + k) log n)                                   *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/



#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <cassert>
#include <cstring>
using namespace std;
typedef long long LL;
const int INF = 1000*1000*1000;
const LL INFLL = (LL) INF * (LL) INF;
#define REP(i,n) for(i=0;i<(n);++i)
#define ALL(c) c.begin(),c.end()
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin()); i !=(c).end();++i)
#define PB push_back
#define MP make_pair
#define FI first
#define SE second


#define SIZE (101*1000)
#define POMI (201*1000)
#define DRZE (257*1024)
#define PRZE (128*1024)
int n,s,m,p,d,l,r,k,i,j;
int prze[POMI][2];
int przegl[POMI];
int wyn[SIZE];
vector<int> data[POMI];
vector<int> gl[SIZE];

int prze1[DRZE];


void up1(int a,int w){
	if(prze1[a]>w)
		prze1[a]=w;
};
void ogr(int a, int b,int w) {
	if(a>b)
		return;
   int va = PRZE + a, vb = PRZE + b;
   up1(va,w);
   if (va != vb) up1(vb,w);
   while (va / 2 != vb / 2) {
     if (va % 2 == 0) up1(va+1,w);
     if (vb % 2 == 1) up1(vb - 1,w); 
     va /= 2; vb /= 2;
   }
}

int getogr(int pom){
	int wyn=INF;
	pom+=PRZE;
	while (pom != 1) {
		if(prze1[pom]<wyn)
			wyn=prze1[pom];
		pom /= 2;
		}
	return wyn;
}

int prze2[DRZE];
int blokady[DRZE];
void akt(int a){
	if(a<PRZE)
		blokady[a]=min(blokady[a*2],blokady[a*2+1])+prze2[a];
	else
		blokady[a]=prze2[a];
}

void up2(int a,int w){
	prze2[a]+=w;
	akt(a);
};
void add(int a, int b,int w) {
	if(a>b)
		return;
   int va = PRZE + a, vb = PRZE + b;
   up2(va,w);
   if (va != vb) up2(vb,w);
   while (va / 2 != vb / 2) {
	 akt(va);
	 akt(vb);
     if (va % 2 == 0) up2(va+1,w);
     if (vb % 2 == 1) up2(vb - 1,w); 
     va /= 2; vb /= 2;
   }
   akt(vb);
   while(va>=1){
		akt(va);
		va/=2;
   }
}


int find(){
	int poz=1;
	
	while(poz<PRZE){
		if(blokady[poz*2]<=blokady[poz*2+1])
			poz*=2;
		else
			poz=poz*2+1;
		}
	return poz-PRZE;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin>>n>>s>>m;
	REP(i,DRZE){
		prze1[i]=INF;
	}
	REP(i,s){
		cin>>p>>d;
		ogr(p,p,d);  
		wyn[p]=d;
	}
	REP(i,m){
		cin>>prze[i][0]>>prze[i][1]>>k;
		add(prze[i][0],prze[i][1],1);
		przegl[i]=k;
		REP(j,k){
			cin>>s;
			data[i].PB(s);
			gl[s].PB(i);
			add(s,s,-1);
		}
	}
	add(0,0,INF);
	int poz=find();;
	int ust=0;
	int pom;
	while(poz!=0 &&poz<=n){
		
		ust++;
		add(poz,poz,INF);
		pom=getogr(poz);
		if(pom<wyn[poz] || pom<=0){
			cout<<"NIE"<<endl;
			return 0;
		}
		wyn[poz]=pom;
		FOREACH(i,gl[poz]){
			if((--przegl[*i])==0){
				
				add(prze[*i][0],prze[*i][1],-1);
				int minimal=INF+1;
				FOREACH(j,data[*i]){
					if(wyn[*j]<minimal)
						minimal=wyn[*j];
				}
				ogr(prze[*i][0],prze[*i][1],minimal-1);
			}
				
		}
		poz=find();
	}
	if(ust!=n){
		cout<<"NIE"<<endl;
		return 0;
	}
	cout<<"TAK"<<endl;
	REP(i,n)
		cout<<wyn[i+1]<<" ";
	cout<<endl;
}
