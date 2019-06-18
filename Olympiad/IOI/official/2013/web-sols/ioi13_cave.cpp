#include "cave.h"
#include <cstdio>
#include <cstdlib>
 
int S[5005], D[5005];
int visited[5005];
 
void change(int s, int e){
    for(int i=s; i<=e; i++){
        if(!visited[i]) S[i] ^= 1;
    }
}
 
int find(int pos, int n){
    int s = 0, e = n-1;
    if(tryCombination(S) != pos) change(0,n-1);
    while (s != e) {
        int m = (s+e)/2;
        change(s,m);
        int t = tryCombination(S);
        change(s,m);
        if(pos != t) e = m;
        else s = m+1;
    }
    return s;
}
 
void exploreCave(int n){
    for (int i=0; i<n; i++) {
        int pos = find(i,n);
        D[pos] = i;
        visited[pos] = 1;
        S[pos] ^= 1;
    }
    answer(S,D);
}