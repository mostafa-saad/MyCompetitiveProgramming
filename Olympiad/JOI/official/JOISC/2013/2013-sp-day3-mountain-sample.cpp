#include "grader.h"

int dr[] = {0, 1, 0, -1}, dc[] = {1, 0, -1, 0};

void search(int r, int c, int ld, int sd, int r1, int c1, int r2, int c2, int x)
{
    while (r1 <= r && r <= r2 && c1 <= c && c <= c2) {
        int h = Measure(r, c);
        if (h > x) {
            r += dr[ld];
            c += dc[ld];
        } else if (h < x) {
            r += dr[sd];
            c += dc[sd];
        } else {
            Pinpoint(r, c);
        }
    }
}

void Rescue(int R, int C, int MR, int MC, int X)
{
    search(MR,  1, 3, 0,  1,  1, MR, MC, X);
    search( R, MC, 2, 3, MR,  1,  R, MC, X);
    search(MR,  C, 1, 2, MR, MC,  R,  C, X);
    search( 1, MC, 0, 1,  1, MC, MR,  C, X);
}
