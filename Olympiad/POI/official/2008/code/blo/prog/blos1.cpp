/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Blokada (BLO)                                             *
 *   Plik:     blos1.cpp                                                 *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie wolne, zlozonosc obliczeniowa O(n*m),         *
 *             zlozonosc pamieciowa O(m). Wynik obliczany jest za pomoca *
 *             algorytmu dfs dla kazdego wierzcholka artykulacji         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N=100000; //maksymalna liczba wierzcholkow w grafie
int n; //liczba wierzcholkow 

vector<int> krawedzie[MAX_N]; //reprezentacja grafu poprzez listy sasiedztwa
bool odwiedzony[MAX_N]; 
bool punkt_artykulacji[MAX_N]; //czy dany wierzcholek jest punktem artykujacji,
                               //wyjatek to wierzcholek 0, dla ktorego zawsze
                               //wartosc wynosi true
int numer[MAX_N]; //jako ktory dany wierzcholek zostal odwiedzony
int low[MAX_N]; //funkcja low dla kazdego wierzcholka
int odwiedzone_wierzcholki;

/* przeszukiwanie w glab, znajdujace punkty artykulacji */
void DfsPunktyArtykujacji(int x,int ojciec){
  odwiedzony[x]=true;
  numer[x]=low[x]=odwiedzone_wierzcholki++;
  for(vector<int>::iterator it=krawedzie[x].begin(); it!=krawedzie[x].end(); ++it)
    if (!odwiedzony[*it]){
      DfsPunktyArtykujacji(*it,x);
      if (low[*it]>=numer[x])
        punkt_artykulacji[x]=true;
      else
        low[x]=min(low[x],low[*it]);
    } else if (*it!=ojciec) low[x]=min(low[x],numer[*it]);
}

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
  punkt_artykulacji[0]=true;
  for (int i=0; i<n; ++i)
    printf("%lld\n",punkt_artykulacji[i]?ZablokowaneSpotkania(i):2*(n-1)); 
}

int main(){
  WczytajGraf();
  DfsPunktyArtykujacji(0,-1);
  ObliczWynik();
  return 0;
}
