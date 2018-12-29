/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Nieefektywnie liczy przedzialy eliminowane    *
 *                         strzalem i liczbe przecietych przedzialow     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

#define BEGIN 1
#define END -1

#define tscanf(...) { assert(scanf(__VA_ARGS__)!=142857); }

#define MAXSHOTS 300
#define MAXSEG 1000*1000

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
    int number[2*MAXSEG];
    int begins[MAXSEG];
    int ends[MAXSEG];
    int leftmost[2*MAXSEG],weight[2*MAXSEG];
    int dp[2][2*MAXSEG];
    tscanf("%d%d",&k,&n);
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
        else
            ends[events[i].seg] = number[i];

//  for(int i=0; i<n; i++)
//    printf("%d - %d\n",begins[i],ends[i]);

    for(int j=1; j<=p; j++)
    {
        weight[j] = 0;
        leftmost[j] = p+1;
    }
    for(int i=0; i<n; i++)
        for(int j=begins[i]; j<=ends[i]; j++)
        {
            weight[j]++;
            leftmost[j] = min(leftmost[j],begins[i]);
        }
    dp[0][0] = dp[1][0] = 0;
    for(int j=1; j<=p; j++)
    {
        dp[0][j] = 0;
    }
    for(int q=1; q<=k; q++)
        for(int j=1; j<=p; j++)
            dp[q%2][j] = max(dp[q%2][j-1],dp[(q-1)%2][leftmost[j]-1]+weight[j]);
    printf("%d\n",dp[k%2][p]);
}

