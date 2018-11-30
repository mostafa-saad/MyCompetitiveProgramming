// Kamil Debowski
// AC solution

#include<cstdio>
#include<vector>
#include<algorithm>
#include<assert.h>
using namespace std;
const int nax = 5e5 + 5;

vector<int> w[nax];
int leaves[nax];

void dfs_first(int a, int father) {
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(b == father) {
			w[a].erase(w[a].begin() + i);
			--i;
		}
		else {
			dfs_first(b, a);
			leaves[a] += leaves[b];
		}
	}
	if(w[a].empty()) leaves[a] = 1;
}

void give_leaves(int a, vector<int> & vec) {
	for(auto b : w[a])
		give_leaves(b, vec);
	if(w[a].empty()) // leaf
		vec.push_back(a);
}

vector<int> sets[3];
int half;
bool cmp(const vector<int> & a, const vector<int> & b) { return a.size() > b.size(); }

void dfs(int a) {
	int big = 0;
	for(auto b : w[a])
		if(leaves[b] > leaves[big])
			big = b;
	if(leaves[big] > half) {
		for(auto b : w[a])
			if(b != big)
				give_leaves(b, sets[0]);
		dfs(big);
		return;
	}
	for(auto b : w[a])
		for(int i = 0; i < 3; ++i)
			if(leaves[b] + (int) sets[i].size() <= half) {
				give_leaves(b, sets[i]);
				break;
			}
	for(int i = 0; i < half; ++i) {
		sort(sets, sets + 3, cmp);
		printf("%d %d\n", sets[0].back(), sets[1].back());
		sets[0].pop_back();
		sets[1].pop_back();
	}
	sort(sets, sets + 3, cmp);
	if(!sets[0].empty())
		printf("%d %d\n", a, sets[0].back());
}

int main()
{
	int n;
	scanf("%d", &n);
	if(n == 1) {
		puts("0");
		return 0;
	}
	if(n == 2) {
		puts("1");
		puts("1 2");
		return 0;
	}
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		w[a].push_back(b);
		w[b].push_back(a);
	}
	int root = 1;
	while((int) w[root].size() < 2) root++;
	dfs_first(root, 0);
	half = leaves[root] / 2;
	printf("%d\n", (leaves[root] + 1) / 2);
	dfs(root);
	return 0;
}
