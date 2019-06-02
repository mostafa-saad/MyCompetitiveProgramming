/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Niebanalne podroze                                 *
 *   Autor:                Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;

const int MAXN = 500000;
const int MOD = 1000000007;

int n, m;
vector<int> graph[MAXN + 3], biconn[MAXN + 3];
vector< pair<int,int> > edges;
int preorder[MAXN + 3], low[MAXN + 3], deg[MAXN + 3], dist[MAXN + 3];
int cycles, length, T;
stack< pair<int,int> > S;
queue<int> Q;
bool vis[MAXN + 3];

void Read(){
	scanf("%d %d", &n, &m);
	for(int i=0; i<m; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}

bool Bfs(int s, int t){
	vis[s] = true;
	Q.push(s);
	int d = 0;
	
	while(!Q.empty()){
		int v = Q.front();
		Q.pop();
		
		for(int i=0; i<(int)biconn[v].size(); i++){
			int u = biconn[v][i];
			if(!vis[u]){
				vis[u] = true;
				dist[u] = dist[v] + 1;
				Q.push(u);
				if(u != t)
					d = max(d, dist[u]);
			}
		}
	}
	
	if(dist[t] <= d)
		return false;
	return true;
}

bool Check(){
	if((int)edges.size() == 1)
		return true;
	
	vector<int> fine;
	
	for(int i=0; i<(int)edges.size(); i++){
		int a = edges[i].first, b = edges[i].second;
		biconn[a].push_back(b);
		biconn[b].push_back(a);
		deg[a]++;
		deg[b]++;
		
		if(deg[a] == 3)
			fine.push_back(a);
		if(deg[b] == 3)
			fine.push_back(b);
		if((int)fine.size() > 2)
			return false;
	}
	
	if(fine.size() == 0){
		if(length == 0)
			length = (int)edges.size();
		if(length != (int)edges.size())
			return false;
		cycles = (cycles+1)%MOD;
		
		return true;
	}
	
	if(fine.size() != 2)
		return false;
	
	int x = fine[0], y = fine[1];
	if(deg[x] != deg[y])
		return false;
	
	bool esc = Bfs(x, y);
	if(esc == false)
		return false;
	
	if(length == 0)
		length = 2*dist[y];
	if(2*dist[y] != length)
		return false;
	
	cycles = (int)(((LL)cycles + ((LL)deg[y]*(deg[y] - 1))/2ll)%MOD); 
	
	return true;
}

void Clean(){
	for(int i=0; i<(int)edges.size(); i++){
		int a = edges[i].first, b = edges[i].second;
		biconn[a].clear();
		biconn[b].clear();
		deg[a] = deg[b] = 0;
		vis[a] = vis[b] = false;
		dist[a] = dist[b] = 0;
	}
	
	edges.clear();
}

bool Dfs(int v, int parent){
	preorder[v] = ++T;
	low[v] = preorder[v];
	bool esc;
	
	for(int i=0; i<(int)graph[v].size(); i++){
		int u = graph[v][i];
		if(u == parent) continue;
		
		if(preorder[u] == 0){
			S.push(make_pair(v, u));
			esc = Dfs(u, v);
			if(esc == false)
				return false;
			low[v] = min(low[v], low[u]);
			pair<int,int> e;
			if(low[u] >= preorder[v]){
				do{
					e = S.top();
					S.pop();
					edges.push_back(e);
				}while(e != make_pair(u,v) && e != make_pair(v, u));
				esc = Check();
				if(esc == false)
					return false;
				Clean();
			}
		}
		else if(preorder[u] < preorder[v]){
			S.push(make_pair(v,u));
			low[v] = min(low[v], preorder[u]);
		}
	}
	
	return true;
}

int main(){
	Read();
	if(m == n-1){
		puts("BRAK");
		return 0;
	}
	bool check = Dfs(1, 0);
	if(check){
		puts("TAK");
		printf("%d %d\n", length, (int)(((LL)2*cycles*length)%MOD));
	}
	else
		puts("NIE");
	
	
	return 0;
}