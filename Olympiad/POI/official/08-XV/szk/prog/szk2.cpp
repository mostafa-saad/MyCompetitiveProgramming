/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szk2.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(l*log l) (l - obwod figury).       *
 *             Implementacja w C++ z uzyciem STL.                        *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <cstring>
#include <map>

using namespace std;

typedef long long LL;

#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define FORL(v,p,k) for(int v=p;v<k;++v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define SIZE(x) (int)x.size()
#define ALL(c) c.begin(),c.end()
#define ST first
#define ND second
#define MP make_pair

typedef pair<int, int> PII;
int n;
map<PII, PII> fau;
vector<PII> wie, t1, t2;
map<PII, int> ost, faustop;
inline int sgn(int x){ return x < 0 ? -1 : 1; }
PII ojc(PII co){ return fau[co] == co ? co : fau[co] = ojc(fau[co]); }
inline PII scal1(PII a){ return MP(a.ST + a.ND, a.ST - a.ND); }
inline PII scal2(PII a){ return MP(a.ST - a.ND, a.ST + a.ND); }
inline PII ocal1(PII a){ return MP((a.ST + a.ND)/2, (a.ST - a.ND)/2); }
inline PII ocal2(PII a){ return MP((a.ST + a.ND)/2, (a.ND - a.ST)/2); }

void lacz(PII a, PII b){
    a = ojc(a); b = ojc(b); if (a==b) return;
    if (faustop[a] < faustop[b]) swap(a, b);
    faustop[a] = faustop[a] + faustop[b];
    fau[b] = a;
}

int main(){
    scanf("%d", &n);
    REP(i, n){ int a, b; scanf("%d%d", &a, &b); wie.PB(MP(a, b)); }
    wie.PB(wie[0]); wie.PB(wie[1]);
    REP(i, n){
        if (wie[i].ST == wie[i+1].ST){
            FOR(y, min(wie[i].ND, wie[i+1].ND)+1, max(wie[i].ND, wie[i+1].ND)-1){
                t1.PB(scal1(MP(wie[i].ST, y)));
                t2.PB(scal2(MP(wie[i].ST, y)));
                fau[MP(wie[i].ST, y)] = MP(wie[i].ST, y);
                faustop[MP(wie[i].ST, y)] = 1;
            }
            if (sgn(wie[i+1].ND-wie[i].ND) * sgn(wie[i+2].ST-wie[i+1].ST) > 0)
                t1.PB(scal1(wie[i+1]));
            else
                t2.PB(scal2(wie[i+1]));
        }else{
            FOR(x, min(wie[i].ST, wie[i+1].ST)+1, max(wie[i].ST, wie[i+1].ST)-1){
                t1.PB(scal1(MP(x, wie[i].ND)));
                t2.PB(scal2(MP(x, wie[i].ND)));
                fau[MP(x,wie[i].ND)] = MP(x, wie[i].ND);
                faustop[MP(x,wie[i].ND)] = 1;
            }
            if (sgn(wie[i+2].ND-wie[i+1].ND) * sgn(wie[i+1].ST-wie[i].ST) > 0)
                t1.PB(scal1(wie[i+1]));
            else
                t2.PB(scal2(wie[i+1]));
        }
        fau[wie[i+1]] = wie[i+1];
        faustop[wie[i+1]] = 1;
    }
    sort(ALL(t1)); sort(ALL(t2));
    for(int i = 0; i + 1 < SIZE(t1); i += 2)
        lacz(ocal1(t1[i]), ocal1(t1[i+1]));
    for(int i = 0; i + 1 < SIZE(t2); i += 2)
        lacz(ocal2(t2[i]), ocal2(t2[i+1]));
    printf("%d\n", n/2);
    REP(i, n){
        PII p = ojc(wie[i]);
        if (ost.count(p) > 0)
            printf("%d %d\n", ost[p]+1, i+1);
        else
            ost[p] = i;
    }
    return 0;
}
