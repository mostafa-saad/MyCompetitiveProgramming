/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZAB (¯aby)                                     *
 *   Plik:                zabb1.c                                        *
 *   Autor:               Piotr Stañczyk                                 *
 *   Opis:                Dijkstra do wyznaczenia odleglosci pol od      *
 *                        elektrod + Dijkstra do znaleznienia najlepszej *
 *                        sciezki, z³o¿onosæ O((wx*wy)log(wx*wy))        *
 *                                                                       *
 *************************************************************************/

#include <math.h>
#include <stdio.h>

#define swap(a, b) do { \
 typeof(a) _tmp = (a); \
 (a) = (b); \
 (b) = _tmp; \
} while(0)

static inline int max(int a, int b)
{
 return a > b ? a : b;
}

#define max_size 1000
#define inf 1000000000

struct PoleEl
{
 int dis; // Priorytet elementu w kolejce
 int waga; // Waga uzywana przez Dijkstre wyszukujaca sciezke
 short int s_x,s_y; // Przesuniecie od najblizszej elektrody
 short int x,y; // Wspolrzedne aktualnego punktu
 int d_wsk; // Wskaznik na pozycje elementu w stosie
};

struct PoleEl pole[max_size][max_size]; // Pole 
struct PoleEl* heap[max_size*max_size+1]; // Kolejka
int heap_size=0;
int wx,wy; // Wymiary pola
int px,py,kx,ky; // Poczatek i koniec wycieczki

static inline void Exchange(int a, int b)
{
 swap(heap[a]->d_wsk,heap[b]->d_wsk);
 swap(heap[a],heap[b]);
}

void UpHeap(int el)
{
 while(el>1 && heap[el>>1]->dis>heap[el]->dis)
 {
  Exchange(el,el>>1);
  el>>=1;
 }
}

void DownHeap(int el)
{
 int zam=el;
 for(;;)
 {
  if(heap_size>=(el<<1) && heap[(el<<1)]->dis<heap[el]->dis) zam=(el<<1);
  if(heap_size>(el<<1) && heap[(el<<1)+1]->dis<heap[zam]->dis) zam=(el<<1)+1;
  if(el==zam) break;
  Exchange(el,zam); 
  el=zam;
 }
}

void PutHeap(int x, int y)
{
 pole[x][y].d_wsk=++heap_size;
 heap[heap_size]=&pole[x][y];
 UpHeap(heap_size);
}

void RemTop()
{
 Exchange(1,heap_size--);
 DownHeap(1);
}

void AddToHeapDis(int x, int y, int t, int cx, int cy)
{
// Dodaje/modyfikuje punkt (x,y) w kolejce priorytetowej dla 1-szej Dijkstry.
// t - priorytet punktu.
// (cx,cy) - przesuniecie od elektrody dla aktualnego punktu
 if(x<0 || y<0 || x>=wx || y>=wy) return;
 if(pole[x][y].dis>t)
 {
  pole[x][y].s_x=cx;
  pole[x][y].s_y=cy;
 }
 if(pole[x][y].dis==inf)
 {
  pole[x][y].dis=t;
  PutHeap(x,y);
 }else if(pole[x][y].dis>t)
 {
  pole[x][y].dis=t;
  UpHeap(pole[x][y].d_wsk);
 }
}


void DikstraDis()
{
// Dijkstra znajdujaca najblizsze elektrody dla poszczegolnych pol
 int px,py,kx,ky;
 while(heap_size)
 {
  px=heap[1]->x;
  py=heap[1]->y;
  kx=pole[px][py].s_x;
  ky=pole[px][py].s_y;
  RemTop();
  if(kx<=0) AddToHeapDis(px+1,py,(kx-1)*(kx-1)+ky*ky,kx-1,ky);
  if(kx>=0) AddToHeapDis(px-1,py,(kx+1)*(kx+1)+ky*ky,kx+1,ky);
  if(ky>=0) AddToHeapDis(px,py-1,kx*kx+(ky+1)*(ky+1),kx,ky+1);
  if(ky<=0) AddToHeapDis(px,py+1,kx*kx+(ky-1)*(ky-1),kx,ky-1);
 }
}

void AddToHeapMax(int x, int y, int t)
{
// Dodaje/modyfikuje punkt (x,y) w kolejce priorytetowej dla Dijkstry szukajacej najlepszej sciezki.
// t - nowy priorytet punktu.
 if(x<0 || y<0 || x>=wx || y>=wy) return;
 t=max(t,-pole[x][y].waga);
 if(pole[x][y].dis==inf)
 {
  pole[x][y].dis=t;
  PutHeap(x,y);
 }else if(pole[x][y].dis>t)
 {
  pole[x][y].dis=t;
  UpHeap(pole[x][y].d_wsk);
 }
}

void DikstraMax()
{
 // Dijkstra obliczajaca najlepsza sciezke
 int px,py,v;
 while(heap_size)
 {
  px=heap[1]->x;
  py=heap[1]->y;
  v=heap[1]->dis;
  RemTop();
  AddToHeapMax(px+1,py,v);
  AddToHeapMax(px,py+1,v);
  AddToHeapMax(px-1,py,v);
  AddToHeapMax(px,py-1,v);
 }
}

int main()
{
 scanf("%d %d",&wx,&wy);
 scanf("%d %d %d %d",&px,&py,&kx,&ky);
 px--; py--; kx--; ky--;
 int elektrody,x,y,z;
 scanf("%d",&elektrody);
 for(x=0;x<wx;x++) for(y=0;y<wy;y++)
 {
  pole[x][y].dis=inf; 
  pole[x][y].x=x;
  pole[x][y].y=y;
 }
 for(z=0;z<elektrody;z++)
 {
  scanf("%d %d",&x,&y);
  AddToHeapDis(x-1,y-1,0,0,0);
 }
 DikstraDis(); // Licz odleglosci najblizszych elektrod
 for(x=0;x<wx;x++) for(y=0;y<wy;y++)
 { // Po wykonaniu 1-szej Dijkstry, przepisz priorytety i zaczynamy 2-ga Dijkstre
  pole[x][y].waga=pole[x][y].dis;
  pole[x][y].dis=inf;
 }
 AddToHeapMax(px,py,-pole[px][py].waga);
 DikstraMax();
 printf("%d\n", -pole[kx][ky].dis);
 return 0;
}
