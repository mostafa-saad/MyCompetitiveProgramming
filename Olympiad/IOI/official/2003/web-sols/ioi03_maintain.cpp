#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

set<pi> graph[205];

struct disj{
	int pa[205];
	void init(int n){for(int i=0; i<=n; i++) pa[i] = i;}
	int find(int x){return pa[x] = (pa[x] == x ? x : find(pa[x]));}
	bool uni(int p, int q){
		p = find(p), q = find(q); 
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int ret, retp, nxt[205];

bool dfs(int s, int e, int x){
	if(s == e) return 1;
	set<pi>::iterator it = s.begin();
	while(it != s.end()){
		pi i = *it++;
		if(i.second != x && dfs(i.second, e, s)){
			nxt[s] = i.second;
			if(ret < i.first){
				ret = i.first;
				retp = s;
			}
			return 1;
		}
	}
	return 0;
}

int main(){
	int n, m, cnt = 0, mst = 0;
	cin >> n >> m;
	disj.init(n);
	while(m--){
		int s, e, x;
		cin >> s >> e >> x;
		if(disj.uni(s, e)){
			graph[s].insert(pi(x, e));
			graph[e].insert(pi(x, s));
			cnt++;
			mst += x;
		}
		else{
			ret = -1e9, retp = -1;
			dfs(s, e, -1);
			if(ret > x){
				mst += x - ret;
				graph[retp].erase(pi(ret, nxt[retp]));
				graph[nxt[retp]].erase(pi(ret, retp));
				graph[s].insert(pi(x, e));
				graph[e].insert(pi(x, s));
			}
		}
		if(cnt == n-1) printf("%d\n",mst);
		else puts("-1");
	}
}