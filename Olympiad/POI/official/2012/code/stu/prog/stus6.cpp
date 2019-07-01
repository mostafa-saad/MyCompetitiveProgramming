/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n^2 * m)                                       *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Sprawdzenie kazdego miejsca po kolei do 0        *
 *                      i zachlanne wyrownywanie terenu                  *
 *                                                                       *
 *************************************************************************/

#include<iostream>
using namespace std;

const int MAXN = 1000000;

int x[MAXN+1];
int pom[MAXN+1];

int n;
long long m;

int kop(int mini) {
  for(int i=1;i<=n;++i)
    pom[i] = x[i];
  long long pomm = m;
  pomm -= pom[mini];
  pom[mini] = 0;
  while(pomm != 0)
  {
    int difi = 1;
    int dif = pom[1] - pom[2];
    if(pom[n] - pom[n-1] > dif) {
      difi = n;
      dif = x[n] - x[n-1];
    }
    for(int i=2;i<n;++i)
      if(pom[i] - min(pom[i-1], pom[i+1]) > dif) {
        difi = i;
        dif = pom[i] - min(pom[i-1], pom[i+1]);
      }
    --pomm;
    --pom[difi];
  }
  int z = max(pom[0] - pom[1], pom[n] - pom[n-1]);
  for(int i=2;i<n;++i)
  {
    z = max(z, pom[i] - pom[i-1]);
    z = max(z, pom[i] - pom[i+1]);
  }
  return z;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(0);
  cin >> n >> m;
  for(int i=1;i<=n;++i)
    cin >> x[i];
  int miejsce = 1;
  int z = kop(1);
  for(int i=2;i<=n;++i)
  {
    int pomz = kop(i);
    if(pomz < z) {
      z = pomz;
      miejsce = i;
    }
  }
  cout << miejsce << ' ' << z << '\n';
  return 0;
}
