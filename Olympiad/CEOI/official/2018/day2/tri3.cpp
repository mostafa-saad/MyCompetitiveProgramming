// Mateusz Radecki
// Queries: O(n*log(n)) (in expectation)
// Complexity: O(n*log^2(n)) (in expectation)

#include <bits/stdc++.h>
#include "trilib.h"
using namespace std;

int n;

map <vector<int>,int> mapa;

int ask(int a, int b, int c)
{
	vector <int> wek{a, b, c};
	for (int h=0; h<2; h++)
	{
		for (int i=0; i<3; i++)
		{
			if (mapa.count(wek))
				return mapa[wek]^h;
			swap(wek[0], wek[1]);
			swap(wek[1], wek[2]);
		}
		swap(wek[0], wek[1]);
	}
	return mapa[wek]=is_clockwise(a, b, c);
}

void shift(vector <int> &wek, int v)
{
	for (int i=0; i<(int)wek.size(); i++)
	{
		if (wek[i]==v)
		{
			vector <int> pom(wek.size());
			for (int j=0; j<(int)wek.size(); j++)
				pom[j]=wek[(j+i)%wek.size()];
			wek=pom;
			return;
		}
	}
	assert(false);
}

vector <int> rec(vector <int> wek)
{
	int a=rand()%wek.size();
	swap(wek[a], wek.back());
	a=wek.back();
	wek.pop_back();
	
	int b=rand()%wek.size();
	swap(wek[b], wek.back());
	b=wek.back();
	wek.pop_back();
	
	if ((int)wek.size()==1)
	{
		if (ask(a, b, wek[0]))
			return {a, b, wek[0]};
		return {b, a, wek[0]};
	}
	
	vector <int> divide[2], hull[2];
	divide[0]=divide[1]={a, b};
	for (int i : wek)
		divide[ask(a, b, i)].push_back(i);
	
	for (int i=0; i<2; i++)
		if ((int)divide[i].size()==2)
			return rec(divide[i^1]);
	
	hull[0]=rec(divide[0]);
	shift(hull[0], a);
	
	hull[1]=rec(divide[1]);
	shift(hull[1], b);
	
	reverse(hull[1].begin(), hull[1].end());
	
	for (int h=0; h<2; h++)
	{
		hull[0].pop_back();
		while (true)
		{
			bool out=true;
			int r=hull[0].size();
			if (r>1 && !ask(hull[0][r-2], hull[0][r-1], hull[1].back()))
			{
				hull[0].pop_back();
				out=false;
			}
			int d=hull[1].size();
			if (d>1 && !ask(hull[0].back(), hull[1][d-1], hull[1][d-2]))
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
	while(!hull[1].empty())
	{
		hull[0].push_back(hull[1].back());
		hull[1].pop_back();
	}
	return hull[0];
}

int main()
{
	n=get_n();
	vector <int> start;
	for (int i=1; i<=n; i++)
		start.push_back(i);
	give_answer(rec(start).size());
	return 0;
}
