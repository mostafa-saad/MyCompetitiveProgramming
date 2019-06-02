/*
Zadanie PRE, generator plikow wejsciowych.
Autor: Dawid Dabrowski + Jan Kanty Milczek (te dobre testy co cokolwiek ubijają)
*/

// Specyfikacja testow znajduje sie w opracowaniu zadania.

#include <cassert>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#include "oi.h"

oi::Random RG;

const int MAXN = 1000000;

const int test[] = {-1, 100, 301, 500, 4000, 5000, 100000, 200000, 500000, 1000000, 1000000};
const int testdk[] = {-1, 20, 70, 100, 450, 1000,  200,  500,  114000,  220000,  216522};
const int wyn[] = {-1, 9, 39, 100, 543, 13000, 5001, 10000, 5000, 13, 400323};

FILE *output;

string word;

void testa(int numer) {
	printf("generuje test %da\n",numer);
	char filename[20];
	sprintf(filename,"../in/pre%da.in",numer);
	output=fopen(filename,"w");
	fprintf(output, "%d\n", test[numer]);
	word = "";
	for (int i=0; i<test[numer]; ++i) {
		word += __builtin_popcount(i)%2 ? 'a' : 'b';
	}
	fprintf(output, "%s\n", word.c_str());
	fclose(output);
}

// slowo fibonacciego
const int FIB_LIMIT = 28;
string fib[FIB_LIMIT + 1];
int fib_nr[] = {-1, 1, 2, 3, 5, 10, 11, 12, 16, 23, 27};
void testb(int numer) {
	printf("generuje test %db\n",numer);
	char filename[20];
	sprintf(filename,"../in/pre%db.in",numer);
	output=fopen(filename,"w");
	fprintf(output, "%d\n", fib[fib_nr[numer]].size());
	fprintf(output, "%s\n", fib[fib_nr[numer]].c_str());
	fclose(output);
}

void gen_fib() {
	fib[0] = 'b';
	fib[1] = 'a';
	for (int i=2; i<FIB_LIMIT; ++i) {
		fib[i] = fib[i-1] + fib[i-2];
	}
}

char ch[1000005];
void testc(int numer) {
	printf("generuje test %dc\n",numer);
	char filename[20];
	sprintf(filename,"../in/pre%dc.in",numer);
	output=fopen(filename,"w");
	int n = test[numer];
	fprintf(output, "%d\n", n);
	int kub = (int)sqrt(n);
	RG.setSeed(n+123321);
	for (int i=0; i<kub; ++i) ch[i] = RG.rand()%26 + 'a';
	for (int i=0; i<n; ++i) fprintf(output, "%c", ch[i%kub]);
	fprintf(output, "\n");
	fclose(output);
}

string losowy(int dl) {
	string ret = "";
	for (int i = 0; i < dl; ++i)
		ret += 'b' + RG.rand() % 3;
	return ret;
}

void testd(int numer) {
	printf("generuje test %dd\n",numer);
	char filename[20];
	sprintf(filename,"../in/pre%dd.in",numer);
	output=fopen(filename,"w");
	int ile = test[numer];
	fprintf(output, "%d\n", ile);
	int reszta = ile - testdk[numer] * 4 + 2;

	RG.setSeed(ile+23321);
	int przerwaboczna = RG.rand() % (reszta / 2 - 1) + 1;

	string boczny = losowy(przerwaboczna);
	string srodek = losowy(reszta - przerwaboczna * 2);
	assert(boczny.length() + srodek.length() + boczny.length() + testdk[numer] * 4 - 2 == ile);

	for (int i = 0; i < testdk[numer]; ++i)
		fprintf(output, "%c", 'a');

	fprintf(output, "%s", boczny.c_str());

	for (int i = 0; i < testdk[numer] - 1; ++i)
		fprintf(output, "%c", 'a');
	
	fprintf(output, "%s", srodek.c_str());

	for (int i = 0; i < testdk[numer] - 1; ++i)
		fprintf(output, "%c", 'a');

	fprintf(output, "%s", boczny.c_str());

	for (int i = 0; i < testdk[numer]; ++i)
		fprintf(output, "%c", 'a');

	fprintf(output, "\n");
	fclose(output);
}

void teste(int numer) {
	printf("generuje test %de\n",numer);
	char filename[20];
	sprintf(filename,"../in/pre%de.in",numer);
	output=fopen(filename,"w");
	int ile = test[numer];
	fprintf(output, "%d\n", ile);
	string wyp = "";
	for (int i=0; i<ile; ++i) wyp += 'a';
	wyp[9] = 'b';
	wyp[ile - 9] = 'b';
	wyp[ile - 10] = 'b';
	fprintf(output, "%s\n", wyp.c_str());
	fclose(output);
}

void testf(int numer, int ile) {
	printf("generuje test %df\n",numer);
	char filename[20];
	sprintf(filename,"../in/pre%df.in",numer);
	output=fopen(filename,"w");
	fprintf(output, "%d\n", ile);
	for (int i=0; i<ile; ++i) fprintf(output, "%c", 'b');
	fprintf(output, "\n");
	fclose(output);
}

void ocengen() {
	printf("generuję testy ocen\n");
	output = fopen("../in/pre1ocen.in", "w");
	fprintf(output, "%d\n%s\n", 6, "zzzzzz");
	fclose(output);
	output = fopen("../in/pre3ocen.in", "w");
	fprintf(output, "%d\n%s\n", 31, "olimpiadainformatycznapiadaooli");
	fclose(output);
	output = fopen("../in/pre2ocen.in", "w");
	fprintf(output, "%d\n%s\n", 15, "papabaxyzpababa");
	fclose(output);
	output = fopen("../in/pre4ocen.in", "w");
	fprintf(output, "%d\n", 1000000);
	RG.setSeed(RG.rand());
	for (int i = 0; i < 1000000; ++i)
		fprintf(output, "%c", RG.rand() % 3 + 'a');
	fprintf(output, "\n");
	fclose(output);
}

int main() {
	gen_fib();
	RG.setSeed(111111);

	ocengen();

	for(int test=1; test<=10; ++test) {
		testa(test);
		testb(test);
		testc(test);
		testd(test);
		teste(test);
	}
	testf(1, 1);
	testf(10, 1000000);
	return 0;
}
