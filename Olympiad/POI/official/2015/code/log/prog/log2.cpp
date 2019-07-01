/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Logistyka                                          *
 *   Autor programu:       Bartosz Tarnawski                                  *
 *   Zlozonosc czasowa:    O(m (log n + log m))                               *
 *   Opis:                 Rozwiazanie weryfikujace                           *
 *****************************************************************************/


#include <iostream>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

typedef tuple<char, int, int> Zdarzenie;
typedef long long LL;

vector<Zdarzenie> zdarzenia;
map<int, int> odl_na_id;
vector<int> uprawnienia;

struct Tree {
    vector<LL> t;
    int sz;
    void init(int n) {
        sz = 1;
        while (sz < n) sz *= 2;
        t.resize(2 * sz, 0);
    }
    void dodaj(int x, LL v) {
        x += sz;
        t[x] += v;
        for (x /= 2; x != 0; x /= 2) {
            t[x] = t[2 * x] + t[2 * x + 1];
        }
    }
    LL suma(int l, int r) {
        l += sz, r += sz;
        LL wyn = t[l];
        if (l != r) {
            wyn += t[r];
        }
        while (l / 2 != r / 2) {
            if (l % 2 == 0) wyn += t[l + 1];   
            if (r % 2 == 1) wyn += t[r - 1];   
            l /= 2, r /= 2;
        }
        return wyn;
    }
};
    
Tree tr_licz, // ile kierowcow ma upr. na dany przedzial odleglosci
     tr_sum;  // suma obslugiwanych odleglosci z danego przedzialu

void zmien(int kto, int typ) {
    int odl = uprawnienia[kto];
    if (odl == 0) return; // i tak nie moze jezdzic
    int id = odl_na_id[odl];
    tr_licz.dodaj(id, typ);
    tr_sum.dodaj(id, typ * odl);
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

    tr_licz.init(przenum + 1);
    tr_sum.init(przenum + 1);

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
            LL calosc = tr_licz.suma(id, przenum);
            LL reszta = tr_sum.suma(0, id - 1);
            bool da_rade = (LL)(a - calosc) * (LL)b <= reszta;
            cout << (da_rade ? "TAK" : "NIE") << endl;
        }
    }

    return 0;
}
