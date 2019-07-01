/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Drzewa przedzialowe                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
using namespace std;

/* Implementacja drzew przedzialowych wg strony:
 * http://was.zaa.mimuw.edu.pl/?q=node/9
 */
#define SIZE 20
int w[1 << (SIZE+1)];

void insert(int x, int val) {
   int v = (1 << SIZE) + x;
   w[v] = val;
   while (v != 1){
     v /= 2;
     w[v] = w[2 * v] + w[2 * v + 1];
   }
}

int query(int a, int b){
   int va = (1 << SIZE) + a;
   int vb = (1 << SIZE) + b;
   
   int wyn = w[va];
   if (va != vb) 
     wyn += w[vb];

   while (va / 2 != vb / 2) {
     if (va % 2 == 0) wyn += w[va + 1]; 
     if (vb % 2 == 1) wyn += w[vb - 1]; 
     va /= 2; vb /= 2;
   }
   return wyn;
}

#define MAXN 1000005
long long wynik;
int n, pos, temp;
vector<int> tab[255];
char s[MAXN];

int main(){
  temp = scanf("%d", &n);
  temp = scanf("%s", s);
  for (int i = n - 1; i >= 0; --i)
    tab[int(s[i])].push_back(i);
  temp = scanf("%s", s);

  for (int i = 0; i < n; ++i){
    pos = tab[int(s[i])].back();
    tab[int(s[i])].pop_back();
    insert(pos, 1);
    pos += query(pos+1, MAXN);
    wynik += pos - i;
  }

  temp = printf("%lld\n", wynik);

  return 0;
}
