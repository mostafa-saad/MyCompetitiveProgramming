/* Author: Jakub Pawlewicz
 * Sweets task model solution
 */

#include <iostream>
#include <vector>

using namespace std;

#define YEAR	2004

void binom_helper(int n, int k, vector<int>& bin)
{
	if (n == 1)
		return;
	if (n & 1) {
		binom_helper(n - 1, k, bin);
		for (int i = k; i > 0; i--)
			bin[i] = (bin[i] + bin[i-1]) % YEAR;
	} else {
		binom_helper(n >> 1, k, bin);
		for (int i = k; i > 0; i--) {
			int bini = 0;
			for (int j = 0; j <= i; j++)
				bini += bin[j] * bin[i - j];
			bin[i] = bini % YEAR;
		}
	}
}

int binom(int n, int k)
{
	if (n < k)
		return 0;
	if (k == 0)
		return 1;
	vector<int> bin(k + 1, 0);
	bin[0] = 1;
	bin[1] = 1;
	binom_helper(n, k, bin);
	return bin[k];
}

int count(int n, vector<int>& m, int x)
{
	int s = 0;
	x += n;
	for (int i = 1; i <= 1 << n; i++) {
		if (i & 1)
			s += binom(x, n);
		else
			s -= binom(x, n);
		if (i == (1 << n))
			break;
		int j = 0;
		int k;
		for (k = i; (k & 1) == 0; k >>= 1)
			j++;
		if (k & 2)
			x += m[j] + 1;
		else
			x -= m[j] + 1;
	}
	return s;
}

int main()
{
	int n, a, b;
	cin >> n >> a >> b;
	vector<int> m(n);
	for (int i = 0; i < n; i++)
		cin >> m[i];
	int res = (count(n, m, b) - (a == 0 ? 0 : count(n, m, a-1))) % YEAR;
	if (res < 0)
		res += YEAR;
	cout << res << endl;
	return 0;
}
