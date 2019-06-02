/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n log k)                                         *
 *   Zlozonosc pamieciowa: O(k)                                               *
 *   Opis:                 Rozwiazanie pamieciochlonne                        *
 *****************************************************************************/

#include "ckollib.h"
#include<cstdio>
using namespace std;

#include<map>
map<int,int> L;

int main(){
  int nowa_karta = karta();
  int mm = 0;
  while(nowa_karta){
    L[nowa_karta]++;
    mm = max(L[nowa_karta],mm);
    nowa_karta = karta();
  }
  if(L.size() == 1){
    odpowiedz((*L.begin()).first);
    return 0;
  }
  for(map<int,int>::iterator it = L.begin(); it != L.end(); it++){
    if((*it).second != mm){
      odpowiedz((*it).first);
      return 0;
    }
  }
  return 0;
}