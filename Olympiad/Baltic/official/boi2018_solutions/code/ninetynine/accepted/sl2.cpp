#include <iostream>
using namespace std;

int main() {
	int num = 0;
	cout << 2 << endl;
	while (num != 99 && cin >> num && num != 99) {
		if (num % 3 == 0)
			++num;
		else
			num += 3 - num % 3;
		cout << num << endl;
	}
}
