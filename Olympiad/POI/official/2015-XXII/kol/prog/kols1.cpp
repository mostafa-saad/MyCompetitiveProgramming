/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie pamieciochlonne                        *
 *****************************************************************************/

#include "ckollib.h"
using namespace std;

#include<vector>
#include<algorithm>
vector<int> L;

int main(){
  int nowa_karta = karta();

  while(nowa_karta){
    L.push_back(nowa_karta);
    nowa_karta = karta();
  }
  sort(L.begin(),L.end());
  
  if(L[0] == L[L.size()-1]){
    odpowiedz(L[0]);
    return 0;
  }
  int k1 = 0;
  while(L[k1] == L[0]) k1++;
  int k2 = L.size()-1;
  while(L[k2] == L[L.size()-1]) k2--;
  if(k1+k2 < (int)L.size()-1){
    odpowiedz(L[0]);
    return 0;
  }
  if(k1+k2 > (int)L.size()-1){
    odpowiedz(L[L.size()-1]);
    return 0;
  }
  while(!L.empty()){
    if(L[L.size()-1] != L[L.size()-k1]){
      odpowiedz(L[L.size()-1]);
      return 0;
    }
    for(int i = 0 ; i < k1; i++) L.pop_back();
  }
  return 0;
}
