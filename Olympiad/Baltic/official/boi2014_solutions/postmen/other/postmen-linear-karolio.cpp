#include <cstdio>
#include <vector>
#include <algorithm>
#pragma comment(linker, "/STACK:16000000")
using namespace std;

typedef pair <int, int> ii;

const int Maxn = 1000005;
const int Maxm = 1000005;

int n, m;
vector <ii> neigh[Maxn];
bool er[Maxm];
int seq[Maxm], slen;
int S[Maxn], Slen;
bool taken[Maxn];

void Traverse(int v)
{
	while (1) {
		while (!neigh[v].empty() && er[neigh[v].back().second]) neigh[v].pop_back();
		if (neigh[v].empty()) return;
		ii u = neigh[v].back();
		er[u.second] = true; Traverse(u.first); seq[slen--] = v;
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int a, b; scanf("%d %d", &a, &b);
		neigh[a].push_back(ii(b, i));
		neigh[b].push_back(ii(a, i));
	}
	slen = m; seq[slen--] = 1;
	Traverse(1);
	for (int i = 0; i <= m; i++) {
		if (taken[seq[i]]) {
			int tof = seq[i];
			int pr = seq[i];
			do {
				printf("%d ", pr);
				pr = S[--Slen]; taken[pr] = false;
			} while (pr != tof);
			printf("\n");
		}
		S[Slen++] = seq[i]; taken[seq[i]] = true;
	}
	return 0;
}