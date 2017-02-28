/*
 * O(n^2logn) based on getting normalizing vector
 * Idea:
 * 1) Select one of the smallest points p0
 * 2) Get all vectors from this point to others p[i]-p0
 * 3) Normalize All the vectors
 * 4) Now if two vectors were in same direction, then thier normal is same
 * 5) Count all the normal vectors with same parameter(dx,dy), i use map
 * 6) Compare with current_maximum , and select max
 * 7) remove p0
 * 8) Go to step one
 */
 
 // Note, using hashtable, this can be reduced to O(n^2)

/*
To normalize a vector

Vector(x, y).
len = sqrt(x*x+y*y)
resultVector = Vector(x/len, y/len)

problem with this approach is the double percison

Another way
resultVector = Vector(x/gcd(x,y), y/gcd(x,y))
*/
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

typedef pair<int, int> point;
#define x	first
#define y   second

point points[701], v;

void normal(point& p0, point& p1, point& v) {	// O(GCD(dx, dy))
	/* Return normalized vector of p0p1 Assume p0 != p1 */
	v.x = p1.x-p0.x, v.y = p1.y-p0.y;
	int a = abs(v.x), b = abs(v.y), t;
	while (b != 0)	t = a % b, a = b, b = t;	/* Find GCD */

	v.x /= a; v.y /= a;
	if(v.x < 0)	v.x *= -1, v.y *= -1;	// NORMAZLIE DIRECTION
}

int line_points_up(int n) {
    int max = 0;

    if(n < 3)	return n;

    while(n-- > 2) {
		map<int, int> cache;
		for(int i=0;i<n;i++) {
			normal(points[n], points[i], v);
			int val = cache[ v.x*1000000+v.y ] + 1;	// If overFlow, use map for point, i belive y should be shifted
			cache[ v.x*1000000+v.y ] = val;
			if(val > max) max = val;
		}
    }
    return max+1;
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
