/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Drzewa (DRZ)                                               *}
{*   Plik:    drz.cpp                                                    *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwi±zanie autorskie, Z³o¿ono¶æ czasowa: O(n logn),       *}
{*            Z³o¿ono¶æ pamiêciowa: O(n)                                 *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <utility>
using namespace std;


#define MAX_N 50000
#define NIESK 1000000000 /* nieskoñczono¶æ */
#define ROOT 0 /* numer korzenia w dowolnym spo¶ród drzew mintree */


struct node
/* Wierzcho³ek drzewa mintree. */
{
  int lsyn, psyn; /* numer lewego i prawego syna */
  int lewy, prawy; /* wierzcho³ek reprezentuje przedzia³ [lewy, prawy] */
  int wart;
}; /* node */

/* Tablica drzew mintree:
 * 0 - A1, 1 - A2, 2 - A3, 3 - B1, 4 - B2, 5 - B3, 6 - C1, 7 - C2, 8 - C3 */
node mintree[9][2 * MAX_N];

int n, i;
int h[MAX_N];
/* Najmniejszy wspó³czynnik nieporz±dku dla zamian danego drzewa. */
long long wyn[MAX_N],
  wspol, /* Pocz±tkowy wspó³czynnik nieporz±dku. */
  akt; /* W³a¶nie liczony wspó³czynnik nieporz±dku. */

/* Tablica dl (drzewo-liczba) reprezentuje funkcjê, która pobiera numer
 * drzewa (miêdzy 0 a n-1) i zwraca jego wysoko¶æ po przenumerowaniu
 * (tak¿e pomiêdzy 0 a n-1).
 * Tablica ld (liczba-drzewo) jest odwróceniem poprzedniej funkcji.
 * Obie tablice s± wyliczane w procedurze przenumeruj. */
int dl[MAX_N], ld[MAX_N];



/*****************************************************************************/
/* Implementacja operacji na drzewach mintree                                */
/*****************************************************************************/

int akt_poz[9]; /* aktualne pozycje wierzcho³ków tworzonych w drzewach
                   mintree 0-8 */


int create(int ndrz, int l, int p)
/* Ta funkcja tworzy wierzcho³ek odpowiadaj±cy przedzia³owi [l, p] w drzewie
 * mintree o numerze ndrz. */
{
  int sr = (l + p) / 2, v = akt_poz[ndrz]++;
  mintree[ndrz][v].lewy = l; mintree[ndrz][v].prawy = p;
  mintree[ndrz][v].wart = NIESK;
  if (l == p)
    return v;
  mintree[ndrz][v].lsyn = create(ndrz, l, sr);
  mintree[ndrz][v].psyn = create(ndrz, sr + 1, p);
  return v;
} /* create */

void build()
/* Ta procedura buduje wszystkie drzewa mintree. */
{
  for (int nr = 0; nr < 9; nr++)
    akt_poz[nr] = 0;
  for (int nr = 0; nr < 9; nr++)
    create(nr, 0, n - 1);
} /* build */

void insert(int ndrz, int wierzch, int klucz, int wart)
/* Ta procedura wstawia element charakteryzowany przez parê (klucz,wart)
 * do drzewa mintree o numerze ndrz; wierzch to aktualnie rozwa¿any wierzcho³ek
 * drzewa. */
{
  mintree[ndrz][wierzch].wart = min(mintree[ndrz][wierzch].wart, wart);
  int l = mintree[ndrz][wierzch].lewy, p = mintree[ndrz][wierzch].prawy;
  if (l < p)
  {
    int sr = (l + p) / 2;
    if (klucz <= sr)
      insert(ndrz, mintree[ndrz][wierzch].lsyn, klucz, wart);
    else
      insert(ndrz, mintree[ndrz][wierzch].psyn, klucz, wart);
  } /* if */
} /* insert */

void del(int ndrz, int wierzch, int klucz)
/* Ta procedura usuwa element o danym kluczu z drzewa mintree o numerze
 * ndrz; wierzch to aktualnie rozwa¿any wierzcho³ek drzewa. */
{
  int l = mintree[ndrz][wierzch].lewy, p = mintree[ndrz][wierzch].prawy;
  if (l == p)
  {
    mintree[ndrz][wierzch].wart = NIESK;
    return;
  } /* if */
  int sr = (l + p) / 2;
  if (klucz <= sr)
    del(ndrz, mintree[ndrz][wierzch].lsyn, klucz);
  else
    del(ndrz, mintree[ndrz][wierzch].psyn, klucz);
  mintree[ndrz][wierzch].wart = 
    min(mintree[ndrz][mintree[ndrz][wierzch].lsyn].wart,
        mintree[ndrz][mintree[ndrz][wierzch].psyn].wart);    
} /* del */

int min_val(int ndrz, int wierzch, int lewy, int prawy)
/* Ta funkcja wykonuje operacjê "min_val" na drzewie mintree o numerze
 * ndrz dla przedzia³u I=[lewy,prawy] i wierzcho³ka v=wierzch. */
{
  if (lewy > prawy)
    return NIESK;
  int l = mintree[ndrz][wierzch].lewy, p = mintree[ndrz][wierzch].prawy;
  if (lewy <= l && p <= prawy)
    return mintree[ndrz][wierzch].wart;
  int sr = (l + p) / 2;
  if (lewy > sr)
    return min_val(ndrz, mintree[ndrz][wierzch].psyn, lewy, prawy);
  if (prawy <= sr)
    return min_val(ndrz, mintree[ndrz][wierzch].lsyn, lewy, prawy);
  return min(min_val(ndrz, mintree[ndrz][wierzch].lsyn, lewy, prawy),
             min_val(ndrz, mintree[ndrz][wierzch].psyn, lewy, prawy));
} /* min_val */

/*****************************************************************************/
/* Koniec implementacji operacji na drzewach mintree                         */
/*****************************************************************************/

pair<int, int> tmp[MAX_N]; /* pomocnicza tablica u¿ywana do sortowania drzew */

void przenumeruj()
/* Ta procedura oblicza tablice dl i ld. Tablica par (wysoko¶æ drzewa,drzewo)
 * zostaje posortowana w kolejno¶ci niemalej±cych wysoko¶ci. */
{
  for (int i = 0; i < n; i++)
    tmp[i] = make_pair(h[i], i);
  sort(tmp, tmp + n);
  for (int i = 0; i < n; i++)
  {
    dl[tmp[i].second] = i;
    ld[i] = tmp[i].second;
  } /* for */
} /* przenumeruj */


void licz_wspol()
/* Ta procedura liczy pocz±tkowy wspó³czynnik nieporz±dku. */
{
  wspol = 0LL;
  for (int i = 0; i < n - 1; i++)
    wspol += abs(h[i] - h[i + 1]);
} /* licz_wspol */



int f1(int a, int b, int h)
{
  return -abs(a - h) - abs(h - b) + a + b;
} /* f1 */

int f2(int a, int b, int h)
{
  return -abs(a - h) - abs(h - b) - a + b;
} /* f2 */

int f3(int a, int b, int h)
{
  return -abs(a - h) - abs(h - b) - a - b;
} /* f3 */

int min(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
/* Minimum z 9 warto¶ci, potrzebne w g³ównej pêtli. */
{
  return min(min(min(a0,a1),min(a2,a3)),min(min(a4,a5),min(min(a6,a7),a8)));
} /* min */

void dod_A(int i)
/* Ta procedura wstawia i-te drzewo do drzew mintree: A1, A2 i A3,
 * przypisuj±c mu warto¶æ równ± sumie warto¶ci z drzewa mintree A i
 * odpowiedniego drzewa mintree Ti. */
{  
  int a = min(h[i - 1], h[i + 1]);
  int b = max(h[i - 1], h[i + 1]);
  insert(0, ROOT, dl[i], -2 * h[i] + f1(a, b, h[i]));
  insert(1, ROOT, dl[i], f1(a, b, h[i]));
  insert(2, ROOT, dl[i], 2 * h[i] + f1(a, b, h[i]));
} /* dod_A */

void dod_B(int i)
/* Ta procedura wstawia i-te drzewo do drzew mintree: B1, B2 i B3,
 * przypisuj±c mu warto¶æ równ± sumie warto¶ci z drzewa mintree B i
 * odpowiedniego drzewa mintree Ti. */
{  
  int a = min(h[i - 1], h[i + 1]);
  int b = max(h[i - 1], h[i + 1]);
  insert(3, ROOT, dl[i], -2 * h[i] + f2(a, b, h[i]));
  insert(4, ROOT, dl[i], f2(a, b, h[i]));
  insert(5, ROOT, dl[i], 2 * h[i] + f2(a, b, h[i]));
} /* dod_B */
 
void dod_C(int i)
/* Ta procedura wstawia i-te drzewo do drzew mintree: C1, C2 i C3,
 * przypisuj±c mu warto¶æ równ± sumie warto¶ci z drzewa mintree C i
 * odpowiedniego drzewa mintree Ti. */
{  
  int a = min(h[i - 1], h[i + 1]);
  int b = max(h[i - 1], h[i + 1]);
  insert(6, ROOT, dl[i], -2 * h[i] + f3(a, b, h[i]));
  insert(7, ROOT, dl[i], f3(a, b, h[i]));
  insert(8, ROOT, dl[i], 2 * h[i] + f3(a, b, h[i]));
} /* dod_C */

/*****************************************************************************/
/* Rozwa¿anie przypadków szczególnych                                        */
/*****************************************************************************/

int zm_wart(int wys, int poz)
/* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku, kiedy drzewo
 * o wysoko¶ci wys zostaje umiejscowione na pozycji poz. */
{
  int wyn = 0;
  if (poz > 0)
    wyn += abs(wys - h[poz - 1]);
  if (poz < n - 1)
    wyn += abs(wys - h[poz + 1]);
  return wyn;
} /* zm_wart */

int zm_wart1(int poz)
/* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku, kiedy drzewa
 * na pozycjach poz i poz+1 zostaj± zamienione miejscami. */
{
  int wyn = 0;
  if (poz > 0)
    wyn -= abs(h[poz] - h[poz - 1]) - abs(h[poz + 1] - h[poz - 1]);
  if (poz + 1 < n - 1)
    wyn -= abs(h[poz + 2] - h[poz + 1]) - abs(h[poz + 2] - h[poz]);
  return wyn;
} /* zm_wart1 */


void przypadki_szczegolne()
/* Rozwa¿enie wszystkich przypadków szczególnych (w ³±cznym czasie O(n)). */
{
  long long pwyn;
  
  /* Drzewo zerowe */
  for (i = 2; i < n; i++)
  {
    pwyn = wspol - zm_wart(h[0], 0) - zm_wart(h[i], i)
                 + zm_wart(h[0], i) + zm_wart(h[i], 0);
    wyn[0] = min(wyn[0], pwyn);
    wyn[i] = min(wyn[i], pwyn);
  } /* for */
  
  /* Drzewo (n-1)-wsze */
  for (i = 0; i < n - 2; i++)
  {
    pwyn = wspol - zm_wart(h[n - 1], n - 1) - zm_wart(h[i], i)
                 + zm_wart(h[n - 1], i) + zm_wart(h[i], n - 1);
    wyn[n - 1] = min(wyn[n - 1], pwyn);
    wyn[i] = min(wyn[i], pwyn);
  } /* for */
  
  /* Pary drzew s±siednich */
  for (i = 0; i < n - 1; i++)
  {
    pwyn = wspol + zm_wart1(i);
    wyn[i] = min(wyn[i], pwyn);
    wyn[i + 1] = min(wyn[i + 1], pwyn);
  } /* for */
} /* przypadki_szczegolne */

/*****************************************************************************/
/* Koniec rozwa¿ania przypadków szczególnych                                 */
/*****************************************************************************/


int main()
{
  scanf("%d",&n);
  for (i = 0; i < n; i++)
    scanf("%d", &h[i]);
  build();
  przenumeruj();
  licz_wspol();
  for (i = 0; i < n; i++)
    wyn[i] = wspol;
  /* Dodajemy wszystkie drzewa do A1, A2 oraz A3. */
  for (i = 0; i < n; i++)
    if (ld[i] > 0 && ld[i] < n - 1)
      dod_A(ld[i]);
  for (i = 0; i < n; i++) /* rozwa¿amy i-te drzewo */
  {
    /* usuwamy s±siadów i-tego drzewa */
    for (int j = 0; j < 9; j++)
    {
      if (ld[i] > 1) /* s±siad nie jest wyj±tkiem */
        del(j, ROOT, dl[ld[i] - 1]);
      if (ld[i] < n - 2) /* s±siad nie jest wyj±tkiem */
        del(j, ROOT, dl[ld[i] + 1]);
    } /* for */

    if (ld[i] > 0 && ld[i] < n - 1)
    /* Ten fragment nie jest wykonywany dla skrajnie lewego oraz skrajnie
     * prawego drzewa. */
    {
      /* wyliczamy minimalny wspó³czynnik */
      int a = min(h[ld[i] - 1], h[ld[i] + 1]);
      int b = max(h[ld[i] - 1], h[ld[i] + 1]);
      int A, B, H = h[ld[i]]; // A=f(a), B=f(b)
      if (a == h[ld[i] - 1])
      {
        A = dl[ld[i] - 1]; B = dl[ld[i] + 1];
      } /* if */
      else
      {
        A = dl[ld[i] + 1]; B = dl[ld[i] - 1];
      } /* else */
      akt = wspol +
        min(f1(a, b, H) - 2 * H + min_val(0, ROOT, 0, A - 1),
            f2(a, b, H) - 2 * H + min_val(1, ROOT, A, B),
            f3(a, b, H) - 2 * H + min_val(2, ROOT, B + 1 , n - 1),
            f1(a, b, H) + min_val(3, ROOT, 0, A - 1),
            f2(a, b, H) + min_val(4, ROOT, A, B),
            f3(a, b, H) + min_val(5, ROOT, B + 1, n - 1),
            f1(a, b, H) + 2 * H + min_val(6, ROOT, 0, A - 1),
            f2(a, b, H) + 2 * H + min_val(7, ROOT, A, B),
            f3(a, b, H) + 2 * H + min_val(8, ROOT, B + 1, n - 1));
      wyn[ld[i]] = akt;
    } /* if */
    
    /* Wstawienie s±siadów z powrotem do odpowiednich drzew mintree -
     * równocze¶nie aktualizujemy drzewa mintree. */
    if (ld[i] > 1) /* s±siad nie jest wyj±tkiem */
    {
      if (dl[ld[i] - 2] > i)
        dod_B(ld[i] - 1);
      else
        dod_C(ld[i] - 1);
    } /* if */
    if (ld[i] < n - 2) /* s±siad nie jest wyj±tkiem */
    {
      if (dl[ld[i] + 2] > i)
        dod_B(ld[i] + 1);
      else
        dod_C(ld[i] + 1);
    } /* if */
  } /* for */
  przypadki_szczegolne();
  for (i = 0; i < n; i++)
    printf("%lld\n", wyn[i]);
  return 0;
} /* main */
