/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Blokada (BLO)                                             *
 *   Plik:     blos2.cpp                                                 *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie wolne, zlozonsc obliczeniowa O(n*m),          *
 *             zlozonosc pamieciowa O(m). Dla kazdego wiercholka         *
 *             obliczamy liczbe zablokowanych spotkan poprzez            *
 *             znalezienie spojnych skladowych grafu powstalego przez    *
 *             usuniecie danego wierzcholka.                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N=100000; //maksymalna liczba wierzcholkow w grafie
int n; //liczba wierzcholkow 

vector<int> krawedzie[MAX_N]; //reprezentacja grafu poprzez listy sasiedztwa
bool odwiedzony[MAX_N]; 

void WczytajGraf(){
  int m; //liczba krawedzi grafu
  scanf("%d %d",&n,&m);
  while (m--){
    int a,b;
    scanf("%d %d",&a,&b);
    //dodanie nowej krawedzi nieskierowanej
    a--; b--;
    krawedzie[a].push_back(b);
    krawedzie[b].push_back(a);
  }
}

/* przeszukiwanie w glab znajdujace rozmiar spojnej skladkowej*/
int Dfs(int x){
  int odwiedzone_wierzcholki=1;
  odwiedzony[x]=1;
  for(vector<int>::iterator it=krawedzie[x].begin(); it!=krawedzie[x].end(); ++it)
    if (!odwiedzony[*it]) 
      odwiedzone_wierzcholki+=Dfs(*it);
  return odwiedzone_wierzcholki;
}

long long ZablokowaneSpotkania(int x){
  long long wynik=2*(n-1); //nikt nie spotka sie z mieszkancem miasta x
  for (int i=0; i<n; ++i) odwiedzony[i]=0;
  odwiedzony[x]=1;
  for (int i=0; i<n; ++i) if (!odwiedzony[i]){
    int rozmiar=Dfs(i);
    wynik+=(long long)rozmiar*(n-1-rozmiar);
  }
  return wynik;
}

void ObliczWynik(){
  for (int i=0; i<n; ++i) printf("%lld\n",ZablokowaneSpotkania(i)); 
}

int main(){
  WczytajGraf();
  ObliczWynik();
  return 0;
}
