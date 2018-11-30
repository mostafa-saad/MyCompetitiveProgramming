// Monument (BOI 2009)
//
// the proposed solution
//
// time complexity: O(N^3)

#include <stdio.h>
#include <stdlib.h>

int P, Q, R, N;
int A = 0, B = 0;
int max = 0;

int dir = 0;

int *stone;
int *maxsqr;

void read(void) {
    FILE *f;
    int x, y, z;
    char *row;
    f = fopen("monument.in", "r");
    fscanf(f, "%i %i %i", &P, &Q, &R);
    N = P; if (Q > N) N = Q; if (R > N) N = R;
    stone = malloc(P*Q*R*sizeof(int));
    maxsqr = malloc(P*Q*R*sizeof(int));
    row = malloc((R+1)*sizeof(char));
    for (y = 0; y < Q; y++) {
        for (x = 0; x < P; x++) {
            fscanf(f, "%s", row);
            for (z = 0; z < R; z++) {
                stone[x*Q*R+y*R+z] = (row[z] == 'N' ? 0 : 1);
            }
        }
    }
    fclose(f);
}

int is_pore(int x, int y, int z) {
    if (dir == 0) return stone[x*Q*R+y*R+z];
    if (dir == 1) return stone[z*P*Q+x*Q+y];
    if (dir == 2) return stone[y*R*P+z*P+x];
}

// this calculates the maximal size of a monument
// whose x- and y-coordinates are given (O(n))
int maxmonu(int x, int y) {
    // we use a stack to store possible starting
    // points (z-coordinates) of monuments and
    // how large their bottom squares can be
    int stack[R+1][2];
    int z, n, s;
    int a = 0, b = 0, m = 0;
    stack[0][0] = 0;
    stack[0][1] = -1;
    n = 0;
    for (z = 0; z < R; z++) {
        s = maxsqr[x*Q*R+y*R+z];
        if (s > stack[n][0]) {
            // after this point, the side length of the
            // bottom square can be "s" or less
            n++;
            stack[n][0] = s;
            stack[n][1] = z;
        }
        if (s < stack[n][0]) {
            // after this point, the side length of the
            // bottom square has to be less than "s" so
            // no monument with the bottom square
            // larger than "s" can be extended further
            while (s < stack[n][0]) {
                if (stack[n][0]*(z-stack[n][1]) > m) {
                    a = stack[n][0];
                    b = (z-stack[n][1]);
                    m = a*b;
                }
                n--;
            }
            if (s > stack[n][0]) {
                n++;
                stack[n][0] = s;
            }
        }
    }
    // finally we go through all monuments whose
    // starting points are still in the stack
    while (n > 0) {
        if (stack[n][0]*(z-stack[n][1]) > m) {
            a = stack[n][0];
            b = (z-stack[n][1]);
            m = a*b;
        }
        n--; 
    }
    if (m > max) {
        A = a; B = b; max = m;
    }
}

void solve(void) {
    int x, y, z;
    int a, b, c, s;
    // we build an array maxsqr which contains for every
    // (x, y, z) in the raw stone the side length of
    // the largest square in the xy-plane which begins
    // at (x, y, z) and doesn't contain any pores (O(n^3))
    for (x = P-1; x >= 0; x--) {
        for (y = Q-1; y >= 0; y--) {
            for (z = 0; z < R; z++) {
                if (is_pore(x, y, z)) {
                    s = 0;
                } else {
                    a = b = c = 1;
                    if (y != Q-1) a += maxsqr[x*Q*R+(y+1)*R+z];
                    if (x != P-1) b += maxsqr[(x+1)*Q*R+y*R+z];
                    if (y != Q-1 && x!= P-1) c += maxsqr[(x+1)*Q*R+(y+1)*R+z];
                    s = a; if (b < s) s = b; if (c < s) s = c;
                }
                maxsqr[x*Q*R+y*R+z] = s;
            }
        }
    }
    // using the information found in the array maxsqr,
    // we can efficiently find the largest monument
    // whose x- and y-coordinates are given (O(n^3))
    for (x = 0; x < P; x++) {
        for (y = 0; y < Q; y++) {
            maxmonu(x, y);
        }
    }
}

// this changes the role of the coordinates
void newdir(void) {
    int t;
    t = P;
    P = Q;
    Q = R;
    R = t;
    dir++;
}

void write(void) {
    FILE *f;
    f = fopen("monument.out", "w");
    fprintf(f, "%i\n", 4*A*B);
    fclose(f);
}

int main(void) {
    read();
    solve();
    newdir();
    solve();
    newdir();
    solve();
    write();
}
