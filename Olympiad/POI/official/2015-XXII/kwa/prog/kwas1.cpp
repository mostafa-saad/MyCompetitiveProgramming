/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kwadraty                                           *
 *   Autor programu:       Adam Karczmarz                                     *
 *   Zlozonosc czasowa:    O(n ^ 4/3)                                         *
 *   Zlozonosc pamieciowa: O(n ^ 4/3)                                         *
 *   Opis:                 Rozwiazanie wolne                                  *
                                                                              *
 *****************************************************************************/

#include <cstdio>
#define scanf(Args...) (scanf(Args)?:0)
using namespace std;

int n;

int main() {
	scanf("%d", &n);
	int ind = 0, sum = 0;
	for (; sum < n; ++ind, sum += ind * ind);
	ind += 3;
	if (ind < 15)
		ind = 15;
	bool dasie[sum + 1][ind];
	int k[sum + 1];
	for (int i = 0; i <= sum; ++i)
		for (int j = 0; j < ind; ++j)
			dasie[i][j] = false;
	for (int j = 0; j < ind; ++j)
		dasie[0][j] = true;

	for (int i = 1; i <= sum; ++i)
		for (int j = 1; j < ind; ++j)
			dasie[i][j] = (dasie[i][j - 1] || (j * j <= i? dasie[i - j * j][j - 1] : false));

	for (int i = 0; i <= sum; ++i) {
		k[i] = 1000000000;
		for (int j = ind - 1; j >= 0; --j)
			if (dasie[i][j])
				k[i] = j;
	}

	if (k[n] == 1000000000)
		printf("- ");
	else
		printf("%d ", k[n]);

	int min = 1000000, zl = 0;
	for (int i = sum; i >= 0; --i) {
		if (k[i] < min)
			min = k[i];
		if (k[i] > min && i <= n)
			++zl;
	}

	printf("%d\n", zl);

}
