/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Okropny wiersz                                   *
 *   Autor:             Lech Duraj                                       *
 *   Zlozonosc czasowa: O(n log^2 n + q log n)                           *
 *   Opis:              Rozwiazanie wzorcowe (KMR)                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

#define _scanf(...) if (scanf(__VA_ARGS__));

using namespace std;

const int maxn = 500002;
const int maxlog = 20;

struct triple  // struktura do sortowania w KMR
{
  int a,b,c;
  triple(int _a, int _b, int _c) : a(_a),b(_b),c(_c) {};
  triple() {};
};

bool operator<(const triple &x, const triple &y)
{
  return (x.b<y.b || (x.b==y.b && x.c<y.c));
}

char A[maxn];
int n, m;
int log_2[maxn];      // stablicowany logarytm dwĂljkowy
int divisor[maxn];    // najmniejszy dzielnik pierwszy
triple aux[maxn];     // tablica pomocnicza do KMR
int kmr[maxlog][maxn];  // tablica KMR: kmr[q][s] to identyfikator slowa dlugosci 2^q na pozycji s, identyfikatory sa rowne wtw. slowa sa identyczne

bool equal(int a, int b, int len)  // sprawdĹş, czy slowa dlugosci len na pozycjach a i b sa identyczne
{
  int s = log_2[len];  
  int d = 1 << s;                            // bierzemy potege dwojki d taka, ze d <= len < 2d
  return kmr[s][a]==kmr[s][b] && kmr[s][a+len-d]==kmr[s][b+len-d];  // [a, a+len) = [b, b+len) <=> [a, a+d) = [b, b+d) i [a+d-len, a+len) = [b+d-len, b+len)
}


int main()
{
  scanf("%d",&n);  
  _scanf("%s\n",A);
  
  log_2[1] = 0;                   // tablicowanie logarytmow
  for(int i=2; i<=n; i++)
    log_2[i] = log_2[i/2]+1;
  m = log_2[n];
  
  for(int i=1; i<=n; i++)        // sito Eratostenesa
    divisor[i] = i;
  for(int i=2; i<=n; i++)
    if (divisor[i]==i)
      for(long long k=(long long)i*i; k<=n; k+=i)
        divisor[k] = min(divisor[k],i);
        
  for(int i=0; i<n; i++)         // brzydko zaimplementowany KMR
    kmr[0][i] = A[i]-'a';
  for(int t=1; t<=m; t++)
  {
    int d = (1 << (t-1));
    for(int i=0; i+2*d<=n; i++)
      aux[i] = triple(i,kmr[t-1][i],kmr[t-1][i+d]);
    sort(aux,aux+n-2*d+1);    // z STL-owym sortem zamiast liniowego countsorta. Praktyka pokazuje, ze liniowy nie jest de facto szybszy.
    int j = 0;
    for(int i=0; i+2*d<=n; i++)
    {
      int s = aux[i].a;
      if (i>0 && aux[i-1]<aux[i])
        kmr[t][s] = ++j;
      else
        kmr[t][s] = j;
    }
  }
  
  int q;
  _scanf("%d",&q);
  while(q--)
  {
    int a,b;
  _scanf("%d %d",&a,&b);
    a--; b--;
    int len = b-a+1;
    int period = len;              // najmniejszy znany okres
    int checking = len;              // liczby pierwsze, ktore zostaly jeszcze do sprawdzenia
    while(checking>1)
    {
       int p = divisor[checking];    
       if (equal(a,a+period/p,len-period/p))  // ten warunek oznacza, ze slowo ma okres period/p
       {                    // jesli ma, to kazdy inny bedzie jego dzielnikiem
         checking /= p; period /=p;
       }
       else
         while (divisor[checking]==p) checking/=p;  // jesli nie ma, to p w maksymalnej potedze dzieli okres, mozemy sprawdzac kolejne liczby pierwsze
    }
    printf("%d\n",period);
  
  }
}
