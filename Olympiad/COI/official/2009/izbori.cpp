#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
int g, s, m, trenutno_glasova;
int kol[101];
vector < pair <int, int> > ga1;
int ga[101], dp[2][201], tko[101];
int sol[101][2];

int moze(int koja, int koliko) {
    int ii = 0;
    if (ga[koja]*20 < g) return 1;
    for (int i = 0; i <= 200; i++) dp[0][i] = g+100;
    dp[0][0] = 0;
    for (int i = 0; i < min(s, 21); i++) if (i != koja) {
        ii = 1-ii;
        for (int j = 0; j <= m; j++) {
            dp[ii][j] = g+100;
            for (int k = 0; k <= j; k++) {
                int dodatno = (ga[koja]*k + koliko) / (koliko+1) - ga[i];
                if (ga[koja]*k % (koliko+1) == 0 && tko[ i ]>tko[ koja ] && k) dodatno++;
                if (dodatno < 0) dodatno = 0;
                if (k && (ga[i]+dodatno)*20 < g) { dodatno += (g+19-20*(ga[i]+dodatno))/20; }
                if (dp[ii][j] > dp[1-ii][j-k] + dodatno) dp[ii][j] = dp[1-ii][j-k] + dodatno;
            }
        }
    }
    if (dp[ii][m-koliko] <= g-trenutno_glasova) return 1;
    return 0;
}

int main() {
    scanf("%d %d %d", &g, &s, &m);
    ga1.resize(s);
    for (int i = 0; i < s; i++) {
        scanf("%d", &ga[i]); 
        ga1[i].second = i; 
        ga1[i].first = -ga[i];
        trenutno_glasova += ga[i];
    }
    sort(ga1.begin(), ga1.end());
    for (int i =0 ; i < s; i++) {tko[i] = ga1[i].second; ga[i] = -ga1[i].first;}
    // Prvi dio zadatka. Simulacija nakon dodjeljivanja preostalih glasova trenutnoj
    // stranci.
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) kol[j] = 0;
        ga[i] += g-trenutno_glasova;
        for (int j = 0; j < m; j++) {
            int max_a = 0, max_b = 1, koji = 0;
            for (int k = 0; k < s; k++) if(ga[k]*20 >= g) {
                if (ga[k]*max_b > max_a*(kol[k]+1)) {
                    max_a = ga[k];
                    max_b = kol[k]+1;
                    koji = k;
                }
                if (ga[k]*max_b == max_a*(kol[k]+1) && tko[koji] > tko[k]) {
                    max_a = ga[k];
                    max_b = kol[k]+1;
                    koji = k;
                }
            }
            kol[koji]++;
        }
        sol[ tko[i] ][0] = kol[i];
        ga[i] -= g-trenutno_glasova;
    }
    // Drugi dio zadatka. Binary search za trazenje minimalnog broja mjesta u
    // parlamentu.
    for (int i = 0; i < s; i++) {
        int lower = 0, upper = m;
        while (lower < upper) {
            if (moze(i, (lower+upper)/2)) upper = (lower+upper)/2; else lower = (lower+upper)/2 + 1;
        }
        sol[ tko[i] ][1] = lower;
    }
    for (int i = 0; i < s; i++) {
        if (i) printf(" ");
        printf("%d", sol[i][0]);
    } printf("\n");
    for (int i = 0; i < s; i++) {
        if (i) printf(" ");
        printf("%d", sol[i][1]);
    } printf("\n");
    
    return 0;
}
