#include <iostream>
using namespace std;

int main() {
	int num = 0;
	cout << 1 << endl;
	while (num != 99 && cin >> num && num != 99) {
		++num;
		cout << num << endl;
	}
}
