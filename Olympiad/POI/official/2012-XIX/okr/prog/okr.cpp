/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Okropny wiersz                                   *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n log log n + q log n)                         *
 *   Opis:              Rozwiazanie autorskie (haszowanie)               *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cassert>
using namespace std;

typedef unsigned long long ULL;

#define FOR(x,y,z) for(int x=y;x<=z;++x)
#define REP(x,y) for(int x=0;x<y;++x)

const int MAX = 500000;
const int K = 31; // podstawa hashowania

char A[MAX+2]; // slowo [1, n]

ULL hash[MAX+1]; // hashe prefiksowe
ULL pot[MAX+1]; // i-ta potega liczby K

int dz[MAX+1]; // najmniejszy dzielnik liczby i

int n;

void sito() { // sito Eratostenesa do znalezienia najmniejszych dzielnikow wszystkich liczb
  dz[1] = 1;
  FOR(i,2,MAX)
    if(!dz[i]) {
      dz[i] = i;
      for(int j=min((ULL)MAX+1,(ULL)i*i);j<=MAX;j+=i)
        if(!dz[j])
          dz[j] = i;
    }
}

bool eq(int a, int b, int c, int d) { // sprawdza czy podslowa [a, b], [c, d] sa rowne
  return (hash[b] - hash[a-1]) * pot[n-b] == (hash[d] - hash[c-1]) * pot[n-d];
}

bool okresowe(int a, int b, int k) { // sprawdza czy podslowo [a, b] ma okres dlugosci k
  return eq(a, b-k, a+k, b); // slowa [a, b-k] oraz [a+k, b] musza byc rowne, zeby slowo [a, b] mialo okres dlugosci k
}

int okres(int a, int b, int L=1) { // slowo [a, b] musi miec okres wielokrotnosci L
    assert(a<=b);
    assert(L>0);
  int m = b - a + 1; // dlugosc tego slowa
  if(m == L) // znalezlismy szukany najkrotszy okres
    return m;
  int k = dz[m/L];
  if (k<=0) fprintf(stderr,"%d!\n",m/L);
  assert(k>0);
  if(okresowe(a, b, m/k))
    return okres(a, a+m/k-1, L);
  while(dz[m/L] == k)
    L *= k;
  return okres(a, b, L);
}

int skmin(int a, int b) {
  int logans = okres(a, b);
  return logans;
}

int main() {
  sito();
  pot[0] = 1;
  FOR(i,1,MAX)
    pot[i] = pot[i-1]*K;

  scanf("%d",&n);  
  if (scanf("%s", A+1));
  FOR(i,1,n)
    hash[i] = hash[i-1] + (A[i]-'a'+1)*pot[i];
  
  int z;
  if (scanf("%d", &z));
  while(z--)
  {
    int a, b;
    if(scanf("%d %d", &a, &b));
    int s = skmin(a,b);
    printf("%d\n", s);
  }
  return 0;
}

