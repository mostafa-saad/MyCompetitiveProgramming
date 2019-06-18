#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n, m;
vector<int> graph[1005];

struct edg{int s,e,x;};
vector<edg> non_tree;
vector<edg> edges[1005];
vector<int> precomp[1005];

int dep[1005], par[1005][10];
int dfn[1005], rdfn[1005], size[1005], piv;

void dfs(int x, int pa){
	dfn[x] = ++piv;
	rdfn[dfn[x]] = x;
	par[x][0] = pa;
	size[x] = 1;
	for(int i=1; i<10; i++){
		par[x][i] = par[par[x][i-1]][i-1];
	}
	for(auto &i : graph[x]){
		if(i == pa) continue;
		dep[i] = dep[x] + 1;
		dfs(i, x);
		size[x] += size[i];
	}
}

int lca(int x, int y){
	if(dep[x] < dep[y]){
		swap(x,y);
	}
	int dx = dep[x] - dep[y];
	for(int i=0; i<10; i++){
		if((dx >> i) & 1) x = par[x][i];
	}
	for(int i=9; i>=0; i--){
		if(par[x][i] != par[y][i]){
			x = par[x][i];
			y = par[y][i];
		}
	}
	if(x != y) return par[x][0];
	return x;
}

int dp[1005][1<<10];

bool inSubtree(int root, int eval){
	return dfn[root] <= dfn[eval] && dfn[eval] <= dfn[root] + size[root] - 1;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s,e,x;
		scanf("%d %d %d",&s,&e,&x);
		if(x == 0){
			graph[s].push_back(e);
			graph[e].push_back(s);
		}
		else{
			non_tree.push_back({s,e,x});
		}
	}
	dfs(1,0);
	int ret = 0;
	for(auto &i : non_tree){
		ret += i.x;
		int l = lca(i.s,i.e);
		int d = dep[i.s] + dep[i.e] - 2 * dep[l];
		if(d%2 == 0){
			edges[l].push_back({i.s,i.e,i.x});
		}
	}
	for(int i=n; i>=1; i--){
		int pos = rdfn[i];
		for(auto &j : edges[pos]){
			int ret = 0;
			int p = j.s, son = -1;
			while(pos != p){
				int msk = (1<<graph[p].size()) - 1;
				for(int j=0; j<graph[p].size(); j++){
					if(inSubtree(graph[p][j], son)) continue;
					msk ^= (1<<j);
				}
				ret += dp[p][msk];
				son = p;
				p = par[p][0];
			}
			p = j.e, son = -1;
			while(pos != p){
				int msk = (1<<graph[p].size()) - 1;
				for(int j=0; j<graph[p].size(); j++){
					if(inSubtree(graph[p][j], son)) continue;
					msk ^= (1<<j);
				}
				ret += dp[p][msk];
				son = p;
				p = par[p][0];
			}
			precomp[pos].push_back(ret);
		}
		int bit = (1<<graph[pos].size()) - 1;
		for(int j=bit; j>=0; j--){
			for(int k=0; k<graph[pos].size(); k++){	
				if(graph[pos][k] == par[pos][0]) continue;
				if(((j >> k) & 1) == 0) dp[pos][j] += dp[graph[pos][k]][0]; 
			}
			int pt = 0;
			for(auto &k : edges[pos]){
				int st = 0, ed = dfn[pos];
				int msk = j;
				bool cant = 0;
				for(int l=0; l<graph[pos].size(); l++){
					if(graph[pos][l] == par[pos][0]) continue;
					if(inSubtree(graph[pos][l], k.s)){
						if(msk & (1<<l)){
							cant = 1;
							break;
						}
						msk |= (1<<l);
					}
					if(inSubtree(graph[pos][l], k.e)){
						if(msk & (1<<l)){
							cant = 1;
							break;
						}
						msk |= (1<<l);
					}
				}
				pt++;
				if(cant) continue;
				dp[pos][j] = max(dp[pos][j], k.x + dp[pos][msk] + precomp[pos][pt-1]);
			}
		}
	}
	printf("%d",ret - dp[1][0]);
}

