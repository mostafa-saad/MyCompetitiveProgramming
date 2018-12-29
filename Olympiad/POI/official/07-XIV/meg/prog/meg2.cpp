/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Megalopolis (MEG)                                          *}
{*   Plik:    meg2.cpp                                                   *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Rozwiazanie zblizone do wzrocowego, o tej samej zlozonosci *}
{*            obliczeniowej O((n+m) * log n)                             *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <vector>
using namespace std;

const int N=250000;
vector<int> kraw[N];
int n;
int BASE;
int drzewo[1<<19];
int ojciec[N];
int rozmiar_poddrzewa[N];
int numer[N];
int glebokosc[N];

void wczytaj_graf(){
  scanf("%d",&n);
  for (int i=0; i<n-1; ++i){
    int a,b;
    //wczytujemy i dodajemy krawedz do grafu
    scanf("%d %d",&a,&b);
    kraw[--a].push_back(--b);
    kraw[b].push_back(a);
  }
}

//uaktualnienie wartosci w drzewie licznikowym
void dodaj(int x,int co){
  x+=BASE;
  while (x>=1){
    drzewo[x]+=co;
    x>>=1;
  }
}

//znajdujemy sume w danym przedziale
int suma(int wezel,int l,int r,int L,int R){
  if (l<=L && R<=r) return drzewo[wezel];
  int M=(L+R)/2;
  int wynik=0;
  if (l<=M) wynik+=suma(2*wezel,l,r,L,M);
  if (r>M) wynik+=suma(2*wezel+1,l,r,M+1,R);
  return wynik;
}

//przenumerowanie wierzcholkow, aby otrzymac porzadek typu preorder
void dfs(int x,int parent,int &nr,int h){
  rozmiar_poddrzewa[x]=1;
  ojciec[x]=parent;
  numer[x]=nr++;
  glebokosc[x]=h;
  for (int i=0; i<(int)kraw[x].size(); ++i){
    int v=kraw[x][i];
    if (v!=parent){
      dfs(v,x,nr,h+1);
      rozmiar_poddrzewa[x]+=rozmiar_poddrzewa[v];
    }
  }
}

int main(){
  int m;
  char txt[2];
  int nr=0;
  wczytaj_graf();
  BASE=1;
  //potrzebujemy o jedno pole wiecej
  while (BASE<=n) BASE<<=1;
  dfs(0,-1,nr,0);
  scanf("%d",&m);
  m+=n-1;
  while (m--){
    scanf("%s",txt); 
    if (txt[0]=='W'){
      int a;
      scanf("%d",&a);
      a--;
      printf("%d\n",glebokosc[a]-suma(1,0,numer[a],0,BASE-1));
    } else{
      int a,b;
      scanf("%d %d",&a,&b);
      a--; b--;
      if (ojciec[a]!=b) swap(a,b);
      dodaj(numer[a],1);
      dodaj(numer[a]+rozmiar_poddrzewa[a],-1);
    }
  }
  return 0;
}
