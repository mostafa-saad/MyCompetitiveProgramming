/**
 * O(log K) solution for one-digit subtask.
 * Author: Donatas Kucinskas
 */

#include <iostream>

using namespace std;

int k, b;

int main() {
	cin >> k >> b;
	long long now, max;
	if (b == 0) {
		now = 10;
		max = 1;
		while (k > max) {
			now *= 10;
			max = max * 10 + 1;
		}
	}
	else if (b == 9) {
		now = 8;
		max = 1;
		while (k > max) {
			now = now * 10 + 8;
			max = max * 10 + 1;
		}
		now++;
	}
	else {
		now = b;
		max = 1;
		while (k > max) {
			max *= 10;
			now *= 10;
		}
	}
	cout << now << endl;
	return 0;
}
