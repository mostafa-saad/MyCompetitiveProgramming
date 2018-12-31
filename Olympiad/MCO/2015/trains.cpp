#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ll,ii> iii;

int n, ax, ay, bx, by, c[751][751], d[751][751], x, y, rx[] = {1,0,-1,0}, ry[] = {0,-1,0,1};
ll ans = -1;

struct cmp
{
	bool operator()(const iii &a, const iii &b)
	{
		return a.first>b.first;
	}
};

int main()
{
	scanf("%d%d%d%d%d", &n, &ax, &ay, &bx, &by);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &c[j][i]);
	priority_queue<iii, vector<iii>, cmp> pq;
	if (c[ax][ay] != -1) pq.push(make_pair(c[ax][ay], make_pair(ax, ay)));
	iii me;
	while (!pq.empty()) {
		while(!pq.empty() && d[pq.top().second.first][pq.top().second.second]) pq.pop();
		if (pq.empty()) break;
		me = pq.top();
		x = me.second.first;
		y = me.second.second;
		if (x == bx && y == by) {
			ans = me.first;
			break;
		}
		d[x][y] = 1;
		pq.pop();
		for (int i = 0; i < 4; i++)
			if (x+rx[i] >= 1 && x+rx[i] <= n && y+ry[i] >= 1 && y+ry[i] <= n && c[x+rx[i]][y+ry[i]] != -1)
				pq.push(make_pair(me.first + c[x+rx[i]][y+ry[i]], make_pair(x+rx[i], y+ry[i])));
	}
	printf("%lld\n", ans);
	return 0;
}
