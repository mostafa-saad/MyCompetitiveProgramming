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
#include <set>
#include <complex>
using namespace std;


const double EPS = (1e-7);
int dcmp(double a, double b) {	return fabs(a-b) <= EPS ? 0 : a < b ? -1 : 1;	}

typedef complex<double> point;
#define x real()
#define y imag()

/*
struct point {
	double x, y;
	point() {}
	point(double x, double y) : x(x), y(y) {}

	bool operator < (const point & a) const {
		if(dcmp(x, a.x) == 0)
			return dcmp(y, a.y) == -1;
		return dcmp(x, a.x) == -1;
	}
};
*/


struct pcmp {
    bool operator () (const point &p0, const point &p1) const {
    	if( dcmp(p0.x, p1.x) == 0)
    		return dcmp(p0.y, p1.y) < 0;
    	return dcmp(p0.x, p1.x) < 0;
    }
};

point points[701], v;


void normal(point& p0, point& p1, point& v) {
	double dx = p1.x-p0.x, dy = p1.y-p0.y;
	double a = hypot(dx, dy);
	v = p1-p0;
	v /= a;
}


int line_points_up(int n)
{
	sort(points, points+n, pcmp());	// Sort all points
    int max = 0;

    if(n < 3)	return n;

    while(n-- > 2) {
		map<point, int, pcmp> cache;
		for(int i=0;i<n;i++) {
			normal(points[n], points[i], v);
 			
			int val = cache[v] + 1;
			cache[v] = val;
			if(val > max) max = val;
		}
    }
    return max+1;
}

int main()
{
	freopen("c.in", "rt", stdin);

    int n, cases;
	string str;

	cin>>cases;

	getline(cin, str);
	getline(cin, str);


	char *l = "";

	while(cases--)
	{
		cout<<l;	l = "\n";
		getline(cin, str);
		for(n=0;  str.size()!= 0 ;)
		{
			istringstream iss(str);
			int a, b;	
			iss>>a>>b;
			points[n] = point(a, b);
			//iss>>points[n].x>>points[n].y;
			n++;
			if(cin.eof())	break;
			getline(cin, str);
		}

		cout<<line_points_up(n)<<"\n";
	}
	return 0;
}
