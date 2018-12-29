/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Antysymetria (ANT)                               *
 *   Plik:              ant.cpp                                          *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *                      Rozwiazanie uzywa algorytmu Manachera,           *
 *                      zmienionego w jednym miejscu.                    *
 *   Zlozonosc czasowa: O(n)                                             *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <string>
#include <cstdio>

typedef long long LL;

using namespace std;
int n;

LL Manacher(string x) {
  LL wynik=0;
  vector<int> r;
  int i=0, j=0;
  while (i<=n-1) {
    while ((i-j>=0) && x[i-j]!=x[i+j+1] && i+j+1<n) j++;
    r.push_back(j); wynik+=j;
    int k=1;
    while (i-k>=0 && r[i-k]!=r[i]-k && k <= j) {
      r.push_back(min(r[i-k],r[i]-k));
      wynik+=r[r.size()-1];
      k++;
    }
    j=max(j-k,0); i+=k;
  }
 return wynik;
}

int main() {
    char ll[500011];
    scanf("%d",&n); 
    scanf("%s",ll);
    string l=ll;
    printf("%lld\n",Manacher(l));
return 0;
}

