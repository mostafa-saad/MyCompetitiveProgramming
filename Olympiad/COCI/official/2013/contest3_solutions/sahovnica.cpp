#include <iostream>
using namespace std;

int main() {
	int r, s;
	cin >> r >> s;
	int a, b;
	cin >> a >> b;
	char sahovnica[104][104];
	for (int i = 0; i < r * a; ++i) {
		for (int j = 0; j < s * b; ++j)
			cout << ((i / a + j / b) % 2 == 0? 'X' : '.');
		cout << endl;
	}
}
