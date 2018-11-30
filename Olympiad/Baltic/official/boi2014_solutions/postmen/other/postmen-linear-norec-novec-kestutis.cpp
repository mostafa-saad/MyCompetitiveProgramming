#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
const int MaxN = 1000010,
	  	  MaxM = 2*1000010;

int E[MaxM][3];
int pr[MaxN] = {0};

int P[MaxN], tmp[MaxN] = {0}, C[MaxN];
int k[MaxM];

int N, M, a, b;


int ANS_cc[MaxM];
int ANS_C = 0;
int ANS_T = 0;
int ANS[2*MaxM];

bool visited[MaxN] = {0};
vector<int> path;
//vector< vector<int> > ANS;

int RET = -1;

int getU (int i, int v) {
	return (v == E[i][0]) ? E[i][1] : E[i][0];
}


inline void dfs(int v) {
	path.clear();
	path.push_back(v);	
	while (v != -1) {
		//printf("V = %d!!!\n", v);
		visited[v] = true;
		int newv = -1;
		for (; pr[v] < C[v]; pr[v]++) {
			int i = pr[v],
				u = getU(k[P[v]+i], v);
				if (E[k[P[v]+i]][2] == false) {
					E[k[P[v]+i]][2] = true;
					if (visited[u]) {
						newv = u;
						while (path.back() != u) {
						        
							ANS[ANS_T++] = path.back();
							ANS_cc[ANS_C]++;
							visited[path.back()] = false;
							path.pop_back();
						} 
						ANS[ANS_T++] = path.back();
						ANS_cc[ANS_C]++;
						ANS_C++;
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
	for (int i = 0; i < path.size(); i++)
		visited[path[i]] = false;
}


int main() {
	path.reserve(MaxN + 100);	
	scanf("%d%d\n", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &E[i][0], &E[i][1]);
		E[i][2] = false;
		C[E[i][0]]++;
		C[E[i][1]]++;
	}
    
	P[1] = 0;
	for (int i = 2; i <= N; i++) {
		P[i] = P[i-1] + C[i-1];
	}
	for (int i = 0; i < M; i++) {
		//printf("E: %d %d\n", E[i][0], E[i][1]);
		k[P[E[i][0]] + tmp[E[i][0]]] = i;
		k[P[E[i][1]] + tmp[E[i][1]]] = i;
		tmp[E[i][0]]++;
		tmp[E[i][1]]++;
	}
	for (int i = 1; i <= N; i++) {
		dfs(i);
		
		}
	ANS_T = 0;
	
	//printf("%d\n", ANS_C);
	for(int i = 0; i < ANS_C; i++) {
		//printf("%d", ANS_cc[i]);
		for (int j = 0; j < ANS_cc[i]; j++)
			printf(" %d", ANS[ANS_T++]);
		printf("\n");
	}
			
	return 0;
}
