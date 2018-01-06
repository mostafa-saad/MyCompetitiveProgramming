/* Khaled kee solution

Kee Using Radical Sweep Line:
For a fixed point, sort other points around it in a clockwise (or anticlockwise) order. We may use angles but this will introduce precision errors. A better approach is to use cross and dot product (see code below).
Use two pointer. For a center C, and a point A, increment the second pointer B, as long as the cross product of (A-C,B-C) is less than or equal 0 (i.e. the A-C is parallel or in the left hand side of B-C) and the dot product is larger than 0 (i.e. A-C is NOT perpendicular on B-C). Count the number of perpendicular vectors on A-C. Their cross product must be less than 0 (not equal) and their dot product must be 0.
Code: http://ideone.com/9f1F0s
Using Slope:
After I solved the problem, I thought of another solution that may be easier. For a fixed center point C, and a current point A, store the slope of the line in reduced fraction form (i.e. pair of {dx,dy}) and find the number of points with the inverse of the slope (i.e. pair of {-dy,dx} or {dy,-dx}).
* 
*/

#include <bits/stdc++.h>
using namespace std;
/***********************************************/
/* Dear online judge:
 * I've read the problem, and tried to solve it.
 * Even if you don't accept my solution, you should respect my effort.
 * I hope my code compiles and gets accepted.
 *  ___  __     _______    _______      
 * |\  \|\  \  |\  ___ \  |\  ___ \     
 * \ \  \/  /|_\ \   __/| \ \   __/|    
 *  \ \   ___  \\ \  \_|/__\ \  \_|/__  
 *   \ \  \\ \  \\ \  \_|\ \\ \  \_|\ \ 
 *    \ \__\\ \__\\ \_______\\ \_______\
 *     \|__| \|__| \|_______| \|_______|
 */
const long long mod = 1000000007;

struct PT { 
  long long x, y; 
  PT() {}
  PT(long long x, long long y) : x(x), y(y) {}
  PT(const PT &p) : x(p.x), y(p.y)    {}
  PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
  PT operator * (long long c)     const { return PT(x*c,   y*c  ); }
  PT operator / (long long c)     const { return PT(x/c,   y/c  ); }
  bool operator<(const PT &p)  const { return make_pair(x,y)<make_pair(p.x,p.y); }
};

long long dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
long long dist2(PT p, PT q)   { return dot(p-q,p-q); }
long long cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }
istream &operator>>(istream &is, PT &p) {
	return is >> p.x >> p.y; 
}
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")"; 
}


PT center;
bool cmp(PT a, PT b)
{
	if (a.x >= center.x  && b.x < center.x)
		return true;
	if (a.x < center.x && b.x >= center.x)
		return false;
	if (a.x - center.x == 0 && b.x - center.x == 0) {
		if (a.y - center.y >= 0 || b.y - center.y >= 0)
			return a.y > b.y;
		return b.y > a.y;
	}

	return cross(a-center,b-center) < 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N,M;
	while(cin>>N && N) {
		vector<PT> a(N);
		M = N - 1;
		for(int i = 0;i < N;i++)
			cin>>a[i];
		long long res = 0;
		for(int i = 0;i < N;i++) {
			center = a[i];
			vector<PT> other;
			for(int j = 0;j < N;j++) {
				if(i == j)
					continue;
				other.push_back(a[j]);
			}
			sort(other.begin(),other.end(),cmp);
			for(int j = 0,k = 1;j + 1 < N;j++) {
				if(k == j)
					k++;
				while(k%M != j && dot(other[j]-a[i],other[k%M]-a[i]) > 0 && cross(other[j]-a[i],other[k%M]-a[i]) <= 0) {
					k++;
				}
				int cnt = 0;
				while((k+cnt)%M != j && dot(other[j]-a[i],other[(k+cnt)%M]-a[i]) == 0 && cross(other[j]-a[i],other[(k+cnt)%M]-a[i]) < 0) {
//					cerr<<a[i]<<' '<<other[j]<<' '<<other[(k+cnt)%M]<<'\n';
					res++,cnt++;
				}
			}
		}
		cout<<res<<'\n';
	}
	return 0;
}
/**/

