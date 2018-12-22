#include <deque>
#include <cstdio>

using namespace std;

struct vlat {
    int visina, kolicina;
    vlat () {}
    vlat (int _visina, int _kolicina) {
        visina = _visina; 
        kolicina = _kolicina;
    }
};

int N;
int cnt[100005];

deque <vlat> DQ;

int main(void) {

    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        int x; scanf("%d", &x); 
        ++cnt[x];
    }

    for (int i = 1; i <= 100000; ++i) {
        if (cnt[i]) DQ.push_back(vlat(i, cnt[i])); 
    }

    bool mirkov_potez = true;
    while (DQ.size() > 2) {
        if (DQ.front().kolicina <= DQ.back().kolicina) {
            vlat mala = DQ.front(), velika = DQ.back();
            DQ.pop_front(); DQ.pop_back();
            
            DQ.front().kolicina += mala.kolicina;
            velika.kolicina -= mala.kolicina - 1;
            DQ.back().kolicina += mala.kolicina - 1;

            if (DQ.size() == 1) {
                DQ.push_back(velika);
                mirkov_potez = false; break;
            }

            --velika.kolicina;
            ++DQ.back().kolicina;
            if (velika.kolicina != 0) DQ.push_back(velika);
       
       } else {
            vlat mala = DQ.front(), velika = DQ.back();
            DQ.pop_front(); DQ.pop_back();
            mala.kolicina -= velika.kolicina; 
            DQ.front().kolicina += velika.kolicina;
            DQ.back().kolicina += velika.kolicina;
            DQ.push_front(mala);
        }
    }

    if (mirkov_potez) printf("Slavko\n"); else printf("Mirko\n");
    printf("%d %d\n", DQ.front().visina, DQ.back().visina);

    return 0;

}   
