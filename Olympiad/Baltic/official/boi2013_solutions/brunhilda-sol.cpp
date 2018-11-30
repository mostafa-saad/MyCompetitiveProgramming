// hoffentlich volle Punkte
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 1000000000
#define MAX 11000000
// MAX has to be significally larger than the real one
int main()
{
	int m, Q;
	cin >> m >> Q;

	vector<int> dp(MAX, 0);	// 1: abziehen, 2: steps
	while(m --> 0)
	{
		int p;
		cin >> p;
		for(int x = p-1; x < MAX; x += p)
			dp[x] = max(dp[x], p-1);
	}

	for(int i = MAX-2; i >= 0; --i)
		dp[i] = max(dp[i], dp[i+1]-1);

	for(int i = 1; i < MAX; ++i)
		if(dp[i] > 0)
			dp[i] = 1+dp[i-dp[i]];
		else
			dp[i] = INF;

	while(Q --> 0)
	{
		int q;
		cin >> q;
		if(dp[q] >= INF)
			cout << "oo\n";
		else
			cout << dp[q] << '\n';
	}
	return 0;
}
