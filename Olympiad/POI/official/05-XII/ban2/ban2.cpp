/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Banknoty)                                 *
 *   Plik:                ban2.cpp                                       *
 *   Autor:               Piotr Stañczyk                                 *
 *   Opis:                rozwi±zanie alternatywne, z³o¿onosæ O(n*m)     *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#define INF 2000
int uzyska[201][20001];
int uzyte[201];
int ilemonet;
int nominal[201], liczba[201];
int wyplata;
int ilenom;

void Wczytaj() {
    scanf("%d", &ilenom);
    for(int x=1;x<=ilenom;x++)
	scanf("%d", &nominal[x]);
    for(int x=1;x<=ilenom;x++)
	scanf("%d", &liczba[x]);
    scanf("%d", &wyplata);
}

void Rozwiaz() {
    for(int y=0;y<=wyplata;y++)
        uzyska[0][y] = INF;

    uzyska[0][0] = 0;
    for(int x=1;x<=ilenom;x++) {
	for(int y=wyplata; y>=0; y--)
	    uzyska[x][y] = uzyska[x-1][y];
	for(int y=wyplata - nominal[x]; y >= 0;y--)
	    for(int z=1;z<=liczba[x];z++) {
		if (y+z*nominal[x] > wyplata || uzyska[x][y+z*nominal[x]] <= uzyska[x][y]+z) break;
		uzyska[x][y+z*nominal[x]] = uzyska[x][y]+z;
	    }
    }
}

void Wypisz() {
    ilemonet = 0;
    int kopia = ilenom;
    while (wyplata > 0) {
	for(int x=0; x <= liczba[ilenom]; x++) if (uzyska[ilenom - 1][wyplata - x*nominal[ilenom]] == uzyska[ilenom][wyplata] - x) {
	    wyplata -= x*nominal[ilenom];
	    uzyte[ilenom] += x;
	    ilemonet += x;
	    ilenom--;
	    break;
	}
    }
    printf("%d\n", ilemonet);
    for(int x=1;x<kopia;x++) printf("%d ", uzyte[x]);
    printf("%d\n", uzyte[kopia]);
}

int main() {
    Wczytaj();
    Rozwiaz();
    Wypisz();
    return 0;
}
