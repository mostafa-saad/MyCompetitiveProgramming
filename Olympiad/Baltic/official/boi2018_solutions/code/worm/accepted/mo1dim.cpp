#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); ++i)

int main(){
	int n, m, k, maxq;
	cin >> n >> m >> k >> maxq;
	// m, k should be 1

	int a = sqrt(n); // not optimised
	int mx = 0, pos;
	for(int cur = 1; cur <= n; cur += a){
		cout << "? " << cur << " 1 1" << endl;
		int res;
		cin >> res;
		if (res == -1) exit(0);
		if(res > mx){
			mx = res;
			pos = cur;
		}
	}

	int le, ri;
	foo:
	le = -1, ri = -1;
	if(pos >= 2){
		cout << "? " << pos-1 << " 1 1" << endl;
		cin >> le;
		if (le == -1) exit(0);
	}
	if(pos+1 <= n){
		cout << "? " << pos+1 << " 1 1" << endl;
		cin >> ri;
		if (ri == -1) exit(0);
	}
	if(le > mx){
		mx = le;
		pos = pos-1;
		goto foo;
	}
	if(ri > mx){
		mx = ri;
		pos = pos+1;
		goto foo;
	}
	cout << "! " << pos << " 1 1" << endl;
}
