// Mateusz Radecki
// Queries: O(n*log(n))
// Complexity: O(n*log(n))

#include <bits/stdc++.h>
#include "trilib.h"
using namespace std;

int n;
vector <int> divide[2], hull[2];

bool is_less(int a, int b)
{
	return is_clockwise(1, a, b);
}

int main()
{
	n=get_n();
	divide[0]=divide[1]={2};
	for (int i=3; i<=n; i++)
		divide[is_clockwise(1, 2, i)].push_back(i);
	for (int h=0; h<2; h++)
	{
		sort(divide[h].begin(), divide[h].end(), is_less);
		for (int i : divide[h])
		{
			int r=hull[h].size();
			while (r>1 && !is_clockwise(hull[h][r-2], hull[h][r-1], i))
			{
				r--;
				hull[h].pop_back();
			}
			hull[h].push_back(i);
		}
		
		if (h)
			reverse(hull[h].begin(), hull[h].end());
		hull[h].insert(hull[h].begin(), 1);
	}
	if ((int)min(hull[0].size(), hull[1].size())==2)
	{
		give_answer(max(hull[0].size(), hull[1].size()));
		return 0;
	}
	for (int h=0; h<2; h++)
	{
		hull[0].pop_back();
		while (true)
		{
			bool out=true;
			int r=hull[0].size();
			if (r>1 && !is_clockwise(hull[0][r-2], hull[0][r-1], hull[1].back()))
			{
				hull[0].pop_back();
				out=false;
			}
			int d=hull[1].size();
			if (d>1 && !is_clockwise(hull[0].back(), hull[1][d-1], hull[1][d-2]))
			{
				hull[1].pop_back();
				out=false;
			}
			if (out)
				break;
		}
		for (int i=0; i<2; i++)
			reverse(hull[i].begin(), hull[i].end());
		swap(hull[0], hull[1]);
	}
	give_answer(hull[0].size()+hull[1].size());
	return 0;
}
