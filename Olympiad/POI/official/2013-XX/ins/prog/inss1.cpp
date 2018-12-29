/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Inspektor                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(m^(2n) * n)                                 *
 *   Zlozonosc pamieciowa: O(m)                                          *
 *   Opis:                 Rozwiazanie wolne.                            *
 *                         Generujemy wszystkie mozliwe godziny przyjscia*
 *                         oraz wyjscia wszystkich informatykow.         *
 *                                                                       *
 *************************************************************************/

#include<stdio.h>
#include<iostream>
#include<cstring>

using namespace std;

#define MAXM 40

//Wejscie:
int N,M,T[MAXM],K[MAXM],I[MAXM];

//Wyjscie:
int res;

//a[i] - w ktorej chwili przyszedl do biura informatyk i
//b[i] - do ktorej chwili byl w biurze informatyk i
//c[i] - ilu bylo informatykow w chwili i
int a[MAXM],b[MAXM],c[MAXM];

void gen(int n) {
    if(n == N+1) {
        memset(c,0,sizeof(c));
        for(int i=1; i<=N; i++)
            for(int j=a[i]; j<=b[i]; j++)
                c[j]++;
        for(int i=1; i<=M; i++) {
            if(c[T[i]] != I[i] + 1 || a[K[i]] > T[i] || b[K[i]] < T[i])
                break;
            res = max(res, i);
        }
    } else {
        a[n] = 0;
        b[n] = 0;
        gen(n+1);
        for(int i=1; i<=M; i++)
            for(int j=i; j<=M; j++) {
                a[n] = i;
                b[n] = j;
                gen(n+1);
            }
    }
}

int main() {
    int tests;
    cin >> tests;
    for(int test = 1; test <= tests; test++) {
        res = 0;
        cin >> N >> M;
        for(int i=1; i<=M; i++) cin >> T[i] >> K[i] >> I[i];
        gen(1);
        cout << res << endl;
    }
}
