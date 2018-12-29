/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Chomiki (CHO)                                             *
 *   Plik:     cho2.cpp                                                  *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Rozwiazanie weryfikujace.                                 *
 *                                                                       *
 *************************************************************************/ 

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

typedef unsigned long long LL;
const int MAXN = 100023;
const int MAXP = 31;
const int W    = 27;
const int MAXX = 201;
const LL  INF  = 100000000000000000LL;

using namespace std;

class Macierz {
    public:
        Macierz(int n) {
            nowka = true;
            rozmiar = n;
        }
        
        int rozmiar;
        long long t[MAXX][MAXX];
        bool nowka;
};

const Macierz operator*(const Macierz& x, const Macierz& y) {
    int rozm = x.rozmiar;
    Macierz odp(rozm);

    for(int i=0; i<rozm; i++) {
        for(int j=0; j<rozm; j++) {
            odp.t[i][j] = INF;
            for(int k=0; k<rozm; k++) {
            odp.t[i][j]=min(x.t[i][k]+y.t[k][j], odp.t[i][j]);
            }
        }
    }
    return odp;
}

LL** pr_left;
LL pot[MAXN];
string anal[MAXX];

int getLen(int w1, int w2) {
    int s = min(anal[w1].size(), anal[w2].size());
    if (w1 == w2) s--;
    for(int odp = s; odp > 0; odp--) {
        if (pr_left[w2][odp]*pot[anal[w1].size()-odp] == 
                pr_left[w1][anal[w1].size()]-pr_left[w1][anal[w1].size()-odp])
            return odp;
    }
    return 0;
}

int main() {
    pot[0] = 1;
    for(int i=1; i<MAXN; i++)
        pot[i] = pot[i-1]*W;

    int n, m;

    scanf("%d%d",&n, &m);
    m--;
    for(int i=0; i<n; i++) {
        char tmp[MAXN];
        scanf("%s",tmp);
        anal[i] = string(tmp);
    }

    pr_left = new LL*[n];

    for(int i=0; i<n; i++) {
        pr_left[i] = new LL[anal[i].size()+1];

        pr_left[i][0] = 0;

        for(size_t j=0; j<anal[i].size(); j++) {
            pr_left[i][1+j] = pr_left[i][j] + pot[j]*int(anal[i][j]-'a');
        }
    }

    vector<Macierz> r;
    r.push_back(Macierz(n));
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            r[0].t[i][j] = anal[j].size()-getLen(i, j);
        }
    }

    for(int i=1; i<MAXP; i++)
        r.push_back(r.back()*r.back());
    
    Macierz wynik(n);
    int p=0;

    while (m>0) {
        if (m%2==1) {
            if (wynik.nowka) wynik=r[p]; else
            wynik = wynik*r[p];
            wynik.nowka = false;
        }
        m/=2;
        p++;
    }
    
    long long ret = INF;
    for(int i=0; i<n; i++) 
    for (int j=0; j<n; j++) {
        ret = min(ret, anal[i].size()+wynik.t[i][j]);
    }
    printf("%lld\n",ret);

    for(int i=0; i<n; i++) delete[] pr_left[i];
    delete[] pr_left;
    return 0;
}
