/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Tomasz Syposz                                 *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

using namespace std;

int dzielnik_pierwsz[10000100];

void sito() {
    for(int i = 2; i<10000100; i++) {
        if(dzielnik_pierwsz[i] == 0) {
            dzielnik_pierwsz[i] = i;
            if(i < 31001)
                for(int j = i*i; j<10000100; j+=i)
                    dzielnik_pierwsz[j] = i;
        }
    }
}

int dzielniki[1000100];
void oblicz_dzielniki(int czego) {
    dzielniki[0] = 1;
    dzielniki[1] = 1;
    while(czego > 1) {
        int ostatnia = dzielniki[0]+1;
        int curr = 1;
        int najnowsza_pierwsza = dzielnik_pierwsz[czego];
        while(czego%najnowsza_pierwsza == 0) {
            curr *= najnowsza_pierwsza;
            for(int i = 1; i <= dzielniki[0]; i++) dzielniki[ostatnia++] = dzielniki[i]*curr;
            czego /= najnowsza_pierwsza;
        }
        dzielniki[0] = ostatnia-1;
    }
}

static inline int min(int a,int b) {
    return (a>b)*b+(a<=b)*a;
}
static inline int max(int a,int b) {
    return (a>b)*a+(a<=b)*b;
}

int SUF = 240;


inline static bool w_przed(int a, int b, int c) {
    if(b == c) return 1;
    return (a-1)/c < b/c;
}

int K;
int daj(int a, int b, int c, int d, int pot) {
    for(int i = 22300; i>pot; i--) {
        if(w_przed(a,b,i)  && w_przed(c,d,i))  return i;
        K++;
    }
    return pot;
}

int x;

int spraw_o(int a,int b,int c, int d) {
    int odp = 0;
    for(int i = max(b-SUF,a); i<=b; i++) {
        oblicz_dzielniki(i);
        for(int j = 1; j <= dzielniki[0]; j++) {
            x++;
            if(w_przed(c,d,dzielniki[j])) odp = max(odp,dzielniki[j]);
        }
    }
    return odp;
}

int main() {
    sito();
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i++) {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int odp = spraw_o(a,b,c,d);
        odp = max(odp,spraw_o(c,d,a,b));
        odp = max(odp,daj(a,b,c,d,odp));

        printf("%d\n", odp);


    }
    fprintf(stderr, "%d %d\n", K, x);
}
