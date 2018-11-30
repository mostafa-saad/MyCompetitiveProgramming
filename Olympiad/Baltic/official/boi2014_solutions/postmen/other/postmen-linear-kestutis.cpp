#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
const int MaxN = 1000010,
	  	  MaxM = 1000010;

int E[MaxN][3];
vector<int> k[MaxN];
int pr[MaxN] = {0};

int N, M, a, b;


bool visited[MaxN] = {0};
vector<int> path;
vector< vector<int> > ANS;

int RET = -1;

int getU (int i, int v) {
	return (v == E[i][0]) ? E[i][1] : E[i][0];
}


void dfs (int v, int p = -1) {
	//printf("%d, ksize= %d!\n", v, k[v].size());
	if (visited[v]) {
		RET = v;
		path.push_back(v);
	}else {
		visited[v] = true;
		for (; pr[v] < k[v].size(); pr[v]++) { 
			//printf("?\n");
			int i = pr[v],
				u = getU(k[v][i], v);
			//printf("%d->%d\n", i, u);
			if (E[k[v][i]][2] == false && u != p) {
				//path.push_back(v);
				dfs(u, v);
				E[k[v][i]][2] = true;
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
		scanf("%d%d", &E[i][0], &E[i][1]);
		E[i][2] = false;
		k[E[i][0]].push_back(i);
		k[E[i][1]].push_back(i);
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
