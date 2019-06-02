
#include <stdio.h>
#include <stdlib.h>
#include "maja.h"

	int l, n, ile_pytan;

	int gramy = 0;

	void blad(char* s) {
		printf("BLAD: %s\n", s);
		exit(1);
	}
	
	int gramy_dalej() {
		if (gramy) blad("powinienes sprobowac zgadnac liczbe przed kolejna gra");
		printf("Podaj n - ograniczenie górne na liczby w grze (0 - koniec): ");
		scanf("%d", &n);
		if (n <= 0) return 0; else {
			do {
				printf("Podaj liczbe jaka ma wymyslic Maja ");
				scanf("%d", &l);
				if (l <= 0 || l > n) printf("zle, liczba poza zakresem!");
			} while (l <= 0 || l > n);
			gramy = 1;
			ile_pytan=0;
			return n;
		}
	}

	int czy_podzielna_przez(int m) {
		if (!gramy) blad("nie zainicjalizowano gry, zapytanie o podzielnosc");
		if (m <= 0) blad("podano m niedodatnie"); 
		ile_pytan++;
		return ((l%m)==0);
	}
	
	void zgaduj(int k) {
		if (!gramy) blad("nie zainicjalizowano gry, proba zgadniecia");
		if (k == l) printf("Twoj program zgadl w %d pytaniach! ta liczba to %d\n", ile_pytan, l);
			else printf("Twoj program nie zgadl! ta liczba to %d a nie %d\n", l, k);
		gramy = 0;	
	}
