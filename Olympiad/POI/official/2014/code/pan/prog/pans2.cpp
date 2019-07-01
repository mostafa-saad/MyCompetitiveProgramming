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


void solve() {
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    int q1 = 1;
    int q2 = 1;
    while(1) {
        if(d/q2<=b/q1 && d/q2>=(a+q1-1)/q1 && (c+q2-1)/q2 <= d/q2) {
            printf("%d\n",d/q2);
            break;
        }
        if(b/q1<=d/q2 && b/q1>=(c+q2-1)/q2 && (a+q1-1)/q1 <= b/q1) {
            printf("%d\n",b/q1);
            break;
        }
        if ((c + q2 - 1)/q2 > d/q2) {
            ++q2;
        } else if ((a + q1 - 1) / q1 > b / q1) {
            ++q1;
        } else if(d/q2 < (a + q1 - 1) /q1) q1++;
        else q2++;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) solve();
    return 0;
}
