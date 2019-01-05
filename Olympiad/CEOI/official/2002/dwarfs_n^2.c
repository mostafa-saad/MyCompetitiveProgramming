#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<assert.h>

#define		MAXN	100000

typedef struct
{
  double x, y;
} point;

int onright(point a, point b, point c)
{
  double dx1, dy1, dx2, dy2;
  
  dx1=b.x-a.x;
  dy1=b.y-a.y;
  dx2=c.x-a.x;
  dy2=c.y-a.y;
  
  return(dx1*dy2-dx2*dy1<0);
}


int N;
point pnt[MAXN];

int main()
{
  int i, j, found;
  point p1, p2;

  scanf("%d\n", &N);
  for(i=0; i<N; i++)
    scanf("%lf %lf\n", &pnt[i].x, &pnt[i].y);
  
  while(scanf("%lf %lf %lf %lf\n", &p1.x, &p1.y, &p2.x, &p2.y)>0)
  {
    if(N<2)
    {
      printf("OK\n");
      fflush(stdout);
      continue;
    }
    
    found=0;
    for(i=0; !found && i<N; i++)
      for(j=0; !found && j<N; j++)
    if(onright(p1, p2, pnt[i])+onright(p1, p2, pnt[j])==1)
    {
      printf("SPLIT\n");
      fflush(stdout);
      found=1;
    }

    if(found)
      continue;

    printf("OK\n");
    fflush(stdout);
  }
  
  return 0;
}
