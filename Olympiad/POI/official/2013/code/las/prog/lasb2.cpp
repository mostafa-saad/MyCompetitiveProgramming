/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Jakub Sygnowski                               *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zachlannie strzela w punkty, w ktorych        *
 *                         przetnie najwiecej odcinkow.                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 1000007
#define MAXK 101
#define REP(I,N) for(int I=0;I<N;I++)
#define INF 1000000007
//#define DEBUG
#ifdef DEBUG
#define deb printf
#else
#define deb(...)
#endif

typedef pair<int,int> PII;
typedef long long LL;

int n,k;
bool przeciety[MAXN];
bool wspolliniowe[2*MAXN];
PII przeciecia[2*MAXN]; //first - ile przecina, second - numer punktu
int sgn(LL x) {
    if (x<0) return -1;
    if (x>0) return 1;
    return 0;
}
long long det(PII a, PII b) {
    return (LL)(a.first)*(LL)(b.second) - (LL)(a.second)*(LL)(b.first);
}
pair<PII,PII> odcinki[MAXN];
pair<PII,int> punkty[2*MAXN];
/* first - wspolrzedne punktu
 * second: -1 jesli jest to koniec odcinka, 1 jesli poczatek
 */

bool comp(PII a, PII b) {
    if (det(a,b) != 0LL)
        return det(a,b) > 0LL;
    return (LL)(a.first)*(LL)(a.first) + (LL)(a.second)*(LL)(a.second) < (LL)(b.first)*(LL)(b.first) + (LL)(b.second)*(LL)(b.second);
}

bool comp2(pair<PII,int> a, pair<PII,int> b) {
    if (det(a.first, b.first) != 0LL)
        return det(a.first, b.first) > 0LL;
    if (a.second != b.second)
        return a.second > b. second;
    return comp(a.first, b.first);
}
void naprosta() {
    /* Robi sortowanie katowe po punktach, zmieniajac problem
     * z dwuwymiarowego na jednowymiarowy
     */
    sort(punkty, punkty+(2*n), comp2);
    deb("posortowane punkty:\n");
    REP(i,2*n) {
        deb("%d %d: %d\n",punkty[i].first.first, punkty[i].first.second,punkty[i].second);
    }
    REP(i,2*n) {
        if (i != 2*n -1 && det(punkty[i].first, punkty[i+1].first) == 0LL) {
            deb("punkty %d i %d sa wspolliniowe\n",i,i+1);
            wspolliniowe[i] = true;
        }
    }
    int przecietych = 0, last = 0;
    REP(i,2*n) {
        if (wspolliniowe[i]) continue;
        else {
            for(int j=last; j<=i; j++) {
                if (punkty[j].second > 0) {
                    przecietych++;
                }
            }
            for(int j=last; j<=i; j++) {
                deb("strzal w %dty punkt - %d przecietych\n",j,przecietych);
                przeciecia[j] = make_pair(przecietych, j);
            }
            for(int j=last; j<=i; j++) {
                if (punkty[j].second < 0) {
                    przecietych--;
                }
            }
            last = i+1;
        }
    }
}
bool mozna(int x) { //czy mozna strzelic w punkt x?
    REP(i,n) {
        if (sgn(det(punkty[x].first, odcinki[i].first)) != sgn(det(punkty[x].first, odcinki[i].second)) || !det(punkty[x].first, odcinki[i].first)) {
            if (przeciety[i]) return false;
        }
    }
    return true;
}
int wynik;
void strzel(int x) { //strzel w punkt x
    REP(i,n) {
        if (sgn(det(punkty[x].first, odcinki[i].first)) != sgn(det(punkty[x].first, odcinki[i].second)) || (det(punkty[x].first, odcinki[i].first) == 0LL)) {
            przeciety[i] = true;
            wynik++;
        }
    }
    deb("\n");
}
PII poczatek, koniec;
int tmp;
int main() {
    tmp = scanf("%d%d",&k,&n);
    REP(i,n) {
        tmp = scanf("%d%d%d%d", &poczatek.first, &poczatek.second, &koniec.first, &koniec.second);
        if(comp(koniec, poczatek))
            swap(poczatek,koniec);
        punkty[2*i] = make_pair(poczatek, i+1);
        punkty[2*i+1] = make_pair(koniec, -i-1);
        odcinki[i] = make_pair(poczatek, koniec);
    }
    naprosta();
    sort(przeciecia, przeciecia+(2*n));
    reverse(przeciecia, przeciecia+(2*n));
    REP(i,2*n) {
        if (!k) break;
        if (mozna(przeciecia[i].second)) {
            strzel(przeciecia[i].second);
            k--;
        }
    }
    printf("%d\n",wynik);
}
