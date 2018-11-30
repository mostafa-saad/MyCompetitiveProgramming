#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 500000;
const int MAX_M = 500000;

int n, m;

vector<int> neigh[MAX_N];

pair<int, int> edges[MAX_N];
bool eUsed[MAX_M];

bool vVisited[MAX_N];
int eVisited[MAX_N];
int back[MAX_N];

void visit(int nr) {
	while (true) {
		int eNr = neigh[nr][eVisited[nr]];
		while (eVisited[nr] < neigh[nr].size() && eUsed[eNr])
			eNr = neigh[nr][++eVisited[nr]];
		if (eVisited[nr] == neigh[nr].size())
			return;
		vVisited[nr] = true;
		eUsed[eNr] = true;

		int next = edges[eNr].first == nr ? edges[eNr].second : edges[eNr].first;
		if (vVisited[next]) {
			//found cycle
			int now = nr;
			while (now != next) {
				vVisited[now] = false;
				printf("%d ", now+1);
				now = back[now];
			}
			printf("%d\n", now+1);
		}
		else {
			back[next] = nr;
		}
		nr = next;
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; ++i) {
		scanf("%d %d", &edges[i].first, &edges[i].second);
		edges[i].first--;
		edges[i].second--;
		neigh[edges[i].first].push_back(i);
		neigh[edges[i].second].push_back(i);
	}
	for (int i = 0; i < n; ++i)
		visit(i);
	return 0;
}
