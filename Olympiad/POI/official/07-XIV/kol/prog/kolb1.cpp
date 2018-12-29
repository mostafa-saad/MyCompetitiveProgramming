/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Koleje (KOL)                                               *}
{*   Plik:    kolb1.cpp                                                  *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Rozwiazanie bledne, losujemy zbior wierzcholkow            *}
{*            opcjonalnych i obliczamy MST dla zbioru wierzcholkow       *}
{*             wymaganych i wylosowanych                                 *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N=5000;
const int MAX_M=500000;
const int MAX_WAGA=100000;
const int MAX_OPERACJE=200000000;

struct Edge{
  int a,b,koszt;
} krawedzie[MAX_M];

int n,m;
int ile_wymaganych;
int wymagany[MAX_N]; //czy dany wierzcholek jest wymagany
int wynik=MAX_WAGA*MAX_N; //szukany wynik
int numery[MAX_N],ile_krawedzi; //liczba oraz numery krawedzi w dotychczas
                               //znalezionym rozwiazaniu
int tmp_numery[MAX_N];
int fu[MAX_N]; //tablica do pamietania ojcow w strukturze Find & Union
int rozpinany[MAX_N]; //czy dany wierzcholek bedzie nalezal do drzewa
                      //w tym losowaniu

void wczytaj(){
  scanf("%d %d",&n,&m);
  for (int i=0; i<m; ++i){
    scanf("%d %d %d",&krawedzie[i].a,&krawedzie[i].b,&krawedzie[i].koszt);
    krawedzie[i].a--;
    krawedzie[i].b--;
  }
  scanf("%d",&ile_wymaganych);
  for (int i=0; i<ile_wymaganych; ++i){
    int x;
    scanf("%d",&x);
    wymagany[--x]=1;
  }
}

void wypisz(){
  printf("%d %d\n",wynik,ile_krawedzi);
  for (int i=0; i<ile_krawedzi; ++i)
    printf("%d %d\n",krawedzie[numery[i]].a+1,krawedzie[numery[i]].b+1);
}

int fufind(int x){
  return fu[x]<0?x:fu[x]=fufind(fu[x]);
}

bool kryt(const Edge &a,const Edge &b){
  return a.koszt<b.koszt;
}

void losuj(int ile){
  int licznik=0;
  for (int i=0; i<n; ++i){
    if (!wymagany[i])
      tmp_numery[licznik++]=i; 
    rozpinany[i]=wymagany[i];
    fu[i]=-1; //poczatkowo kazdy wierzcholek jest w jednoelementowym zbiorze
  }
  while (ile--){
    int pos=rand()%licznik;
    int x=tmp_numery[pos];
    swap(tmp_numery[pos],tmp_numery[--licznik]);
    rozpinany[x]=1;
  }
}

void licz(){
  int proby=MAX_OPERACJE/MAX_M;
  sort(krawedzie,krawedzie+m,kryt); //sortujemy krawedzie wzgledem kosztu
  while (proby--){
    int wylosowane=rand()%(n-ile_wymaganych+1);
    int zbiory=ile_wymaganych+wylosowane;
    int uzyte=0;
    int acc=0;
    losuj(wylosowane);
    //wykonujemy algorytm Kruskal'a
    for (int i=0; acc<wynik && zbiory>1 && i<m; ++i){
      int a=krawedzie[i].a;
      int b=krawedzie[i].b;
      if (rozpinany[a] && rozpinany[b]){
        a=fufind(a);
        b=fufind(b);
        if (a!=b){
          zbiory--;
          if (fu[a]<fu[b]) swap(a,b);
          fu[b]+=fu[a];
          fu[a]=b;
          acc+=krawedzie[i].koszt;
          tmp_numery[uzyte++]=i;
        }
      }
    }
    if (zbiory==1 && acc<wynik){
      wynik=acc;
      ile_krawedzi=uzyte;
      for (int i=0; i<uzyte; ++i)
        numery[i]=tmp_numery[i];
    }
  }
}

int main(){
  wczytaj();
  licz();
  wypisz();
  return 0;
}
