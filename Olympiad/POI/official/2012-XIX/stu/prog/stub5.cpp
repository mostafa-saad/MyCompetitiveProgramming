/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Wyszukiwanie binarne po wyniku i sprawdzenie     *
 *                      tylko 30 najniznych punktow jako kandydatow do   *
 *                      dokopania sie do 0                               *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<iostream>
using namespace std;

const int MAXN = 1000000;
const int PROB = 30;

int x[MAXN+1];
int pom[MAXN+1];
int s[MAXN+1];

int n;
long long m;

bool cmp(const int &a, const int &b) {
  return x[a] < x[b] || (x[a] == x[b] && a < b);
}

long long wyrownaj(int p) {
  long long ruchy = 0;
  for(int i=1;i<=n-1;++i)
  {
    if(pom[i] + p < pom[i+1]) {
      ruchy += pom[i+1] - (pom[i] + p);
      pom[i+1] = pom[i] + p;
    }
  }
  for(int i=n;i>=2;--i)
  {
    if(pom[i] + p < pom[i-1]) {
      ruchy += pom[i-1] - (pom[i] + p);
      pom[i-1] = pom[i] + p;
    }
  }
  return ruchy;
}

int gdzie_kopac(int p) {
  for(int k=1;k<=min(n, PROB);++k)
  {
     for(int i=1;i<=n;++i)
       pom[i] = x[i];
     long long ruchy = pom[s[k]];
     pom[s[k]] = 0;
     ruchy += wyrownaj(p);
     if(ruchy <= m)
       return s[k];
  }
  return -1;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(0);
  int h = 0;
  long long sumx = 0;
  cin >> n >> m;
  for(int i=1;i<=n;++i)
  {
    cin >> x[i];
    sumx += x[i];
    h = max(h, x[i]);
    s[i] = i;
  }
  if(sumx <= m) {
    cout << 1 << ' ' << 0 << '\n';
    return 0;
  }
  sort(s+1, s+n+1, cmp);
  int p = 1, q = h;
  while(p < q) // wyszukiwanie binarne po wyniku
  {
    int r = (p+q)/2;
    if(gdzie_kopac(r) != -1)
      q = r;
    else
      p = r + 1;
  }
  cout << gdzie_kopac(p) << ' ' << p << '\n';
  return 0;
}
