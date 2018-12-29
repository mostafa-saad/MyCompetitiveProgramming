/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Opis:                 Weryfikator odpowiedzi programu zawodnika     *
 *                                                                       *
 *************************************************************************/

#include "oi.h"
#include <limits>
#include <queue>
#include <cstdarg>

using namespace oi;
using namespace std;

void endf(const char* msg, int line, int position)
{
    printf("WRONG\nWiersz %d: %s\n", line, msg);
    exit(1);
}

Scanner *test;

const int BUF = 8192;

void ensure(bool condition, const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    if(!condition) {
        char buf[BUF];
        vsprintf(buf, fmt, va);
        test->error(buf);
    }
    va_end(va);
}

const int N = 500 * 1000;

vector<int> G[N + 1];
int indeg[N + 1];
int topo[N + 1];
int dp[N + 1];

int calc_length(int n, int k) {
    queue<int> kol;
    for(int i=1; i<=n; i++) if(indeg[i] == 0) kol.push(i);

    int nr = 0;
    while(!kol.empty()) {
        int v = kol.front();
        kol.pop();

        topo[++nr] = v;

        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            indeg[*it] --;
            if(indeg[*it] == 0) kol.push(*it);
        }
    }

    for(int i=1; i<=n; i++) {
        int v = topo[i];
        if(v == k) dp[v] = numeric_limits<int>::min();
        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            dp[*it] = max(dp[*it], dp[v] + 1);
        }
    }

    return *max_element(dp+1, dp+1+n);

}

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Uruchomienie: %s in out wzo\n", argv[0]);
        return 1;
    }
    FILE *fin = fopen(argv[1], "r");
    int n, m;
    fscanf(fin, "%d %d", &n, &m);

    for(int i=1; i<=m; i++) {
        int a, b;
        fscanf(fin, "%d %d", &a, &b);
        G[a].push_back(b);
        indeg[b] ++;
    }

    fclose(fin);

    FILE *fwzo = fopen(argv[3], "r");
    int wzo_t;
    fscanf(fwzo, "%*d %d", &wzo_t);
    fclose(fwzo);

    test = new Scanner(argv[2], endf, PL);
    int zaw_k = test->readInt(1, n);
    test->readSpace();
    int zaw_t = test->readInt(0, numeric_limits<int>::max());
    test->skipWhitespaces();

    ensure(wzo_t == zaw_t, "Bledna dlugosc trasy. Podano %d, a oczekiwano %d.", zaw_t, wzo_t);
    int length = calc_length(n, zaw_k);
    ensure(length == zaw_t, "Dlugosc najdluzszej trasy nie zgadza sie z dlugoscia podana przez zawodnika. Podano %d, a dlugosc wynosi %d.", zaw_t, length);


    printf("OK\n");
    delete test;
    return 0;
}
