/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Michal Zgliczynski                               *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Podejscie meet-in-the-middle                     *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
typedef long long LL;

const int N = 88;
const int K = 4500000; //ok 3^14
LL fib[N];
LL pot[N]; // pot[i] = 3^n
int best;
map<int, int> tab;
LL n;

void generuj(int pocz, int kon, int kt){
  int dl = kon - pocz  +1;
  for(LL i = 0 ; i < pot[dl] ; i++){ // liczby w zapisie trojkowym
    LL sum = 0;
    int res= 0;
    int temp = i;
    for(int j = pocz ; j <= kon ; j++){
      if(temp%3 == 1) sum += fib[j];
      else if(temp%3 == 2) sum -= fib[j];
      if(temp%3 >= 1) res++;
      temp /= 3;
    }
    if(kt == 0){
      if(tab.find(sum) == tab.end()) tab[sum] = res;
      else tab[sum] = min(tab[sum], res);
    }
    else{
      if(tab.find(n-sum) != tab.end())
        best = min(best, res + tab[n-sum]);
    }
  }
}

int main(){
  ios_base::sync_with_stdio(0);
  pot[0] = 1;
  for(int i = 1; i< N;i++)
    pot[i] = min(pot[i-1] * 3, 1000000000LL); // potem sa ujemne wartosci i wyniku tego jest WA
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
    best =N;
    generuj(0,pos/2,0); 
    generuj(pos/2 + 1, pos, 1);
    cout << best << endl;
  }
}
