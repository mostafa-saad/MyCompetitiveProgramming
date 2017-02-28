/*
	O(n^2 * log n) solution
	Take each point and try all direction from it, sort them ...
	Program supposes that no two points have the same positions

	Idea:
	1) Determine the smallest point	p0	--> find_prepare() method do that
	2) Sort the pints around it	p0	--> Sort()		   method do that
	3) Try CrossProduct(p0, p[0], p[1])		where p[] is the array of reminder points
	4) Assume we get that all of them (p0, p[0], p[1]) were lined up, so we have answer=3
	5) Try CrossProduct(p0, p[1], p[2])
	6) Assume they were lined up, so we have answer=4
	7) Try CrossProduct(p0, p[2], p[3])
	8) Assume they were lined up, so we have answer=5
	7) Try CrossProduct(p0, p[3], p[4])
	8) Assume they were Not lined up, So we have new direction of other points
	9) Compare 5 with bestMax & intialize current max points
	10)Do the process again untill u fininsh all points
	11)Decrease number of points, no need now for p0
	12)If all points fininsh then break;
	13) Go to step 1

	The half of the idea is taken from the problem setter idea for problem 270 at UVA
	Thanks for him.

	I do not know exactly what problem setter do in his code.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct point
{
	int x, y;
};

point points[701];
point p0, v1, v2;

int cp( point &p0, point &p1, point &p2 )	//Cross product
{
	v1.x = p1.x - p0.x;
	v1.y = p1.y - p0.y;
	v2.x = p2.x - p0.x;
	v2.y = p2.y - p0.y;

	return v1.x*v2.y - v1.y*v2.x;
}

bool smaller_angle(point p1, point p2) /* Sort by smaller polar angle */
{
	// I calc the Cross product manually to make it faster
	// This method is called O(n^2 * log n), so its efficency lead to efficient program

	// We determine priority of p1, p2 depend on p0 location, the cuurent smallest point
	v1.x = p1.x - p0.x;
	v1.y = p1.y - p0.y;
	v2.x = p2.x - p0.x;
	v2.y = p2.y - p0.y;

	return (v1.x*v2.y - v1.y*v2.x) < 0;
};

void find_prepare(int& n)
{	// Find point with lower y then x to sort reminder points
	// around it as in grham scan.
	int i, s = 0;
	for(i=1;i<n;i++)
	{
		if(points[i].y <= points[s].y)
			if(points[i].y < points[s].y || points[i].x < points[s].x)
				s = i;
	}
	p0 = points[s], points[s] = points[n-1], points[n-1] = p0;	//swap p0 to last elem
}

int line_points_up(int n)
{
    int i, m, max = 2;

    if(n < 3)	return n;

    while(n > 2)
	{
		find_prepare(n); // To find Next point to sort around & set it in p0
		n--;
        sort(points, points+n, smaller_angle);	// Sort them around p0

        m = 2 ;	// Initial maximum
		for(i=0;i<n-1;i++)
		{
			if( cp(p0, points[i], points[i+1]) == 0)   /* Co-linear with p0 */
				m++;
			else			 /* Collection of points take another direction */
			{
				if(m > max)
					max = m; /* save best lining up from pervious direction */
				m = 2;
			}
		}
		if(m > max)
			max = m;
    }
    return max;
}

int main()
{
	//freopen("c.in", "rt", stdin);
    int n, cases;
	string str;

	cin>>cases;

	getline(cin, str);
	getline(cin, str);


	char*l = "";

	while(cases--)
	{
		cout<<l;	l = "\n";
		getline(cin, str);
		for(n=0;  str.size()!= 0 ;)
		{
			istringstream iss(str);
			iss>>points[n].x>>points[n].y;
			n++;
			if(cin.eof())	break;
			getline(cin, str);
		}

		cout<<line_points_up(n)<<"\n";
	}
	return 0;
}
