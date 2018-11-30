#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
const int MaxN = 100010,
	  	  MaxM = 400010;
typedef pair<int, int> pii;

pii ppair(int a, int b) {
	return make_pair(min(a, b), max(a, b));
}

vector<int> k[MaxN];
int pr[MaxN] = {0};
set <pii> S;

int N, M, a, b;


bool visited[MaxN] = {false};
vector<int> path;
vector< vector<int> > ANS;

int RET = -1;

void dfs (int v, int p = -1) {
	//printf("%d!\n", v);
	if (visited[v]) {
		RET = v;
		path.push_back(v);
	}else {
		visited[v] = true;
		for (; pr[v] < k[v].size(); pr[v]++) { 
			int i = pr[v];
			//printf("%d->%d\n", pr[v], k[v][pr[v]]);
			if (S.find(ppair(v, k[v][i])) == S.end() && k[v][i] != p) {
				//path.push_back(v);
				dfs(k[v][i], v);
				S.insert(ppair(v, k[v][i]));
				//Mat[v][k[v][i]] = Mat[k[v][i]][v] = false;
				if (v != RET) {
					path.push_back(v);
					break;
				} else {
					ANS.push_back(path);
					path.clear();					
				}
			}
		}
		visited[v] = false;	
	}	

}


int main() {
	
	scanf("%d%d\n", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &a, &b);
		k[a].push_back(b);
		k[b].push_back(a);
	}
	
	for (int i = 1; i <= N; i++)
		dfs(i);
	
	//printf("%d\n", ANS.size());
	for (int i = 0; i < ANS.size(); i++) {
		//printf("%d", ANS[i].size());
		for (int j = 0; j < ANS[i].size(); j++)
			printf(" %d", ANS[i][j]);
		printf("\n");

	}
	return 0;
}
