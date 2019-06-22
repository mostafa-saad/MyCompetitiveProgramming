/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LOT (Lot na Marsa)                             *
 *   Plik:                lots3.cpp                                      *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie alternatywne (nieoptymalne)        *
 *                        Algorytm o zlozonosci czasowej O(n log n)      *
 *                        i pamieciowej O(n). Wykorzystuj±cy stóg z STL  *
 *                                                                       *
 *************************************************************************/
#include<cstdio>
#include<cstdlib>
#include<queue>

using namespace std;

// struktura do rpzechowywanie sum czêsciowych razem z numerem wierzcho³ka
struct moja{
  int d, num;
  moja(int d, int num): d(d), num(num) {}
  bool operator<(const moja &n) const {
    return d>n.d;
  }
};

const int MAX = 1000000 + 10;
priority_queue<moja > kopiec[2];
int n, odl[MAX], zap[MAX], calk = 0, przejscie =0, minpo[2], delta[2][MAX];
bool res[MAX], uzyte[2][MAX];

// funkcja obliczajaca sumy czesciowe w obu kierunkach
// i inicjujaca oba kopce 
void preprocess() {
  delta[0][0] = delta[1][n-1] = 0;
  for (int i=1, j=n-2; i < n ; ++i, --j) {
    delta[0][i] = delta[0][i-1] + zap[i-1] - odl[i-1];
    delta[1][j] = delta[1][j+1] + zap[j+1] - odl[j];
    uzyte[0][i] = uzyte[1][j] = false;
    kopiec[0].push(moja(delta[0][i],i));
    kopiec[1].push(moja(delta[1][j],j));
  }
  calk = delta[0][n-1] + zap[n-1] - odl[n-1];
  minpo[0] = minpo[1] = 0; 
}

// funkcja zwracajaca mimimalna sume czesciowa dla zadanego kopca
// pomija elementy juz usuniete
inline int min(int num) {
  while (uzyte[num][kopiec[num].top().num]) kopiec[num].pop();
  return kopiec[num].top().d;
}

//glowna funkcja do sprawdzania czy mozna zaczac od danej bazy
inline bool sprawdz(int i,int num) {
  return (minpo[num] + przejscie >= 0) && (min(num) - delta[num][i] >= 0) ;
}

int main() {
  scanf("%d\n", &n);
  for(int i=0; i<n; ++i) scanf("%d %d\n", &zap[i], &odl[i]);

  preprocess();
  // oddzielnie obslugiwany przypadek n==1, juz wyciety z zadania
  if (n==1) res[0] = zap[0] >= odl[0];
  else
    // sprawdzenie czy z danego wierzcholka mozemy objechac bazy jadac zgodnie
    // z ruchem wskazowek zegara
    for(int i=0; i<n; ++i) {
      if (delta[0][i]< minpo[0]) minpo[0] = delta[0][i];
      przejscie = calk - delta[0][i];
      res[i] = sprawdz(i,0);
      uzyte[0][i] = true;
    }
    // sprawdza czy z danego wierzcholka mozna objechac wszystkkie bazy
    // jadac przeciwnie do ruchu wskazowwek zegara
    for(int i=n-1; i>=0; --i) {
      if (delta[1][i]< minpo[1]) minpo[1] = delta[1][i];
      przejscie = calk - delta[1][i];
      res[i] = res[i] || sprawdz(i,1);
      uzyte[1][i] = true;
    }
  // wypisywanie wyników
  for(int i=0; i<n; ++i)
     printf((res[i]) ? "TAK\n" : "NIE\n");
  return 0;
}

