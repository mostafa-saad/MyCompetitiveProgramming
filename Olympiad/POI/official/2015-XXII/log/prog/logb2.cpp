/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Logistyka                                          *
 *   Autor programu:       Bartosz Lukasiewicz                                *
 *   Opis:                 Rozwiazanie bledne                                 *
 *                         rozwiazanie offline, bez long longow               *
 *****************************************************************************/


#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdio>
using namespace std;

#define MP make_pair

class zdarzenie
{
public:
  char rodzaj;
  int x, y;
};

const int MAX_N=1e6;
const int MAX_M=1e6;
const int R=1<<20;

int n, m, uprawnienia[MAX_N+5], war[MAX_M+5];
zdarzenie operacje[MAX_M+5];
pair<int, int> T[2*R];

pair<int, int> operator + (const pair<int, int> & a, const pair<int, int> b)
{
  return MP (a.first+b.first, a.second+b.second);
}

pair<int, int> suma (int lewy, int prawy)
{
  lewy+=R, prawy+=R;
  
  pair<int, int> ret=T[lewy];
  if (lewy!=prawy) ret=ret+T[prawy];
  
  while (lewy/2!=prawy/2)
  {
    if (lewy%2==0) ret=ret+T[lewy+1];
    if (prawy%2==1) ret=ret+T[prawy-1];
    lewy/=2, prawy/=2;
  }

  return ret;
}

void dodaj (int k, pair<int, int> wartosc)
{
  k+=R;
  T[k]=T[k]+wartosc;
  
  while (k>1)
  {
    k/=2;
    T[k]=T[2*k]+T[2*k+1];
  }
}

int warToNumer (int x)
{
  int p=1, k=m;
  
  while (p<k)
  {
    int s=(p+k)/2;
    if (x<=war[s]) k=s;
    else p=s+1;
  }

  return p;
}

int main()
{
  scanf ("%d %d", &n, &m);

  for (int i=1; i<=n; i++)
    uprawnienia[i]=-1;
  
  for (int i=1; i<=m; i++)
  {
    scanf (" %c %d %d", &operacje[i].rodzaj, &operacje[i].x, &operacje[i].y);
    war[i]=operacje[i].y;
  }
  sort (war+1, war+1+m);

  for (int i=1; i<=m; i++)
    if (operacje[i].rodzaj=='U')
    {
      int kierowca=operacje[i].x;
      
      if (uprawnienia[kierowca]!=-1)
	dodaj (warToNumer (uprawnienia[kierowca]), MP (-uprawnienia[kierowca], -1));
      
      uprawnienia[kierowca]=operacje[i].y;
      dodaj (warToNumer (uprawnienia[kierowca]), MP (uprawnienia[kierowca], 1));
    }
    else
    {
      int p=warToNumer (operacje[i].y);
      pair<int, int> w=suma (0, p);

      int mozliwosc=w.first + ((T[1].second-w.second) * operacje[i].y);
      int potrzeba=operacje[i].x * operacje[i].y;

      printf ((mozliwosc >= potrzeba) ? "TAK\n" : "NIE\n");
    }

  return 0;
}