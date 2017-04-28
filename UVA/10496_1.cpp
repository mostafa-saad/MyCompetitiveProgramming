#include <iostream>
#include <cmath>
using namespace std;

int n, m, list[15], x[15], y[15], best, curLen, nodes[15];

int abs(int x)
{
	if(x < 0) x*=-1;
	return x;
}

void swap(int&a , int& b)
{
	int t = a;
	a = b;
	b = t;
}

int sp(int i, int j)
{
	return abs(x[i]-x[j]) + abs(y[i]-y[j]);
}

int found = 0;
void go(int from, int n)
{
	if(n == 0)
	{
		if(curLen+sp(nodes[from], nodes[m]) < best)
			best = curLen+sp(nodes[from], nodes[m]);
		return ;
	}

	for(int i=0;i<n;i++)
	{
		curLen += sp(nodes[i], nodes[from]);
		swap(nodes[i], nodes[n-1]);

		if(curLen <= best)
			go(n-1, n-1);

		swap(nodes[i], nodes[n-1]);
		curLen -= sp(nodes[i], nodes[from]);
	}
}

int main()
{
	int i, cases;

	cin>>cases;

	for(i=0;i<15;i++)
		list[i] = i, nodes[i] = i;

	while(cases--)
	{
		cin	>>i>>i
			>>x[0]>>y[0]>>n;

		x[n] = x[0], y[n] = y[0];

		for(i=0;i<n;i++)
			cin>>x[i]>>y[i];


		m = n;
		curLen = 0;
		best = 100000000;

		go(n, n);

		cout<<"The shortest path has length "<<best<<"\n";
	}
	return 0;
}
