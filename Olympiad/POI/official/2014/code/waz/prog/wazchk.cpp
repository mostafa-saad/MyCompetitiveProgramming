/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Waz                                           *
 *   Autor:                Jakub Radoszewski                             *
 *   Opis:                 Weryfikator odpowiedzi programu zawodnika     *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#include "oi.h"
using namespace oi;

#define MAX_N 2000

int t[3][MAX_N], t1[3][MAX_N];
int n;

void endf(const char* msg, int line, int position)
{
    printf("WRONG\nWiersz %d: %s\n", line, msg);
    exit(1);
}

bool jest[3 * MAX_N + 1];

int x[]= {0,0,-1,1};
int y[]= {-1,1,0,0};
inline bool ins(int g,int h) {
    return g>=0 && g<h;
}

void dfs(int a, int b, int p, Scanner *test)
{
    if (p == 3 * n)
        return;
    bool ok = false;
    for (int i = 0; i < 4; i++)
    {
        int a1 = a + x[i], b1 = b + y[i];
        if (ins(a1, 3) && ins(b1, n) && t1[a1][b1] == p + 1)
        {
            ok = true;
            dfs(a1, b1, p + 1, test);
        }
    }
    if (!ok)
        test->error("Waz nie jest spojny");
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Uruchomienie: %s in out wzo\n", argv[0]);
        return 1;
    }
    FILE *fin = fopen(argv[1], "r");
    fscanf(fin, "%d", &n);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < n; j++)
            fscanf(fin, "%d", t[i] + j);
    fclose(fin);

    Scanner *test = new Scanner(argv[2], endf, PL);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            t1[i][j] = test->readInt(1, 3 * n);
            if (t[i][j] && t[i][j] != t1[i][j])
                test->error("Zmienilo sie jedno z pol wejsciowych");
            if (jest[t1[i][j]])
                test->error("Liczba powtarza sie");
            jest[t1[i][j]] = true;
            if (j < n - 1) test->readSpace();
            else if(i<2) {
                test->skipWhitespacesUntilEOLN();
                test->readEoln();
            }
        }
    }
    test->skipWhitespaces();
    test->readEof();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < n; j++)
            if (t1[i][j] == 1)
                dfs(i, j, 1, test);
    delete test;
    printf("OK\n");
    return 0;
}
