/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     poslib.c                                                  *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Przykladowa biblioteka dla zawodnikow do C/C++            *
 *                                                                       *
 *************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "poslib.h"

#define MAXN 1000000000
#define MAXAB 10000

#define TAK 1
#define NIE 0

static int N;
static int A,B;
static long long koszt;
static int pietro;

void inicjuj(int *n, int *a, int *b) {
    printf("Biblioteka: wczytuje ze standardowego wejscia liczby N, A, B oraz numer pietra, na ktorym Bitocy uwiezil Bajtyne.\n");

	scanf("%d%d%d%d", &N, &A, &B, &pietro);
	if(N < 1 || N > MAXN || A < 1 || A > MAXAB || B < 1 || B > MAXAB || pietro < 1 || pietro > N) {
		printf("Nieprawidlowe dane!\n");
		exit(0);
	}
	koszt = 0;
	*n = N; *a = A; *b = B;

	printf("Bajtek: Jestem gotowy! Podaj liczbe pieter oraz koszty odpowiedzi A i B.\n");
	printf("Bitocy: Wieza ma %d pieter. Koszt odpowiedzi TAK to %d, a NIE - %d bajtalarow.\n", N, A, B);
}

int pytaj(char c, int x) {
	if(c == 'W') {
		printf("Bajtek: Czyz kochana ma Bajtyna jest wyzej niz pietro %d?\n", x);
		if(pietro > x) {
			koszt += A;
			printf("Bitocy: Tak, Bajtyna jest wyzej niz pietro %d. Do tej pory wydales %lld bajtalarow.\n", x, koszt);
			return TAK;
		} else {
			koszt += B;
			printf("Bitocy: Nie, Bajtyna nie jest wyzej niz pietro %d. Do tej pory wydales %lld bajtalarow.\n", x, koszt);
			return NIE;
		}
	} else { // c == 'N'
		printf("Bajtek: Czyz kochana ma Bajtyna jest nizej niz pietro %d?\n", x);
		if(pietro < x) {
			koszt += A;
			printf("Bitocy: Tak, Bajtyna jest nizej niz pietro %d. Do tej pory wydales %lld bajtalarow.\n", x, koszt);
			return TAK;
		} else {
			koszt += B;
			printf("Bitocy: Nie, Bajtyna nie jest nizej niz pietro %d. Do tej pory wydales %lld bajtalarow.\n", x, koszt);
			return NIE;
		}
	}
}

void odpowiedz(int wynik) {
	printf("Bajtek: Ma kochana jest na pietrze %d!\n", wynik);
	if(wynik == pietro) {
		printf("Bitocy: Ugh.. Zgadles. Ale wzbogacilem sie o %lld bajtalarow... tylko Bajtyna wie, czy mogles ja znalezc, wydajac mniej.\n", koszt);
	} else {
		printf("Bitocy: Bwahaha! Wydales %lld bajtalarow, a i tak zgadles zle :-P. Pozegnaj sie ze swoja ukochana, a ja wlasnie ide do niej na pieterko... %d.\n", koszt, pietro);
	}
	exit(0);
}
