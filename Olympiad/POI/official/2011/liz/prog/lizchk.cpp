/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Lizak                                            *
 *   Autor:             Mateusz Baranowski                               *
 *   Opis:              Program sprawdzajacy wyjscia                     *
 *                                                                       *
 *************************************************************************/

#include "weryfikator.h"

#define MAX_N 1000000

void wrong(const char* msg, int line, int pos)
{
    fprintf(stdout, "WRONG\n%s\n", msg);
	exit(EXIT_SUCCESS);
}

FILE *in, *out;

int n, m, k, i, a, b, w;
int sum[MAX_N + 1];
int maks[2];
char s[MAX_N];
char c;

void oblicz_pomocnicze() {
	int i = 0;

	sum[0] = 0;
	for (i = 0; i < n; ++i)
		if (s[i] == 'T')
			sum[i + 1] = sum[i] + 2;
		else
			sum[i + 1] = sum[i] + 1;

	maks[sum[n] % 2] = sum[n];
	i = 0;
	while ((i < n) && (s[i] == 'T') && (s[n-i-1] == 'T'))
		++i;

	if (i == sum[n])
		maks[1 - (sum[n] % 2)] = 0;
	else
		maks[1 - (sum[n] % 2)] = sum[n] - i * 2 - 1;
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Bledna ilosc argumentow\n");
		exit(EXIT_FAILURE);
	}

	in = fopen(argv[1], "r");
	fscanf(in, "%d%d%s", &n, &m, s);

	oblicz_pomocnicze();

	out = fopen(argv[2], "r");
	Scanner odp(out, wrong, PL);

	for (i = 0; i < m; ++i) {
		fscanf(in, "%d", &k);
		a = 0;
		c = odp.readChar();
		while ((c <= '9') && (c >= '0')	&& (a < n)) {
			a = a*10 + c - 48; 
			c = odp.readChar();
		}

		if (a == 0) {
			if ((c == 'N') && (odp.readChar() == 'I')
					&& (odp.readChar() == 'E')) {
				if (maks[k % 2] >= k)
					wrong ("Oczekiwano przedzial, otrzymano 'NIE'", 0, 0);
			} else
				wrong ("Bledny format odpowiedzi: Nieoczekiwany znak", 0, 0);
		} else {
			if ((a > n) || (a == 0))
				wrong ("Liczba calkowita spoza zakresu", 0, 0);

			if (c != ' ')
				wrong ("Brak Spacji", 0, 0);

			b = odp.readInt(1, n);
			if (a > b)
				wrong ("Bledny przedzial", 0, 0);
			else {
				if (maks[k % 2] < k)
					wrong ("Oczekiwano 'NIE', otrzymano przedzial", 0, 0);
				w = sum[b] - sum[a-1];
				if (w != k) {
					printf ("WRONG\n");
					printf ("Oczekiwano przedzialu o koszcie %d", k);
					printf (" otrzymano przedzial wartosci %d\n", w);
					exit (EXIT_SUCCESS);
				}
			}
		}
		odp.skipWhitespacesUntilEOLN();
		odp.readEoln();
	}
	odp.readEof();
	
 	printf("OK\n"); 
	exit(EXIT_SUCCESS);
}
