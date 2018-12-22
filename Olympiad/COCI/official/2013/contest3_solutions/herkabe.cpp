#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

string a[3003];
int faktorijel[3003];
const int mod = 1000000007;
char ime[3003];

int rijesi(int lo, int hi, int p)
{
	if (hi - lo <= 1)
		return 1;
	int ret = 1;
	int novi_lo = lo;
	int komponenata = 1;
	for (int i = lo + 1; i < hi; ++i)
		if (a[novi_lo][p] != a[i][p]) {
			ret = (long long)ret * rijesi(novi_lo, i, p + 1) % mod;
			novi_lo = i;
			++komponenata;
		}
	ret = (long long)ret * rijesi(novi_lo, hi, p + 1) % mod;
	return (long long)ret * faktorijel[komponenata] % mod;
}

int main() {
	int n;
	scanf("%d", &n);
	faktorijel[0] = 1;
	for (int i = 0; i < n; ++i) {
		scanf("%s", ime);
		a[i] = ime;
		faktorijel[i + 1] = (long long)faktorijel[i] * (i + 1) % mod;
	}
	sort(a, a+n);
	printf("%d\n", rijesi(0, n, 0));
}
