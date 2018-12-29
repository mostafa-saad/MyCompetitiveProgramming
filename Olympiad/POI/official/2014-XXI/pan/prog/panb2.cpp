/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Tomasz Syposz                                 *
 *   Opis:                 Rozwiazanie bledne                            *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<cstdio>

using namespace std;

const int X = 660;
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

int max(int a,int b) {
    return (a>b)*a+(a<=b)*b;
}

int main() {
    sito();
    int n;
    scanf("%d",&n);
    for(int i =0; i<n; i++) {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        if(b-a < X) {
            int odp = 0;
            for(int k = a; k<=b; k++) {
                oblicz_dzielniki(k);
                for(int j = 1; j<=dzielniki[0]; j++) {
                    if(c/dzielniki[j] < d/dzielniki[j] || d%dzielniki[j] == 0) {
                        odp = max(odp,dzielniki[j]);
                    }
                }
            }
            printf("%d\n", odp);
        }
        else if(d-c < X) {
            int odp = 0;
            for(int k = c; k<=d; k++) {
                oblicz_dzielniki(k);
                for(int j = 1; j<=dzielniki[0]; j++) {
                    if(a/dzielniki[j] < b/dzielniki[j] || b%dzielniki[j] == 0) {
                        odp = max(odp,dzielniki[j]);
                    }
                }
            }
            printf("%d\n", odp);
        }
        else {
            int q1 = 1;
            int q2 = 1;
            while(true) {
                if(d/q2<=b/q1 && d/q2>=a/q1) {
                    printf("%d\n",d/q2);
                    break;
                }
                if(b/q1<=d/q2 && b/q1>=c/q2) {
                    printf("%d\n",b/q1);
                    break;
                }
                if(d/q2 < a/q1) q1++;
                else q2++;
            }
        }
    }
}
