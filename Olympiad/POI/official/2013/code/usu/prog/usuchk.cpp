/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Usuwanka                                      *
 *   Autor:                Igor Adamski                                  *
 *   Opis:                 Weryfikator odpowiedzi programu zawodnika     *
 *                                                                       *
 *************************************************************************/

#include<cassert>
#include<stack>
#include "oi.h"
using namespace std;

const int MAXN = 1000000;

void wrong(const char* msg, int line=0, int position=0) {
    printf("WRONG\n");
    if(line)
        printf("Linia %d: ", line);
    printf("%s\n", msg);
    exit(1);
}

char A[MAXN+2];
int B[MAXN+1];
int cnt[MAXN+1];

int main(int argc, char *argv[]) {
    oi::Scanner in(argv[1], wrong, oi::PL);
    oi::Scanner out(argv[2], wrong, oi::PL);
    int n = in.readInt(2, MAXN);
    in.readSpace();
    int k = in.readInt(1, n-1);
    in.readEoln();
    in.readString(A, n+1);
    for(int i=1; i<=n/(k+1); ++i)
    {
        int sum = 0;
        int last = 0;
        for(int j=0; j<k+1; ++j)
        {
            int p = out.readInt(last+1, n-k+j) - 1;
            last = p + 1;
            out.skipWhitespaces();
            if(B[p]) {
                char msg[100];
                sprintf(msg, "Pozycja %d podana dwa razy.", p+1);
                wrong(msg);
            }
            sum += (A[p] == 'b' ? 1 : -k);
            B[p] = i;
        }
        if(sum)
            wrong("Podany ruch nie zawiera dokladnie k bialych i jednego czarnego klocka.", i);
    }
    out.readEof();

    stack<int> S;
    for(int i=0; i<n; ++i)
    {
        if(S.empty() || S.top() <= B[i]) {
            S.push(B[i]);
            ++cnt[B[i]];
            if(cnt[B[i]] == k+1) {
                assert((int)S.size() >= k+1);
                for(int j=0; j<k+1; ++j)
                {
                    assert(S.top() == B[i]);
                    S.pop();
                }
            }
        }
        else {
            char msg[100];
            sprintf(msg, "Ruch numer %d nie jest poprawny.", S.top());
            wrong(msg);
        }
    }
    printf("OK\n");
    return 0;
}

