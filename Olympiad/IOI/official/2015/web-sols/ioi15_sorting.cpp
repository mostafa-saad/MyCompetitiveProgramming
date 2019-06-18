#include "sorting.h"
#include <algorithm>
using namespace std;
 
int *s, *x, *y, *p, *q, n;
int obj[200005], cur[200005];
int orev[200005], crev[200005];
 
bool trial(int t){
    for(int i=0; i<n; i++){
        obj[i] = i;
    }
    for(int i=t-1; i>=0; i--){
        swap(obj[x[i]], obj[y[i]]);
    }
    for(int i=0; i<n; i++){
        orev[obj[i]] = i;
        cur[i] = s[i];
        crev[cur[i]] = i;
    }
    int pt = 0;
    for(int i=0; i<t; i++){
        swap(obj[x[i]], obj[y[i]]);
        swap(cur[x[i]], cur[y[i]]);
        crev[cur[x[i]]] = x[i];
        orev[obj[x[i]]] = x[i];
        crev[cur[y[i]]] = y[i];
        orev[obj[y[i]]] = y[i];
        while(pt < n && crev[pt] == orev[pt]) pt++;
        if(pt == n){
            p[i] = q[i] = 0;
            continue;
        }
        int p1 = crev[pt];
        int p2 = orev[pt];
        p[i] = p1;
        q[i] = p2;
        swap(cur[p1], cur[p2]);
        crev[cur[p1]] = p1;
        crev[cur[p2]] = p2;
    }
    while(pt < n && crev[pt] == orev[pt]) pt++;
    return (pt == n);
}
 
int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    n = N, s = S, x = X, y = Y, p = P, q = Q;
    int s = 0, e = M;
    while(s != e){
        int m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    trial(s);
    return s;
}