/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     poslib.c                                                  *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Biblioteka interaktywna                                   *
 *                                                                       *
 *************************************************************************/

/*
	Mozliwe strategie:
	S_SPRAWIEDLIWA: odpowiada dla z gory wybranego pietra
	S_PESYMISTYCZNA: udziela odpowiedzi tak, aby otrzymywac pesymistyczny koszt.
	S_OPTYMISTYCZNA: udziela odpowiedzi tak, aby poprawiac szacowanie na pesymistyczny koszt.
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "poslib.h"

#define MAX(a,b) ((a)>(b)?(a):b)

#define MAGIC 512345678
#define MAGIC_BEGIN -92345678
#define MAGIC_END -98765432
#define MAGIC_OUT -880403

#define MAXN 1000000000
#define MAXAB 10000

#define MIN_S 0
#define MAX_S 2
#define S_SPRAWIEDLIWA 0
#define S_PESYMISTYCZNA 1
#define S_OPTYMISTYCZNA 2

#define TAK 1
#define NIE 0
#define OK 1
#define ERR 0

static int Q[100*MAXAB]; // Q[i] - maksymalna liczba pieter wsrod ktorych mozna znalezc odpowiedz kosztem i
static char buf[1024]; // bufor na komunikaty
static int l,r; // przedzial w ktorym Bajtek moze wiedziec, ze jest odpowiedz.
static int w; // maksymalny koszt jaki pesymistycznie musi jeszcze poniesc Bajtek
static long long koszt; // koszt jaki poniosl juz Bajtek

static int N,A,B; // dane
static int strategia = -1; // strategia wykorzystywana przez biblioteke
static int pietro; // pietro - jezeli S_SPRAWIEDLIWA

static int zainicjowane = 0; // czy zostalo juz wywolana funkcja inicjuj

/*
Oblicza lub zwraca spamietane Q[i]
*/
static int q(int i) {
	 if(i < 0) return 0;
	 if(Q[i] == 0) { // jesli nie bylo jeszcze obliczone, to oblicz
		/* Majac do dyspozycji i bajtalarow zadajemy pytanie
		   i albo zostajemy z i-a bajtalarami i maksymalnie mozemy obsluzyc i-a pieter
		   albo zostajemy z i-b bajtalarami i maksymalnie mozemy obsluzyc i-b pieter
		*/
		Q[i] = q(i-A) + q(i-B);
		if(Q[i] == 0) Q[i] = 1; // zawsze mozna zgadnac jak sie ma jedno pietro.
	 }
	 return Q[i];
}



/*
Konczy prace z danym wynikiem i komentarzem.
*/
static void end(int wynik, char *komentarz) {
	printf("%d\n", MAGIC_OUT); // zaczecie outputu od magicznej liczby
	printf("wynik=%d n=%d a=%d b=%d strategia=%d pietro=%d\n", wynik, N, A, B, strategia, pietro);
	printf("%s\n", komentarz);
	exit(0);
}

static int use_interactive = 0;

void interactive_inicjuj(int *n, int *a, int *b) {
	if(N < 1 || N > MAXN || A < 1 || A > MAXAB || B < 1 || B > MAXAB || pietro < 1 || pietro > N) {
		end(ERR, "Nieprawidlowe dane na wejsciu\n");
	}
	koszt = 0;
	*n = N; *a = A; *b = B;
}

int interactive_pytaj(char c, int x) {
	if(c == 'W') {
		if(pietro > x) {
			koszt += A;
			return TAK;
		} else {
			koszt += B;
			return NIE;
		}
	} else { // c == 'N'
		if(pietro < x) {
			koszt += A;
			return TAK;
		} else {
			koszt += B;
			return NIE;
		}
	}
}

void interactive_odpowiedz(int wynik) {
    char buf[1024];
	if(wynik == pietro) {
        sprintf(buf, "Bajtkowi udalo sie zgadnac i wydal %lld bajtalarow.\n", koszt);
        end(OK, buf);
	} else {
        sprintf(buf, "Bajtek nie zgadl. Podal pietro %d, a powinien %d. Wydal %lld bajtalarow.\n", wynik, pietro, koszt);
        end(ERR, buf);
	}
}

/*
Inicjuje gre pomiedzy Bajtkiem i Bitocym.
*/
void inicjuj(int *n, int *a, int *b) {
	if(zainicjowane != 0) {
		end(ERR, "Program zawodnika moze wolac funkcje inicjuj tylko raz.");
	}
	zainicjowane = 1;
	int magic_begin, magic_end;
	scanf("%d", &magic_begin);
    if (magic_begin != MAGIC_BEGIN) {
        // interactive mode
        N = magic_begin;
        scanf("%d%d%d", &A, &B, &pietro);
        use_interactive = 1;
        interactive_inicjuj(n, a, b);
        return;
    }
	scanf("%d%d%d%d%d%d", &N, &A, &B, &strategia, &pietro, &magic_end);
	if(magic_begin!=MAGIC_BEGIN || N<1 || N>MAXN || A<1 || A>MAXAB || B<1 || B>MAXAB ||
			strategia<MIN_S || strategia>MAX_S || pietro<1 || pietro>N || magic_end!=MAGIC_END) {
		end(ERR, "Program zawodnika nie moze wczytywac zadanego inputu.");
	}
	
	l = 1; r = N;
	
	// Wyznacza koszt jaki musi poniesc Bajtek.
	int step = 1; w=step;
	do {
		w -= step;
		while(q(w) < N) w += step;
		step /= 2;
	} while(step != 0);
	
	koszt = 0;
	*n = N; *a = A; *b = B;
}

/*
Odpowiada na pytanie Bajtka zgodnie z wybrana strategia.
*/
int pytaj(char c, int x) {
    if (use_interactive) {
      return interactive_pytaj(c, x);
    }

	if(zainicjowane == 0) end(ERR, "Program zawodnika nie wywolal funkcji inicjuj.");
	if(c != 'N' && c != 'W') {
		end(ERR,"Nieprawidlowy argument do pytaj.");
	}
	
	/*
	Wyznaczanie, czy pytanie jest optymalne
	*/
	if(c == 'N' && (x <= l || x > r)) {
		sprintf(buf, "Pytanie o %d jest nieoptymalne (aktualny przedzial: [%d,%d])", x, l, r);
		end(ERR, buf);
	}
	if(c == 'W' && (x < l || x >= r)) {
		sprintf(buf, "Pytanie o %d jest nieoptymalne (aktualny przedzial: [%d,%d])", x, l, r);
		end(ERR, buf);
	}
	
	int nie_szer=0, tak_szer=0; // dlugosci przedzialow otrzymanych po odpowiedzi nie lub tak
	if(c == 'W') { nie_szer = x-l+1; tak_szer = r-x; }
	else /* c == 'N' */ { tak_szer = x-l; nie_szer = r-x+1; }
	
	if(q(w - B) < nie_szer) { // po odpowiedzi NIE zwieksza sie szacowanie na pesymistyczny koszt
		int w2 = w - B; while(q(w2) < nie_szer) w2++;
		sprintf(buf, "Mozliwy pesymistyczny koszt: %lld. Po zadaniu tego pytania - %lld.", koszt+w, koszt+w2+B);
		end(ERR, buf);
	}
	if(q(w - A) < tak_szer) { // po odpowiedzi TAK zwieksza sie szacowanie na pesymistyczny koszt
		int w2 = w - A; while(q(w2) < tak_szer) w2++;
		sprintf(buf, "Mozliwy pesymistyczny koszt: %lld. Po zadaniu tego pytania - %lld.", koszt+w, koszt+w2+A);
		end(ERR, buf);
	}
	
	/*
	Wyznaczenie odpowiedzi na pytanie w zaleznosci od strategii
	*/
	int koszt_nie = w - B, koszt_tak = w - A; // pesymistyczne koszty, gdy odpowie sie NIE badz TAK.
	while(q(koszt_nie) >= nie_szer) koszt_nie--; koszt_nie++;
	while(q(koszt_tak) >= tak_szer) koszt_tak--; koszt_tak++;
	int odp=TAK;
	if(strategia == S_SPRAWIEDLIWA) {
		if(c == 'W') { if(pietro > x) odp = TAK; else odp = NIE; }
		else /* c == 'N' */ { if(pietro < x) odp = TAK; else odp = NIE; }
	} else if(strategia == S_PESYMISTYCZNA) {
		if(koszt_nie + B > koszt_tak + A) odp = NIE; else odp = TAK;
	} else if(strategia == S_OPTYMISTYCZNA) {
		if(koszt_nie + B > koszt_tak + A) odp = TAK; else odp = NIE;
	}
	
	/*
	Udzielanie odpowiedzi
	*/
	if(odp == TAK) {
		if(c == 'W') l = x+1; else /* c == 'N' */ r = x-1;
		w = koszt_tak;
		koszt += A;
	} else /* odp == NIE */ {
		if(c == 'W') r = x; else /* c == 'N' */ l = x;
		w = koszt_nie;
		koszt += B;
	}
	return odp;
}

/*
Weryfikuje odpowiedz otrzymana od Bajtka
*/
void odpowiedz(int wynik) {
    if (use_interactive) {
      interactive_odpowiedz(wynik);
      return;
    }

	if(zainicjowane == 0) end(ERR, "Program zawodnika nie wywolal funkcji inicjuj.");
	
	if(l == r && l == wynik) { // ok
		sprintf(buf, "Koszt: %lld.", koszt);
		end(OK, buf);
	}
	if(l != r) { // jeszcze nie dosc pytan aby udzielic jednoznacznej odpowiedzi
		sprintf(buf, "Niedostateczna liczba pytan. (aktualny przedzial: [%d, %d]).", l, r);
		end(ERR, buf);
	}
	if(l != wynik) { // zly wynik
		sprintf(buf, "Oczekiwano pietra %d, wczytano pietro %d.", l, wynik);
		end(ERR, buf);
	}
}
