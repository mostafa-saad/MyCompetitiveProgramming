/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     trob1.cpp                                                 *
 *   Autor:    Anna Niewiarowska                                         *
 *   Opis:     Rozwiazanie niepoprawne (bledy zaokraglen).               *
 *                                                                       *
 *************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

const int N=3000; //max. liczba punktow

struct point {
  int x;
  int y;
};

int n; //liczba punktow
int actx, acty; //wspolrzedne akt. obrabianego punktu
point t[N];


void input() {
  scanf("%d ", &n);
  for (int i=0; i<n; i++) scanf("%d %d ", &(t[i].x), &(t[i].y));
}

//funkcja porownawcza - sortowanie biegunowe wzgledem punktu (actx, acty)
int fpor(const void *v1, const void *v2) {
  double x1,x2,y1,y2;

  x1 = (((point *)v1) ->x) - actx;
  x2 = (((point *)v2) ->x) - actx;
  y1 = (((point *)v1) ->y) - acty;
  y2 = (((point *)v2) ->y) - acty;
  if (x1==0 && x2==0) return 0;
  if (x1==0) return -1;
  if (x2==0) return 1;
  double d1 = y1/x1;
  double d2 = y2/x2;
  if ( d1 < d2) return -1;
  if ( d1 > d2) return 1;
  return 0;
}

double poletr(double x1, double y1, double x2, double y2) {
  double a,b,cosl;

  a = sqrt(x1*x1+y1*y1);
  b = sqrt(x2*x2+y2*y2);
  cosl=0;
  if (a*b != 0) cosl = (x1*x2+y1*y2)/(a*b);
  if (cosl>1) cosl=1;
  if (cosl <-1) cosl=-1;
  return (0.5*a*b*sqrt(1-cosl*cosl));
}

//oblicza pole trojkatow o najmniejszym wierzcholku nr
double pole(int nr) {
  double wyniktmp; //wynik tymczasowy
  point sl, sp; //punkt -- suma wspolrzednych punktow na lewo/prawo

  sl.x=0; sl.y=0; sp.x=0; sp.y=0;
  wyniktmp=0;
  for (int i=nr+1; i<n; i++)
    if (t[i].x>actx || (t[i].x==actx && t[i].y<acty) ) {sp.x+=t[i].x-actx; sp.y+=t[i].y-acty;}
      else {sl.x+=t[i].x-actx; sl.y+=t[i].y-acty;}
  for (int i=nr+1; i<n; i++) {
    point p; p.x=t[i].x-actx; p.y=t[i].y-acty;
    wyniktmp+=poletr(p.x,p.y,sl.x,sl.y);
    wyniktmp+=poletr(p.x,p.y,sp.x,sp.y);
    if (p.x>0 || (p.x==0 && p.y<0) ) { //punkt przechodzi z prawej na lewa
      sp.x-=p.x; sp.y-=p.y;
      sl.x+=p.x; sl.y+=p.y;
    } else { //punkt przechodzi z lewej na prawa
      sl.x-=p.x; sl.y-=p.y;
      sp.x+=p.x; sp.y+=p.y;
    }
  }
  return (wyniktmp/2); //kazdy trojkat policzony dwa razy
}

int main() {
  double wynik;

  input();
  wynik=0;
  for (int i=0; i<n-2; i++) {
    actx = t[i].x;
    acty = t[i].y;
    qsort(&(t[i+1]),n-i-1,sizeof(point),fpor);
    wynik+=pole(i);
  }
  long long tmp = (long long)(wynik*10);
  printf("%llu.%d\n",tmp/10,(int)(tmp%10));

  return 0;
}
