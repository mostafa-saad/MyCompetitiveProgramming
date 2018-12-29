/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Przestepcy                                    *
 *   Autor:                Marek Sommer                                  *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

int n,k,m,l,ost,leww,praw;

int tab[1000005];

int tabkol[1000005];
int naskol[1000005];
int popkol[1000005];
int nas[1000005];
int pop[1000005];
int *lew = nas;
int *pra = pop;
vector<int> kral[1000005];
vector<int> *krap = kral;
int *lic = naskol;
int *mam = popkol;
int *naj = tabkol;

int main()
{
    int ret;
    ret = scanf("%d%d",&n,&k);
    for(int i=1; i<=n; i++) ret = scanf("%d",tab+i);
    ret = scanf("%d%d",&m,&l);
    ost = 0;
    while(m--)
    {
        int x;
        ret = scanf("%d",&x);
        if(ost==0) leww = x;
        naskol[x] = ost;
        ost = x;
    }
    for(int i=1; i<=n; i++)
    {
        nas[i]=tabkol[naskol[tab[i]]];
        tabkol[tab[i]]=i;
        kral[nas[i]].push_back(i);
    }
    for(int i=1; i<=n; i++) lew[i] = 0;
    for(int i=1; i<=n; i++)
    {
        if(tab[i]==leww) lew[i]=i;
        if(lew[i]) for(int j=0; j<((int)kral[i].size()); j++) lew[kral[i][j]]=lew[i];
    }

    for(int i=1; i<=n; i++) pop[i] = popkol[i] = 0;

    ost = 0;
    while(l--)
    {
        int x;
        ret = scanf("%d",&x);
        if(ost==0) praw = x;
        popkol[x] = ost;
        ost = x;
    }
    if(ret<0) return 1;
    for(int i=1; i<=n; i++) kral[i].clear();
    for(int i=1; i<=n; i++) tabkol[i]=0;
    for(int i=n; i>=1; i--)
    {
        pop[i]=tabkol[popkol[tab[i]]];
        tabkol[tab[i]]=i;
        krap[pop[i]].push_back(i);
    }
    for(int i=1; i<=n; i++) pra[i] = 0;
    for(int i=n; i>=1; i--)
    {
        if(tab[i]==praw) pra[i]=i;
        if(pra[i]) for(int j=0; j<((int)krap[i].size()); j++) pra[krap[i][j]]=pra[i];
    }
    for(int i=1; i<=n; i++) mam[i] = lic[i] = naj[i] = 0;
    for(int i=1; i<=n; i++) lic[tab[i]]++;
    int d = 1,ile = 0;
    for(int i=1; i<=n; i++)
    {
        if(!mam[tab[i]] && lic[tab[i]])
        {
            mam[tab[i]]=true;
            ile++;
        }
        while(ile)
        {
            lic[tab[d]]--;
            if(lic[tab[d]]==0 && mam[tab[d]]) ile--;
            d++;
        }
        d--;
        lic[tab[d]]++;
        ile++;
        naj[i]=d;
    }
    vector<int>wyn;
    for(int i=1; i<=n; i++)
    {
        if(tab[i]!=ost) continue;
        if(!lew[i] || !pra[i]) continue;
        int a = lew[i]-1;
        int b = pra[i]+1;
        if(a<1 || b>n) continue;
        if(b<=naj[a]) wyn.push_back(i);
    }
    printf("%d\n",(int)wyn.size());
    for(int i=0; i<((int)wyn.size()); i++) printf("%d ",wyn[i]);
    printf("\n");
    return 0;
}
