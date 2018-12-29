/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kwadraty                                           *
 *   Autor programu:       Adam Karczmarz                                     *
 *   Zlozonosc czasowa:    O(1)                                               *
 *   Zlozonosc pamieciowa: O(1)                                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cmath>
#define scanf(Args...) (scanf(Args)?:0)
using namespace std;

typedef long long LL;

const int s12 = 1 + 4 + 9 + 16 + 25 + 36 + 49 + 64 + 81 + 100 + 121 + 144;
const int dpkw = 30;
const int magicConst = 130;

bool dasie[s12 + 1][dpkw];
int k[s12 + 1];

void preprocessing() {
	for (int i = 0; i < dpkw; ++i)
		dasie[0][i] = true;
	for (int i = 1; i <= s12; ++i) {
		k[i] = 100;
		for (int j = 1; j < dpkw && j * j <= i; ++j) {
			dasie[i][j] = (dasie[i][j - 1] || dasie[i - j * j][j - 1]);
			if (k[i] == 100 && dasie[i][j])
				k[i] = j;
		}
		for (int j = 1; j < dpkw; ++j)
			dasie[i][j] |= dasie[i][j - 1];
	}
}

LL n;

int ileprzerosdox (int x) {
	int zl = 0, min = 99;
	for (int i = s12; i > 0; --i) {
		if (k[i] < min)
			min = k[i];
		if (i <= x && k[i] > min)
			++zl;
	}
	return zl;
}

int main() {
	preprocessing();
	scanf("%Ld", &n);
	if (n <= s12) {
		if (k[int(n)] == 100)
			printf("- ");
		else
			printf("%d ", k[int(n)]);
		printf("%d\n", ileprzerosdox(int(n)));
	} else {
		int indeks = 0;
		LL suma = 0LL;
		for (; suma < n; ++indeks, suma += LL(indeks) * indeks);
		int K = (suma - n > magicConst? indeks : (k[s12 - int(suma - n)] > 12? indeks + 1 : indeks));
		printf("%d ", K);
		LL wynik = 0LL;
		wynik += LL(ileprzerosdox(s12));
		wynik += LL(ileprzerosdox(s12) - ileprzerosdox(s12 - magicConst)) * (indeks - 12 - 1);
		if (suma - n <= magicConst)
			wynik += LL(ileprzerosdox(s12 - int(suma - n)) - ileprzerosdox(s12 - magicConst));
		printf("%Ld\n", wynik);
	}
}
