#include <iostream>
#include <cmath>
using namespace std;
 
int n, list[15], x[15], y[15], best;

int abs(int x)
{
	if(x < 0) x*=-1;
	return x;
}

int sp(int i, int j)
{
	return abs(x[i]-x[j]) + abs(y[i]-y[j]);
}

void swap(int&a , int& b)
{
	int t = a;
	a = b;
	b = t;
}


void perm(int i, int len)
{
	if(i==n)
	{
		int d = len + sp(list[0], list[n-1]);

		if(d < best)	best = d;	
	}
	else
	{
		for(int j=i;j<n;j++)	/* Try all swaps from i to n with index i */
		{
			swap(list[i], list[j]);

			int newlen = (i == 0) ? 0 : newlen = sp(list[i-1], list[i]); 

			if(len + newlen < best)		/* Pruning Condition */
				perm(i+1, len + newlen);
			swap(list[i], list[j]);
		}
	}
}

int main()
{
	int i, cases;

	cin>>cases;

	for(i=0;i<15;i++)
		list[i] = i;

	while(cases--)
	{
		cin>>i>>i>>x[0]>>y[0]>>n;

		for(i=1;i<=n;i++)
			cin>>x[i]>>y[i];

		best = 100000000;
		n++;
		perm(1, 0);

		cout<<"The shortest path has length "<<best<<"\n";
	}
	return 0;
}