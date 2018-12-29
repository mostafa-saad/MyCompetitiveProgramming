/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tets5.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie za wolne.                          *
 *                        Stosuje drzewo czwórkowe                       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int D,S,n;
int wynik;

/* Drzewo czworkowe, [0] - wartosc w tym polu, [1] - maksimum z synow */
int drzewo[3000000][2];

/* Funkcja mowiaca jak wysoko upadnie klocek o rogach (a,b)-(c,d)
   rozwazamy pole w drzewie i, pol tej wielkosci jest ile, koncza sie w miejscu koniec,
   jest to pole j-te w kolejnosci z tych, ma rogi (p,q), (r,s) */
int jak_wysoko(int a,int b,int c,int d,int i,int ile,int koniec,int j,int p,int q,int r,int s){
  int w,tmp;
  /* Rozlaczne? */
  if (a >= r || p >= c || b >= s || q >= d)
    return 0;
  /* W calosci sie zawiera? */
  if (a <= p && c >= r && b <= q && d >= s)
    return drzewo[i][1];
  /* Pierwszy kandydat to my */
  w = drzewo[i][0];
  /* Rozwazamy synow */
  tmp = jak_wysoko(a,b,c,d,koniec+(j<<2),(ile<<2),koniec+(ile<<2),(j<<2),p,q,(p+r)/2,(q+s)/2);
  if (tmp > w) w=tmp;
  tmp = jak_wysoko(a,b,c,d,koniec+(j<<2)+1,(ile<<2),koniec+(ile<<2),(j<<2)+1,(p+r)/2,q,r,(q+s)/2);
  if (tmp > w) w=tmp;
  tmp = jak_wysoko(a,b,c,d,koniec+(j<<2)+2,(ile<<2),koniec+(ile<<2),(j<<2)+2,p,(q+s)/2,(p+r)/2,s);
  if (tmp > w) w=tmp;
  tmp = jak_wysoko(a,b,c,d,koniec+(j<<2)+3,(ile<<2),koniec+(ile<<2),(j<<2)+3,(p+r)/2,(q+s)/2,r,s);
  if (tmp > w) w=tmp;
  return w;
}

/* Funkcja dodajaca klocek o rogach (a,b)-(c,d) o wysokosci w
   rozwazamy pole w drzewie i, pol tej wielkosci jest ile, koncza sie w miejscu koniec,
   jest to pole j-te w kolejnosci z tych, ma rogi (p,q), (r,s) */
void dodaj_klocek(int a,int b,int c,int d,int w,int i,int ile,int koniec,int j,int p,int q,int r,int s){
  /* Rozlaczne? */
  if (a >= r || p >= c || b >= s || q >= d)
    return;
  /* Aktualizujemy [1] */
  if (drzewo[i][1] < w)
    drzewo[i][1] = w;
  /* W calosci sie zawiera? */
  if (a <= p && c >= r && b <= q && d >= s){
    if (drzewo[i][0] < w)
      drzewo[i][0]=w;
    return;
  }
  /* Rozwazamy synow */
  dodaj_klocek(a,b,c,d,w,koniec+(j<<2),(ile<<2),koniec+(ile<<2),(j<<2),p,q,(p+r)/2,(q+s)/2);
  dodaj_klocek(a,b,c,d,w,koniec+(j<<2)+1,(ile<<2),koniec+(ile<<2),(j<<2)+1,(p+r)/2,q,r,(q+s)/2);
  dodaj_klocek(a,b,c,d,w,koniec+(j<<2)+2,(ile<<2),koniec+(ile<<2),(j<<2)+2,p,(q+s)/2,(p+r)/2,s);
  dodaj_klocek(a,b,c,d,w,koniec+(j<<2)+3,(ile<<2),koniec+(ile<<2),(j<<2)+3,(p+r)/2,(q+s)/2,r,s);
}

int main(void){
  int a,b,c,d,w; /* Lewy dolny, prawy gorny rog i wysokosc klocka */
  int poziom;
  scanf("%d%d%d",&D,&S,&n);
  while(n--){
    scanf("%d%d%d%d%d",&c,&d,&w,&a,&b); c+=a; d+=b;
    poziom = jak_wysoko(a,b,c,d,0,1,1,0,0,0,1024,1024);
    poziom += w;
    dodaj_klocek(a,b,c,d,poziom,0,1,1,0,0,0,1024,1024);
    if (poziom > wynik)
      wynik = poziom;
  }
  printf("%d\n",wynik);
  return 0;
}
