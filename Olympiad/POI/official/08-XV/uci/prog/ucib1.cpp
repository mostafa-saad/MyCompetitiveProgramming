/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     ucib1.cpp                                                 *
 *   Autor:    Wojciech Tyczyñski                                        *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;


#define MAX_N 105


int ruch[4][2]={{-1,0},{0,1},{1,0},{0,-1}};

int n,m;          // rozmiary planszy
int P;          // wynik podajemy modulo P
int x,y;        // pozycja kryjówki
bool mozna[MAX_N][MAX_N];    // czy pole jest dla nas dostêpne
int wyn[4][MAX_N][MAX_N][MAX_N][2];  // tablica wynikow
bool odcinek[MAX_N][MAX_N][MAX_N][4];  // tablice unikania policji


inline int oblicz(int l0, int l1, int l2, int l3, int k) {
  if (l0==0) return 1;

  int w=0;
  if (l1>0) w+=wyn[k][l0][l1-1][l2][(l0+l1+l2+l3+1)%2];
  w+=wyn[(k+1)%4][l1][l2][l3][(l0+l1+l2+l3+1)%2];
  return w;
}


int main() {
  scanf("%d%d%d",&n,&m,&P);
  scanf("%d%d",&x,&y);

  char buf[MAX_N];
  for(int i=0; i<n; i++) {
    scanf("%s",buf);
    for(int j=0; j<m; j++) mozna[i][j]=(buf[j]=='+');
  }

  int l0,l1,l2,l3;
  for(int sum=0; sum<=n+m-2; sum++)
    for(int i=0; i<x && i<=sum; i++)
      for(int j=0; j<y && j+i<=sum; j++)
        for(int k=0; k<=m-x && k+j+i<=sum; k++) {  
          l0=i,l1=j,l2=k,l3=sum-i-j-k;
          if (l3>n-y) continue;

          for(int kier=0; kier<4; kier++) {
            wyn[kier][l0][l1][l2][sum%2]=oblicz(l0,l1,l2,l3,kier)%P;
            swap(l0,l1),swap(l1,l2),swap(l2,l3);
          }
        }

  printf("%d\n",wyn[0][x-1][y-1][m-x][(n+m)%2]);
  return 0;
}
