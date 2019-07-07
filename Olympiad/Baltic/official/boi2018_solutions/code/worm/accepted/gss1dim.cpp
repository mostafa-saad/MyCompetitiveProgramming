#include <iostream>
#include <math.h>
#include <cassert>
using namespace std;

int n, m, k, q;

double phi = (1 + sqrt(5)) / 2;

int value(int x){
	if(x <= 0 || x > n) return 0;

	cout << "? " << x << " 1 1" << endl;

	int ans;
	cin >> ans;
	if(ans == -1) exit(0);

	return ans;
}

int goldenmean(int from, int to){
	int ans = from + (to - from + 1) / phi;
	assert(ans <= to);
	return ans;
}

int gss(int from, int to, int x, int fx){
	assert(from <= x);
	assert(x <= to);

	if(to==from) return x;

	int y = goldenmean(from, to);

	if(2*x > from+to) y = from+to - y;
	if(x == y){
		assert(2*x == from+to);
		++y;
	}

	assert(from <= y && y <= to);

	int fy = value(y);

	if(x > y){
		swap(x, y);
		swap(fx, fy);
	}

	if( fx <= fy ) return gss( x+1, to, y, fy);
	else           return gss(from, y-1, x, fx);
}

void done(int res){
	cout << "! " << res << " 1 1" << endl;
	exit(0);
}

int main(){
	cin >> n >> m >> k >> q;
	// m, k should be 1

	int x = goldenmean(1, n);
	int res = gss( 1, n, x, value(x));
	done(res);
}
