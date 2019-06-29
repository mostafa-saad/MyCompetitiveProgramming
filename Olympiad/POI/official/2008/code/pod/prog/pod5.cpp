/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pod5.cpp                                                  *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie o zlozonosci O(sqrt(V) * 2^V), brutalnie      *
 *             generuje wszystkie podzbiory, wszystkie operacje          *
 *             na maskach bitowych.                                      *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

const int N=26;
int n; //liczba wierzcholkow
int krawedzie[N]; //skompresowana macierz sasiedztwa w postaci maski bitowej
int populacja_tab[1<<(N/2)]; //liczba jedynek dla danej maski bitowej

void wczytaj(){
  int m; //liczba krawedzi
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i){
    int a, b;
    scanf("%d %d", &a, &b);
    a--; b--;
    //dodajemy krawedz przez operacje alternatywy bitowej
    krawedzie[a] |= 1<<b;
    krawedzie[b] |= 1<<a;
  }
}

#define populacja(x) (populacja_tab[x & 0x1FFF] + populacja_tab[(x >> 13) & 0x1FFF])

void licz(){
  int wynik[N/2]; //najlepsze znalezione rozwiazanie
  int podzial = N*N; //wartosc przekroju dla najlepszego podzialu
  for (int podzbior = 1; podzbior < (1<<(N/2)); ++podzbior)
    populacja_tab[podzbior] = populacja_tab[podzbior/2] + podzbior%2;

  //generujemy wszystkie podzbiory
  for (int podzbior = 0; podzbior < (1<<n); ++podzbior)
    if (populacja(podzbior) == n/2 && podzbior%2){
      //mamy podzial na polowy, wierzcholek 0 jest zawarty w przetwarzanym
      int suma = 0; //wartosc aktualnego przekroju
      for (int i = 0; i < n; ++i) 
        if ((1<<i) & podzbior){
          //liczymy krawedzie wychodzace z wierzcholka i w kierunku 
          //drugiej polowy zbiory wierzcholkow
          int krawedzie_wystajace = krawedzie[i] & ~podzbior;
          suma += populacja(krawedzie_wystajace);
        }
      if (suma < podzial) {
        podzial = suma;
        int licznik = 0;
        for (int i = 0; i < n; ++i)
          if ((1<<i) & podzbior)
            wynik[licznik++] = i;
      }
    }

  for (int i = 0; i < n/2; ++i) 
    printf("%d ",wynik[i] + 1);
  puts("");
}

int main(){
  wczytaj();
  licz();
}
