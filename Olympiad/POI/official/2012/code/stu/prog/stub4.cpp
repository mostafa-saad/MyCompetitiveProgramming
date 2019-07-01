/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Dokopanie sie w najnizszym miejscu i zachlanne   *
 *                      wyrownywanie terenu                              *
 *                                                                       *
 *************************************************************************/

#include<iostream>
using namespace std;

const int MAXN = 1000000;

int x[MAXN+1];

int n;
long long m;

void kop() {
  int mini = 1;
  for(int i=1;i<=n;++i)
    if(x[i] < x[mini])
      mini = i;
  m -= x[mini];
  x[mini] = 0;
  while(m != 0)
  {
    int difi = 1;
    int dif = x[1] - x[2];
    if(x[n] - x[n-1] > dif) {
      difi = n;
      dif = x[n] - x[n-1];
    }
    for(int i=2;i<n;++i)
      if(x[i] - min(x[i-1], x[i+1]) > dif) {
        difi = i;
        dif = x[i] - min(x[i-1], x[i+1]);
      }
    --m;
    --x[difi];
  }
  int z = max(x[0] - x[1], x[n] - x[n-1]);
  for(int i=2;i<n;++i)
  {
    z = max(z, x[i] - x[i-1]);
    z = max(z, x[i] - x[i+1]);
  }
  cout << mini << ' ' << z << endl;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(0);
  cin >> n >> m;
  for(int i=1;i<=n;++i)
    cin >> x[i];
  kop();
  return 0;
}
