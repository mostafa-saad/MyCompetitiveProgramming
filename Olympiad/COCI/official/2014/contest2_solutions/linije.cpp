#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int N;
vector<int> E[510], G[1010];
int left[510], right[510];
int visited[510], cookie;
int cnt_x[510], cnt_y[510];

int dfs(int node) {
	if(node == -1) return 1;
	if(visited[node] == cookie) return 0;
	visited[node] = cookie;

	for(int i = 0; i < E[node].size(); ++i)
		if(dfs(left[E[node][i]])) {
			left[E[node][i]] = node;
			right[node] = E[node][i];
			return 1;
		}

	return 0;
}

void matching(void) {
	int ret = 0;
	for(int i = 1; i <= 500; ++i) {
		++cookie;
		if(dfs(i)) ++ret;
	}
}

int main(void) {

	scanf("%d", &N);

	for(int i = 0; i < N; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		++cnt_x[x]; ++cnt_y[y];
		E[x].push_back(y);
	}

	memset(left, -1, sizeof left);
	memset(right, -1, sizeof right);

	matching();

	for(int i = 1; i <= 500; ++i) {
		if(cnt_x[i] > 0 && right[i] == -1) return printf("Mirko\n"), 0;
		if(cnt_y[i] > 0 && left[i] == -1) return printf("Mirko\n"), 0;
	}

	printf("Slavko\n");

	return 0;

}
