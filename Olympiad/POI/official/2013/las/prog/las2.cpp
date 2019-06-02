/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O(nk)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

#define fru(j,n) for(int j=0;j<n;++j)
#define x first
#define y second

using namespace std;

typedef pair<pair<int,int>,int> punkt;
const int MAXN =500002,MAXK=102,KATOW=MAXN*2;
punkt P[MAXN*2];
pair<int,int> S[MAXN];//kąty końców odcinków

bool cmp (const punkt &a, const punkt &b)
{
    if(1LL*a.x.x*b.x.y!=1LL*a.x.y*b.x.x) return
            1LL*a.x.x*b.x.y < 1LL*a.x.y*b.x.x;
    return a.y<b.y;
}
pair<int,bool> WYD[MAXN*2]; //wydarzenia

int ILE[KATOW],//ile odcinkow przetnie laser pod tym katem
    PRAWO[KATOW];//gdzie najdalej sięga odcinek przeciety tym laserem
multiset<int> MS;
int D[2][KATOW];
int main()
{
    int k,n;
    scanf("%d%d",&k,&n);
    if(n==0)
    {
        printf("%d\n",0);
        return 0;
    }
    int c=0;//pomocniczy index po tablicach (przyjmie wart. e [0 do 2n-1]
    fru(i,n) fru(j,2)
    {
        P[c].y=i+j*MAXN;
        scanf("%d%d",&P[c].x.x,&P[c].x.y);
        c++;
    }
    //przejście z płaszczyzny na prostą
    sort(P,P+c,cmp);
    int e=0;//liczba różnych kątów
    fru(i,c)
    {
        if(i && 1LL*P[i].x.x*P[i-1].x.y!=1LL*P[i].x.y*P[i-1].x.x) e++;
        int t=P[i].y;
        if(t/MAXN) S[t%MAXN].x=e;
        else S[t%MAXN].y=e;
    }
    e++;
    fru(i,n) if(S[i].x>S[i].y) swap(S[i].x,S[i].y);
    sort(S,S+n);
    c=0;
    //liczenie tablic pomocniczych: ILE i PRAWO
    fru(i,e)
    {
        while(c<n && S[c].x==i) MS.insert(S[c++].y);
        ILE[i]=MS.size();
        PRAWO[i]=*(MS.rbegin())+1;
        if(MS.find(i)!=MS.end()) MS.erase(i);
    }
    //liczenie wyniku
    bool tu=0,tam=1;
    int ans=0;
    fru(j,k)
    {
        fru(i,e)
        {
            if(i) D[tu][i]=max(D[tu][i],D[tu][i-1]);
            D[tam][PRAWO[i]]=max(D[tam][PRAWO[i]],D[tu][i]+ILE[i]);
        }
        fru(i,e+1) ans=max(ans,D[tam][i]);
        fru(i,e+1) D[tu][i]=0;
        swap(tu,tam);
    }
    printf("%d\n",ans);
    return 0;
}
