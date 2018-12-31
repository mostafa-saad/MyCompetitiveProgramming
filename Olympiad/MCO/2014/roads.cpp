#include <cstdio>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int N, E, dist[400005]; //Potential trap: never double declared space
vector<int> adjList[400005];
queue<int> q;
int main () {
	scanf("%d%d", &N, &E);
	for (int i = 0, A, B, V; i < E; ++i) {
		scanf("%d%d%d", &A, &B, &V);
		adjList[A*2+V].push_back(B*2+(1-V));  //X*2 means X0, X*2+1 means X1
		adjList[B*2+V].push_back(A*2+(1-V)); 
	}
	memset(dist, -1, sizeof(dist));
	q.push(0), q.push(1); //Multi source
	dist[0] = dist[1] = 0;
	/* standard BFS */
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (vector<int>::iterator it = adjList[x].begin(); it != adjList[x].end(); ++it) {
			if (dist[*it] != -1) continue;
			dist[*it] = dist[x] + 1;
			q.push(*it);
		}
	}
	
	//Checking both sinks
	if (dist[(N-1)*2] == -1 && dist[(N-1)*2+1] != -1) printf("%d\n", dist[(N-1)*2+1]);
	else if (dist[(N-1)*2] != -1 && dist[(N-1)*2+1] == -1) printf("%d\n", dist[(N-1)*2]);
	else printf("%d\n", min(dist[(N-1)*2], dist[(N-1)*2+1]));
}
