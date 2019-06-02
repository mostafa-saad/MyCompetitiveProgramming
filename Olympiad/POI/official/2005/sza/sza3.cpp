/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZA (Szablon)                                  *
 *   Plik:                sza3.cpp                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nadoptymalne                       *
 *                        Program o z³o¿ono¶ci czasowej                  *
 *                        i pamiêciowej O(n), obliczaj±cy d³ugo¶ci       *
 *                        szablonów on-line.                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<string>
using namespace std;

#define MAX_LEN 500000

/* Deklaracje zmiennych globalnych. */
int pref_suf[MAX_LEN + 1];      // Tablica d³ugo¶ci najd³u¿szych prefikso-sufiksów
                           // (tak zwana funkcja prefiksowa).
char sl[MAX_LEN];               // Rozwa¿ane s³owo.
int n;                          // D³ugo¶æ rozwa¿anego s³owa.

int zakres[MAX_LEN + 1],        // Zakresy s³owa, które mo¿na pokryæ poszczególnymi
                           // prefiksami s³owa, jako szablonami.
 szablony[MAX_LEN + 1];         // Najkrótsze szablony dla kolejnych
                           // prefiksów s³owa.


/* Procedura wyliczaj±ca warto¶ci funkcji prefiksowej
 * dla podanego w parametrze s³owa.
 * Zak³adamy przy tym dla u³atwienia, ¿e
 * litery s³owa s± numerowane od jedynki (czyli litera
 * zerowa s³owa jest nieznacz±ca). */
void licz_pref_suf(string slowo)
{
  int k = 0;

  /* Inicjalizacja funkcji prefiksowej. */
  pref_suf[0] = pref_suf[1] = 0;

  /* Wyliczanie kolejnych warto¶ci funkcji prefiksowej. */
  for (int q = 2; q <= n; q++) {
    /* Niezmiennik: najd³u¿szy prefikso-sufiks prefiksu danego
       s³owa o d³ugo¶ci q ma d³ugo¶æ k. */
    while (k > 0 && slowo[k + 1] != slowo[q])
      k = pref_suf[k];
    if (slowo[k + 1] == slowo[q])
      k++;
    pref_suf[q] = k;
  }                             /* for */
}                               /* licz_pref_suf */


int main()
{
  /* Odczyt s³owa i wyliczenie funkcji prefiksowej. */
  scanf("%s", sl);
  n = strlen(sl);
  licz_pref_suf('a' + string(sl));

  /* Obliczanie najkrótszych szablonów dla prefiksów s³owa,
     wykonywane on-line. */
  for (int j = 1; j <= n; j++)
    szablony[j] = zakres[j] = j;

  /* Pêtla po wszystkich, d³u¿szych ni¿ jeden, prefiksach
     danego s³owa - w j-tym kroku rozwa¿amy j-ty prefiks. */
  for (int j = 2; j <= n; j++) {
    int b = pref_suf[j];
    if (b > 0) {
      /* Sprawdzamy, czy najkrótszy szablon najd³u¿szego prefikso-sufiksu
         danego prefiksu s³owa jest dobrym szablonem dla aktualnego
         prefiksu: */
      int q = szablony[b];
      if (zakres[q] >= j - q) {
        /* je¿eli tak, to wybieramy jego jako szablon, */
        szablony[j] = q;
        zakres[q] = j;
      }                         /* if */
      /* je¿eli nie, to ju¿ jest ustawione szablony[i]=i. */
    }                           /* if */
  }                             /* for */

  /* Wypisanie wyniku */
  printf("%d\n", szablony[n]);
  return 0;
}                               /* main */
