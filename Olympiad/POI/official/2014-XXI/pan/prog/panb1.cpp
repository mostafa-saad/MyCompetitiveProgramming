/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Tomasz Syposz                                 *
 *   Opis:                 Rozwiazanie bledne                            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

using namespace std;

void solve() {
    int a,b,c,d;
    scanf("%d%d%d%d\n",&a,&b,&c,&d);
    for(int i = 100000; i>=1; i--)
        if( (a-1)/i != b/i && (c-1)/i != d/i) {
            printf("%d\n",i);
            return;
        }
}

int main() {
    int n;
    scanf("%d\n", &n);
    for(int i = 0; i < n; i++) solve();
    return 0;
}
