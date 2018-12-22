#include <cstdio>
#include <iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	int sol = 2;
	for (int i = 0; i < n; i++) {
		sol += sol - 1;
	}
	cout << sol * sol << endl;
	return 0;
}
