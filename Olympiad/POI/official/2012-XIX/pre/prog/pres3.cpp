/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne: sprawdzanie rownowaznosci   *
 *                      cyklicznej slow za pomoca KMP                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1000005;

int N;
char word[2 * MAXN];

/* KMP z funkcja prefiksowa
 * Slowa numerujemy od 0. */

/* Funkcja prefiksowa dla slowa a. */
vector<int> compute(const char *a, int n) {
  vector<int> p(n);
  int j = 0;
  for (int i = 1; i < n; ++i) {
    while (j && a[j] != a[i]) j = p[j - 1];
    if (a[j] == a[i]) ++j;
    p[i] = j;
  }
  return p;
}

/* KMP - sprawdza, czy wzorzec a wystepuje w tekscie b. */
bool kmp(const char *a, int n, const char *b, int m) {
  vector<int> p(compute(a, n));
  int j = 0;
  for (int i = 0; i < m; ++i) {
    while (j && a[j] != b[i]) j = p[j - 1];
    if (a[j] == b[i]) ++j;
    if (j == n) return true;
  }
  return false;
}

bool cycEq(int len) {
  memcpy(word + N + 1, word + N + 1 - len, len * sizeof(char));
	return kmp(word + 1, len, word + N + 1 - len, 2 * len);
}

int main() {
	scanf("%d%s", &N, word + 1);
	for (int i = N / 2; i > 0; --i) {
		if (cycEq(i)) {
			printf("%d\n", i);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
