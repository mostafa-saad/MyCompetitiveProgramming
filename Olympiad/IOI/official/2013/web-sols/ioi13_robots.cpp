#include <cstdio>
#include <algorithm>
#include <utility>
#include <queue>
#include "robots.h"
using namespace std;
typedef pair<int,int> pi;
 
int n,p,q;
 
pi a[1000005];
int b[50005], c[50005];
 
int t[1000005];
 
bool trial(int x){
    priority_queue<int> pq;
    int bp = 0;
    int cnt = 0;
    for (int i=0; i<n; i++) {
        while(bp < p && b[bp] <= a[i].first){
            int p = x;
            while (p && !pq.empty()) {
                pq.pop();
                p--;
                cnt++;
            }
            bp++;
        }
        pq.push(a[i].second);
    }
    while(bp < p){
        int p = x;
        while (p && !pq.empty()) {
            pq.pop();
            p--;
            cnt++;
        }
        bp++;
    }
    int sz = (int)pq.size();
    for (int i=sz-1; i>=0; i--) {
        t[i] = pq.top();
        pq.pop();
    }
    bp = 0;
    int que = 0;
    for (int i=0; i<sz; i++) {
        while(bp < q && c[bp] <= t[i]){
            int p = min(x,que);
            que -= p;
            cnt += p;
            bp++;
        }
        que++;
    }
    while (bp < q) {
        int p = min(x,que);
        que -= p;
        cnt += p;
        bp++;
    }
    return cnt == n;
}
 
int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]){
    p = A, q = B, n = T;
    for (int i=0; i<n; i++) {
        a[i] = pi(W[i],S[i]);
    }
    for (int i=0; i<p; i++) {
        b[i] = X[i];
    }
    for (int i=0; i<q; i++) {
        c[i] = Y[i];
    }
    sort(a,a+n);
    sort(b,b+p);
    sort(c,c+q);
    if(!trial(T)) return -1;
    int s = 0, e = T;
    while (s != e) {
        int m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    return s;
}