#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
const int MaxN = 500010,
	  	  MaxM = 2*500010;


int E[MaxM][3];
int pr[MaxN] = {0};

int P[MaxN], tmp[MaxN] = {0}, C[MaxN];
int k[MaxM];

int N, M, a, b;

bool visited[MaxN] = {0};
vector<int> path;

int newv = -1, u;

int getU (int i, int v) {
	return (v == E[i][0]) ? E[i][1] : E[i][0];
}


void dfs(int v) {
	path.clear();
	path.push_back(v);	
	while (v != -1) {
		//printf("V = %d!!!\n", v);
		visited[v] = true;
		newv = -1;
		for (; pr[v] < C[v]; pr[v]++) {
			int i = k[P[v] + pr[v]];
				if (E[i][2] == false) {
					u = getU(i, v);
					E[i][2] = true;
					if (visited[u]) {
						newv = u;
						while (path.back() != u) {
						       	printf("%d ", path.back());
							visited[path.back()] = false;
							path.pop_back();
						}
						printf("%d\n", path.back());
					}else {
						newv = u;
						path.push_back(u);
					}
					break;
				}
		}
		if (newv == -1 and path.size() > 1) {
			newv = path.back();
			path.pop_back();
		}
		v =newv;
	}
	visited[path[0]] = false;
	//for (int i = 0; i < path.size(); i++)
	//	visited[path[i]] = false;
}



int main() {
	path.reserve(MaxN);	
	scanf("%d%d\n", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &E[i][0], &E[i][1]);
		C[E[i][0]]++;
		C[E[i][1]]++;
	}
    
	P[1] = 0;
	for (int i = 2; i <= N; i++) {
		P[i] = P[i-1] + C[i-1];
	}
	for (int i = 0; i < M; i++) {
		a = E[i][0]; b = E[i][1];
		k[P[a] + tmp[a]] = i;
		k[P[b] + tmp[b]] = i;
		tmp[a]++;
		tmp[b]++;
	}
	for (int i = 1; i <= N; i++) {
		dfs(i);
		
		}
	return 0;
}
