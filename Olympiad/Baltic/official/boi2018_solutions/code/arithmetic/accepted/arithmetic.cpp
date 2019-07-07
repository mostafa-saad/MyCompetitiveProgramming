#include <bits/stdc++.h>
using namespace std;

int main() {
	long long a, b, c, ab;
	cin >> a >> b >> c;
	ab = a * b;
	if (ab >= 10*c) {
		cout << ab / (10*c);
		ab %= 10*c;
	}
	cout << setprecision(18) << fixed << (long double)ab / c << endl;
}
