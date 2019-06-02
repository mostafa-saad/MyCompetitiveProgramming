/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Hydrorozgrywka                                     *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(n + m)                                           *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <cstdio>
#include <cassert>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 500 * 1000;
const int maxM = 500 * 1000;

// stany dp:
const int wyg = 0; // zaczynający wygra wchodząc do podkaktusa
const int prz = 1; // zaczynający przegra wchodząc do podkaktusa
const int pie = 2; // zaczynający zacznie jeszcze raz, jeśli w podkaktusie nic się nie roztrzygnie
const int dru = 3; // zaczynający nie zacznie jeszcze raz, jeśli w podkaktusie nic się nie roztrzygnie

int zlacz_dp(int a, int b) // jeśli w wierzchołku łączą się dwa cykle o wynikach a, b, to jaki będzie łączny wynik?
{
  if(a == wyg || b == wyg)
    return wyg;
  if(a == prz)
    return b;
  if(b == prz)
    return a;
  if((a == dru) != (b == dru))
    return dru;
  return pie;
}

int zlacz_mozliwosci(int a, int b) // wybierz lepszą z możliwości
{
  if(a == wyg || b == wyg)
    return wyg;
  if(a == prz)
    return b;
  if(b == prz)
    return a;
  if(a == b)
    return a;
  return wyg; // jeśli jest wybór, to się wygrało
}

int n, m;
int root;

vector<int> graf[maxN + 5];

struct punkt // reprezentuje wierzchołek na cyklu
{
  int w; // numer wierzchołka
  int poz; // pozycja danego cyklu na liście cykli wierzchołka w
  punkt(int w) : w(w), poz(-1) {}
  int licz_poza();
};

struct cykiel // reprezentuje cykl na liście cylki wierzchołka
{
  int c; // numer cyklu
  int poz; // pozycja danego wierzchołka na cyklu
  int dp; // wynik dla podkaktusa powstałego przez rozcięcie grafu w danym wierzchołku i pozostawienie spójnej z cyklem c
  int pref; // prefiksowy wynik
  int suf; // sufiksowy wynik
  cykiel(int c, int poz) : c(c), poz(poz), dp(pie), pref(pie), suf(pie) {}
};

int cyk; // liczba cykli
vector<punkt> cykl[maxM + 5]; // tablica cykli
vector<cykiel> ktore[maxN + 5]; // tablica przypisująca cykle wierzchołkom

bool odw[maxN + 5];
bool wyjscie[maxN + 5];
int ojc[maxN + 5];

void dfs_cykiele(int w, int o);
void przelicz_prefikso_sufiksy(int w);
void licz_oprocz(int w, int c);
int licz_wyniki(const vector<int> &wyniki);
void licz_jeden(int w, int poz_c);

void licz_cykiel(int c, int w) // c -- numer cyklu, w -- wierzchołek z którego się przybyło
{
  vector<int> wyniki;
  vector<int> odpowiedzi;
  for(int i = 0; i < (int) cykl[c].size(); i++)
    wyniki.push_back(cykl[c][i].licz_poza());
  odpowiedzi.resize(wyniki.size(), (cykl[c].size() % 2 == 0) ? pie : dru);
  const int roz = (int) wyniki.size();
  int ile_wygranych = 0;
  for(int i = 0; i < (int) wyniki.size(); i++)
  {
    if(wyniki[i] == wyg || wyniki[i] == dru)
    {
      ile_wygranych++;
      for(int j = (i - 1 + roz) % roz, k = 1; j != i; j = (j - 1 + roz) % roz, k ^= 1)
      {
        if(k == 0)
          odpowiedzi[j] = wyg;
        if(wyniki[j] == wyg || wyniki[j] == dru)
          break;
      }
      for(int j = (i + 1) % roz, k = 1; j != i; j = (j + 1) % roz, k ^= 1)
      {
        if(k == 0)
          odpowiedzi[j] = wyg;
        if(wyniki[j] == wyg || wyniki[j] == dru)
          break;
      }
    }
  }
  if(ile_wygranych)
  {
    for(int i = 0; i < (int) odpowiedzi.size(); i++)
      if(odpowiedzi[i] != wyg)
        odpowiedzi[i] = prz;
    if(ile_wygranych == 1)
      for(int i = 0; i < (int) wyniki.size(); i++)
        if(wyniki[i] == wyg || wyniki[i] == dru)
          odpowiedzi[i] = (cykl[c].size() % 2 == 0) ? pie : dru;
  }
  for(int i = 0; i < (int) cykl[c].size(); i++)
  {
    if(cykl[c][i].w != w)
    {
      ktore[cykl[c][i].w][cykl[c][i].poz].dp = odpowiedzi[i];
      przelicz_prefikso_sufiksy(cykl[c][i].w);
      for(int j = 0; j < (int) ktore[cykl[c][i].w].size(); j++)
        if(ktore[cykl[c][i].w][j].c != c)
          licz_cykiel(ktore[cykl[c][i].w][j].c, cykl[c][i].w);
    }
  }
}

int main()
{
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= m; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    graf[a].push_back(b);
    graf[b].push_back(a);
  }
  dfs_cykiele(1, -1);
  for(int i = 1; i <= cyk; i++)
  {
    for(int j = 0; j < (int) cykl[i].size(); j++)
    {
      cykl[i][j].poz = (int) ktore[cykl[i][j].w].size();
      ktore[cykl[i][j].w].push_back(cykiel(i, j));
    }
  }
  root = -1;
  for(int i = 1; i <= n; i++)
    if((int) ktore[i].size() == 1)
      root = i;
  assert(root >= 1 && root <= n);
  licz_oprocz(root, -1);
  licz_cykiel(ktore[root][0].c, root);
  for(int i = 1; i <= n; i++)
  {
    const int wyn = ktore[i].back().pref;
    if(wyn == wyg || wyn == dru)
      printf("1\n");
    else
      printf("2\n");
  }
  return 0;
}

void przelicz_prefikso_sufiksy(int w) // przelicza wyniki prefiksowe i sufiksowe dla tablicy cykli wierzchołka w
{
  if(ktore[w].empty())
    return;
  ktore[w][0].pref = ktore[w][0].dp;
  for(int i = 1; i < (int) ktore[w].size(); i++)
    ktore[w][i].pref = zlacz_dp(ktore[w][i - 1].pref, ktore[w][i].dp);
  ktore[w].back().suf = ktore[w].back().dp;
  for(int i = (int) ktore[w].size() - 2; i >= 0; i--)
    ktore[w][i].suf = zlacz_dp(ktore[w][i + 1].suf, ktore[w][i].dp);
}

int punkt::licz_poza()
{
  const int a = (poz == 0) ? pie : ktore[w][poz - 1].pref;
  const int b = (poz == (int) ktore[w].size() - 1) ? pie : ktore[w][poz + 1].suf;
  return zlacz_dp(a, b);
}

// liczy wynik dla wierzchołka w bez cyklu c -- wypełnia dp, suf i pref w odpowiednich miejscach (poza c)
void licz_oprocz(int w, int c)
{
  for(int i = 0; i < (int) ktore[w].size(); i++)
    if(ktore[w][i].c != c)
      licz_jeden(w, i);
  przelicz_prefikso_sufiksy(w);
}

// mając dany cykl wyników, zwarca wynik dla wierzchołka, który znajduje się przed pierwszym wynikiem na cyklu
// !!! funkcja próbuje iść tylko w prawo (do przodu) !!!
int licz_wyniki(const vector<int> &wyniki)
{
  int kto = 1; // 0 -- zaczynający, 1 -- ten drugi
  for(int i = 0; i < (int) wyniki.size(); i++)
  {
    if(wyniki[i] == wyg || wyniki[i] == dru)
      return (kto == 0) ? wyg : prz;
    kto ^= 1;
  }
  if(kto == 0)
    return pie;
  return dru;
}

// liczy wynik dla wierzchołka w z cyklem c -- wypełnia dp w odpowiednim cykielu
void licz_jeden(int w, int poz_c)
{
  const int &c = ktore[w][poz_c].c;
  int poz = -1;
  for(int i = 0; i < (int) cykl[c].size(); i++)
  {
    if(cykl[c][i].w != w)
      licz_oprocz(cykl[c][i].w, c);
    else
      poz = i;
  }
  assert(poz != -1);
  vector<int> wyniki;
  for(int i = poz + 1; i < (int) cykl[c].size(); i++)
    wyniki.push_back(cykl[c][i].licz_poza());
  for(int i = 0; i < poz; i++)
    wyniki.push_back(cykl[c][i].licz_poza());
  const int a = licz_wyniki(wyniki);
  reverse(wyniki.begin(), wyniki.end());
  const int b = licz_wyniki(wyniki);
  ktore[w][poz_c].dp = zlacz_mozliwosci(a, b);
}

void dfs_cykiele(int w, int o)
{
  odw[w] = true;
  ojc[w] = o;
  for(int i = 0; i < (int) graf[w].size(); i++)
  {
    if(graf[w][i] == o || wyjscie[graf[w][i]])
      continue;
    if(odw[graf[w][i]]) // zwijanie cyklu
    {
      int x = w;
      cyk++;
      while(x != graf[w][i])
      {
        cykl[cyk].push_back(punkt(x));
        x = ojc[x];
      }
      cykl[cyk].push_back(punkt(x));
    }
    else // zejście niżej
      dfs_cykiele(graf[w][i], w);
  }
  wyjscie[w] = true;
}
