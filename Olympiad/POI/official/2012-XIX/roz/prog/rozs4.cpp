/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Michal Zgliczynski                               *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Rozwiazanie opierajace sie na problemie          *
 *                      pakowania plecaka                                *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;

const int N = 88;
const int K = 4000000;
LL fib[N];
int F[2*K];
int best;
int pos; // najwieksza liczba w rozkladzie

vector<LL> zb;

int main(){
  ios_base::sync_with_stdio(0);
  LL n;
  fib[0] = 0 , fib[1] =1;
  for(int i = 2;i<N;i++)
    fib[i] = fib[i-1] + fib[i-2];
  int z;
  cin >> z;
  while(z--){
    cin >> n;
    zb.push_back(n);
  }
  for(int i = 0;i<(int)zb.size() ; i++)
    n = max(n, zb[i]);
  pos = N-1;
  while(fib[pos] > n) pos--;
  pos += 2;
  int MAXW = fib[pos] + n;
  // F[MAXW] - zapakowanie zera
  for(int i =0 ; i <= 2*MAXW ;i++)
    F[i] = N;
  F[MAXW] = 0;
  for(int i =1 ; i <= pos ; i++){
    for(int j = 2*MAXW ; j >= fib[i] ; j--)
      F[j] = min(F[j], F[j - fib[i]] + 1); // +F[i]
    for(int j = 0; j + fib[i] <= 2*MAXW;j++)
      F[j] = min(F[j], F[j + fib[i]] + 1); // -F[i]
  }
  for(int  i = 0;i<(int)zb.size();i++)
    cout << F[MAXW + zb[i]] << endl;
}
