#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <utility>
using namespace std;

// full solution
// (author: simon buerger)

void readTree(int n, vector<int>& nodes)
{
	nodes.resize(n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &nodes[i]);
		nodes[i]--;
		if(nodes[i] == -1)
			nodes[i] = i;
	}
}

#define LOGN 17	// will work for n <= 100.000
int n, q;
vector<int> par[LOGN];
vector<vector<int> > g;
vector<int> low;
vector<int> post;
vector<bool> ball;
vector<int> layer;	// root is at 0
int root;
bool cmpLow(int a, int b) { return low[a] < low[b]; }
bool cmpPostInv(int a, int b) { return post[a] > post[b]; }
priority_queue<int, vector<int>, bool(*)(int,int)> empty(cmpPostInv);
vector<int> full;	// not ordered in any sense

void dfsLow(int v)
{
	if(v == root)
		layer[v] = 0;
	else
		layer[v] = 1 + layer[par[0][v]];

	low[v] = v;
	for(int i = 0; i < (int)g[v].size(); ++i)
	{
		int w = g[v][i];
		dfsLow(w);
		low[v] = min(low[v], low[w]);
	}
}

void dfsPost(int v)
{
	static int time = 0;
	for(int i = 0; i < (int)g[v].size(); ++i)
		dfsPost(g[v][i]);
	post[v] = time++;
}

int add()	// return pos
{
	int k = empty.top();
	empty.pop();
	ball[k] = true;
	return k;
}

int remove(int pos)	// return position of actual remove
{
	if(!ball[pos])
		cerr << "ERROR: remove from empty node" << endl;
	//cerr << "remove " << pos;
	for(int level = LOGN-1; level >= 0; --level)
		if(ball[par[level][pos]])
			pos = par[level][pos];

	ball[pos] = false;
	empty.push(pos);
	//cerr << " actual = " << pos << endl;
	return pos;
}

int main(int argc, char** argv)
{
	scanf("%d %d", &n, &q);

	g.resize(n);
	for(int i = 0; i < LOGN; ++i)
		par[i].resize(n);
	ball.resize(n, false);
	low.resize(n);
	post.resize(n);
	layer.resize(n);

	readTree(n, par[0]);

	for(int i = 0; i < n; ++i)
		if(par[0][i] == i)
			root = i;
		else
			g[par[0][i]].push_back(i);

	par[0][root] = root;
	for(int level = 1; level < LOGN; ++level)
		for(int i = 0; i < n; ++i)
			par[level][i] = par[level-1][par[level-1][i]];

	dfsLow(root);
	for(int i = 0; i < n; ++i)
		sort(g[i].begin(), g[i].end(), cmpLow);

	dfsPost(root);
	for(int i = 0; i < n; ++i)
		empty.push(i);

	for(int i = 0; i < q; ++i)
	{
		int t, k;
		scanf("%d %d", &t, &k);

		if(t == 1)	// add k balls
		{
			for(int j = 0; j < k; ++j)
			{
				int pos = add();
				if(j+1 == k)
					printf("%d\n", pos+1);
			}
		}
		else if(t == 2)	// remove one ball from position k
		{
			--k;
			int actual = remove(k);
			printf("%d\n", layer[k]-layer[actual]);
		}
		else cerr << "ERROR: invalid t" << endl;
	}
}
