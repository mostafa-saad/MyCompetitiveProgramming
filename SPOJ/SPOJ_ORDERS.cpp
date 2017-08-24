//Coach wahab sol: 1945048
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<bitset>
#include<cstring>
#include<climits>
#include<deque>
#include<utility>
#include <complex>
#include <numeric>
#include <functional>
#include <stack>
#include <iomanip>

using namespace std;

#define rep(i,n) for(int  i=0;i<(int)(n);++i)
long double ZERO = 0;
const long double INF = 1 / ZERO, EPSILON = 1e-12;
#define all(c) (c).begin(),(c).end()
#define rep2(i,a,b) for(int i=(a);i<=((int)b);++i)
#define foreach(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();++it)

#define sz(v) ((int)((v).size()))

#define rrep(i,n) for(int  i=((int)n)-1;i>=0;--i)
#define rall(c) (c).rbegin(),(c).rend()
#define rrep2(i,a,b) for(int i=(a);i>=((int)b);--i)
#define rforeach(it,c) for(__typeof((c).rbegin()) it=(c).rbegin();it!=(c).rend();++it)
#define rep2d(i, j, v) rep(i, sz(v)) rep(j, sz(v[i]))
#define foreach2d(i, j, v) foreach(i,v) foreach(j,*i)
struct BIT
{
	vector<int> freq;
	int size;

	void resize(int nsize)
	{
		freq.clear();
		size = 1 << int(ceil(log2(nsize)));
		freq.resize(size);
	}

	int getCum(int ind) const
	{
		ind++;
		int ret = 0;
		while (ind)
		{
			ret += freq[ind - 1];
			ind -= ind & -ind;
		}
		return ret;
	}

	void addFreq(int ind, int v)
	{
		ind++;
		while (ind <= size)
		{
			freq[ind - 1] += v;
			ind += ind & -ind;
		}
	}

	string print(int s) const
	{
		stringstream ss;
		char *sep = "";
		for (int i = 0; i < s; ++i)
		{
			ss << sep << "(" << i << "," << getCum(i) << ")";
			sep = ",";
		}
		return ss.str();
	}

	int lower_bound(int tf)
	{
		int m = size >> 1;
		int s = 0;
		while (m)
		{
			if (tf > freq[s + m - 1])
			{
				s += m;
				tf -= freq[s - 1];
			}
			m >>= 1;
		}
		return s;
	}
};

int arr[200000];
int main()
{
#ifndef ONLINE_JUDGE
	freopen("1.in", "rt", stdin);
	//freopen("1.out", "wt", stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		BIT b;
		b.resize(n+1);
		rep(i,n)
			b.addFreq(i+1,1);
		rep(i,n)
			scanf("%d",&arr[i]);
		char *sep="";
		rrep(i,n)
		{
			int x;
			x=b.lower_bound(i-arr[i]+1);
			arr[i]=x;

			b.addFreq(x,-1);
		}

		rep(i,n)
			printf("%s%d",sep,arr[i]),sep=" ";
		printf("\n");
	}
	return 0;
}
