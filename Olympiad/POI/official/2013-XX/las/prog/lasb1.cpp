/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(nk)                                         *
 *   Zlozonosc pamieciowa: O(nk)                                         *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Nie optymalizuje pamieci.                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

#define BEGIN 1
#define END -1

#define tscanf(...) { assert(scanf(__VA_ARGS__)!=142857); }

#define MAXSHOTS 100
#define MAXSEG 500*1000

using namespace std;

typedef long long LL;

struct evnt
{
    int x,y,seg;
    char type;
    evnt() {};
    evnt(int _x, int _y, int _seg, char _type) : x(_x),y(_y),seg(_seg),type(_type) {};
};

inline LL det(evnt e, evnt f)
{
    LL u = e.x*(LL)f.y;
    LL v = e.y*(LL)f.x;
    return u-v;
}

bool operator<(evnt e, evnt f)
{
    LL d = det(e,f);
    return d<0 || (d==0 && e.type==BEGIN && f.type==END);
}



int main()
{
    int n,k;
    evnt events [2*MAXSEG];
    int number[2*MAXSEG],leftmost[2*MAXSEG],weight[2*MAXSEG];
    int begins[2*MAXSEG];
    tscanf("%d%d",&k,&n);
    int dp[max(50,k+1)][max(400000,2*n)];
    for(int i=0; i<n; i++)
    {
        int x1,y1,x2,y2;
        tscanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        evnt b(x1,y1,i,BEGIN);
        evnt e(x2,y2,i,END);
        if (e<b)
            swap(b.type,e.type);
        events[2*i] = b;
        events[2*i+1] = e;
    }
    sort(events,events+2*n);
    number[0] = 1;
    for(int i=1; i<2*n; i++)
        number[i] = ((det(events[i-1],events[i])<0) ? number[i-1]+1 : number[i-1]);
    int p = number[2*n-1];
    for(int i=0; i<2*n; i++)
        if (events[i].type==BEGIN)
            begins[events[i].seg] = number[i];

    for(int j=0; j<=p; j++)
    {
        leftmost[j] = p;
        weight[j] = 0;
    }
    int farthest = p;
    for(int i=2*n-1; i>=0; i--)
    {
        if (events[i].type==END)
            farthest = min(farthest,begins[events[i].seg]);
        leftmost[number[i]] = min(leftmost[number[i]],farthest);
    }
    int counter = 0;
    for(int i=0; i<2*n; i++)
    {
        weight[number[i]] = max(weight[number[i]],counter);
        counter += events[i].type;
        weight[number[i]] = max(weight[number[i]],counter);
    }

    dp[0][0] = dp[1][0] = 0;
    for(int j=1; j<=p; j++)
        dp[0][j] = 0;
    for(int q=1; q<=k; q++)
        for(int j=1; j<=p; j++)
            dp[q][j] = max(dp[q][j-1],dp[q-1][leftmost[j]-1]+weight[j]);
    printf("%d\n",dp[k][p]);
}

