/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Waz                                           *
 *   Autor:                Jakub Radoszewski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         Programowanie dynamiczne.                     *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define SIZE(x) ((int)(x).size())

// co najmniej + 1
#define M 1010

int n;
int t[M][3];
bool koniec;

int x[]= {0,0,-1,1};
int y[]= {-1,1,0,0};
inline bool ins(int g,int h) {
    return g>=0 && g<h;
}
inline int ABS(int x) {
    return x<0 ? -x : x;
}

void wypisz()
{
    REP(i,3)
    {
        REP(j,n-1) printf("%d ",t[j][i]);
        printf("%d\n",t[n-1][i]);
    }
}

// Rownosc z dokladnoscia do 0.
inline bool rowne(int a,int b,int co)
{
    return ins(co-1,3*n) && (!t[a][b] || t[a][b]==co);
}


bool cykl[M][3*M][3][3][2]; // (x, val, pierwszy_wybrany, drugi_wybrany, kier)
// -- czy jest taki cykl; w lewo (kier==0) lub w prawo (kier==1)
char Cykl[M][3*M][3][3][2]; // (x, val, pierwszy_wybrany, drugi_wybrany, kier) - ojcowie

void licz_cykl()
{
    if (koniec) return;
    FOR(v,1,3*n) REP(k,2)
    {
        int kk = (n-1)*k;
        if (rowne(kk,0,v) && rowne(kk,1,v+1) && rowne(kk,2,v+2))
            cykl[kk][v][0][2][k] = true;
        if (rowne(kk,2,v) && rowne(kk,1,v+1) && rowne(kk,0,v+2))
            cykl[kk][v][2][0][k] = true;
    }
    FOR(p,1,n-1) FOR(v,1,3*n) REP(a,3) REP(b,3) if (a!=b) REP(k,2)
    {
        int pp = !k ? p : n-1-p;
        int kier = !k ? 1 : -1;
        int c=3-a-b;
        if (rowne(pp,a,v) && rowne(pp,b,v+2+3*p))
        {
            if (ABS(a-c)==1 && rowne(pp,c,v+1)     && cykl[pp-kier][v+2][c][b][k])
            {
                cykl[pp][v][a][b][k] = true;
                Cykl[pp][v][a][b][k] = 1;
            }
            if (ABS(b-c)==1 && rowne(pp,c,v+1+3*p) && cykl[pp-kier][v+1][a][c][k])
            {
                cykl[pp][v][a][b][k] = true;
                Cykl[pp][v][a][b][k] = 2;
            }
        }
    }
}

void odzysk_cykl(int p,int v,int a,int b,int k)
{
//  fprintf(stderr,"odzyskuje cykl: %d %d %d %d %d  (p val a b k)\n",p,v,a,b,k);
    assert(cykl[p][v][a][b][k]);
    t[p][a] = v;
    t[p][b] = (!k ? v+2+3*p : v+2+3*(n-1-p));
    int c=3-a-b;
    if (p==k*(n-1))
    {
        t[p][c]=t[p][a]+1;
        return;
    }
    int oo=Cykl[p][v][a][b][k];
    assert(oo>=1 && oo<=2);
    if (oo==1) t[p][c]=v+1;
    else t[p][c]=t[p][b]-1;
    if (oo==1) odzysk_cykl(p + (!k ? -1 : 1), v+2, c, b, k);
    else odzysk_cykl(p + (!k ? -1 : 1), v+1, a, c, k);
}


short ciagnie[M][3*M][3][2][2]; // (x, val, y, kier, monot) --
// ile pol w prawo (kier==0)/w lewo (kier==1)
// ciagnie sie od danego pola ciag val, val+1,... (monot==0) lub ciag val, val-1,... (monot==1)

void licz_ciagnie()
{
    if (koniec) return;
    // kier==0
    FORD(i,n-1,0) FOR(val,1,3*n) REP(j,3) REP(monot,2)
    {
        ciagnie[i][val][j][0][monot] = !rowne(i,j,val) ? 0 : (!ins(i+1,n) ? 1 : 1+ciagnie[i+1][val + (!monot ? 1 : -1)][j][0][monot]);
    }
    // kier==1
    REP(i,n) FOR(val,1,3*n) REP(j,3) REP(monot,2)
    {
        ciagnie[i][val][j][1][monot] = !rowne(i,j,val) ? 0 : (!ins(i-1,n) ? 1 : 1+ciagnie[i-1][val + (!monot ? 1 : -1)][j][1][monot]);
    }
}

void pociagnij(int p,int val,int a,int k,int monot,int ile)
{
    while (ile--)
    {
        t[p][a]=val;
        val += (!monot ? 1 : -1);
        p += (!k ? 1 : -1);
    }
}

void probuj_dwa_cykle()
{
    if (koniec) return;
    FOR(i,0,n-1) FOR(j,i,n-1) REP(a,3) REP(b,3) if (a!=b)
    {
        int c=3-a-b;
        if (ciagnie[i][1][a][0][0] < j-i+1 || ciagnie[j][3*n][b][1][1] < j-i+1) continue;
        int val = 1 + j-i+1 + 3*(n-1-j);
        if (ciagnie[j][val][c][1][0] < j-i+1) continue;
        int vpr = 1 + j-i+1;
        int vle = val + j-i+1;
        if (!(j+1==n && ABS(a-c)==1) && !(j+1<n && cykl[j+1][vpr][a][c][1])) continue;
        if (!(i-1==-1 && ABS(b-c)==1) && !(i>0 && cykl[i-1][vle][c][b][0])) continue;

        pociagnij(i,1,a,0,0,j-i+1);
        pociagnij(j,3*n,b,1,1,j-i+1);
        pociagnij(j,val,c,1,0,j-i+1);
        if (j+1<n) odzysk_cykl(j+1,vpr,a,c,1);
        if (i>0) odzysk_cykl(i-1,vle,c,b,0);
        koniec=true;
        return;
    }

    // monot=1, ale za duzo zmian, lepiej od nowa
    FOR(i,0,n-1) FOR(j,i,n-1) REP(a,3) REP(b,3) if (a!=b)
    {
        int c=3-a-b;
        if (ciagnie[i][3*n][a][0][1] < j-i+1 || ciagnie[j][1][b][1][0] < j-i+1) continue;
        int val = 3*n - (j-i+1) - 3*(n-1-j);
        if (ciagnie[j][val][c][1][1] < j-i+1) continue;
        if (!(j+1==n && ABS(a-c)==1) && !(j+1<n && cykl[j+1][val+1][c][a][1])) continue;
        if (!(i-1==-1 && ABS(b-c)==1) && !(i>0 && cykl[i-1][1 + j-i+1][b][c][0])) continue;

        pociagnij(i,3*n,a,0,1,j-i+1);
        pociagnij(j,1,b,1,0,j-i+1);
        pociagnij(j,val,c,1,1,j-i+1);
        if (j+1<n) odzysk_cykl(j+1,val+1,c,a,1);
        if (i>0) odzysk_cykl(i-1,1 + j-i+1,b,c,0);
        koniec=true;
        return;
    }

}


bool sciezka[M][3][2][2]; // (x, y, kier, monot) -- czy jest sciezka z (x,y) w prawo (kier==0) lub w lewo (kier==1)
// idaca a,...,3n (monot=0) lub a,...,1 (monot=1)
short Sciezka[M][3][2][2]; // (x, y, kier, monot) -- ojcowie

void licz_sciezka()
{
    if (koniec) return;
    REP(k,2) REP(monot,2)
    {
        int pocz=n-1, kon=-1, kkkier=-1;
        if (k) {
            pocz=0;
            kon=n;
            kkkier=1;
        }
        for (int p=pocz; p!=kon; p+=kkkier) REP(a,3)
        {
            int val = (!k ? 1+3*p : 1+3*(n-1-p));
            if (monot) val=3*n+1-val;
            int zmiana = (!monot ? 1 : -1);
            int val1=val;

            // probuj cykl
            REP(b,3) if (a!=b)
            {
                if (!monot && cykl[p][val][a][b][1-k])
                {
                    sciezka[p][a][k][monot] = true;
                    Sciezka[p][a][k][monot] = 1 + b;
                }
                if (monot && cykl[p][1][b][a][1-k])
                {
                    sciezka[p][a][k][monot] = true;
                    Sciezka[p][a][k][monot] = 1 + b;
                }
            }
            if (a==1) continue;

            // a==0 lub a==2
            // probuj zawijas + cykl
            int kkkon=n;
            if (k) kkkon=-1;
            for (int i=p; i!=kkkon; i-=kkkier)
            {
                // zawijas
                val=val1;
                int skok = ABS(i-p)+1;
                if (ciagnie[p][val][a][k][monot] < skok) continue;
                val += zmiana*skok;
                int ost=3*n;
                if (monot) ost=1;
                int ost1=ost;
                REP(c,3) if (a!=c)
                {
                    ost=ost1;
                    int b=3-a-c;
                    if (ciagnie[i][ost][c][1-k][1-monot] < skok) continue;
                    ost -= zmiana*skok;
                    if (ciagnie[p][ost][b][k][1-monot] < skok) continue;
                    ost -= zmiana*skok;

                    // cykl
                    if (!monot && ins(i-kkkier,n) && cykl[i-kkkier][val][a][b][1-k])
                    {
                        sciezka[p][a][k][monot] = true;
                        Sciezka[p][a][k][monot] = 10 + 2000*c + i;
                    }
                    if (monot && ins(i-kkkier,n) && cykl[i-kkkier][ost][b][a][1-k])
                    {
                        sciezka[p][a][k][monot] = true;
                        Sciezka[p][a][k][monot] = 10 + 2000*c + i;
                    }
                }
            }

            // probuj fragment patha
            int kier = (!a ? 1 : -1);
            for (int i=p; i!=kkkon; i-=kkkier)
            {
                val=val1;
                int skok = ABS(i-p)+1;
                // zygzak na pozycjach p..i
                if (ciagnie[p][val][a][k][monot] < skok) continue;
                val += zmiana*skok;
                if (ciagnie[i][val][a+kier][1-k][monot] < skok) continue;
                val += zmiana*skok;
                if (ciagnie[p][val][a+2*kier][k][monot] < skok) continue;
                val += zmiana*skok;
                if (i == (1-k)*(n-1) || sciezka[i-kkkier][a+2*kier][k][monot])
                {
                    sciezka[p][a][k][monot] = true;
                    Sciezka[p][a][k][monot] = 10000 + i;
                    break;
                }
            }
        }
    }
}

void odzysk_sciezka(int p,int a,int k,int monot)
{
    assert(sciezka[p][a][k][monot]);
//  fprintf(stderr,"odzyskuje sciezke: %d %d %d %d  (p a k monot)\n",p,a,k,monot);
    int oo=Sciezka[p][a][k][monot];
//  fprintf(stderr,"Ojciec: %d\n",oo);
    int val = (!k ? 1+3*p : 1+3*(n-1-p));
    if (monot) val=3*n+1-val;
    int zmiana = (!monot ? 1 : -1);
    int kkkier=-1;
    if (k) kkkier=1;

    if (oo<10)
    {
        // cykl
        int b=oo-1;
        if (!monot) odzysk_cykl(p,val,a,b,1-k);
        else odzysk_cykl(p,1,b,a,1-k);
        return;
    }
    if (oo<10000)
    {
        oo-=10;
        int i=oo%2000;
        int c=oo/2000;

        // zawijas
        int skok = ABS(i-p)+1;
        pociagnij(p,val,a,k,monot,skok);
        val += zmiana*skok;
        int ost=3*n;
        if (monot) ost=1;
        int b=3-a-c;
        pociagnij(i,ost,c,1-k,1-monot,skok);
        ost -= zmiana*skok;
        pociagnij(p,ost,b,k,1-monot,skok);
        ost -= zmiana*skok;

        // cykl
        if (!monot) odzysk_cykl(i-kkkier,val,a,b,1-k);
        else odzysk_cykl(i-kkkier,ost,b,a,1-k);
        return;
    }
    // zygzak
    int kier = (!a ? 1 : -1);
    int i=oo-10000;
    int skok = ABS(i-p)+1;
    pociagnij(p,val,a,k,monot,skok);
    val += zmiana*skok;
    pociagnij(i,val,a+kier,1-k,monot,skok);
    val += zmiana*skok;
    pociagnij(p,val,a+2*kier,k,monot,skok);
    val += zmiana*skok;
    if (i != (1-k)*(n-1))
    {
//    fprintf(stderr,"Rekur:   ");
        odzysk_sciezka(i-kkkier,a+2*kier,k,monot);
    }
}

void probuj_dwie_sciezki()
{
    if (koniec) return;
    FOR(p,-1,n-1) REP(a,3) REP(monot,2)
    {
        bool jest = true;
        if (p>=0)  jest &= sciezka[p][a][1][monot];
        if (p+1<n) jest &= sciezka[p+1][a][0][1-monot];
        if (jest)
        {
            if (p>=0)  odzysk_sciezka(p,a,1,monot);
            if (p+1<n) odzysk_sciezka(p+1,a,0,1-monot);
            koniec=true;
            return;
        }
    }
}


void doit()
{
    licz_cykl();
    licz_ciagnie();
    probuj_dwa_cykle();
    licz_sciezka();
    probuj_dwie_sciezki();
}

int main()
{
    scanf("%d",&n);
    REP(i,3) REP(j,n) scanf("%d",t[j]+i); // ! na odwrot !
    koniec=false;
    doit();
    if (koniec)
    {
        wypisz();
    } else puts("NIE");
    return 0;
}
