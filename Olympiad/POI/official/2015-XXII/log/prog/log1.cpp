/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Logistyka                                          *
 *   Autor programu:       Bartosz Lukasiewicz                                *
 *   Zlozonosc czasowa:    O(n + m log a_max)                                 *
 *   Opis:                 Rozwiazanie wzorcowe, online                       *
 *****************************************************************************/


#include <utility>
#include <cstdio>
using namespace std;

#define MP make_pair

typedef long long ll;

const int MAX_W=1<<30;
const int MAX_N=1e6;

pair<ll, int> operator + (const pair<ll, int> & a, const pair<ll, int> b)
{
  return MP (a.first+b.first, a.second+b.second);
}

struct Drzewo
{
  struct Wezel
  {
    Wezel *lewy, *prawy;
    pair<ll, int> wartosc;
    
    Wezel(): lewy(), prawy(), wartosc() {}

    ~Wezel()
    {
      delete lewy;
      delete prawy;
    }
  } korzen;

  void dodaj (int gdzie, pair<ll, int> wartosc)
  {
    int a=0, b=MAX_W-1;
    Wezel* obecny = &korzen;

    while (true)
    {
      obecny->wartosc=obecny->wartosc+wartosc;
      if (a==b) break;

      int s=(a+b)/2;
      if (gdzie<=s)
      {
	if (!obecny->lewy) obecny->lewy=new Wezel;
	obecny=obecny->lewy;
	b=s;
      }
      else
      {
	if (!obecny->prawy) obecny->prawy=new Wezel;
	obecny=obecny->prawy;
	a=s+1;
      }
    }
  }

  pair<ll, int> zapytanie (int a, int b, int obcA, int obcB, const Wezel* wezel) const
  {
    if (obcA>b || obcB<a || !wezel) return MP (0LL, 0);
    if (obcA>=a && obcB<=b) return wezel->wartosc;

    int s=(obcA+obcB)/2;
    pair<ll, int> v1=zapytanie (a, b, obcA, s, wezel->lewy);
    pair<ll, int> v2=zapytanie (a, b, s+1, obcB, wezel->prawy);

    return v1+v2;
  }

  pair<ll, int> zapytanie (int a, int b) const
  {
    return zapytanie (a, b, 0, MAX_W-1, &korzen);
  }
} T;

int n, m, uprawnienia[MAX_N+5];

int main()
{
  scanf ("%d %d", &n, &m);
  
  for (int i=1; i<=n; i++)
    uprawnienia[i]=-1;
  
  int u=0;
  while (m--)
  {
    char operacja;
    int a, b;
    scanf (" %c %d %d", &operacja, &a, &b);
    
    if (operacja=='U')
    {
      if (uprawnienia[a]!=-1)
	T.dodaj (uprawnienia[a], MP (ll (-uprawnienia[a]), -1));
      
      if (uprawnienia[a]==-1) u++;
      uprawnienia[a]=b;
      T.dodaj (uprawnienia[a], MP (ll (uprawnienia[a]), 1));
    }
    else
    {
      pair<ll, int> p=T.zapytanie (0, b);
      ll mozliwosc=p.first + (ll (u-p.second) * ll (b));
      ll potrzeba=ll(a) * ll(b);
      
      printf ((mozliwosc >= potrzeba) ? "TAK\n" : "NIE\n");
    }
  }
}