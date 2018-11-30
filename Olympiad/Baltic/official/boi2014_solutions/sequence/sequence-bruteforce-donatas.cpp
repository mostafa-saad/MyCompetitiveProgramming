/**
 * An invalid brute-force solution.
 * Should pass subtask 2.
 *
 * Author: Donatas Kucinskas
 */

#include <iostream>

using namespace std;

const int MAX_K = 100000;

int k;
int B[MAX_K];

bool contains(int number, int digit) {
	while (number != 0) {
		int now = number % 10;
		if (now == digit)
			return true;
		number /= 10;
	}
	return false;
}

long long calcAnswer() {
	for (int n = 1; true; ++n) {
		bool found = true;
		for (int i = 0; i < k; ++i)
			if (!contains(n+i, B[i])) {
				found = false;
				break;
			}
		if (found)
			return n;
	}
}


int main() {
	cin >> k;
	for (int i = 0; i < k; ++i)
		cin >> B[i];
	cout << calcAnswer() << endl;
	return 0;
}
