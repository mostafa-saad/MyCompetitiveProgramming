/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1000005   
long long wynik;
int n, j, temp;
char s1[MAXN],s2[MAXN];

int main(){
  temp = scanf("%d", &n);
  temp = scanf("%s", s1);
  temp = scanf("%s", s2);
  
  for (int i = 0; i < n; ++i){
    for(j = i; s2[j] != s1[i]; j++);
    for(; j > i; j--, wynik++)
      swap(s2[j], s2[j-1]);
  }

  temp = printf("%lld\n", wynik);

  return 0;
}
