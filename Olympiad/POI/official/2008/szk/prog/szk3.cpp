/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szk3.cpp                                                  *
 *   Autor:    Anna Niewiarowska                                         *
 *   Opis:                                                               *
 *                                                                       *
 *************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a>b)?(b):(a))

const int MAX_N = 100000;
const int MAX_M = 300000;

struct point{
  int x;
  int y;
  int type; //0-bok,1-wierzcholek o dwusiecznej ll-ur,2-wierzcholek ul-lr
  int ll; //sasiedzi
  int lr; //sasiedzi
  int paired; //czy wierzcholek zostal juz sparowany
};

point t[MAX_M]; //kolejne wierzcholki
int order[MAX_M]; //porzadek wierzcholkow
int n; //liczba wierzcholkow
int points; //liczba punktow kratowych

//dodaje punkty kratowe scian
void wall(int v1, int v2) {
  if (t[v1].x!=t[v2].x)
    for (int j=MIN(t[v1].x,t[v2].x)+1; j<MAX(t[v1].x,t[v2].x); j++) {
      t[points].x=j; t[points].y=t[v1].y; t[points].type=0;
      points++;
    }
  else
    for (int j=MIN(t[v1].y,t[v2].y)+1; j<MAX(t[v1].y,t[v2].y); j++) {
      t[points].x=t[v1].x; t[points].y=j; t[points].type=0;
      points++;
    }
}

//oblicza typ wierzcholka v1 sasiadujacego z wierzcholkami v2 i v3
void vertex(int v1, int v2, int v3) {
  if (t[v1].x>=t[v2].x && t[v1].y>=t[v2].y && t[v1].x>=t[v3].x && t[v1].y>=t[v3].y) t[v1].type=1;
  else if (t[v1].x<=t[v2].x && t[v1].y<=t[v2].y && t[v1].x<=t[v3].x && t[v1].y<=t[v3].y) t[v1].type=1;
  else t[v1].type=2;
}

//wczytuje dane o grafie
void input() {
  scanf("%d ",&n);
  for (int i=0; i<n; i++)
    scanf("%d %d ",&(t[i].x),&(t[i].y));
  points=n;
  for (int i=0; i<n-1; i++) wall(i,i+1);
  wall(n-1,0);
  for (int i=1; i<n-1; i++) vertex(i,i-1,i+1);
  vertex(0,1,n-1);
  vertex(n-1,0,n-2);
}

//funkcja porownawcza dla porzadku ll-ur
int fpor1(const void *v1,const void *v2){
  point p1=t[*(int *)v1];
  point p2=t[*(int *)v2];
  if (p1.y-p1.x!=p2.y-p2.x) return ((p1.y-p1.x)-(p2.y-p2.x));
  return (p1.y-p2.y);
}

//funkcja porownawcza dla porzadku lr-ul
int fpor2(const void *v1,const void *v2){
  point p1=t[*(int *)v1];
  point p2=t[*(int *)v2];
  if (p1.y+p1.x!=p2.y+p2.x) return ((p1.y+p1.x)-(p2.y+p2.x));
  return (p1.x-p2.x);
}

int find_next_ll(int pos) {
  int tmp = pos+1;
  while (tmp<points && t[order[tmp]].type==2) tmp++;
  if (tmp>=points) return -1;
  return tmp;
}

int find_next_lr(int pos) {
  int tmp = pos+1;
  while (tmp<points && t[order[tmp]].type==1) tmp++;
  if (tmp>=points) return -1;
  return tmp;
}

//znajduje sasiadow dla wierzcholkow
void neighbours() {
  int act, act2;
  for (int i=0; i<points; i++) order[i]=i;
  qsort(order, points, sizeof(int), fpor1);
  act=find_next_ll(-1);
  while (act>=0 && act<points) {
    act2=find_next_ll(act);
    t[order[act]].ll=order[act2];
    t[order[act2]].ll=order[act];
    act=find_next_ll(act2);
  }
  qsort(order, points, sizeof(int), fpor2);
  act=find_next_lr(-1);
  while (act>=0 && act<points) {
    act2=find_next_lr(act);
    t[order[act]].lr=order[act2];
    t[order[act2]].lr=order[act];
    act=find_next_lr(act2);
  }
}


int find_target_lr(int pos);
//znajduje element, do ktorego prowadzi sciezka
int find_target_ll(int pos) {
  int target = t[pos].ll;
  if (t[target].type==0)
    return find_target_lr(target);
  return target;
}
int find_target_lr(int pos) {
  int target = t[pos].lr;
  if (t[target].type==0)
    return find_target_ll(target);
  return target;
}

//znajdowanie pary dla elementu o numerze pos
void pair(int pos) {
  int res=0;
  if (t[pos].type==1) res=find_target_ll(pos);
  else res=find_target_lr(pos);
  t[pos].paired=1;
  t[res].paired=1;
  printf("%d %d\n",pos+1,res+1);
}

int main() {
  input();
  printf("%d\n",(n/2));
  neighbours();

  for (int i=0; i<n; i++) t[i].paired=0;
  for (int i=0; i<n; i++) if (t[i].paired==0) pair(i);
  return 0;
}
