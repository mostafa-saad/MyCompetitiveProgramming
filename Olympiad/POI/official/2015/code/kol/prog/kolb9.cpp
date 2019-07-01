/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(1)                                               *
 *   Opis:                 Rozwiazanie bledne                                 *
 *****************************************************************************/

#include "ckollib.h"

int main() {
	int wynik = 0, liczba;
	while((liczba = karta()) != 0) {
		wynik ^= liczba;
	}
	odpowiedz(wynik);
	return 0;
}
