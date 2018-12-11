/*
 * Author: Gyeonggeun Kim(kriii)
 * Time Complexity: O(N^2)
 */
#include <stdio.h>
#include <vector>
using namespace std;

const long long dec_cost = 1, inc_cost = 1;

struct envelope
{
	envelope(long long s, long long w)
	{
		slope = s; width = w;
	}
	long long slope, width;
};

struct conv_func
{
	conv_func(){
		base_cost = 0;
		func.clear();
		func.push_back(envelope(1e18,-1));
	}
	long long base_cost;
	vector<envelope> func;

	void append(long long width)
	{
		base_cost += width * dec_cost;

		vector<envelope> new_func;
		int i = 0;
		while (func[i].slope < -dec_cost) new_func.push_back(func[i++]);

		if (func[i].slope == -dec_cost) func[i].width += width;
		else new_func.push_back(envelope(-dec_cost,width));
		while (func[i].slope < inc_cost) new_func.push_back(func[i++]);
		new_func.push_back(envelope(inc_cost,-1));
		func = new_func;
	}

	conv_func operator +(conv_func b){
		auto &a = (*this);
		conv_func ret;
		auto &func = ret.func;
		func.clear();
		ret.base_cost = a.base_cost + b.base_cost;

		long long ax = 0, bx = 0;
		int i = 0, j = 0;
		bool stop = 0;

		while (!stop){
			auto &p = a.func[i], &q = b.func[j];
			envelope next_env(p.slope+q.slope,-1);
			long long next_ax = ax + p.width;
			long long next_bx = bx + q.width;
			long long prev_x = max(ax,bx);
			if (p.width == -1 && q.width == -1) stop = 1;
			else if (q.width == -1){
				next_env.width = next_ax - prev_x;
				i++, ax = next_ax;
			}
			else if (p.width == -1){
				next_env.width = next_bx - prev_x;
				j++, bx = next_bx;
			}
			else{
				long long next_x = min(next_ax,next_bx);
				next_env.width = next_x - prev_x;
				if (next_x == next_ax) i++, ax = next_ax;
				if (next_x == next_bx) j++, bx = next_bx;
			}

			func.push_back(next_env);
		}

		return ret;
	}
};

int N,M,V;
vector<pair<int, int> > G[100010];

conv_func dfs(int x)
{
	conv_func ret;
	for (auto p : G[x]){
		int y = p.first, c = p.second;
		auto chd = dfs(y);
		chd.append(c);
		if (ret.func.size() == 1) ret = chd;
		else ret = ret + chd;
	}
	return ret; 
}

int main()
{
	scanf ("%d %d",&N,&M);
	V = N + M;

	for (int i=2;i<=V;i++){
		int x,c; scanf ("%d %d",&x,&c);
		G[x].push_back(make_pair(i,c));
	}

	auto res = dfs(1);
	long long base = res.base_cost;
	long long ans = base;
	for (int i=0;i<res.func.size();i++){
		auto e = res.func[i];
		if (e.width == -1) break;
		base += e.slope * e.width;
		if (ans > base)
			ans = base;
	}

	printf ("%lld\n",ans);

	return 0;
}