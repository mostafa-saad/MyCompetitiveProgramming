#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<int,int>pii;
#define SIZE (1<<21)
#define LOG 21
class unionfind
{
public:
	int par[SIZE * 2];
	int ran[SIZE * 2];
	void init()
	{
		for (int i = 0; i<SIZE * 2; i++)
		{
			par[i] = i;
			ran[i] = 0;
		}
	}
	int find(int a)
	{
		if (a == par[a])return a;
		else return par[a] = find(par[a]);
	}
	void unite(int a, int b)
	{
		//printf("%d %d\n", a, b);
		a = find(a);
		b = find(b);
		if (a == b)return;
		if (ran[a]>ran[b])
		{
			par[b] = a;
		}
		else
		{
			par[a] = b;
		}
		if (ran[a] == ran[b])ran[b]++;
	}
};
unionfind uf;
void adde(int a, int b, bool f)
{
	if (f)uf.unite(a * 2, b * 2), uf.unite(a * 2 + 1, b * 2 + 1);
	else uf.unite(a * 2, b * 2 + 1), uf.unite(a * 2 + 1, b * 2);
}
class segtree
{
public:
	vector<pii>seg[1 << (LOG + 1)];
	bool isok;
	void init()
	{
		isok = true;
		for (int i = 0; i < 1 << (LOG + 1); i++)seg[i].clear();
	}
	void add(int beg, int end)
	{
		int node = 1;
		int lb = 0, ub = (1 << LOG) - 1;
		for (;;)
		{
			int m = (lb + ub) / 2;
			if (end <= m)ub = m, node = node * 2;
			else if (m + 1 <= beg)lb = m + 1, node = node * 2 + 1;
			else
			{
				seg[node].push_back(make_pair(beg, end));
				break;
			}
		}
	}
	void solve1(int node, int lb, int ub)
	{
		sort(seg[node].begin(), seg[node].end());
		vector<pii>a, b;
		int mini = 1000000000;
		for (int i = 0; i < seg[node].size(); i++)
		{
			if (mini > seg[node][i].second)
			{
				mini = seg[node][i].second;
				a.push_back(seg[node][i]);
			}
			else b.push_back(seg[node][i]);
		}
		for (int i = 1; i < b.size(); i++)if (b[i - 1].second < b[i].second)isok = false;
		int pt = 0;
		for (int i = 0; i < a.size(); i++)
		{
			for (;;)
			{
				if (pt == b.size())break;
				if (a[i].second > b[pt].second)break;
				if (a[i].first < b[pt].first)adde(a[i].first, b[pt].first, false);
				pt++;
			}
			if (pt != 0)pt--;
		}
	}
	int idx[SIZE], imos[SIZE];
	void solve2(int node, int lb, int ub)
	{
		fill(idx, idx + ub - lb + 1, -1);
		fill(imos, imos + seg[node].size() + 1, 0);
		for (int i = 0; i < seg[node].size(); i++)idx[seg[node][i].first - lb] = i;
		for (int i = 1; i < ub - lb + 1; i++)if (idx[i] == -1)idx[i] = idx[i - 1];
		for (int i = 0; i < seg[node * 2].size(); i++)if (idx[seg[node * 2][i].first - lb] < idx[seg[node * 2][i].second - lb])imos[idx[seg[node * 2][i].first - lb] + 1]++, imos[idx[seg[node * 2][i].second - lb]]--;
		for (int i = 0; i < seg[node * 2].size(); i++)if (idx[seg[node * 2][i].first - lb] < idx[seg[node * 2][i].second - lb])adde(seg[node * 2][i].first, seg[node][idx[seg[node * 2][i].second - lb]].first, false);
		for (int i = 1; i <= seg[node].size(); i++)imos[i] += imos[i - 1];
		for (int i = 0; i<int(seg[node].size()) - 1; i++)if (imos[i])adde(seg[node][i].first, seg[node][i + 1].first, true);
	}
	void solve3(int node, int lb, int ub)
	{
		for (int i = 0; i < seg[node].size(); i++)swap(seg[node][i].first, seg[node][i].second);
		sort(seg[node].begin(), seg[node].end());
		for (int i = 0; i < seg[node].size(); i++)swap(seg[node][i].first, seg[node][i].second);
		fill(idx, idx + ub - lb + 1, -1);
		fill(imos, imos + seg[node].size() + 1, 0);
		for (int i = 0; i < seg[node].size(); i++)idx[seg[node][i].second - lb] = i;
		for (int i = 1; i < ub - lb + 1; i++)if (idx[i] == -1)idx[i] = idx[i - 1];
		for (int i = 0; i < seg[node * 2 + 1].size(); i++)if (idx[seg[node * 2 + 1][i].first - lb] < idx[seg[node * 2 + 1][i].second - lb])imos[idx[seg[node * 2 + 1][i].first - lb] + 1]++, imos[idx[seg[node * 2 + 1][i].second - lb]]--;
		for (int i = 0; i < seg[node * 2 + 1].size(); i++)if (idx[seg[node * 2 + 1][i].first - lb] < idx[seg[node * 2 + 1][i].second - lb])adde(seg[node * 2 + 1][i].first, seg[node][idx[seg[node * 2 + 1][i].second - lb]].first, false);
		for (int i = 1; i <= seg[node].size(); i++)imos[i] += imos[i - 1];
		for (int i = 0; i<int(seg[node].size()) - 1; i++)if (imos[i])adde(seg[node][i].first, seg[node][i + 1].first, true);
	}
	void calc()
	{
		for (int i = LOG - 1; i >= 0; i--)
		{
			for (int j = 0; j < (1 << i); j++)
			{
				int node = (1 << i) + j;
				solve1(node, j << (LOG - i), ((j + 1) << (LOG - i)) - 1);
				solve2(node, j << (LOG - i), (j << (LOG - i)) + (1 << (LOG - 1 - i)) - 1);
				solve3(node, (j << (LOG - i)) + (1 << (LOG - 1 - i)), ((j + 1) << (LOG - i)) - 1);
				for (int k = 0; k < seg[node * 2].size(); k++)seg[node].push_back(seg[node * 2][k]);
				for (int k = 0; k < seg[node * 2 + 1].size(); k++)seg[node].push_back(seg[node * 2 + 1][k]);
			}
		}
	}
};
segtree tree;
int main()
{
	int num;
	scanf("%d",&num);
	tree.init();
	vector<pii>vec;
	for(int i=0;i<num;i++)
	{
		int za,zb;
		scanf("%d%d",&za,&zb);
		za--,zb--;
		vec.push_back(make_pair(za,zb));
		tree.add(za, zb);
	}
	uf.init();
	tree.calc();
	for (int i = 0; i < num; i++)if (uf.find(vec[i].first * 2) == uf.find(vec[i].first * 2 + 1))tree.isok = false;
	int cnt = 0;
	for (int i = 0; i < num; i++)if (uf.find(vec[i].first * 2) == vec[i].first * 2)cnt++;
	for (int i = 0; i < num; i++)if (uf.find(vec[i].first * 2 + 1) == vec[i].first * 2 + 1)cnt++;
	int ans=tree.isok;
	for (int i = 0; i < cnt / 2; i++)ans = ans * 2 % 1000000007;
	printf("%d\n",ans);
}