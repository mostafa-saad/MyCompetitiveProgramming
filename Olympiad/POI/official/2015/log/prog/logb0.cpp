/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Logistyka                                          *
 *   Autor programu:       Bartosz Lukasiewicz                                *
 *   Opis:                 Rozwiazanie bledne (czesciowe), dla a, s <= 10^6   *
 *****************************************************************************/


#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
using namespace std;

#define MP make_pair

typedef long long ll;

const int MAX_N=1e6;
const int MAX_M=1e6;
const int MAX_A=1e6;
const int R=1<<20;

int n, m, wpisy[MAX_N+5];
pair<ll, int> tree[2*R];

pair<ll, int> operator + (const pair<ll, int> & a, const pair<ll, int> b)
{
  return MP (a.first+b.first, a.second+b.second);
}

pair<ll, int> suma (int l, int p)
{
  l+=R, p+=R;
  
  pair<ll, int> ret=tree[l];
  if (l!=p) ret=ret+tree[p];
  
  while (l/2!=p/2)
  {
    if (l%2==0) ret=ret+tree[l+1];
    if (p%2==1) ret=ret+tree[p-1];
    l/=2, p/=2;
  }

  return ret;
}

void dodaj (int k, pair<ll, int> wartosc)
{
  k+=R;
  tree[k]=tree[k]+wartosc;
  
  while (k>1)
  {
    k/=2;
    tree[k]=tree[2*k]+tree[2*k+1];
  }
}

void uaktualnienie (int k, int a)
{
  dodaj (wpisy[k], MP (ll(-wpisy[k]), -1));
  wpisy[k]=a;
  dodaj (wpisy[k], MP (ll(wpisy[k]), 1));
}

void zapytanie (int c, int s)
{
  pair<ll, int> w=suma (0, s);
  
  ll calaTrasa=ll(c) * ll(s);
  ll zasieg=w.first + (ll(s) * ll(n-w.second));
  
  printf (zasieg>=calaTrasa ? "TAK\n" : "NIE\n");
}

int main()
{
  scanf ("%d %d", &n, &m);

  dodaj (0, MP (0LL, n));
  
  for (int i=1; i<=m; i++)
  {
    char operacja;
    int a, b;
    scanf (" %c %d %d", &operacja, &a, &b);

    if (operacja=='U')
      uaktualnienie (a, b);
    if (operacja=='Z')
      zapytanie (a, b);
  }

  return 0;
}