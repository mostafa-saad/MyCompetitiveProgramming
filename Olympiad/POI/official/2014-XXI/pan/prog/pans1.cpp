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

int min(int a,int b) {
    if(a < b) return a;
    return b;
}

void solve() {
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    for(int i = min(b,d); i>=1; i--)
        if( (a-1)/i != b/i && (c-1)/i != d/i) {
            printf("%d\n",i);
            return;
        }
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) solve();
    return 0;
}
