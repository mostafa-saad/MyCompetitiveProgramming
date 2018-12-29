/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Jakub Sygnowski                               *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Kilka razy losuje k punktow, w ktore strzela  *
 *                         i wybiera najlepszy trafiony wynik.           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef pair<int,int> PII;
#define REP(i,n) for(int i=0;i<n;i++)
#define F first
#define S second
#define MP make_pair
#define MAXV 500007
//#define DEBUG
#ifdef DEBUG
#define deb printf
#else
#define deb(...)
#endif
long long det(PII a,PII b) {
    return a.F*b.S - b.F*a.S;
}
int sgn(long long x) {
    if (x>0) return 1;
    if (x<0) return -1;
    return 0;
}
pair<PII,PII> odcinki[MAXV];
bool przecina(PII a, int x) {
//czy strzala wystrzelona w kierunku punktu a przecina odcinek x
//	deb("sprawdzam, czy punkt a %d %d przecina odcinek nr %d\n",a.F,a.S,x);
//	deb("d1 %lld d2 %lld\n",det(a,odcinki[x].F),det(a,odcinki[x].S));
    return sgn(det(a,odcinki[x].F)) != sgn(det(a,odcinki[x].S)) || (!det(a,odcinki[x].F));
}
int n,k,res,a,scietych;
bool bylo[MAXV];
bool zeps;
int ile(PII a) {
    deb("wylosowalem punkt %d %d\n",a.F,a.S);
    int rs = 0;
    REP(i,n) {
        if (przecina(a,i)) {
            deb("przecina sie z %d: %d %d %d %d\n",i, odcinki[i].F.F,odcinki[i].F.S,odcinki[i].S.F,odcinki[i].S.S);
            scietych++;
            bylo[i] = true;
            rs++;
        }
    }
    deb("lacznie z %d\n",rs);
    return rs;
}
bool fajnie(PII x) {
    REP(i,n) {
        if (bylo[i] && przecina(x,i)) return false;
    }
    return true;
}
PII losuj() {
    if (rand()%2)
        return odcinki[rand()%n].F;
    else return odcinki[rand()%n].S;
}
int wynik() {
    REP(i,n) bylo[i] = false;
    a = rand()%n;
    scietych = 0;
    int prob = 50;
    int tmpr = 0;
    PII odc;
    REP(i,k) {
        if (scietych == n) break;
        odc = losuj();
        while(prob-- && !fajnie(odc)) odc = losuj();
        if (prob <= 0) break;
        tmpr += ile(odc);
    }
    deb("udalo sie uzyskac %d\n",tmpr);
    return tmpr;
}
#include <sys/time.h>
struct timeval czas;
int tmp;
int main() {
    gettimeofday(&czas,0);
    srand(czas.tv_usec);
    tmp = scanf("%d%d",&k,&n);
    REP(i,n) {
        tmp = scanf("%d%d%d%d",&odcinki[i].F.F,&odcinki[i].F.S,&odcinki[i].S.F,&odcinki[i].S.S);
    }
    int strzalow = 0;
    res = 0;
    if (n*k>0)
        strzalow = max(10,10*1000*1000/(n*k));
    while(strzalow--) {
        res = max(res,wynik());
    }
    printf("%d\n",res);
}
