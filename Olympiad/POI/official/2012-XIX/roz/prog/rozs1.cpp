/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Michal Zgliczynski                               *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Generuje wszystkie mozliwe rozklady              *
 *                                                                       *
 *************************************************************************/

#include <iostream>
using namespace std;
typedef long long LL;

const int N = 88;
LL fib[N];
int pot[N]; // pot[i] = 3^n
int best;

int main(){
  ios_base::sync_with_stdio(0);
  LL n;
  pot[0] = 1;
  for(int i = 1; i< N;i++)
    pot[i] = min(pot[i-1] * 3, 1000000000); // potem sa ujemne wartosci i w wyniku tego jest WA
  fib[0] = 1 , fib[1] =2;
  for(int i  = 2; i < N; i++)
    fib[i] = fib[i-1] + fib[i-2];
  int z;
  cin >> z;
  while(z--){
    cin >> n;
    int pos = N-1;
    while(fib[pos] > n) pos--;
    pos+=2; // najwieksza mozliwa liczba
    best = N;
    for(int i = 0 ; i < pot[pos] ; i++){ // liczby w zapisie trojkowym
      LL sum = 0;
      int res= 0;
      int temp = i;
      for(int j = 0 ; j < pos ; j++){
        if(temp%3 == 0) sum += fib[j];
        else if(temp%3 == 1) sum -= fib[j];
        if(temp%3 <= 1) res++;
        temp /= 3;
      }
      if(sum == n) best = min(best, res);
    }
    cout << best << endl;
  }
}
