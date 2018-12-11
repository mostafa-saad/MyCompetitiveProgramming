#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "koala.h"

#define FO(i,a,b) for (int i = (a); i < (b); i++)
#define true 1
#define false 0

int minValue(int N, int W) {
    int B[N+5];
    int R[N+5];
    FO(i,0,N) B[i] = 0;
    B[0] = 1;
    playRound(B, R);
    FO (i,0,N) {
        if (R[i] <= B[i]) {
            return i;
        }
    }
    assert(0);
}

int maxValue(int N, int W) {
    int B[N+5];
    int R[N+5];
    int setSize = N;
    int inSet[N+5];
    FO (i,0,N) inSet[i] = 1;
    while (setSize > 1) {
        FO (i,0,N) {
            if (inSet[i]) {
                B[i] = W/setSize;
            } else {
                B[i] = 0;
            }
        }
        playRound(B,R);
        setSize = 0;
        FO (i,0,N) {
            if (R[i] > B[i] && inSet[i]) {
                inSet[i] = true;
                setSize++;
            } else {
                inSet[i] = false;
            }
        }
    }
    FO (i,0,N) {
        if (inSet[i]) return i;
    }
}

int greaterValue(int N, int W) {
    int B[N+5], R[N+5];
    int vals[4] = {1,3,6,8};
    int lo = 0;
    int hi = 3;
    int mid;
    while (lo <= hi) {
        mid = (lo+hi)/2;
        FO (i,0,N) B[i] = 0;
        B[0] = B[1] = vals[mid];
        playRound(B,R);
        if (R[0] > B[0] && R[1] > B[1]) {
            lo = mid+1;
        } else if (R[0] <= B[0] && R[1] <= B[1]) {
            hi = mid-1;
        } else if (R[0] > B[0]) {
            return 0;
        } else {
            return 1;
        }
    }
    assert(false);
}

int *sortRange(int *, int);
void allValues(int N, int W, int *P) {
    if (W == 2*N) {
        int startV[105];
        FO (i,0,N) startV[i] = i;
        int *finalV = sortRange(startV, N);
        FO (i,0,N) {
            P[finalV[i]] = N-i;
        }
    } else {
        // TODO: Implement Subtask 5 solution here.
        // You may leave this block unmodified if you are not attempting this
        // subtask.
    }
}

int B[105], R[105];

int *sortRange(int *A, int nA) {
    int *cpA = malloc(sizeof(int)*nA);
    memcpy (cpA, A, nA*sizeof(int));
    if (nA == 1) return cpA;
    int ofC[nA/2+1];
    int osC[nA/2+1];
    int ofN = 0;
    int osN = 0;
    FO (i,0,nA) {
        if (i%2) {
            osC[osN++] = A[i];
        } else {
            ofC[ofN++] = A[i];
        }
    }
    int *f = sortRange(ofC, ofN);
    int *s = sortRange(osC, osN);
    int fN = 0;
    int sN = 0;
    int aN = 0;
    while (fN < ofN || sN < osN) {
        if (fN == ofN) {
            cpA[aN++] = s[sN++];
        } else if (sN == osN) {
            cpA[aN++] = f[fN++];
        } else {
            FO (i,0,100) B[i] = 0;
            B[f[fN]] = B[s[sN]] = 100;
            playRound(B,R);
            if (R[f[fN]] > B[f[fN]]) {
                cpA[aN++] = f[fN++];
            } else {
                cpA[aN++] = s[sN++];
            }
        }
    }
    return cpA;
}
