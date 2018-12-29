/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Szymon Stankiewicz                            *
 *   Opis:                 Weryfikator odpowiedzi programu zawodnika     *
 *                                                                       *
 *************************************************************************/

#include "oi.h"

using namespace oi;

int tab[1000007], pop=-1, akt, n;

const int MIN=1, MAX=1000000;

void endf(const char* msg, int line, int position) {
    printf("WRONG\nWiersz %d: %s\n", line, msg);
    exit(1);
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Uruchomienie: %s in out wzo\n", argv[0]);
        return 1;
    }
    Scanner in(argv[1], PL), out(argv[2], endf, PL), wzor(argv[3], PL);
    int k = in.readInt(MIN, MAX);
    out.skipWhitespacesUntilEOLN();
    pop=out.readInt(0, k);
    int OKAY=wzor.readInt(0, MAX);
    if(pop==0 && OKAY!=0)
        out.error("Rozwiazanie istnieje");
    if(pop!=0 && OKAY==0)
        out.error("Rozwiazanie nie istnieje");
    if(pop==0)
    {
        printf("OK\n");
        return 0;
    }
    in.readSpace();
    int p=in.readInt(MIN, k);
    in.readSpace();
    int q=in.readInt(MIN, k);
    in.readEoln();
    for(int i = 0; i<k; i++)
    {
        if(i) in.readSpace();
        tab[i]=in.readInt(MIN, MAX);
        n+=tab[i];
    }

    for(int i = 1; i<n; i++)
    {
        out.skipWhitespacesUntilEOLN();
        akt=out.readInt(MIN, k);
        if(akt==pop)
            out.error("Dwa identyczne klocki obok siebie");
        if(i==0 && akt!=p)
            out.error("Ciag zaczyna sie zlym elementem");
        if(i==n-1 && akt!=q)
            out.error("Ciag konczy sie zlym elementem");
        pop=akt;
        tab[akt-1]--;
        if(tab[akt-1]<0)
            out.error("Uzyto zbyt duzo klockow tego samego koloru");
    }
    out.skipWhitespaces();
    out.readEof();
    printf("OK\n");
    return 0;
}
