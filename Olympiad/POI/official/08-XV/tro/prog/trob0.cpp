/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     trob0.cpp                                                 *
 *   Autor:    Anna Niewiarowska                                         *
 *   Opis:     Rozwiazanie niepoprawne (bledy zaokraglen).               *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <math.h>

#define MAX_N 3000

struct point
{
  int x, y;
};

int n;
point t[MAX_N];

double pole(int i, int j, int k) {
  double a,b,cosl;

  a = sqrt((t[i].x-t[j].x)*(t[i].x-t[j].x)+(t[i].y-t[j].y)*(t[i].y-t[j].y));
  b = sqrt((t[i].x-t[k].x)*(t[i].x-t[k].x)+(t[i].y-t[k].y)*(t[i].y-t[k].y));
  cosl=0;
  if (a*b != 0) cosl = ((t[i].x-t[j].x)*(t[i].x-t[k].x)+(t[i].y-t[j].y)*(t[i].y-t[k].y))/(a*b);
  if (cosl>1) cosl=1;
  if (cosl <-1) cosl=-1;
  return (0.5*a*b*sqrt(1-cosl*cosl));
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%u%u", &(t[i].x), &(t[i].y));
  double wyn = 0.0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      for (int k = j + 1; k < n; k++)
        wyn += pole(i,j,k);

  long long tmp = (long long)(wyn*10);
  printf("%llu.%d\n",tmp/10,(int)(tmp%10));
  return 0;
}
