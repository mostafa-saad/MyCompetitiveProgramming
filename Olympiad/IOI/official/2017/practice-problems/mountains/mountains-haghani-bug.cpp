#include <iostream>
#include <vector>
#include "mountains.h"
#define x first
#define y second
using namespace std;
typedef pair<long long, long long> point;
const int MAX = 2005;
int dp[MAX][MAX];
point p[MAX];
long long ccw(point a, point b, point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
int maximum_deevs(vector<int> y)
{
	int n = y.size();
	for (int i = 0; i < n; i++)
	{
		p[i].x = i;
		p[i].y = y[i];
	}
	for (int r = 1; r <= n; r++)
	{
		int sum = 0, last = r - 1;
		point bn(p[r - 1].x, p[r - 1].y - 1);
		dp[r - 1][r] = 1;
		for (int l = r - 2; l >= 0; l--)
		{
			dp[l][r] = dp[l][r - 1];
			if (ccw(p[l], bn, p[r - 1]) > 0)
			{
				sum += dp[l + 1][last];
				last = l;
				bn = p[l];
			}
			dp[l][r] = max(dp[l][r], 1 + sum + dp[l][last]);
		}
	}
	return dp[0][n];
}
