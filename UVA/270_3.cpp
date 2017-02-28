// Another buggy code by mostafa_saad
#include <set>
#include <map>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <complex>
using namespace std;

#define all(v)				((v).begin()), ((v).end())
#define sz(v)				((int)((v).size()))
#define clr(v, d)			memset(v, d, sizeof(v))
#define repa(v)				for(int i=0;i<(sz(v));++i) for(int j=0;j<(sz(v[i]));++j)
#define rep(i, v)			for(int i=0;i<(sz(v));++i)
#define lp(i, cnt)			for(int i=0;i<(cnt);++i)
#define lpi(i, s, cnt)		for(int i=(s);i<(cnt);++i)
#define P(x)				cout<<#x<<" = { "<<x<<" }\n"

typedef long long ll;
typedef long double ld;

const int OO = (int)1e8;	// Note, IF Small may be WRONG, Large may generate OVERFLOW
const double PI  = acos(-1);
const double EPS = (1e-7);
int dcmp(ld x, ld y) {	return fabs(x-y) <= EPS ? 0 : x < y ? -1 : 1;	}


typedef complex<ld> point;
#define X real()
#define Y imag()
#define angle(a)				(atan2((a).imag(), (a).real()))		// [-PI, PI]
#define vec(a,b)				((b)-(a))
#define same(p1,p2)				(dp(vec(p1,p2),vec(p1,p2)) < EPS)
#define dp(a,b)					( (conj(a)*(b)).real() )
#define cp(a,b)					( (conj(a)*(b)).imag() )
#define length(a)				(hypot((a).imag(), (a).real()))
#define normalize(a)			(a)/length(a)
#define rotateO(p,ang)			((p)*exp(point(0,ang)))
#define rotateA(p,angle,about)	(rotateO(vec(about,p),ang)+about)
#define polar(r,ang)			((r)*exp(point(0,ang)))

struct pcmp {
    point center;
    pcmp(point c) : center(c) {}
    bool operator () (const point &p0, const point &p1) const {
    	return dcmp( cp(p0-center, p1-center), 0) == 1;
    	//return angle(p0-center) < angle(p1-center);
    }
};

int linePointsUp(vector<point> p)
{
	if( sz(p) < 3)		return sz(p);
	int mx = 2;

	while( sz(p) > 2) {
		int mi = 0;
		rep(i, p) if( make_pair(p[i].Y, p[i].X) < make_pair(p[mi].Y, p[mi].X))
			mi = i;
		swap(p.back(), p[mi]);
		point p0 = p.back();	p.pop_back();
		sort( all(p), pcmp(p0));

		int m = 2;
		lp(i, sz(p)-1){
			if( cp(p[i]-p0, p[i+1]-p0) ==0) 	m++;
			else mx = max(mx, m), m = 2;
		}
		mx = max(mx, m);
	}
	return mx;
}

int main()
{
//	freopen("c.in", "rt", stdin);

    int n, cases;
	string str;

	cin>>cases;

	// ignore two lines
	getline(cin, str);
	getline(cin, str);

	char* l = "";

	while(cases--)
	{
		cout<<l;	l = "\n";

		getline(cin, str);
		vector<point> points(1000);
		for(n=0; str.size()!= 0 ; )
		{
			istringstream iss(str);
			iss>>points[n].X>>points[n].Y;
			n++;
			if(cin.eof())	break;
			getline(cin, str);
		}
		points.resize(n);

		cout<<linePointsUp(points)<<"\n";
	}
	return 0;
}
