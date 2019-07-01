/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon.cpp                                                    *}
{*   Autor:   Jakub Pachocki                                             *}
{*   Opis:    Rozwiązanie wzorcowe                                       *}
{*            Złożoność: O(n + m)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include <cstdio>

const int N = 5000;

int n;

int count[N];
int degree[N];

int main() {
	scanf("%d", &n);
	int edges = 0;
	for (int i = 1; i <= n; ++i) {
		int currentDegree;
		scanf("%d", &currentDegree);
		++count[currentDegree];
		edges += currentDegree;
		while (getchar() != '\n'); // pomijamy opis krawedzi
	}
	edges /= 2;
	int last = 0;
	for (int i = n - 1; i >= 0; --i)
		for (int j = 0; j < count[i]; ++j)
			degree[last++] = i;
	int m = 1;
	int result = 0;
	int sum = 0;
	for (int i = 0; i < n - 1; ++i) {
		sum += degree[i] - i;
		if (sum == edges) {
			if (degree[i + 1] == degree[i])
				result += count[degree[i]];
			else
				++result;
		}
	}
	printf("%d\n", result);

}
