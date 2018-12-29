/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Niebanalne podroze                                 *
 *   Autor:                Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie wolne - liczymy roznice symetryczne    *
 *                         cykli bazowych                                     *
 *****************************************************************************/

#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;

const int MAXN = 500000;
const int MOD = 1000000007;

int n, m;
vector<int> graph[MAXN + 3];
int d[MAXN + 3], parent[MAXN + 3];
bool vis[MAXN + 3];
int cycles, length;
vector< pair<int,int> > baseCycles[2*MAXN + 3];
set< pair<int,int> > xorCycles;

void Read(){
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}

inline pair<int,int> sortEdge(pair<int,int> e){
	if(e.first > e.second)
		swap(e.first, e.second);
	return e;
}

bool Dfs(int v){
	vis[v] = true;
	for(int i=0; i<(int)graph[v].size(); i++){
		int u = graph[v][i];
		if(!vis[u]){
			d[u] = d[v] + 1;
			parent[u] = v;
			bool esc = Dfs(u);
			if(esc == false)
				return false;
		}
		else if(d[u] + 1 < d[v]){
			if(length == 0)
				length = d[v] - d[u] + 1;
			else if(length != d[v] - d[u] + 1)
				return false;
			cycles++;
			baseCycles[cycles].push_back(sortEdge(make_pair(v, u)));
			int w = v;
			while(w != u){
				baseCycles[cycles].push_back(sortEdge(make_pair(w, parent[w])));
				w = parent[w];
			}
		}
	}
	
	return true;
}

bool computeXor(int a, int b){
	xorCycles.clear();
	for(int i=0; i<(int)baseCycles[a].size(); i++)
		xorCycles.insert(baseCycles[a][i]);
	for(int i=0; i<(int)baseCycles[b].size(); i++){
		if(xorCycles.find(baseCycles[b][i]) != xorCycles.end())
			xorCycles.erase(baseCycles[b][i]);
		else
			xorCycles.insert(baseCycles[b][i]);
	}
	if((int)xorCycles.size() == 2*(int)baseCycles[a].size())
		return true;
	else if((int)xorCycles.size() == (int)baseCycles[a].size()){
		cycles++;
		return true;
	}
	
	return false;
}

int main(){
	Read();
	if(m == n-1){
		puts("BRAK");
		return 0;
	}
	bool check = Dfs(1);
	if(!check){
		puts("NIE");
		return 0;
	}
	
	int C = cycles;
	for(int i=1; i<=C; i++)
		for(int j=1; j<i; j++){
			check = computeXor(i, j);
			if(!check){
				puts("NIE");
				return 0;
			}
		}
	
	puts("TAK");
	printf("%d %d\n", length, (int)(((LL)2*cycles*length)%MOD));
	
	
	return 0;
}