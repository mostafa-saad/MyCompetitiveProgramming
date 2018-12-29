/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Waz                                           *
 *   Autor:                Jakub Radoszewski                             *
 *   Zlozonosc czasowa:    O(n^11)                                       *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<utility>
#include<sstream>
#include<cstring>
#include<vector>
#include<map>
#include<numeric>
#include<cassert>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SIZE(x) ((int)(x).size())

typedef pair<int,int> PII;
const PII pusty = MP(-1,-1);

const int M=1010;
int t[M][3],n;

struct stan
{
    int t[3]; // liczby w polach, jesli t[0]==-1, to stan zly
    PII interval[2]; // przedzialy wartosci, rozlaczne, interval[0]<interval[1], no moze, ze drugi pusty
    int deg[3]; // zapotrzebowanie na krawedzie, zawsze 0..1
};

bool operator<(const stan &a,const stan &b)
{
    REP(i,3) if (a.t[i]!=b.t[i]) return a.t[i]<b.t[i];
    REP(i,2) if (a.interval[i]!=b.interval[i]) return a.interval[i]<b.interval[i];
    REP(i,3) if (a.deg[i]!=b.deg[i]) return a.deg[i]<b.deg[i];
    return false;
}

inline stan daj_stan(int a,int b,int c)
{
    stan s;
    // t
    if (a==b || a==c || b==c) {
        s.t[0]=-1;
        return s;
    }
    s.t[0]=a;
    s.t[1]=b;
    s.t[2]=c;

    // degi
    REP(j,3) if (s.t[j]==1 || s.t[j]==3*n) s.deg[j]=1;
    else s.deg[j]=2;
    REP(j,2) if (abs(s.t[j]-s.t[j+1])==1) {
        --s.deg[j];
        --s.deg[j+1];
    }
    REP(j,3) if (s.deg[j]==2) {
        s.t[0]=-1;
        return s;
    }

    // intervaly
    if (abs(a-b)==1 && abs(b-c)==1)
    {
        s.interval[0]=MP(min(a,c),max(a,c));
        s.interval[1]=pusty;
        return s;
    }
    if (abs(a-b)==1)
    {
        if (a<b) s.interval[0]=MP(a,b);
        else s.interval[0]=MP(b,a);
        s.interval[1]=MP(c,c);
        if (s.interval[0]>s.interval[1]) swap(s.interval[0],s.interval[1]);
        return s;
    }
    if (abs(b-c)==1)
    {
        if (b<c) s.interval[0]=MP(b,c);
        else s.interval[0]=MP(c,b);
        s.interval[1]=MP(a,a);
        if (s.interval[0]>s.interval[1]) swap(s.interval[0],s.interval[1]);
        return s;
    }
    s.t[0]=-1;
    return s;
}

map<stan,int> Mapa[M];
vector<stan> S[M];
vector<int> parent[M];

inline int mapuj_stan(int i,stan &s)
{
    if (Mapa[i].find(s)!=Mapa[i].end()) return -1;
    Mapa[i][s]=SIZE(S[i]);
    S[i].PB(s);
    return SIZE(S[i])-1;
}

void odtworz(int i,int sn)
{
    const stan &s=S[i][sn];
    REP(j,3) t[i][j]=s.t[j];
    if (!i)
    {
        // Wypisujem wynik
        REP(j,3) REP(ii,n)
        {
            printf("%d",t[ii][j]);
            if (ii<n-1) putchar(' ');
            else puts("");
        }
        exit(0);
    }
    odtworz(i-1,parent[i][sn]);
}

inline void sprawdz(int sn)
{
    const stan &s=S[n-1][sn];
//  if (s.interval[1]!=pusty) return;
//  if (s.interval[0]!=MP(1,3*n)) return;
    REP(j,3) if (s.deg[j]) return;
    // Mamy rozwiazanie!!!
    odtworz(n-1,sn);
}

inline bool pokryty(int a,PII interval)
{
    return interval.FI<=a && a<=interval.SE;
}

PII interval[6];

// Wstawia punkty do przedzialow
inline bool insert_interval(stan &s)
{
    int pocz=0;
    int akt=0;
    REP(j,2) interval[j]=s.interval[j];
    if (interval[1]==pusty) pocz=1;
    else pocz=2;
    REP(j,3)
    {
        REP(k,pocz+j) if (pokryty(s.t[j],interval[k])) return false;
        interval[pocz+j]=MP(s.t[j],s.t[j]);
    }
    pocz+=3;
    sort(interval,interval+pocz);

    FOR(i,1,pocz-1)
    {
        if (interval[akt].SE+1>=interval[i].FI)
        {
            interval[akt].SE=interval[i].SE;
            interval[i]=pusty;
        } else
        {
            ++akt;
            interval[akt]=interval[i];
        }
    }
    if (akt>=2) return false;
    REP(j,2) s.interval[j]=interval[j];
    return true;
}

struct trojka
{
    int a,b,c;
};

inline trojka MT(int a,int b,int c)
{
    trojka tt;
    tt.a=a;
    tt.b=b;
    tt.c=c;
    return tt;
}


void doit(int i,int sn)
{
    if (sn==-1) return; // wiele wizyt u tego samego wujka
    if (i==n-1) {
        sprawdz(sn);
        return;
    }
    const stan &s=S[i][sn];
    if (!accumulate(s.deg,s.deg+3,0)) return;

    // probujemy ustalic wartosci z sasiedztwa
    int lo[3],hi[3];
    REP(j,3) {
        lo[j]=1;
        hi[j]=3*n;
    }
    REP(j,3) if (s.deg[j]==1)
    {
        // optymalizacja
        lo[j]=s.t[j]-1;
        hi[j]=s.t[j]+1;
    }
    REP(j,3) if (t[i+1][j])
    {
        if (!pokryty(t[i+1][j],MP(lo[j],hi[j]))) return; // bardzo zle
        lo[j]=hi[j]=t[i+1][j];
    }

    // glowna petla ustalajaca wartosci
    stan s1;
    vector<trojka> kand;
    if (lo[1]==1 && hi[1]==3*n && ((lo[0]==1 && hi[0]==3*n) || (lo[2]==1 && hi[2]==3*n)))
    {
        FOR(a,lo[0],hi[0]) FOR(b,max(a-1,1),min(a+1,3*n)) if (b!=a) FOR(c,lo[2],hi[2]) kand.PB(MT(a,b,c));
        FOR(c,lo[2],hi[2]) FOR(b,max(c-1,1),min(c+1,3*n)) if (b!=c) FOR(a,lo[0],hi[0]) kand.PB(MT(a,b,c));
    }
    if (kand.empty())
    {
        FOR(a,lo[0],hi[0]) if (a!=s.t[0]) FOR(b,lo[1],hi[1]) if (b!=s.t[1]) FOR(c,lo[2],hi[2]) if (c!=s.t[2]) kand.PB(MT(a,b,c));
    }

    REP(ii,SIZE(kand))
    {
        int a=kand[ii].a,b=kand[ii].b,c=kand[ii].c;
        REP(j,3) s1.deg[j]=2;
        s1.t[0]=a;
        s1.t[1]=b;
        s1.t[2]=c;

        // degi
        REP(j,3) if (abs(s1.t[j]-s.t[j])==1) --s1.deg[j];
        REP(j,3) if (s1.t[j]==1 || s1.t[j]==3*n) --s1.deg[j];
        REP(j,2) if (abs(s1.t[j]-s1.t[j+1])==1) {
            --s1.deg[j];
            --s1.deg[j+1];
        }
        // sprawdzenie
        bool zle=false;
        REP(j,3) if (s1.deg[j]==2 || s1.deg[j]<0) {
            zle=true;
            break;
        }
        if (zle) continue;

        // interval
        REP(j,2) s1.interval[j]=s.interval[j];
        if (!insert_interval(s1)) continue;

        int sn1=mapuj_stan(i+1,s1);
        if (sn1!=-1)
        {
            parent[i+1].PB(sn);
            doit(i+1,sn1);
        }
    }
}

// Wstawia, jesli dobre
inline void wstaw0(vector<trojka> &kand,int a,int b,int c)
{
    if (t[0][0] && t[0][0]!=a) return;
    if (t[0][1] && t[0][1]!=b) return;
    if (t[0][2] && t[0][2]!=c) return;
    kand.PB(MT(a,b,c));
}

int main()
{
    scanf("%d",&n);
    REP(i,3) REP(j,n) scanf("%d",t[j]+i);

    vector<trojka> kand0;
    FOR(a,3,3*n-1) {
        wstaw0(kand0,1,a,a+1);
        wstaw0(kand0,a+1,a,1);
        wstaw0(kand0,1,a+1,a);
        wstaw0(kand0,a,a+1,1);
    }
    FOR(a,1,3*n-3) {
        wstaw0(kand0,3*n,a,a+1);
        wstaw0(kand0,a+1,a,3*n);
        wstaw0(kand0,3*n,a+1,a);
        wstaw0(kand0,a,a+1,3*n);
    }
    FOR(a,1,3*n-2) {
        wstaw0(kand0,a,a+1,a+2);
        wstaw0(kand0,a+2,a+1,a);
    }
    REP(ii,SIZE(kand0))
    {
        const trojka &tt=kand0[ii];
        stan s=daj_stan(tt.a,tt.b,tt.c);
        if (s.t[0]!=-1) doit(0,mapuj_stan(0,s));
    }
    return 0;
}
