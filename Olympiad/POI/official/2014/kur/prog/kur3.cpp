/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Zlozonosc czasowa:    O(k(n+m))                                     *
 *   Zlozonosc pamieciowa: O(n+mk)                                       *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
const int INF = 1000*1000*1001;
const LL INFLL = (LL) INF * (LL) INF;

#define MAXN 500*1000
#define MAXM 500*1000
#define PROB 26

int tmp,firma,n,m,i,a,b,j,idZapytania;
vector<int> paczki;
vector<int> zapytania[MAXN+2];
int firmy[MAXN+1];
int potencjalniMonopolisci[MAXM][PROB];
int potencjalniMonopolisciIloscPaczek[MAXM][PROB];
vector<int> poczatkiPrzedzialow;
int odpowiedzi[MAXM];
int main() {
    srand (time(NULL));
    ios_base::sync_with_stdio(0);
    cin>>n;
    cin>>m;
    paczki.push_back(0);
    for(i=0; i<n; ++i) {
        cin>>tmp;
        paczki.push_back(tmp);
    }
    paczki.push_back(0);

    for(i=0; i<m; ++i) {
        cin>>a>>b;
        zapytania[a].push_back(i);
        zapytania[b+1].push_back(-i-1);
        poczatkiPrzedzialow.push_back(a);
        for(j=0; j<PROB; ++j) {
            potencjalniMonopolisci[i][j]=paczki[a+rand()%(b-a+1)];
        }
    }

    for(i=0; i<n+2; ++i) {
        for(unsigned zap=0; zap<zapytania[i].size(); ++zap) {
            if(zapytania[i][zap]>=0) {
                idZapytania=zapytania[i][zap];
                for(j=0; j<PROB; ++j) {
                    firma=potencjalniMonopolisci[idZapytania][j];
                    potencjalniMonopolisciIloscPaczek[idZapytania][j]=firmy[firma];
                }
            } else {
                idZapytania=-zapytania[i][zap]-1;
                for(j=0; j<PROB; ++j) {
                    firma=potencjalniMonopolisci[idZapytania][j];
                    if(2*(firmy[firma]-potencjalniMonopolisciIloscPaczek[idZapytania][j])>
                            i-poczatkiPrzedzialow[idZapytania])
                        odpowiedzi[idZapytania]=firma;
                }
            }
        }
        ++firmy[paczki[i]];
    }
    for(i=0; i<m; ++i) {
        cout<<odpowiedzi[i]<<endl;
    }
    return 0;
}

