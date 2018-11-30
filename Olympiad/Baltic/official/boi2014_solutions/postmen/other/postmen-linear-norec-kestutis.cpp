#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
const int MaxN = 1000010,
	  	  MaxM = 100010;

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


void dfs(int v) {
	visited[v] = true;
	path.push_back(v);	
	while (v != -1) {
		//printf("V = %d!!!\n", v);
		visited[v] = true;
		int newv = -1;
		for (; pr[v] < k[v].size(); pr[v]++) {
			int i = pr[v],
				u = getU(k[v][i], v);
				if (E[k[v][i]][2] == false) {
					//printf("  U = %d\n", u);
					E[k[v][i]][2] = true;
					if (visited[u]) {
						newv = u;
						ANS.push_back(vector<int>());
						while (path.back() != u) {
							ANS[ANS.size()-1].push_back(path.back());
							visited[path.back()] = false;
							path.pop_back();
						} 
						ANS[ANS.size()-1].push_back(u);
					}else {
						newv = u;
						path.push_back(u);
					}
					break;
				}
		}
		v =newv;
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
	
	printf("%d\n", ANS.size());
	for (int i = 0; i < ANS.size(); i++) {
		printf("%d", ANS[i].size());
		for (int j = 0; j < ANS[i].size(); j++)
			printf(" %d", ANS[i][j]);
		printf("\n");
	}
	return 0;
}
