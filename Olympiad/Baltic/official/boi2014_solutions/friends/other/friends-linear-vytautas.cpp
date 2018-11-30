/*
 * A linear time solution (not tested properly)
 *
 * Author: Vytautas Gruslys
 */

#include <cstdio>
#include <cstdlib>

using namespace std;

#define MAX_N 2000010

#define NO 0
#define INITIAL 1
#define FINAL 2
#define MULTIPLE 3

int N;
char seq[MAX_N];

void readInput()
{
    scanf ("%d\n", &N);
    for (int i = 0; i < N; ++i)
        scanf ("%c", &seq[i]);
}

void writeOutput(int ans)
{
    if (ans == NO) {
        printf ("NOT POSSIBLE\n");
    }

    else if (ans == INITIAL) {
        
        for (int i = 0; i < N/2; ++i)
            printf ("%c", seq[i]);
        printf ("\n");
   
    }

    else if (ans == FINAL) {
        
        for (int i = 0; i < N/2; ++i)
            printf ("%c", seq[N/2+1+i]);
        printf ("\n");

    }

    else if (ans == MULTIPLE) {
        printf ("NOT UNIQUE\n");
    }   

    exit (0);
}

bool tryInitial()
{
    int extra = 0;
    for (int i = 0; i < N/2; ++i) {
        while (seq[i] != seq[N/2+i+extra]) {
            ++extra;
            if (extra > 1)
                return false;
        }
    }
    return true;
}

bool tryFinal()
{
    int extra = 0;
    for (int i = 0; i < N/2; ++i) {
        while (seq[i+extra] != seq[N/2+i+1]) {
            ++extra;
            if (extra > 1)
                return false;
        }
    }
    return true;
}

bool coincides()
{
    for (int i = 0; i < N/2; ++i) {
        if (seq[i] != seq[N/2+1+i])
            return false;
    }

    return true;
}

int main()
{
    readInput();

    if (N%2 == 0)
        writeOutput (NO);

    if (tryInitial()) {
        if (tryFinal() && !coincides())
            writeOutput (MULTIPLE);
        else
            writeOutput (INITIAL);
    }

    else if (tryFinal())
        writeOutput (FINAL);
    
    else
        writeOutput (NO);
    
    return 0;
}
