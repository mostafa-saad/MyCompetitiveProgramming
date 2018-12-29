/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals6.cpp                                      *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie alternatywne polegajace na budowie *
 *                        drzewa typu TRIE, do ktorego dodawane sa       *
 *                        palindromy w niemalejacym porzadku wzgledem    *
 *                        dlugosci, dla kazdego slowa tez za pomoca      *
 *                        algorytmy Manahera obliczane sa na poczatku    *
 *                        promienie palindromow, tak aby w miejscu gdzie *
 *                        napotkamy koniec innego krotszego palindromu   *
 *                        mozna bylo szybko odpowiedziec na pytanie czy  *
 *                        pozostaly fragment jest palindromem, zlozonosc *
 *                        O(n), gdzie n - suma dlugosci slow             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

const int MAX=2000001;

struct Wezel {
  map<char, Wezel*> nast;
  int czyKoniec;              // czy dany wezel jest koncowy
  Wezel():czyKoniec(0) {}
};

char slowo[MAX];
vector<string> slowa;

vector<int> palParzyste(MAX), palNieparzyste(MAX);
struct Wezel root;

void Manacher(const string &x, int niep, vector<int> &r) {
  int n=x.size(), i=1, j=0, k;
  while(i<n) {
    while(i+j<=n && i-j>0 && x[i-j-1]==x[i+j+niep]) j++;
    r[i]=j;
    k=1;
    while(r[i-k]!=r[i]-k && k<=j) {
      r[i+k] = min(r[i-k], r[i]-k); k++;
    }
    j=max(0,j-k); i+=k;
  }
}

inline int palindrom(int i, int j) {
  int dl = slowa[i].size();
  if ((dl-j)&1)
    return palNieparzyste[j+((dl-j)>>1)] >= (dl-j)>>1;
  else
    return (palParzyste[j+((dl-j)>>1)] >= (dl-j)>>1);
}

inline void preprocess(int k, int dl) {
  for(int i=0 ; i < dl ; palNieparzyste[i]=0, palParzyste[i++]=0);
  Manacher(slowa[k],0,palParzyste);
  Manacher(slowa[k],1,palNieparzyste);
}

int dodaj(int k) {
  const string &slowo = slowa[k];
  int res=1,dl = slowo.size();
  struct Wezel *wierzch = &root;
  preprocess(k, dl);
  for (int i=0 ; i<dl ; ++i) {
    if (!wierzch->nast[slowo[i]]) wierzch->nast[slowo[i]] = new struct Wezel();
    wierzch = wierzch->nast[slowo[i]];
    if (wierzch->czyKoniec && palindrom(k,i+1))
      res+=2;
  }
  wierzch->czyKoniec=k+1;
  return res;
}

struct porownanie {
  bool operator()(const string &a, const string &b) const {return a.size()<b.size();}
};

int main() {
  int dl, n, wynik=0;
  scanf("%d",&n);
  for(int i=0; i<n; ++i) {
    scanf("%d %s",&dl,slowo);
    slowa.push_back(slowo);
  }
  sort(slowa.begin(),slowa.end(),porownanie());

  for(int i=0; i<n ; ++i) wynik+=dodaj(i);

  printf("%d\n", wynik);
  return 0;
}
