#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "libconq.c"


int stairs[MAX_N+1];
int N;

/* count value of soldiers */
int can_win(void)
{
    int va[MAX_N+1];
    int i,n;
    
    bzero(va,sizeof(va));
    for (i=1;i<=N;i++) va[i]=stairs[i];
    for (i=N;i>1;i--)
    {
	n=va[i]/2;
	va[i]-=2*n;
	va[i-1]+=n;
    }
    
    if (va[1]) return 1;
    return 0;
}

int cmpf(const void *a, const void *b)
{
    return (*((int *)a) - *((int *)b));
}

/* returns 1 iff a[1..N] <= b[1..N] */
int smaller(int *a, int *b)
{
    int i;

    for (i=1;i<=N;i++)
    {
	if (a[i]<b[i]) return 1;
    }
    
    return 0;
}

void normalize(int *a, int from)
{
    int i,n;

    for (i=from;i>2;i--)
    {
	n=a[i]/2;
	a[i]-=2*n;
	a[i-1]+=n;
    }
}

void denormalize(int *a, int to)
{
    int i,n,limit;

    for (i=2;i<to;i++)
    {
	if (i==2) limit=1; else limit=0;
	n=(a[i]-limit); // printf("(%d)",n);
	a[i]-=n;
	a[i+1]+=2*n;
    }
}

/* select subset of soldiers with value >= 1/2 */
int divide(int *sub)
{
    int count=0,i;
    int start, st[MAX_N+1];
    
    bzero(st,sizeof(st));
    for(i=0;i<=N;i++) sub[i]=0;
    
    for (start=1;start<=N;start++)
    {
	if (stairs[start])
	{
	    st[start]+=stairs[start];
	    normalize(st,start);
	    if (st[2])    // ok, we reached 1/2 or more
	    {
		denormalize(st,start);
		// sub[start]=stairs[start]-(start>2?st[start]:0);
		sub[start]=(start>2?stairs[start]-st[start]:1);
		count+=sub[start];
		break;
	    }
	    
	    sub[start]=stairs[start];
	    count+=sub[start];
//	    printf("subset: "); for (i=N;i>0;i--) printf("%d%s",sub[i],(i==1?"\n":" "));
	}
    }
    
    return count;
}

int main(void)
{
    int count,ret,i;
    int sub[MAX_N+1];

    start(&N,stairs);
    
    if (can_win())
    {
	while (1)
	{
	    count=divide(sub);

	    ret=step(sub);

	    
	    if (ret==1) for (i=1;i<=N;i++) stairs[i]=sub[i];
		   else for (i=1;i<=N;i++) stairs[i]-=sub[i];
	    for (i=1;i<=N;i++) stairs[i-1]=stairs[i];
	}
    }
    else   /* sorry, cannot win, so stop in one step */
    {
	bzero(stairs,sizeof(stairs));
	step(stairs);	
    }

    return 0;
}
