// RozwiÄzanie bĹÄdne
// Sprawdzanie okresu probabilistyczne + zejĹcie logarytmiczne
// O(n log log n + q log n)
// Lech Duraj

#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cassert>
#include <cmath>
using namespace std;

typedef unsigned long long ULL;

#define FOR(x,y,z) for(int x=y;x<=z;++x)
#define REP(x,y) for(int x=0;x<y;++x)
#define _scanf(...) if (scanf(__VA_ARGS__));

const int MAX = 500000;
const int K = 31; // podstawa hashowania
const int checks = 1000;

char A[MAX+2]; // slowo [1, n]

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

bool okresowe(int a, int b, int k) { // sprawdza czy podslowo [a, b] ma okres dlugosci k
  if ((b-a+1)%k) return false;
  if (b-a+1==k) return true;
  int t = (int)sqrt(b-a+1);
  for(int i=0; i<t; i++)
  {
    int s = a+random()%(b-a+1-k);
  if (s>=a && s+k<=b && A[s]!=A[s+k])
  {
    return false;
  }
  }
  return true; 
}

int okres(int a, int b, int L=1) { // slowo [a, b] musi miec okres wielokrotnosci L
  int m = b - a + 1; // dlugosc tego slowa
  if(m == L) // znalezlismy szukany najkrotszy okres
    return m;
  int k = dz[m/L];
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
  
  scanf("%d",&n);  
  _scanf("%s", A+1);
  
  int z;
  _scanf("%d", &z);
  while(z--)
  {
    int a, b;
    _scanf("%d %d", &a, &b);
    int s = skmin(a,b);
    printf("%d\n", s);
//    printf("%d (%d)\n",s,(b-a+1)/s);
  }
  return 0;
}

