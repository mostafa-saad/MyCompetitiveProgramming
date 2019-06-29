/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Robinson (ROB)                                            *
 *   Plik:     rob5.cpp                                                  *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie o zlozonosci pamieciowej i obliczeniowej      *
 *             O(n^2)                                                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int N=2000;

char mapa[N][N+1];
int n;
int starti,startj; //pozycja startowa lodki (wspolrzedne dziobu)
vector<int> bok; //ciag grubosci kolejnych poziomych przekojow przez lodke
bool zle[3*N][3*N]; //czy lodka (jej dziob) nie moze stac w tym miejscu,
                    //gdyz bedzie nachodzic na trzcine
bool przykryty[3*N][3*N]; //tablica pomocnicza dla funkcji zabron_pola


int ostatni[3*N]; //numer kolumny ostatniego pola trzciny w tym wierszu
int poczatek[N+1],koniec[N+1]; //numery wierszy w ktorych w danej kolumnie jest lodz
int dist[3*N][3*N]; //odleglosc obliczana przy algorytmie BFS
int mini,minj,maxi,maxj; //ograniczenia wspolrzednych lodzi

/*zmieniamy uklad planszy, aby obrocic os symetrii lodzi o 90 stopni*/
void symetria(){
  for (int i=0; i<n; ++i)
    for (int j=0; j<i; ++j)
      swap(mapa[i][j],mapa[j][i]);
}


/*szukanie lodki na planszy, zakladajac ze os symetrii lodki jest linia pionowa*/
int znajdz_lodke(){
  mini=n,minj=n,maxi=0,maxj=0;
  for (int i=0; i<n; ++i) 
    for (int j=0; j<n; ++j)
      if (mapa[i][j]=='r'){
        mini=min(mini,i);
        minj=min(minj,j);
        maxi=max(maxi,i);
        maxj=max(maxj,j);
      }  
  if ((maxj-minj)%2) return 0;
  int sym=(maxj+minj)/2;
  bok.clear(); 
  starti=mini; startj=sym;
  for (int i=mini; i<=maxi; ++i){
    int lewy=0,prawy=0;
    for (int j=minj; j<=maxj; ++j) if (mapa[i][j]=='r'){
      if (j<sym) lewy++;
      if (j>sym) prawy++;
    }
    if (lewy!=prawy) return 0; //lodka nie jest symetryczna
    bok.push_back(lewy);
  }
  return 1;
}

void wczytaj(){
  scanf("%d",&n);
  for (int i=0; i<n; ++i) scanf("%s",mapa[i]);

  if (!znajdz_lodke()){
    symetria();
    znajdz_lodke();
  }
}

void przetworz_przekroje(){
  int szer=*max_element(bok.begin(),bok.end());
  for (int j=0; j<=szer; ++j){
    poczatek[j]=n; koniec[j]=0;
    for (int i=0; i<(int)bok.size(); ++i) if (bok[i]>=j){
      poczatek[j]=min(poczatek[j],i);
      koniec[j]=i;
    }
  }
}

/*procedura ta oblicza ktore pola sa zabronione (gdzie nie moze znajdowac sie
  dziob lodzi, biorac pod uwage lewa (zamien=0) lub prawa (zamien=1) strone lodzi*/
void zabron_pola(int zamien){
  int szer=*max_element(bok.begin(),bok.end());
  int przedzialy[3*N];
  for (int i=0; i<3*n; ++i) ostatni[i]=-n;
  for (int j=0; j<3*n; ++j){
    if (j>=n && j<2*n)
      for (int i=0; i<n; ++i) if (mapa[i][(zamien?3*n-1-j:j)-n]=='X') ostatni[i]=j;

    for (int i=0; i<3*n; ++i) przedzialy[i]=0;

    for (int i=0; i<n; ++i) if (j-ostatni[i]<=szer){
      int d=j-ostatni[i];
      przedzialy[n+i-koniec[d]]++;
      przedzialy[n+i-poczatek[d]+1]--;
    }
    int acc=0;
    for (int i=0; i<3*n; ++i){
      acc+=przedzialy[i];
      if (acc){
        przykryty[i][zamien?3*n-1-j:j]=1;
      }
    }
  }
}

int bfs(){
  int dx[]={0,0,1,-1};
  int dy[]={1,-1,0,0}; 
  vector<pair<short int,short int> > q;
  for (int i=0; i<3*n; ++i)
    for (int j=0; j<3*n; ++j)
      dist[i][j]=-1;

  starti+=n; startj+=n;
  mini+=n; maxi+=n; minj+=n; maxj+=n;

  q.push_back(make_pair(starti,startj));
  dist[starti][startj]=0;
  for (int pos=0; pos<(int)q.size(); ++pos){
    int i=q[pos].first;
    int j=q[pos].second;
    if (!przykryty[i][j]) return dist[i][j];
    for (int ruch=0; ruch<4; ++ruch){
      int ni=i+dx[ruch];
      int nj=j+dy[ruch];
      if (ni>=0 && ni<3*n && nj>=0 && nj<3*n && dist[ni][nj]==-1 && !zle[ni][nj]){
        dist[ni][nj]=dist[i][j]+1;
        q.push_back(make_pair(ni,nj));
      }
    }
  }
  return -1;
}

int wyplyn(){
  przetworz_przekroje();
  zabron_pola(0);
  zabron_pola(1);
  for (int i=0; i<3*n; ++i)
    for (int j=0; j<3*n; ++j){
      zle[i][j]=przykryty[i][j];
      przykryty[i][j]=false;
    }

  for (int i=0; i<n; ++i)
    for (int j=0; j<n; ++j)
      mapa[i][j]='X';

  zabron_pola(0);
  zabron_pola(1);

  int x=bfs();
  if (x>=0) printf("%d\n",x);
  return x>=0;
}

int main(){
  wczytaj();
  if (!wyplyn()) printf("NIE\n");
  return 0;
}
