/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Logistyka                                          *
 *   Autor programu:       Bartosz Tarnawski                                  *
 *   Zlozonosc czasowa:    O(m sqrt n)                                        *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;

typedef tuple<char, int, int> Zdarzenie;
typedef long long LL;

vector<Zdarzenie> zdarzenia;
map<int, int> odl_na_id;
vector<int> uprawnienia;

struct Buckets {
    vector<LL> sumy, t;
    int S;
    void init(int n) {
        S = max((int)sqrt(n), 1);
        t.resize(n);
        sumy.resize(n / S + 1);
    }
    void dodaj(int x, LL v) {
        t[x] += v;
        sumy[x / S] += v;
    }
    LL suma(int l, int r) {
        int l1 = l / S, r1 = r / S;
        LL wyn = 0;
        if (l1 < r1) {
            for (int i = l1 * S + l % S; i < (l1 + 1) * S; i++) {
                wyn += t[i];
            }
            for (int i = r1 * S; i <= r1 * S + r % S; i++) {
                wyn += t[i];
            }
            for (int i = l1 + 1; i < r1; i++) {
                wyn += sumy[i];
            }
        } else {
            for (int i = l1 * S + l % S; i <= r1 * S + r % S; i++) {
                wyn += t[i];
            }
        }
        return wyn;
    }
};
    
Buckets bu_licz, // ile kierowcow ma upr. na dany przedzial odleglosci
     bu_sum;  // suma obslugiwanych odleglosci z danego przedzialu

void zmien(int kto, int typ) {
    int odl = uprawnienia[kto];
    if (odl == 0) return; // i tak nie moze jezdzic
    int id = odl_na_id[odl];
    bu_licz.dodaj(id, typ);
    bu_sum.dodaj(id, typ * odl);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        char typ;
        int a, b;
        cin >> typ >> a >> b;
        zdarzenia.push_back(Zdarzenie(typ, a, b));
        odl_na_id[b] = 1; // na razie tylko oznacz taka odleglosc
    }
    
    int przenum = 0;
    for (pair<const int, int> &it : odl_na_id) {
        it.second = ++przenum; 
    }
    // od teraz 1 |-> najmniejsza odleglosc, przenum |-> najwieksza odleglosc

    uprawnienia.resize(n + 1, 0);

    bu_licz.init(przenum + 1);
    bu_sum.init(przenum + 1);

    for (Zdarzenie &z : zdarzenia) {
        char typ;
        int a, b;
        tie(typ, a, b) = z;
        if (typ == 'U') {
            zmien(a, -1);
            uprawnienia[a] = b;
            zmien(a, 1);
        } else {
            int id = odl_na_id[b];
            LL calosc = bu_licz.suma(id, przenum);
            LL reszta = bu_sum.suma(0, id - 1);
            bool da_rade = (LL)(a - calosc) * (LL)b <= reszta;
            cout << (da_rade ? "TAK" : "NIE") << endl;
        }
    }

    return 0;
}
