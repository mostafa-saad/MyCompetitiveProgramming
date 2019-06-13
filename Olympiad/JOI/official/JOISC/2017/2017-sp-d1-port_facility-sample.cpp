#include<stdio.h>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
#define SIZE (1<<21)
int toz[SIZE];
class segtree
{
public:
	int seg1[22][SIZE];
	int seg2[22][SIZE];
	int low[SIZE*2],u1[SIZE*2],u2[SIZE*2];
	int x[SIZE * 2];
	int pt;
	void init()
	{
		for(int i=0;i<SIZE;i++)low[i+SIZE]=u1[i+SIZE]=u2[i+SIZE]=i;
		for(int i=SIZE-1;i>=1;i--)low[i]=low[i*2],u1[i]=u1[i*2],u2[i]=u2[i*2];
	}
	void add1(int beg, int end)
	{
		int node = 1;
		int lb = 0, ub = SIZE - 1;
		int dep=0;
		for (;;)
		{
			seg1[dep][u1[node]++]=end;
			if (lb == ub)break;
			node *= 2;
			dep++;
			if (beg <= (lb + ub) / 2)ub = (lb + ub) / 2;
			else lb = (lb + ub) / 2 + 1, node++;
		}
	}
	void add2(int beg,int end)
	{
		int node = 1;
		int lb = 0, ub = SIZE - 1;
		int dep=0;
		for (;;)
		{
			seg2[dep][u2[node]++]=beg;
			if (lb == ub)break;
			node *= 2;
			dep++;
			if (end <= (lb + ub) / 2)ub = (lb + ub) / 2;
			else lb = (lb + ub) / 2 + 1, node++;
		}
	}
	void get(int beg, int end, int node, int lb, int ub, int dep)
	{
		if (end < lb || ub < beg)return;
		if (beg <= lb&&ub <= end)
		{
			for (;;)
			{
				if(low[node]==u1[node])break;
				int z=seg1[dep][u1[node]-1];
				if(z<=end)break;
				x[pt++] = toz[z];
				u1[node]--;
			}
			for (;;)
			{
				if(low[node]==u2[node])break;
				int z=seg2[dep][u2[node]-1];
				if(z>=beg)break;
				x[pt++] = toz[z];
				u2[node]--;
			}
			return;
		}
		get(beg, end, node * 2, lb, (lb + ub) / 2, dep+1);
		get(beg, end, node * 2 + 1, (lb + ub) / 2 + 1, ub,dep+1);
	}
};
segtree tree;
int a[1000000], b[1000000];
int col[2000000];
typedef pair<int, int>pii;
int main()
{
	int num;
	scanf("%d", &num);
	for (int i = 0; i < num; i++)scanf("%d%d", &a[i], &b[i]), a[i]--, b[i]--, toz[a[i]] = toz[b[i]] = i;
	tree.init();
	for(int i=0;i<num+num;i++)if(b[toz[i]]==i)tree.add1(a[toz[i]],b[toz[i]]);
	for(int i=num+num-1;i>=0;i--)if(a[toz[i]]==i)tree.add2(a[toz[i]],b[toz[i]]);
	int ans = 1;
	for (int i = 0; i < num; i++)
	{
		if (col[i] == 0)
		{
			ans = ans * 2 % 1000000007;
			queue<pii>que;
			que.push(make_pair(i, 1));
			for (;;)
			{
				if (que.empty())break;
				pii z = que.front();
				que.pop();
				if (col[z.first] != 0)
				{
					if (col[z.first] != z.second)
					{
						printf("0\n");
						return 0;
					}
					continue;
				}
				col[z.first] = z.second;
				tree.pt = 0;
				tree.get(a[z.first], b[z.first], 1, 0, SIZE - 1, 0);
				for (int j = 0; j < tree.pt; j++)que.push(make_pair(tree.x[j], -z.second));
			}
		}
	}
	vector<int>va, vb;
	for (int i = 0; i < num + num; i++)
	{
		if (a[toz[i]] == i)
		{
			if (col[toz[i]] == 1)va.push_back(toz[i]);
			else vb.push_back(toz[i]);
		}
		else
		{
			if (col[toz[i]] == 1)
			{
				if (va[va.size() - 1] != toz[i])ans = 0;
				else va.pop_back();
			}
			else
			{
				if (vb[vb.size() - 1] != toz[i])ans = 0;
				else vb.pop_back();
			}
		}
	}
	printf("%d\n", ans);
}