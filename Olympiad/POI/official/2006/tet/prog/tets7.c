/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tets7.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie za wolne.                          *
 *                        Stosuje D poprawnych rozaiwazan tetrisa 2D dla *
 *                        kazdej linii z heurystyka: wpierw wszystko     *
 *                        wczytuje i okresla, w ktora strone sie         *
 *                        bardziej oplaca.                               *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int D,S,n;
int wynik;

/* Spadniete klocki */
struct{
  int d,s,h,x,y;
} klocki[20000];

/* Drzewa maksymalne, [0] - wartosc w tym miejscu, [1] - maksimum po synach */
int drzewa[1000][2049][2];

/* Funkcja zwracajaca maksimum dla drzewa i-tego, przedzial a do c, rozwazamy przedzial bazowy j, od x do y */
int jak_wysoko(int i, int a, int c, int j, int x, int y){
  int w,tmp;
  /* poza przedzialem */
  if (c <= x || y <= a) return 0;
  /* Jesli jestesmy w calosci zawarci to koniec */
  if (a <= x && y <= c)
    return drzewa[i][j][1];
  /* Nasz klocek to pierwszy kandydat */
  w = drzewa[i][j][0];
  /* Dalej idziemy wglab */
  tmp = jak_wysoko(i, a, c, j<<1, x, (x+y)/2);
  if (tmp > w) w=tmp;
  tmp = jak_wysoko(i, a, c, (j<<1)+1, (x+y)/2, y);
  if (tmp > w) w=tmp;
  return w;
}

/* Funkcja aktualizujaca drzew i-te, przedzial a do c wysokosci w, rozwazamy przedzial bazowy j, od x do y */
void dodaj_klocek(int i, int a, int c, int w, int j, int x, int y){
  /* poza przedzialem */
  if (c <= x || y <= a) return;
  /* aktualizujemy [1], czyli maksimum */
  if (drzewa[i][j][1] < w)
    drzewa[i][j][1] = w;
  /* Jesli jestesmy w calosci zawarci to koniec */
  if (a <= x && y <= c){
    if (drzewa[i][j][0] < w)
      drzewa[i][j][0] = w;
    return;
  }
  /* Dalej idziemy wglab */
  dodaj_klocek(i, a, c, w, j<<1, x, (x+y)/2);
  dodaj_klocek(i, a, c, w, (j<<1)+1, (x+y)/2, y);
}
  
int main(void){
  int a,b,c,d,w; /* Lewy dolny, prawy gorny rog i wysokosc klocka */
  int poziom,i,j,tmp;
  int iled,iles; /* Do liczenia */
  scanf("%d%d%d",&D,&S,&n);
  iled=0; iles=0;
  for (i=0;i<n;++i){
    scanf("%d%d%d%d%d",&(klocki[i].d),&(klocki[i].s),&(klocki[i].h),&(klocki[i].x),&(klocki[i].y));
    iled += klocki[i].d;
    iles += klocki[i].s;
  }
  if (iles < iled){
    for (j=0;j<n;++j){
      a = klocki[j].x; b = klocki[j].y;
      c = klocki[j].d + a; d = klocki[j].s + b;
      poziom = 0;
      for (i=b;i<d;++i){
        tmp = jak_wysoko(i, a, c, 1, 0, 1024);
        if (tmp > poziom)
          poziom = tmp;
      }
      poziom += klocki[j].h;
      for (i=b;i<d;++i)
        dodaj_klocek(i, a, c, poziom, 1, 0, 1024);
      if (poziom > wynik)
        wynik = poziom;
    }
  }
  else{
    for (j=0;j<n;++j){
      a = klocki[j].x; b = klocki[j].y;
      c = klocki[j].d + a; d = klocki[j].s + b;
      poziom = 0;
      for (i=a;i<c;++i){
        tmp = jak_wysoko(i, b, d, 1, 0, 1024);
        if (tmp > poziom)
          poziom = tmp;
      }
      poziom += klocki[j].h;
      for (i=a;i<c;++i)
        dodaj_klocek(i, b, d, poziom, 1, 0, 1024);
      if (poziom > wynik)
        wynik = poziom;
    }
  }
  printf("%d\n",wynik);
  return 0;
}
