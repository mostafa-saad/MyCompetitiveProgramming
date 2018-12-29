/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Blokada (BLO)                                             *
 *   Plik:     blob1.cpp                                                 *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie bledne, bardzo zblizone do wzorcowego, blad   *
 *             w sprawdzaniu czy wierzcholek jest rozdzielajacy.         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N=100000; //maksymalna liczba wierzcholkow w grafie
int n; //liczba wierzcholkow 

vector<int> krawedzie[MAX_N]; //reprezentacja grafu poprzez listy sasiedztwa
long long blokada[MAX_N]; //liczba zablokowanych spotkan dla kazdego wierzcholka
bool odwiedzony[MAX_N]; 
int numer[MAX_N]; //jako ktory dany wierzcholek zostal odwiedzony
int low[MAX_N]; //funkcja low dla kazdego wierzcholka
int odwiedzone_wierzcholki;

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

/* przeszukiwanie w glab
 * funkcja zwraca liczbe wierzcholkow z poddrzewa przeszukiwania*/
int Dfs(int x,int ojciec){
  int liczba_odwiedzonych=1; 
  int liczba_zablokowanych=0;
  odwiedzony[x]=true;
  numer[x]=low[x]=odwiedzone_wierzcholki++;
  blokada[x]=2*(n-1); //z wierzcholka x (i do wierzcholka x) nie da sie dojechac
  for(vector<int>::iterator it=krawedzie[x].begin(); it!=krawedzie[x].end(); ++it)
    if (!odwiedzony[*it]){
      int rozmiar=Dfs(*it,x);
      liczba_odwiedzonych+=rozmiar;
      if (low[*it]>numer[x]){ /*blad, nierownosc powinna byc nieostra*/
        blokada[x]+=(long long)(n-1-rozmiar)*rozmiar; 
        liczba_zablokowanych+=rozmiar;
      } else{
        low[x]=min(low[x],low[*it]);
      }
    } else  if (*it!=ojciec) low[x]=min(low[x],numer[*it]);
  blokada[x]+=(long long)(n-1-liczba_zablokowanych)*liczba_zablokowanych;
  return liczba_odwiedzonych;
}

void WypiszWynik(){
  for (int i=0; i<n; ++i) printf("%lld\n",blokada[i]); 
}

int main(){
  WczytajGraf();
  Dfs(0,-1);
  WypiszWynik();
  return 0;
}
