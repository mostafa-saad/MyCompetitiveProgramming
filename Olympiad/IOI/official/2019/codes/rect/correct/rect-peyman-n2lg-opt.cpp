//In the name of God
//Peyman Jabbarzade Ganje
//Boarder shouldn't be equal with inside
#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> pii;

const int maxn = 3000 + 10, maxx=1e7;
int n,m, fen_t[maxx];
long long ans;
vector<int>vec, nozoli, will_remove;
map<int, int> fp[maxn][maxn];
vector<pii> sp[2][maxn][maxn];

void fen_add(int x,int val)
{
	x++;
	while(x>0){
		fen_t[x]+=val;
		x -= x&(-x);
	}
}

int fen_f(int x)
{
	x++;
	int ret = 0;
	while(x<maxx){
		ret += fen_t[x];
		x += x&(-x);
	}
	return ret;
}

void add_pair(int type, int lvl, int l, int r)
{
	int tmp = 1;
	if(fp[lvl][l].find(r) != fp[lvl][l].end())
		tmp += fp[lvl][l][r];

	if(type == 0) {
		if(r-l-1>0)
			sp[type][lvl+1][r].push_back(pii(r-l-1, tmp));
	}
	else {
		if(r-l-1>0)
			sp[type][r][lvl+1].push_back(pii(tmp, r-l-1));
	}

	fp[lvl+1][l][r] = tmp;
}

void extract_pairs(int type, int lvl)
{
	nozoli.clear();
	for(int i=0;i<vec.size();i++)
	{
		int last=-1;
		while(nozoli.size() && vec[nozoli.back()] < vec[i])
		{
			if(vec[nozoli.back()] > last)
				add_pair(type, lvl, nozoli.back(), i);
			last = vec[nozoli.back()];
			nozoli.pop_back();
		}
		if(nozoli.size()) add_pair(type, lvl, nozoli.back(), i);
		nozoli.push_back(i);
	}
}

long long count_rectangles(vector<vector<int> >a)
{
	n = a.size();
	m = a[0].size();

	for(int i=0;i<n;i++)
	{
		vec.clear();
		for(int j=0;j<m;j++)
			vec.push_back(a[i][j]);
		extract_pairs(0,i);
	}
	for(int i=0;i<=max(n,m);i++)
		for(int j=0;j<=max(n,m);j++)
			fp[i][j].clear();

	for(int j=0;j<m;j++)
	{
		vec.clear();
		for(int i=0;i<n;i++)
			vec.push_back(a[i][j]);
		extract_pairs(1,j);
	}

	for(int i=0;i<=max(n,m);i++)
		for(int j=0;j<=max(n,m);j++)
			if(sp[0][i][j].size() && sp[1][i][j].size())
			{
				sort(sp[0][i][j].begin(), sp[0][i][j].end());
				sort(sp[1][i][j].begin(), sp[1][i][j].end());
				// sp[0].X fix sp[1].X moteghaier
				int p = 0;
				will_remove.clear();
				for(int k=0;k<sp[1][i][j].size();k++)
				{
					while(p<sp[0][i][j].size() && sp[0][i][j][p].X <= sp[1][i][j][k].X)
					{
						fen_add(sp[0][i][j][p].Y, 1);
						will_remove.push_back(sp[0][i][j][p].Y);
						p++;
					}
					ans += fen_f(sp[1][i][j][k].Y);
				}
				for(int k=0;k<will_remove.size();k++)
					fen_add(will_remove[k], -1);
			}
	return ans;
}
