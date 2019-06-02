/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gra Tower Defense                             *
 *   Autor:                Marcin Andrychowicz                           *
 *   Opis:                 Weryfikator odpowiedzi programu zawodnika     *
 *                                                                       *
 *************************************************************************/

#include <vector>
using namespace std;
#include "oi.h"
using namespace oi;
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)

void endf(const char* msg, int line, int position)
{
    printf("WRONG\nWiersz %d: %s\n", line, msg);
    exit(1);
}

const int MAXN = 500000;
int n, m, k;
vector<int> edges[MAXN + 1], towers;
bool safe[MAXN + 1], vis[MAXN + 1];

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Uruchomienie: %s in out wzo\n", argv[0]);
        return 1;
    }

    //in
    FILE *fin = fopen(argv[1], "r");
    fscanf(fin, "%d %d %d", &n, &m, &k);
    while(m--) {
        int a, b;
        fscanf(fin, "%d %d", &a, &b);
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    //out
    Scanner *test = new Scanner(argv[2], endf, PL);
    int r = test->readInt(1, k);
    test->skipWhitespacesUntilEOLN();
    test->readEoln();
    for(int i=1; i<=r; i++) {
        towers.push_back(test->readInt(1, n));
        test->skipWhitespaces();
    }
    test->readEof();

    //test
    FORE(i, towers) {
        if(vis[*i])
            test->error("powtarzajaca sie wieza");
        vis[*i] = true;
        safe[*i] = true;
        FORE(j, edges[*i])
        safe[*j] = true;
    }
    for(int i=1; i<=n; i++) {
        bool ok = safe[i];
        FORE(j, edges[i])
        ok |= safe[*j];
        if(!ok)
            test->error("niepokryty wierzcholek");
    }
    delete test;

    printf("OK\n");
}
