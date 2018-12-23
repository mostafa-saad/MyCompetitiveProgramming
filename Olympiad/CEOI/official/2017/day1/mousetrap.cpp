#include <iostream>
#include <iomanip>
#include <climits>
#include <stack>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <cassert>

#define FOR(i,n) for(int i=0,_n=n;i<_n;i++)
#define FORR(i,s,n) for(int i=s,_n=n;i<_n;i++)
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define vi vector<int>
#define fs first
#define sec second

#define maxn 1000000

using namespace std;
typedef long long ll;

const ll MOD = 1000000007LL;

vi drevo[maxn+5];
int parent[maxn+5];
int cena[maxn+5];
vector <pii> subtrees;
int ispath[maxn+5];
int root, mis, n;

int dfs1(int poz, int pr){//dobi podatke o starsu, vrne podatek o tem, ali se nahaja na poti do misi oz. kako dalec je
	int stars=-1;
	FOR(i,drevo[poz].size())if(drevo[poz][i]==pr)stars=i;
	if(stars!=-1)drevo[poz].erase(drevo[poz].begin()+stars);
	parent[poz]=pr;
	int napoti=-1;
	if(poz==mis)napoti=0;
	FOR(i,drevo[poz].size())napoti=max(napoti,dfs1(drevo[poz][i],poz));
	ispath[poz]=napoti;
	if(napoti==-1)return napoti;
	return napoti+1;
}

void dfs2(int poz, int c){//izracuna ceno sebe in sinov in po potrebi doda v subtrees
	if(drevo[poz].size()==0){//list
		cena[poz]=c;
		return;
	}
	if(ispath[poz]==-1){
		int nyuc=c+drevo[poz].size();
		FOR(i,drevo[poz].size())dfs2(drevo[poz][i],nyuc);
		if(drevo[poz].size()==1){
			cena[poz]=c+1;
			return;
		}
		int best=-1;
		int sbest=-1;
		FOR(i,drevo[poz].size()){
			if(cena[drevo[poz][i]]>best){
				sbest=best;
				best=cena[drevo[poz][i]];
				continue;
			}
			if(cena[drevo[poz][i]]>sbest)sbest=cena[drevo[poz][i]];
		}
		cena[poz]=sbest;
		return;
	}
	int nyuc=c+drevo[poz].size()-1;//ne stejemo povezave naprej po poti
	if(poz==root)nyuc=0;
	if(poz==mis)nyuc++;//ce smo pri misi, potem ni nadaljevanja poti
	FOR(i,drevo[poz].size())dfs2(drevo[poz][i],nyuc);
	if(poz==root)return;//v korenu nam ni treba nic vec rezat
	FOR(i,drevo[poz].size())if(ispath[drevo[poz][i]]==-1)subtrees.pb(mp(ispath[poz],cena[drevo[poz][i]]));
}

int main(){
	scanf("%d%d%d",&n,&root,&mis);
	root--;
	mis--;
	FOR(i,n-1){
		int a,b;
		scanf("%d%d",&a,&b);
		a--,b--;
		drevo[a].pb(b);
		drevo[b].pb(a);
	}
	int pathl = dfs1(root,-1);
	dfs2(root,0);
	sort(subtrees.begin(),subtrees.end());
	int l=0,d=n;
	while(l<d){
		int s=(l+d)/2;
		int x=0,y=0,pt=0;
		FOR(i,pathl){
			if(pt>=subtrees.size()){
				d=s;
				break;
			}
			x++;
			int ydelta=0;
			while(pt<subtrees.size() && subtrees[pt].fs<=i){
				if(subtrees[pt].sec+y>s){//rezat treba
					ydelta++;
					x--;
				}
				pt++;
			}
			y+=ydelta;
			if(x<0 || y>s){//ni bilo dovolj rezov
				l=s+1;
				break;
			}
		}
	}
	printf("%d\n",l);
	return 0;
}
