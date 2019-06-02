/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Klocki (KLO)                                               *}
{*   Plik:    klo6.cpp                                                   *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie: Poprawne w O(n*log(n)), wykorzystuje          *}
{*            drzewo licznikowe                                          *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long int LL;

struct MaxTree {
    LL* el;
    int s;
    MaxTree(int size) {
        el = new LL[2*(s = 1<<size)];
        for(int x=2*s-1;x>=0;x--) el[x]=0;
    }
    ~MaxTree(){delete[] el;}
    void Set(int p, LL v) {
        for(p+=s, el[p]=v, p>>=1; p>0; p>>=1)
            el[p] = max(el[p<<1], el[(p<<1)+1]);
    }
    LL Find(int p, int k) {
        LL m = -2000000000;
        p+=s;
        k+=s;
        while(p<k) {
            if((p&1)==1) m=max(m,el[p++]);
            if((k&1)==0) m=max(m,el[k--]);
            p>>=1;
            k>>=1;
        }
        if(p==k) m=max(m,el[p]);
        return m;
    }
};

int Size(int n) {
    int r = 1;
    while(n) {
        r++;
        n >>= 1;
    }
    return r;
}

const int MAX_V = 1000001;
int lista[MAX_V];
struct el {
    int v, nast, skad, res;
};
el tab[100001];

int main() {
    int n;
    scanf("%d", &n);
    MaxTree t(17);
    for(int x=0;x<=1000000;x++) lista[x] = -1;
    for(int x=1;x<=n;x++) {
        scanf("%d", &tab[x].v);
        tab[x].nast = lista[tab[x].v];
        lista[tab[x].v] = x;
        tab[x].res = 0;
    }
    for(int x=1;x<=n;x++) {
        int el = lista[x];
        while(el != -1) {
            if (el >= x) {
                LL mv = t.Find(1, el - x + 1);
                int pos = mv & (0xFFFFFFFF);
                int val = mv >> 32;
                tab[el].skad = pos;
                tab[el].res = val + 1;
                t.Set(el - x + 1, ((LL)tab[el].res << 32) + el);
            }
            el = tab[el].nast;
        }
    }
    int p = 0;
    for(int x = 1; x <= n; x++) {
        if (tab[x].res > tab[p].res) p = x;
    }
    printf("%d\n", n - tab[p].v);
    while(p) {
        tab[p].v *= -1;
        p = tab[p].skad;
    }
    int usuniete = 0;
    for(int x = n; x > 0 && tab[x].v >= 0; x--) printf("%d ", x);
    for(int x = 1; x <= n; x++) if (tab[x].v < 0) {
        for(int y = x + tab[x].v - usuniete; y > 0; y--) {
            printf("%d ", x - y);
            usuniete++;
        }
    }
    printf("\n");
    return 0;
}
