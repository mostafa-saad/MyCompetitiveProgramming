/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Odwiedziny                                         *
 *   Zlozonosc czasowa:    O(n * sqrt(n) * log n)                             *
 *   Autor programu:       Tomasz Syposz                                      *
 *   Opis:                 Rozwiazanie alternatywne                           *
 *                                                                            *
 *****************************************************************************/


#include<cstdio>
#include<vector>
#include<map>

using namespace std;

int C[50500];

vector<int> Adj[50500];
map<int,int> Sp[50500];
int Z1[50500];
int Z2[50500];

int Kol[50500];
int J[50500];

int In[50500],Out[50500];

int TIME;
void Time(int u){
	In[u] = ++TIME;
	for(int i = 0; i < (int)Adj[u].size(); i++) if(In[Adj[u][i]] == 0) Time(Adj[u][i]);
	Out[u] = ++TIME;
}

inline bool poddrzewo(int a, int b){
	if(In[a] <= In[b] && Out[a] >= Out[b]) return 1;
	return 0;
}

vector<int> sc;
int SPref(int a,int b, int c){
	if(Sp[a][b] == 0){
		if(c-b < 0) Sp[a][b] = C[a];
		else{
			Sp[a][b] = C[a] + SPref(sc[c-b],b,c-b);
		}
	}
	return Sp[a][b];
}

int Num[50500];
int LCA[50500];
int zLCA1[50500];
int zLCA2[50500];
int n;

int lca(int a){
	int b = Kol[Num[a]+1];
	int p = 0;
	int k = sc.size()-1;
	
	if(poddrzewo(a,b)) return a;
	
	while(p+1 != k){
		int m = (p+k)/2;
		if(poddrzewo(sc[m],b)) p = m;
		else k = m;
	}
	
	return sc[p];
}

int zlca1(int a, int skok){
	int b = Kol[Num[a]+1];
	int k = sc.size()-1;
	int p = k/skok;
	k = 0;
	if(poddrzewo(a,b)) return a;
	if(!poddrzewo(sc[sc.size()-1-p*skok],b)) return -1;
	
	while(p-1 != k){
		int m = (p+k)/2;
		if(poddrzewo(sc[sc.size()-m*skok-1],b)) p = m;
		else k = m;
	}
	return sc[sc.size()-p*skok-1];
}

int zlca2(int a, int skok){
	int b = Kol[Num[a]-1];
	int k = sc.size()-1;
	int p = k/skok;
	k = 0;
	if(poddrzewo(a,b)) return a;
	if(!poddrzewo(sc[sc.size()-1-p*skok],b)) return -1;
	
	while(p-1 != k){
		int m = (p+k)/2;
		if(poddrzewo(sc[sc.size()-m*skok-1],b)) p = m;
		else k = m;
	}
	return sc[sc.size()-p*skok-1];
}

int O[50500];
void dfs(int u){
	sc.push_back(u);
	O[u] = 1;
	if(Z1[u] != 0) SPref(u,Z1[u],sc.size()-1);
	if(Z2[u] != 0) SPref(u,Z2[u],sc.size()-1);
	
	if(Num[u] != n) {
		LCA[u] = lca(u);
		zLCA1[u] = zlca1(u,J[Num[u]]);
	}
	
	if(Num[u] != 1){
		zLCA2[u] = zlca2(u,J[Num[u]-1]);
	}
	
	for(int i = 0; i < (int)Adj[u].size(); i++) if(O[Adj[u][i]] == 0) dfs(Adj[u][i]);
	sc.pop_back();
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &C[i]);
	
	for(int i = 1; i < n; i++){
		int a,b;
		scanf("%d%d", &a,&b);
		Adj[a].push_back(b);
		Adj[b].push_back(a);
	}
	
	for(int i = 1; i<=n; i++){
		scanf("%d", &Kol[i]);
		Num[Kol[i]] = i;
	}
	
	for(int i = 1; i<n; i++){
		scanf("%d", &J[i]);
		Z2[Kol[i]] = J[i];
		Z1[Kol[i+1]] = J[i];
	}
	Time(1);
	dfs(1);
	for(int i = 1;i < n; i++){
		int ans = SPref(Kol[i],J[i],-1) + SPref(Kol[i+1],J[i],-1);
		if(zLCA1[Kol[i]] != -1)
			ans -= SPref(zLCA1[Kol[i]],J[i],-1);
		if(zLCA2[Kol[i+1]] != -1)
			ans -= SPref(zLCA2[Kol[i+1]],J[i],-1);
		
		if(LCA[Kol[i]] == zLCA1[Kol[i]]) ans += C[LCA[Kol[i]]];
		printf("%d\n", ans);
	}

	return 0;
}
