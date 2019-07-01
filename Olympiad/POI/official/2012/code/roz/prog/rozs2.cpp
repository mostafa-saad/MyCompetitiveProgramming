/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Michal Zgliczynski                               *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Bada wszystkie mozliwe rozklady, korzysta ze     *
 *                      spostrzenia, ze kazda liczba maksymalnie raz     *
 *                      wystepuje oraz ze maksymalna uzyta liczba jest   *
 *                      niezbyt duza                                     *
 *                                                                       *
 *************************************************************************/

#include <iostream>
using namespace std;
typedef long long LL;

const int N = 88;
LL fib[N];
int best;

void go(int pos, int ile, LL n){
  if(ile > best) return;
  if(n == 0){
    if(best > ile) best = ile;
    return ;
  }
  if(pos == 0) return;
  go(pos-1, ile, n);
  go(pos-1, ile+1, n - fib[pos]);
  go(pos-1, ile+1, n + fib[pos]);
}

// Ile liczb w rozkladzie w systemie fibonacciego
int rozklad(LL n){
  int res =0;
  for(int i= N-1 ; i>= 1; i--){
    if(n >= fib[i]){
      res++;
      n -= fib[i];
    }
  }
  return res;
}

int main(){
  ios_base::sync_with_stdio(0);
  LL n;
  fib[0] = 0 , fib[1] =1;
  for(int i = 2; i<N;i++)
    fib[i] = fib[i-1] + fib[i-2];
  int z;
  cin >> z;
  while(z--){
    cin >> n;
    int pos = N-1;
    while(fib[pos] > n) pos--;
    best = rozklad(n);
    go(pos+2, 0, n);
    cout << best << endl;
  }
}
