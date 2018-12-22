#include <iostream>
#include <vector>
using namespace std;

int main()
{
	long long A, B, rjesenje = 0;
	cin >> A >> B;

	// NZV = lcm(1, 2, ..., K-1)
	long long NZV = 1;

	int snaga[100];
	snaga[2] = 1;
	for (int K = 2; K < 100; K++)
	{
		for (int i = 2; i < K; i++) {
			if (K % i != 0) {
				snaga[K] = snaga[i] + 1;
				break;
			}
		}
		long long novi_NZV = NZV;
		vector<int> prosti_djelitelji_K;
		for (int p = 2, k = K; k > 1; p++) {
			if (k % p == 0) {
				prosti_djelitelji_K.push_back(p);
				while (k % p == 0) {
					k /= p;
				}
			}
		}
		if ((int)prosti_djelitelji_K.size() == 1) {
			novi_NZV *= prosti_djelitelji_K[0];
		}

		rjesenje += (snaga[K] + 1) * (B/NZV - (A-1)/NZV);

		if (novi_NZV > B || novi_NZV < 0) break;
		rjesenje -= (snaga[K] + 1) * (B/novi_NZV - (A-1)/novi_NZV);

		NZV = novi_NZV;
	}
	cout << rjesenje << endl;
}
