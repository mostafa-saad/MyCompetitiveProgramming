/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tet.c                                          *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                        Stosuje dwuwymiarowy dag prostokatow bazowych. *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int n,D,S;
int wynik;

/* DAG prostokatow bazowych, dag[x][y] - prostokat bazowy powstaly
   z iloczynu bazowego x razy bazowy y na kazdej wspolrzednej,
   bazowe na wspolrzednych sa liczone jak w drzewie licznikowym:
   1 to [0..1023], x sie sklada z 2*x i 2*x+1,
   pierwsze pole dagu to wysokosc klocka, drugie to maksimum z synow,
   trzecie to maksimum z potomkow o rownej wysokosci, czwarte to maksimum
   z potomkow o rownej szerokosci  */
int dag[2049][2049][4];
/* Tablica bylo, przy przegladaniu DAGu, by nie robic wielokrotnie tego samego */
int bylo[2049][2049];
/* Do liczenie liczby wywolan funkcji na DAGu, aby nie czyscic tablicy "bylo" */
int licznik; 

/* Funkcja zwracajaca jak wysoko zatrzyma sie klocek 
   (a,b),(c,d) - lewy dolny i prawy gorny rog klocka
   i, j - rozwazamy prostokat bazowy (i,j), o wymiarach
   (p,q) (r,s) */
int jak_wysoko(int a,int b,int c,int d,int i,int j,int p,int q,int r,int s){
  int w,tmp;
  if (bylo[i][j] == licznik) return 0;
  bylo[i][j]=licznik;
  /* Nie przecinaja sie */
  if (a >= r || p >= c || b >= s || q >= d)
    return 0;
  /* Jestesmy na dolnym poziomie */
  if (i >= 1024 && j >= 1024) 
    return dag[i][j][1];
  /* Prostokat rozwazany jest w calosci w naszym */
  if (a <= p && b <= q && c >= r && d >= s)
    return dag[i][j][1];
  w = dag[i][j][0]; /* Nasza wysokosc */
  /* Teraz jesli prostokat szukany jest w szerokosci lub dlugosci w calosci nadzbiorem rozwazanego
     bazowego, musimy w poprawic o szerokosci */
  if (a <= p && c >= r)
    if (w < dag[i][j][3])
      w = dag[i][j][3];
  if (b <= q && d >= s)
    if (w < dag[i][j][2])
      w = dag[i][j][2];
  /* Dzielimy wzdluz x, jesli ma to sens - czyli szerokosc >1, prostokat nie zajmuje calej szerokosci */ 
  if (i < 1024 && (!(a <= p && c >= r))){
    tmp = jak_wysoko(a,b,c,d,i<<1,j,p,q,(p+r)/2,s);
    if (tmp > w) w = tmp;
    tmp = jak_wysoko(a,b,c,d,(i<<1)+1,j,(p+r)/2,q,r,s);
    if (tmp > w) w = tmp;
  }
  /* Dzielimy wzdluz y, jesli ma to sens - czyli szerokosc >1, prostokat nie zajmuje calej szerokosci */
  if (j < 1024 && (!(b <= q && d >= s))){
    tmp = jak_wysoko(a,b,c,d,i,j<<1,p,q,r,(q+s)/2);
    if (tmp > w) w = tmp;
    tmp = jak_wysoko(a,b,c,d,i,(j<<1)+1,p,(q+s)/2,r,s);
    if (tmp > w) w = tmp;
  }
  return w;
}  

/* Funkcja wkladajaca klocek na okreslonej wysokosci
   (a,b),(c,d) - lewy dolny i prawy gorny rog klocka
   i, j - rozwazamy prostokat bazowy (i,j), o wymiarach
   (p,q) (r,s), w - wysokosc */
void wstaw_klocek(int a,int b,int c,int d,int i,int j,int p,int q,int r,int s,int w){
  if (bylo[i][j] == licznik) return;
  bylo[i][j]=licznik;
  /* Nie przecinaja sie */
  if (a >= r || p >= c || b >= s || q >= d)
    return;
  /* Aktualizujemy */
  if (dag[i][j][1] < w)
    dag[i][j][1]=w;
  /* Teraz jesli prostokat szukany jest w szerokosci lub dlugosci w calosci nadzbiorem rozwazanego
     bazowego, musimy w poprawic dag[2] i dag[3] */
  if (a <= p && c >= r)
    if (dag[i][j][2] < w)
      dag[i][j][2] = w;
  if (b <= q && d >= s)
    if (dag[i][j][3] < w)
      dag[i][j][3] = w;
  /* Prostokat rozwazany jest w calosci w naszym */
  if (a <= p && b <= q && c >= r && d >= s){
    if (dag[i][j][0] < w)
      dag[i][j][0] = w;
    return;
  }
  /* Dzielimy wzdluz x, jesli ma to sens - czyli szerokosc >1, prostokat nie zajmuje calej szerokosci */
  if (i < 1024 && (!(a <= p && c >= r))){
    wstaw_klocek(a,b,c,d,i<<1,j,p,q,(p+r)/2,s,w);
    wstaw_klocek(a,b,c,d,(i<<1)+1,j,(p+r)/2,q,r,s,w);
  }
  /* Dzielimy wzdluz y, jesli ma to sens - czyli szerokosc >1, prostokat nie zajmuje calej szerokosci */
  if (j < 1024 && (!(b <= q && d >= s))){
    wstaw_klocek(a,b,c,d,i,j<<1,p,q,r,(q+s)/2,w);
    wstaw_klocek(a,b,c,d,i,(j<<1)+1,p,(q+s)/2,r,s,w);
  }
}  

int main(void){
  int poziom;
  int a,b,c,d,w; /* Lewy dolny, prawy gorny rog i wysokosc klocka */
  scanf("%d%d%d",&D,&S,&n);
  while(n--){
    scanf("%d%d%d%d%d",&c,&d,&w,&a,&b);
    c+=a; d+=b;
    ++licznik;
    poziom = jak_wysoko(a,b,c,d,1,1,0,0,1024,1024);
    poziom += w;
    if (wynik < poziom) wynik = poziom;
    ++licznik;
    wstaw_klocek(a,b,c,d,1,1,0,0,1024,1024,poziom);
  }
  printf("%d\n",wynik);
  return 0;
}
