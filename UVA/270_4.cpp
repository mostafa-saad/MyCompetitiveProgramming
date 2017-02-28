
/*

This code i take from a solver & ty to guess how it is working
I found description in the board that match what he trying to do
I hope i understand it well.

  Algorithm   : Lining point on a line.
  Method	  : Using point-line duality.
  Complexity  : MlogM where M = n*(n-1)/2 where n is he input points

  Description :
				Transform the problem into "given M different lines,
				find the largest subset that pass through the same point",
				and then traverse the whole plane subdivision given by the
				M lines, and look for a vertex with the largest degree.
				Where M = n(n-1)/2
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

struct ln
{	int dx, dy;		};

struct point
{	int x, y;		};


ln lns[700*450];
point points[700];
int lastln;

bool smaller_angle (const ln k1, const ln k2)
{
	return (k1.dy * k2.dx - k2.dy * k1.dx) < 0;
}

int cp(ln k1, ln k2)
{
	return (k1.dy * k2.dx - k2.dy * k1.dx);
}

int traverse_count()
{
	int m=0, n=0, a;

	for (a = 0; a < lastln-1; a++)
	{
		if (!cp(lns[a], lns[a+1]) )	/* Two lines are same direction */
			n ++;
		else
		{
			if (m < n)
				m = n;
			n = 0;
		}
	}
	if (m < n)
		m = n;

	return m;
}

void generate_lines (int n)		/* Point-line duality */
{
	int a, b;
	point j, k, q;

	for (a = 0; a <n; a++)	/* Construct all possible lines --> n*(n-1)/2 */
		for (b = a+1; b < n; b++)
		{
			j = points[a], k = points[b];

			if (j.x > k.x)	/* Normalization */
				q = j, j = k, k = q;

			lns[lastln].dx = k.x - j.x;
			lns[lastln].dy = k.y - j.y;
			lastln ++;
		}
}

int main ()
{
	int n, i, cases;
	string str;

	cin>>cases;
	cin.ignore(10, '\n');
	cin.ignore(10, '\n');

	char *l = "";
	while(cases--)
	{
		cout<<l;	l = "\n";
		getline(cin, str);
		for(n=0; str.size()!= 0 ; )
		{
			istringstream iss(str);
			iss>>points[n].x>>points[n].y;
			n++;
			if(cin.eof())	break;
			getline(cin, str);
		}

		lastln = 0;
		generate_lines(n);

		sort(lns, lns+lastln, smaller_angle);

		i = traverse_count();
		/* so i is the larges set of lines pass throgh a specific point */

		/* Reverse formula n(n-1)/2 */
		i = (int)((1 + sqrt(9 + 8*i)) / 2);
		/* so i is the larges set of points on smae line */

		cout<<i<<"\n";
	}
	return 0;
}