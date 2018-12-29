/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Biblioteka interaktywna                          *
 *                                                                       *
 *************************************************************************/


/*
    Mozliwe strategie:
    S_LOSOWA: gra losowo, dopoki stawka+pula < 1/2 n
    S_POPTYMALNA: gra optymalnie, ale myli sie w 10% przypadkow dopoki stawka+pula < 1/2 n
    S_OPTYMALNA: gra optymalnie
    S_OCEN: strategia ocen, wszystko losowe
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define S_LOSOWA 0
#define S_POPTYMALNA 1
#define S_OPTYMALNA 2
#define S_OCEN 3

#define OK 1
#define ERR 0

#define MAXN 30000
#define MAX_IND 250

#define WYGRYWAJACA 1
#define PRZEGRYWAJACA 2
#define NIEZNANA 0

#define MAGIC_IN_SUM 74967
#define MAGIC_OUT 756396726

#define ALOJZY 1
#define BAJTAZAR 2

#define PAS 1
#define P2 2
#define P3 3

static int n; // dane
static int strategia; // strategia wykorzystywana przez biblioteke
static int pozycja[MAXN + 1][MAX_IND]; // okresla, czy pozycja jest wygrywajaca czy przegrywajaca
static int optymalny_ruch[MAXN + 1][MAX_IND]; // okresla jaki ruch jest optymalny
static int indeks_stawki[MAXN + 1]; // zamienia wartosc stawki na indeks w tablicach pozycja i optymalny_ruch
static int zainicjowane = 0; // czy zostalo juz wywolana funkcja inicjuj
static int pula, stawka; // aktualna wartosc puli i stawki
static int kolej; // aktualny zawodnik
static int randval; //bardzo pseudo losowa wartosc
static int ruchocenval = 2; //zmienna na kolejny ruch ocen

//Zmienia i zwraca pseudo losowego inta
static int randint(){
    randval = (randval + 3) * (randval + 7);
    randval %= 100;
    return randval;
}

//Zwraca kolejno Podwojenie, Potrojenie, Pas, Podwojenie, ...
static int ruch_ocen(){
    ruchocenval = (ruchocenval + 1) % 3;
    return PAS + ruchocenval;
}
    

//Wypelnia tablice indeks_stawki
static void oblicz_indeksy(int maxn){
    int aind = 0;
    int i, j;
    for(i = 1; i <= maxn; i *= 2){
        for(j = 1; i * j <= maxn; j *= 3){
            indeks_stawki[i * j] = aind++;
        }
    }
}

//Konczy prace z danym wynikiem i komentarzem.
static void koncz(int wynik, const char *komentarz) {
    printf("%d\n", MAGIC_OUT); // pierwsza linia: magic out
    printf("%d\n", wynik); // druga linia: wynik
    printf("%s\n", komentarz); // trzecia linia: komentarz
    exit(0);
}

//sprawdza rekurencyjnie drzewo gry spamietujac wyniki, ustawia tez optymalny ruch
static int sprawdz_pozycje(int pula_poz, int stawka_poz){
    if(pula_poz + stawka_poz >= n)return PRZEGRYWAJACA;
    int stawka_ind = indeks_stawki[stawka_poz];
    if(pozycja[pula_poz][stawka_ind] != NIEZNANA)return pozycja[pula_poz][stawka_ind];
    int rPAS = sprawdz_pozycje(pula_poz + stawka_poz, 1);
    int rP2 = sprawdz_pozycje(pula_poz, stawka_poz * 2);
    int rP3 = sprawdz_pozycje(pula_poz, stawka_poz * 3);
    if(rPAS == PRZEGRYWAJACA){
        optymalny_ruch[pula_poz][stawka_ind] = PAS;
        pozycja[pula_poz][stawka_ind] = WYGRYWAJACA;
        return WYGRYWAJACA;
    }
    if(rP2 == PRZEGRYWAJACA){
        optymalny_ruch[pula_poz][stawka_ind] = P2;
        pozycja[pula_poz][stawka_ind] = WYGRYWAJACA;
        return WYGRYWAJACA;
    }
    if(rP3 == PRZEGRYWAJACA){
        optymalny_ruch[pula_poz][stawka_ind] = P3;
        pozycja[pula_poz][stawka_ind] = WYGRYWAJACA;
        return WYGRYWAJACA;
    }
    pozycja[pula_poz][stawka_ind] = PRZEGRYWAJACA;
    optymalny_ruch[pula_poz][stawka_ind] = PAS + randint() % 3;
    return PRZEGRYWAJACA;
}

//Generuj ruch Bajtazara, biorac pod uwage strategie
static int generuj_ruch(){
    sprawdz_pozycje(pula, stawka);
    if((strategia != S_OCEN && pula + stawka >= (n * 5 / 7)) || strategia == S_OPTYMALNA || (strategia == S_POPTYMALNA && randint() % 10 != 3)){
        return optymalny_ruch[pula][indeks_stawki[stawka]];
    }
    if(strategia == S_OCEN){
        return ruch_ocen();
    }
    return PAS + randint() % 3;
}

//Inicjuje gre pomiedzy Alojzym i Bajtazarem
int inicjuj() {
    if(zainicjowane != 0) {
        koncz(ERR, "Program zawodnika moze wolac funkcje inicjuj tylko raz.");
    }
    zainicjowane = 1;
    int magic;
    scanf("%d%d%d", &n, &strategia, &magic);
    if(n < 1 || n > MAXN || strategia < 0 || strategia > 3 || n + strategia + magic != MAGIC_IN_SUM){
        koncz(ERR, "Program zawodnika nie moze wczytywac zadanego inputu.");
    }
    pula = 0;
    stawka = 1;
    kolej = ALOJZY;
    oblicz_indeksy(n);
    return n;
}

//Aktualizuje pule i stawke, biorac pod uwage ruch X
static void wykonaj_ruch(int x){
    if(x == PAS){
        pula = pula + stawka;
        stawka = 1;
    }
    else if(x == P2){
        stawka = stawka * 2;
    }
    else if(x == P3){
        stawka = stawka * 3;
    }
}

//Wykonuje ruch gracza
void alojzy(int x) {
    if(zainicjowane == 0) koncz(ERR, "Program zawodnika nie wywolal funkcji inicjuj.");
    if(x != PAS && x != P2 && x != P3){
        koncz(ERR, "Nieprawidlowy ruch Alojzego.");
    }
    if(kolej != ALOJZY){
        koncz(ERR, "Ruch Alojzego bez wczesniejszego ruchu Bajtazara.");
    }
    if(pula + stawka >= n){
        koncz(ERR, "Suma puli i stawki przekroczyla n.");
    }
    kolej = BAJTAZAR;
    wykonaj_ruch(x);
}

//Generuje i wykonuje ruch Bajtazara
int bajtazar(){
    if(zainicjowane == 0) koncz(ERR, "Program zawodnika nie wywolal funkcji inicjuj.");
    if(kolej != BAJTAZAR){
        koncz(ERR, "Pytanie o ruch Bajtocego przed wykonaniem ruchu Alojzego.");
    }
    if(pula + stawka >= n){
        koncz(OK, "");
    }
    int x = generuj_ruch();
    kolej = ALOJZY;
    wykonaj_ruch(x);
    return x;
}
