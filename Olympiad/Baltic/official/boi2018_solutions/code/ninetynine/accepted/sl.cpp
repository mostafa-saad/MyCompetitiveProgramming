#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
	int num = 0;
	cout << 1 << endl;
	while (cin >> num && num != 99) {
		int r;
		if (num % 3 == 0)
			r = num + 1 + rand() % 2;
		else
			r = (num / 3 * 3 + 3);
		cout << r << endl;
		if (r == 99) break;
	}
}
