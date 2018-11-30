#include<cstdio>
#include<vector>
#include<stack>
#include<set>

using namespace std;

const int MNODES = 200010;
set<int> g[MNODES];
bool visited[MNODES];
stack<pair<int, int> > s;

void delete_edge(int u, int v)
{
	g[u].erase(v);
	g[v].erase(u);
}

void dfs(int v)
{
	while(!g[v].empty())
	{
		int w = *g[v].begin();
		delete_edge(v, w);
		dfs(w);
		s.push(make_pair(v, w));
	}
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);

	for(int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].insert(v);
		g[v].insert(u);
	}

	dfs(1);

	stack<int> c;
	vector<vector<int> > cycles;

	while(!s.empty())
	{
		pair<int, int> e = s.top();
		s.pop();

		if(c.empty())
		{
			c.push(e.first);
			visited[e.first] = true;
		}

		if(visited[e.second])
		{
			cycles.push_back(vector<int>());
			cycles.back().push_back(e.second);

			while(c.top() != e.second)
			{
				cycles.back().push_back(c.top());
				visited[c.top()] = false;
				c.pop();
			}

			c.pop();
		}

		c.push(e.second);
		visited[e.second] = true;
	}

	printf("%d\n", (int)cycles.size());
	for(int i = 0; i < (int)cycles.size(); ++i)
	{
		printf("%d ", (int)cycles[i].size());
		for(int j = 0; j < (int)cycles[i].size(); ++j)	printf("%d ", cycles[i][j]);
		printf("\n");
	}

	return 0;
}
