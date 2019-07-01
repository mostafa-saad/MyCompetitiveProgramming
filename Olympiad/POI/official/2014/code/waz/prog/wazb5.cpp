/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Waz                                           *
 *   Autor:                Jakub Radoszewski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Blad w "hamilton2".                           *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<utility>
#include<sstream>
#include<cstring>
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

typedef pair<char,short> PII;

const int M=1010;

const int PRAWO=0;
const int LEWO=1; // na odwroconej tablicy
const int ROSNACA=1;
const int MALEJACA=0;

int n;
int t[2][M][3];
bool ustaw=false; // tryb ustawiania wartosci

inline bool zgodne(int &a,int b)
{
    if (ustaw)
    {
        if (!a) a=b;
    }
    return !a || !b || (a==b);
}

void harmonizuj()
{
    REP(i,n) REP(j,3) zgodne(t[PRAWO][i][j],t[LEWO][n-1-i][j]);
    REP(j,3) REP(i,n)
    {
        printf("%d",t[PRAWO][i][j]);
        if (i<n-1) putchar(' ');
        else puts("");
    }
}

// ROSNACA: +1   MALEJACA: -1
inline int mon_wsp(int monot)
{
    return 2*monot-1;
}
inline int mon_akt(int x,int monot)
{
    int akt=3*x+1;
    if (monot==MALEJACA) akt=3*n+1-akt;
    return akt;
}

char hamilton_t[2][M][3][2];
PII hamilton_wypisz[2][M][3][2];

short ciagnie_t[2][M][3][3*M+1][2];

int ciagnie(int kier,int x,int y,int val,int monot)
{
    if (x==n || val<1 || val>3*n) return 0;
    short &w=ciagnie_t[kier][x][y][val][monot];
    if (w!=-1) return w;
    if (!zgodne(t[kier][x][y],val)) return w=0;
    return w=1+ciagnie(kier,x+1,y,val+mon_wsp(monot),monot);
}

bool ciag(int kier,int x1,int y,int akt,int x2,int monot)
{
    if (ustaw)
    {
        int diff=mon_wsp(monot);
        FOR(i,x1,x2) {
            if (!zgodne(t[kier][i][y],akt)) return false;
            akt+=diff;
        }
        return true;
    }
    return ciagnie(kier,x1,y,akt,monot)>=x2-x1+1;
}

/* Czy podprostokat [x1,x2] x [0,2] mozna pokryc jednym
   zygzakiem "tam - z powrotem - tam" z pola (x1,y)
   do pola (x2,2-y)? */
int zygzak(int kier,int x1,int y,int x2,int monot)
{
    int akt=mon_akt(x1,monot),diff=mon_wsp(monot);
    if (!ciag(kier,x1,y,akt,x2,monot)) return false;
    akt+=(x2-x1+1)*diff;
    akt+=(x2-x1)*diff;
    if (!ciag(kier,x1,1,akt,x2,1-monot)) return false;
    akt+=diff;
    if (!ciag(kier,x1,2-y,akt,x2,monot)) return false;
    return true;
}

int zawijas(int kier,int x1,int y1,int len,int y2,int monot)
{
    int akt=mon_akt(x1,monot),diff=mon_wsp(monot);
    int x2=x1+len-1;
    if (!ciag(kier,x1,y1,akt,x2,monot)) return false;
    if (monot==ROSNACA) akt=3*n;
    else akt=1;
    diff=-diff;
    akt+=(x2-x1)*diff;
    if (!ciag(kier,x1,3-y1-y2,akt,x2,monot)) return false;
    akt+=diff;
    if (!ciag(kier,x1,y2,akt,x2,1-monot)) return false;
    return true;
}

int zawijas_handshake(int kier,int x1,int y,int y1,int x2,int y2)
{
    int akt=1;
    if (!ciag(kier,x1,y1,akt,x2,ROSNACA)) return false;
    akt+=3*(n-x2-1)+2*(x2-x1+1)-1;
    if (!ciag(kier,x1,y,akt,x2,MALEJACA)) return false;
    akt+=3*x1+1;
    if (!ciag(kier,x1,y2,akt,x2,ROSNACA)) return false;
    return true;
}

char hamilton2_t[2][M][3][3*M+1][3];
char hamilton2_wypisz[2][M][3][3*M+1][3]; // uzywane tylko jesli y1,y2!=1 (inaczej nie ma wyboru)
const int RUSZ_Y1=0;
const int RUSZ_Y2=1;

/* Czy podprostokat [x,n-1] x [0,2] mozna pokryc sciezka Hamiltona
   o poczatku w (x,y1) i koncu w (x,y2), o rosnacych wartosciach,
   poczawszy od wartosci val1? */
char hamilton2(int kier,int x,int y1,int val1,int y2)
{
    if (x==n) return true; // a BUG
    char &w=hamilton2_t[kier][x][y1][val1][y2];
    if (!ustaw && w!=-1) return w;
    char &wo=hamilton2_wypisz[kier][x][y1][val1][y2];

    int val2=val1+3*(n-x)-1;
    if (!zgodne(t[kier][x][y1],val1)) return w=false;
    if (!zgodne(t[kier][x][y2],val2)) return w=false;
    if (y1==1)
    {
        if (!zgodne(t[kier][x][2-y2],val1+1)) return w=false;
        if (hamilton2(kier,x+1,2-y2,val1+2,y2)) return w=true;
    } else if (y2==1)
    {
        if (!zgodne(t[kier][x][2-y1],val2-1)) return w=false;
        if (hamilton2(kier,x+1,y1,val1+1,2-y1)) return w=true;
    } else
    {
        // mamy wybor
        if (wo!=RUSZ_Y2)
        {
            if (zgodne(t[kier][x][1],val1+1) && hamilton2(kier,x+1,1,val1+2,y2)) {
                wo=RUSZ_Y1;
                return w=true;
            }
        }
        if (wo!=RUSZ_Y1)
        {
            if (zgodne(t[kier][x][1],val2-1) && hamilton2(kier,x+1,y1,val1+1,1)) {
                wo=RUSZ_Y2;
                return w=true;
            }
        }
    }
    return w=false;
}

/* Czy podprostokat [x,n-1] x [0,2] mozna pokryc sciezka Hamiltona,
   zaczynajac z pola (x,y) i konczac na wartosci 1 lub 3n? */
char hamilton(int kier,int x,int y,int monot)
{
    if (x==n) return true;
    char &w=hamilton_t[kier][x][y][monot];
    if (!ustaw && w!=-1) return w;
    PII &wo=hamilton_wypisz[kier][x][y][monot];

    // opcja 1: zygzak
    if (y!=1)
    {
        FOR(i,x,n-1)
        {
            if (wo.FI!=-1 && !(wo.FI==1 && wo.SE==i)) continue;
            if (zygzak(kier,x,y,i,monot) && hamilton(kier,i+1,2-y,monot))
            {
                wo=MP(1,i);
                return w=true;
            }
        }
    }
    // opcja 2: hamilton2
    REP(y2,3) if (y2!=y)
    {
        if (wo.FI!=-1 && !(wo.FI==2 && wo.SE==y2)) continue;
        int akt=mon_akt(x,monot);
        if (monot==MALEJACA) akt-=3*(n-x)-1;
        if ((monot==ROSNACA &&  hamilton2(kier,x,y,akt,y2)) ||
                (monot==MALEJACA && hamilton2(kier,x,y2,akt,y)))
        {
            wo=MP(2,y2);
            return w=true;
        }
    }
    // opcja 3: hamilton2 z zawijasem
    if (y!=1)
    {
        REP(y2,3) if (y2!=y) FOR(len,1,n-x-1)
        {
            if (wo.FI!=-1 && !(wo.FI==3 && wo.SE/n==y2 && wo.SE%n==len)) continue;
            int akt=mon_akt(x,monot),diff=mon_wsp(monot);
            if (!zawijas(kier,x,y,len,y2,monot)) continue;

            akt+=len*diff;
            int x1=x+len;
            if (monot==MALEJACA) akt-=3*(n-x1)-1;
            if ((monot==ROSNACA &&  hamilton2(kier,x1,y,akt,y2)) ||
                    (monot==MALEJACA && hamilton2(kier,x1,y2,akt,y)))
            {
                wo=MP(3,n*y2+len);
                return w=true;
            }
        }
    }

    return w=false;
}

// haczyk w zadaniu - konfiguracja innej postaci
int wkier=-1,wx1=-1,wx2=-1,wy=-1,wy1=-1;
int haczyk()
{
    REP(kier,2) FOR(x1,1,n-2) FOR(x2,x1,n-2) REP(y,3) REP(y1,3) if (y1!=y)
    {
        if (wkier!=-1 && !(wkier==kier && wx1==x1 && wx2==x2 && wy==y && wy1==y1)) continue;
        int y2=3-y-y1;
        if (!zawijas_handshake(kier,x1,y,y1,x2,y2)) continue;
        if (hamilton2(kier,x2+1,y1,x2-x1+2,y) && hamilton2(1-kier,n-1-(x1-1),y,2*(x2-x1+1)+3*(n-x2-1)+1,y2))
        {
            wkier=kier;
            wx1=x1;
            wx2=x2;
            wy=y;
            wy1=y1;
            return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d",&n);
    REP(j,3) REP(i,n) scanf("%d",t[PRAWO][i]+j);
    REP(i,n) REP(j,3) t[LEWO][i][j]=t[PRAWO][i][j];
    REP(i,n/2) REP(j,3) swap(t[LEWO][i][j],t[LEWO][n-1-i][j]);

    memset(hamilton_t,-1,sizeof(hamilton_t));
    memset(hamilton2_t,-1,sizeof(hamilton2_t));
    memset(hamilton_wypisz,-1,sizeof(hamilton_wypisz));
    memset(hamilton2_wypisz,-1,sizeof(hamilton2_wypisz));
    memset(ciagnie_t,-1,sizeof(ciagnie_t));

    // gdy konfiguracje da sie podzielic na dwie czesci
    FOR(i,0,n) REP(y,3) REP(monot,2)
    {
        bool czy=true;
        czy &= hamilton(PRAWO,i,y,monot);
        czy &= hamilton(LEWO,n-1-(i-1),y,1-monot);
        if (czy)
        {
            ustaw=true;
            hamilton(PRAWO,i,y,monot);
            hamilton(LEWO,n-1-(i-1),y,1-monot);
            harmonizuj();
            exit(0);
        }
    }
    if (haczyk())
    {
        ustaw=true;
        haczyk();
        harmonizuj();
        exit(0);
    }
    return 0;
}
