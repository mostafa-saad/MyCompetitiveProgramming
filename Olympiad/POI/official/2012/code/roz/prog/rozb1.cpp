/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Michal Zgliczynski                               *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Rozklada na sume liczb Fibonacciego              *
 *                                                                       *
 *************************************************************************/

#include <iostream>
using namespace std;
typedef long long LL;

const int N = 88;
LL fib[N];

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
  for(int i = 2; i< N;i++)
    fib[i] = fib[i-1] + fib[i-2];
  int z;
  cin >> z;
  while(z--){
    cin >> n;
    cout << rozklad(n) << endl;
  }
}
