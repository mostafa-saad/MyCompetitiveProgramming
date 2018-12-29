/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Jakub Sygnowski                               *
 *   Zlozonosc czasowa:    O(nk log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 500007
#define MAXK 101
#define REP(I,N) for(int I=0;I<N;I++)
#define INF 1000000007
//#define DEBUG
#ifdef DEBUG
#define deb printf
#else
#define deb(...)
#endif

int n,k,tab[2*MAXN],przec[2*MAXN],numer[MAXN],zamkniete[2*MAXN],prawo[2*MAXN];
/* tab - tablica przechowujaca poczatki i konce odcinkow
 * po zrobieniu sortowania katowego. Liczba a (-a)
 * na pozycji i oznacza, ze i-te w kolejnosci zdarzenie
 * to poczatek (koniec) a-tego odcinka (w kolejnosci
 * posortowania katowego)
 * przec - mowi ile odcinkow przetnie strzala wystrzelona
 * w kierunku i-tego (w kolejnosci posortowania
 * katowego) punktu (z dokladnoscia do punktow
 * wspolliniowych)
 * numer - nowy numer nadany odcinkowi. oznacza numer
 * konca danego odcinka posrod innych
 * zamkniete - najwiekszy numer odcinka takiego,
 * ze konczy sie on wczesniej niz i-ty punkt
 * prawo - numer najwiekszego odcinka takiego, ze
 * jest on przeciety przy strzale w punkt i
 */
bool wspolliniowe[2*MAXN];
/* czy punkt i oraz i+1 leza na tej samej prostej razem z 0,0?
 */
int dp[2][MAXN]; //dp[1][2]
/* numer najwczesniejszego konca odcinka, takiego, ze za pomoca
 * ([1]+1) strzalow w punkty z odcinkow o numerach [1..nr] mozna uzyskac
 * wynik [2] (jesli nie mozna uzyskac takiego wyniku
 * to INF)
 * inaczej: 'jak duzo poczatkowych odcinkow potrzebuje,
 * aby uzyskac wynik [2], zakladajac, ze zrobie
 * [1]+1 strzalow
 * uwaga: strzelam tylko w konce i poczatki odcinkow
 */

int najwiekszy(int strzalow, int nastepny) {
    /* najwiekszy wynik([2] z dp), jaki mozna uzyskac robiac
     * (strzalow+1) strzalow, z ktorych najdalszy (w punkt
     * z odcinka o najwiekszym numerze) jest mniejszy niz 'nastepny'
     */
    int lowb = 0, upb = n;
    /* zalozenia (niezmiennik):
     * dp[strzalow][lowb] < nastepny
     * dp[strzalow][upb] >= nastepny
     */
    while (lowb != upb-1) {
        int proba = (lowb+upb)/2;
        if (dp[strzalow%2][proba] < nastepny)
            lowb = proba;
        else
            upb = proba;
    }
    deb("najlepszy wynik, jaki mozna uzyskac robiac %d strzalow, z ktorych najdalszy trafia blizej niz %d wynosi %d\n",strzalow+1,nastepny,lowb);
    return lowb;
}

void inicjalizacja() {
    REP(i,2) {
        dp[i][0] = 0;
        REP(j,n) {
            dp[i][j+1] = INF;
        }
    }
}

void pierwszywiersz() {
    /* wylicza dp[0], przec, prawo, zamkniete. zamiata.
     */
    int przecietych = 0, najdalszy = 0, ostatni = 0, last = 0;
    /* przecietych - ile odcinkow jest aktualnie przecietych
     * najdalszy - najwiekszy sposrod numerow odcinkow, ktore
     * zostaly juz 'otwarte'
     * ostatni - najwiekszy sposrod numerow odcinkow, ktore zostaly
     * juz zamkniete
     * last - pierwszy sposrod punktow, ktore leza na tej samej prostej
     * (wychodzacej z 0,0), co aktualny punkt; wszystkie takie punkty
     * przetwarzam jednoczesnie
     */
    REP(i,2*n) {
        if (wspolliniowe[i]) {
            continue;
        } else {
            for(int j=last; j<=i; j++) {
                zamkniete[j] = ostatni;
                if (tab[j] > 0) { //poczatek odcinka
                    przecietych++;
                    najdalszy = max(najdalszy,tab[j]);
                }
            }
            dp[0][przecietych] = min(dp[0][przecietych],najdalszy);
            for(int j=last; j<=i; j++) {
                przec[j] = przecietych;
                prawo[j] = najdalszy;
            }
            for(int j=last; j<=i; j++) {
                if (tab[j] < 0) { //koniec odcinka, strzelam
                    przecietych--;
                    ostatni++;
                }
            }
            last = i+1;
        }
    }
    deb("ilosc odcinkow przecinanych w kolejnych punktach: \n");
    REP(i,2*n) deb("%d ",przec[i]);
    deb("\n");
    for(int j=n-1; j>=0; j--)
        dp[0][j] = min(dp[0][j], dp[0][j+1]);

    deb("zamkniete (z ktorych odcinkow moge skorzystac przed strzeleniem w ity punkt):\n");
    REP(i,2*n) deb("%d ",zamkniete[i]);
    deb("\n");
    deb("prawo (numer najwiekszego odcinka takiego, ze jest on przeciety podczas strzalu w ity punkt):\n");
    REP(i,2*n) deb("%d ",prawo[i]);
    deb("\n");
    deb("pierwszy wiersz dp: \n");
    REP(i,n)
    deb("%d ",dp[0][i]);
    deb("\n");
}

void liczdp() {
    int wczesniej;
    for(int i=1; i<k; i++) {
        for(int j=0; j<2*n; j++) {
            if (tab[j] > 0) {
                /* mam dany poczatek odcinka. chce uzyskac jak najlepszy wynik,
                 * oddajac i-1 strzalow w odcinki o numerach < j (tzn. lezacych
                 * na lewo od punktu j) oraz strzelajac raz w koniec odcinka
                 * zaczynajacego sie w j (jest to tab[j]-ty koniec w kolejnosci
                 * posortowania katowego)
                 */
                wczesniej = najwiekszy((i-1)%2, zamkniete[j] + 1);
                dp[i%2][wczesniej+przec[j]] =
                    min(dp[i%2][wczesniej+przec[j]],prawo[j]);
                deb("mozliwosc dp[%d][%d] = %d\n",i,wczesniej+przec[j],tab[j]);
            } else {
                wczesniej = najwiekszy(i-1,zamkniete[j]+1);
                dp[i%2][wczesniej+przec[j]] =
                    min(dp[i%2][wczesniej+przec[j]],prawo[j]);
                deb("mozliwosc2 dp[%d][%d] = %d\n",i,wczesniej+przec[j],prawo[j]);
            }
        }
        for(int j=n-1; j>=0; j--)
            dp[i%2][j] = min(dp[i%2][j], dp[i%2][j+1]);
        /* rozpropaguj korzystne zmiany, zeby mozna bylo korzystac
         * z wyszukiwania binarnego
         */
    }
}

typedef pair<int,int> PII;
typedef long long LL;
long long det(PII a, PII b) {
    return (LL)(a.first)*(LL)(b.second) - (LL)(a.second)*(LL)(b.first);
}


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
    int otwarty = 1;
    REP(i,2*n) {
        if (i != 2*n -1 && det(punkty[i].first, punkty[i+1].first) == 0LL) {
            deb("punkty %d i %d sa wspolliniowe\n",i,i+1);
            wspolliniowe[i] = true;
        }
        if (punkty[i].second < 0) { //koniec odcinka
            tab[i] = -otwarty;
            numer[-punkty[i].second] = otwarty;
            otwarty++;
        }
    }
    REP(i,2*n) {
        if (punkty[i].second > 0) { //poczatek odcinka
            tab[i] = numer[punkty[i].second];
        }
    }

    deb("ciag zdarzen: \n");
    REP(i,2*n) deb("%d ",tab[i]);
    deb("\n");
}

PII poczatek, koniec;
int wynik;
int tmp;
int main() {
    tmp = scanf("%d%d",&k,&n);
    REP(i,n) {
        tmp = scanf("%d%d%d%d", &poczatek.first, &poczatek.second, &koniec.first, &koniec.second);
        if (comp(koniec, poczatek))
            swap(poczatek,koniec);
        punkty[2*i] = make_pair(poczatek, i+1);
        punkty[2*i+1] = make_pair(koniec, -i-1);
    }
    naprosta();
    inicjalizacja();
    pierwszywiersz();
    liczdp();
    REP(i,k) REP(j,n+1) {
        if (dp[i%2][j] != INF)
            /* cos roznego od INF w dp[i][j] oznacza, ze mozna, korzystajac dokladnie
             * z i strzalow i strzelajac w odcinki, ktorych konce maja numery
             * w przedziale [1..dp[i][j]] uzyskac wynik j
             */
            wynik = max(wynik, j);
    }
    printf("%d\n",wynik);
}
