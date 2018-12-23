//Mateusz Radecki
#include <bits/stdc++.h>
using namespace std;

int n;

vector <int> divi;
vector <set<int>> res;

int main()
{
	scanf("%d", &n);
	for (int i=1; i*i<=n; i++)
	{
		if (!(n%i))
		{
			divi.push_back(i);
			if (n/i!=i)
				divi.push_back(n/i);
		}
	}
	sort(divi.begin(), divi.end());
	res.resize(divi.size());
	res[0].insert(0);
	for (int i=0; i<(int)divi.size(); i++)
		for (int j=0; j<i; j++)
			if (!(divi[i]%divi[j]))
				for (int l : res[j])
					res[i].insert(l+divi[i]/divi[j]-1);
	
	printf("%d\n", (int)res.back().size());
	for (int i : res.back())
		printf("%d ", i);
	printf("\n");
	return 0;
}
