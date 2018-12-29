/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kupchk.cpp                                                *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Program weryfikujacy poprawnosc wyjscia wygenerowanego    *
 *             przez program zawodnika, format:                          *
 *             ./kupchk.e in out_zawodnika out_wzorcowy                  *
 *                                                                       *
 *************************************************************************/

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int v[2000][2048];

__attribute__ ((format (printf, 1, 2)))
void error(const char *fmt, ...)
{
	va_list fmt_args;
	printf("WRONG\n");
	va_start(fmt_args, fmt);
	vprintf(fmt, fmt_args);
	va_end(fmt_args);
	exit(1);
}

int main(int argc, char *argv[])
{
	int k, n, x1, y1, x2, y2;
	long long s = 0;

	/* czytanie .in */
	FILE *f = fopen(argv[1], "r");
	fscanf(f, "%d%d", &k, &n);
	for (int y = 0; y < n; y++)
	for (int x = 0; x < n; x++)
		fscanf(f, "%d", &v[x][y]);
	fclose(f);
	
	/* czytanie wzorcowego .out */
	f = fopen(argv[3], "r");
	char buf[20];
	fscanf(f, "%4s", buf);
	bool sol_exists = strcmp(buf, "NIE") != 0;
	fclose(f);
	
	f = fopen(argv[2], "r");
	char *err;
	fscanf(f, "%7s", buf);
	if (!sol_exists)
		if (strcmp(buf, "NIE") != 0)
			error("oczekiwano 'NIE'");
		else {
			printf("OK\n");
			return 0;
		}
	if (strcmp(buf, "NIE") == 0)
		error("spodziewano sie rozwiazania, a wczytano 'NIE'");
	x1 = strtol(buf, &err, 10);
	if (strlen(buf) > 6 || *err)
		error("blad przy wczytywaniu x1");
	if (x1 <= 0 || x1 > n)
		error("x1=%d poza zakresem", x1);
	fscanf(f, "%7s", buf);
	y1 = strtol(buf, &err, 10);
	if (strlen(buf) > 6 || *err)
		error("blad przy wczytywaniu y1");
	if (y1 <= 0 || y1 > n)
		error("y1=%d poza zakresem", y1);
	fscanf(f, "%7s", buf);
	x2 = strtol(buf, &err, 10);
	if (strlen(buf) > 6 || *err)
		error("blad przy wczytywaniu x2");
	if (x2 <= 0 || x2 > n)
		error("x2=%d poza zakresem", x2);
	fscanf(f, "%7s", buf);
	y2 = strtol(buf, &err, 10);
	if (strlen(buf) > 6 || *err)
		error("blad przy wczytywaniu y2");
	if (y2 <= 0 || y2 > n)
		error("y2=%d poza zakresem", y2);
	for (int x = x1 - 1; x < x2; x++)
	for (int y = y1 - 1; y < y2; y++)
		s += v[x][y];
	if (s < k)
		error("cena=%lld<%d=k", s, k);
	if (s > 2 * k)
		error("cena=%lld>%d=2k", s, 2 * k);

	printf("OK\n");	
	return 0;
}
