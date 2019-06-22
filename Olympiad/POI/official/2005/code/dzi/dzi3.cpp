/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzi3.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Rozwi±zanie poprawne o zlozonosci O(n log * n).*
 *                        Z³o¿ono¶æ pamiêciowa jest liniowa. Program ten *
 *                        nie przechowuje w pamiêci krawêdzi grafu,      *
 *                        wykorzystuje reprezentacjê zbiorów roz³±cznych *
 *                        Find & Union w celu wykrywania cykli.          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;       //maksymalna liczba wierzcho³ków

int deg[MAXN];                  //tablica w której utrzymywane s± stopnie wierzcho³ków
int fu[MAXN];                   //tablica w której pamiêtana jest struktura Find & Union
//tablice pomocnicze do sprawdzania pladzielnosci i symetrii
int wezly[MAXN], liscie[MAXN], sasiad[MAXN];
long long k, r;
int n, m;                       //liczba wierzcho³ków oraz liczba krawêdzi

/*funkcja ta zwraca numer sk³adowej do której nale¿y
 w danej chwili wierzcho³ek*/
int fufind(int x)
{
  if (fu[x] < 0)
    return x;
  //kompresja scie¿ki
  fu[x] = fufind(fu[x]);
  return fu[x];
}

/*procedura uaktualnia informacje w tablicach pomocniczych
po dodaniu do grafu krawêdzi (a,b)*/
void dodaj(int a, int b)
{
  deg[a]++;
  if (deg[a] == 1)
    sasiad[a] = b;
  else {
    wezly[b]++;
    if (deg[a] == 2)
      wezly[sasiad[a]]++;
  }
}

/*funkcja ta wczytuje krawêdzie i sprawdza czy graf jest lasem*/
bool cykl()
{
  for (int i = 1; i <= m; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    dodaj(a, b);
    dodaj(b, a);

    a = fufind(a);
    b = fufind(b);
    if (a == b)
      /*wierzcho³ki nale¿a do tej samej
         spójnej sk³adowej, zatem powstaje cykl */
      return true;

    if (fu[a] < fu[b])          //³±czenie wed³ug rangi
      swap(a, b);

    fu[b] += fu[a];
    fu[a] = b;

  }
  return false;
}

//funkcja ta sprawdza, czy graf jest pladzielny
bool pladzielny()
{
  for (int i = 1; i <= n; ++i)
    if (wezly[i] > 2)
      return false;
    else
      wezly[i] = 0;
  return true;
}

void inicjuj()
{
  for (int i = 1; i <= n; ++i) {
    deg[i] = 0;
    fu[i] = -1;                 //ka¿dy wierzcho³ek nale¿y do innego zbioru
    liscie[i] = 0;
    wezly[i] = 0;
  }
}

//g³ówna procedura programu, zlicza wszystkie konfiguracje
void licz()
{
  r = 1;
  scanf("%d %d %lld", &n, &m, &k);
  inicjuj();

  if (cykl() || (!pladzielny())) {
    printf("0\n");
    return;
  }

  int izolowane = 0;
  //zliczam liczbe wierzcho³ków o poszczególnych stopniach
  for (int i = 1; i <= n; ++i)
    if (deg[i] == 0)
      izolowane++;
    else if (deg[i] == 1)
      r = (r * (++liscie[sasiad[i]])) % k;
    else
      wezly[fufind(i)]++;

  int skladowe = 0;
  for (int i = 1; i <= n; ++i)
    if (fu[i] < -1)
      //wierzcho³ek i jest korzeniem sk³adowej o liczbie wierzcholkow > 1
    {
      r = (r * (2 * (++skladowe))) % k;
      if (wezly[i] >= 2)        //sk³adowa nie jest symetryczna
        r = (r * 2) % k;
    }

  //trzeba jeszcze doliczyæ rozstawienia wierzcho³ków izolowanych
  for (int i = n + 1; i >= n + 2 - izolowane; --i)
    r = (r * i) % k;
  printf("%lld\n", r);
}

int main()
{
  licz();
  return 0;
}
