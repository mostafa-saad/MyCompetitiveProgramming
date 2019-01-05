#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<assert.h>

#define		MAXN	100000

typedef struct
{
  double x, y;
} point;

typedef struct
{
  double f, t;
  int pnt1, pnt2;
} interval;

int ininterval(double *d, interval *i)
{
  if(*d<i->f)
    return -1;
  
  if(*d>i->t)
    return 1;

  return 0;
}

int sort_y(point *x, point *y)
{
  
  if(x->y>y->y)
    return -1;
  if(x->y<y->y)
    return 1;

  if(x->x<y->x)
    return -1;
  if(x->x>y->x)
    return 1;

  return 0;
}

double areaof(point a, point b, point c)
{
  double dx1, dy1, dx2, dy2;
  
  dx1=b.x-a.x;
  dy1=b.y-a.y;
  dx2=c.x-a.x;
  dy2=c.y-a.y;

//  printf("area of [%3lf,%3lf], [%3lf,%3lf], [%3lf,%3lf]: %3lf\n", a.x, a.y, b.x, b.y, c.x, c.y, fabs(dx1*dy2-dx2*dy1));
  return fabs(dx1*dy2-dx2*dy1);
}


int onright(point a, point b, point c)
{
  double dx1, dy1, dx2, dy2;
  
  dx1=b.x-a.x;
  dy1=b.y-a.y;
  dx2=c.x-a.x;
  dy2=c.y-a.y;
  
  if(dx1*dy2-dx2*dy1<0)
    return 1;
   else
    return 0;
}


int N;
point pnt[MAXN];
interval I[MAXN+1];

void convex_hull()
{
  point l[MAXN], r[MAXN];
  int ls, rs;
  
  int i;

  I[0].pnt2=N-1;
  if(N<=2)
    return;
  
  l[0]=r[0]=pnt[0];
  l[1]=r[1]=pnt[1];
  ls=rs=2;
  
  for(i=2; i<N; i++)
  {
    while(ls>1 && onright(l[ls-2], l[ls-1], pnt[i]))
      ls--;
    while(rs>1 && !onright(r[rs-2], r[rs-1], pnt[i]))
      rs--;
    l[ls++]=r[rs++]=pnt[i];
  }
  
  N=0;
  for(i=0; i<ls; i++)
    pnt[N++]=l[i];
  I[0].pnt2=N-1;
  for(i=rs-2; i>0; i--)
    pnt[N++]=r[i];
}


int main()
{
  int i;
  point p1, p2;
  double d;
  interval *X;

  scanf("%d\n", &N);
  for(i=0; i<N; i++)
    scanf("%lf %lf\n", &pnt[i].x, &pnt[i].y);
  
  qsort(pnt, N, sizeof(point), (int(*)(const void *, const void *))sort_y);
  convex_hull();
  if(N>1)
  {
    I[0].f=0;
    I[0].pnt1=0;
    for(i=0; i<N; i++)
    {
      I[i].t=atan2(pnt[i].y-pnt[(i+1)%N].y, pnt[i].x-pnt[(i+1)%N].x);
      if(I[i].t<0)
        I[i].t+=2*M_PI;
      assert(I[i].f<I[i].t);
      
      I[i+1].f=I[i].t;
      I[i+1].pnt1=(i+1)%N;
      I[i+1].pnt2=I[i].pnt2;
      while(areaof(pnt[i], pnt[(i+1)%N], pnt[(I[i+1].pnt2+1)%N])>areaof(pnt[i], pnt[i+1], pnt[I[i+1].pnt2]))
        I[i+1].pnt2=(I[i+1].pnt2+1)%N;
      
    }
    I[N].t=2*M_PI;
    assert(I[N].f<I[N].t);
  }

/*  for(i=0; i<N; i++)
    printf("%3lf %3lf\n", pnt[i].x, pnt[i].y);

  for(i=0; i<=N; i++)
    printf("uhol %3lf - %3lf: body [%3lf,%3lf], [%3lf,%3lf]\n", I[i].f, I[i].t, pnt[I[i].pnt1].x, pnt[I[i].pnt1].y, pnt[I[i].pnt2].x, pnt[I[i].pnt2].y);
*/

  while(scanf("%lf %lf %lf %lf\n", &p1.x, &p1.y, &p2.x, &p2.y)>0)
  {
    if(N<2)
    {
      printf("OK\n");
      fflush(stdout);
      continue;
    }
    
    d=atan2(p2.y-p1.y, p2.x-p1.x);
    if(d<0)
      d+=2*M_PI;
    X=bsearch(&d, I, N+1, sizeof(interval), (int(*)(const void *, const void *))ininterval);
    assert(X);

    if(onright(p1, p2, pnt[X->pnt1])+onright(p1, p2, pnt[X->pnt2])==1)
    {
      printf("SPLIT\n");
      fflush(stdout);
      continue;
    }

    d=atan2(p1.y-p2.y, p1.x-p2.x);
    if(d<0)
      d+=2*M_PI;
    X=bsearch(&d, I, N+1, sizeof(interval), (int(*)(const void *, const void *))ininterval);
    assert(X);

    if(onright(p1, p2, pnt[X->pnt1])+onright(p1, p2, pnt[X->pnt2])==1)
    {
      printf("SPLIT\n");
      fflush(stdout);
      continue;
    }

    printf("OK\n");
    fflush(stdout);
  }
  
  return 0;
}
