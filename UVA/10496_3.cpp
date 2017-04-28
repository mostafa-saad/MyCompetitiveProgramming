// By Assma Magdi

# include <iostream>
# include <fstream>
# include <math.h>
using namespace std;

ifstream fin("10496.txt");
#define cin fin

int R, C;
bool grid[25][25];
int startr, startc;

int Solve(int r, int c, int counter, int n)
{
	if(counter == n)
		return abs(r - startr) + abs(c - startc);
	int i, j;
	int temp, min = 100000000;
	for(i=1; i<=R; i++)
	{
		for(j=1; j<=C; j++)
		{
			if(grid[i][j])
			{
				grid[i][j] = 0;
				temp = Solve(i, j, counter +1, n) + abs(r - i) + abs(c - j);
				if(temp < min)
					min = temp;
				grid[i][j] = 1;
			}
		}
	}
	return min;
}

int main()
{
	int t, n, i, j, k, x, y, r, c;
	cin>>t;
	for(j=0; j<t; j++)
	{
		cin>>R>>C;
		cin>>r>>c;
		startr = r;
		startc = c;
		cin>>n;
		for(i=0; i<=R; i++)
		{
			for(k=0; k<=C; k++)
			{
				grid[i][k] = 0;
			}
		}
		for(i=0; i<n; i++)
		{
			cin>>x>>y;
			grid[x][y] = 1;
		}
		int s = Solve(r, c, 0, n);
		cout<<"The shortest path has length "<<s<<endl;
	}
	return 0;
}
