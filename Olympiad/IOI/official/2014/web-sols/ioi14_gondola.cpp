#include <cstdio>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include "gondola.h"
 
using namespace std;
typedef pair<int,int> pi;
 
int valid(int n, int inputSeq[]){
    set<int> s;
    for (int i=0; i<n; i++) {
        if(s.find(inputSeq[i]) != s.end()) return 0;
        s.insert(inputSeq[i]);
    }
    int piv = -1;
    for (int i=0; i<n; i++) {
        if(inputSeq[i] <= n){
            if(piv == -1){
                piv = i;
            }
            else{
                int res = i + (inputSeq[piv] - piv) + n;
                res %= n;
                if(res == 0) res = n;
                if(inputSeq[i] != res) return 0;
            }
        }
    }
    return 1;
}
 
priority_queue<pi,vector<pi>,greater<pi> > pq, pq2;
 
int replacement(int n, int gondolaSeq[], int replacementSeq[]){
    int piv = 0, piv2 = n+1, piv3 = 0;
    for (int i=0; i<n; i++) {
        if(gondolaSeq[i] <= n){
            piv = gondolaSeq[i] - i - 1+ n;
            piv %= n;
        }
    }
    int newSeq[100005] = {};
    for (int i=0; i<n; i++) {
        newSeq[i] = gondolaSeq[(i + n - piv)%n];
        if(newSeq[i] > n) pq.push(pi(newSeq[i],i+1));
    }
    while (!pq.empty()) {
        pi x = pq.top();
        pq.pop();
        replacementSeq[piv3++] = x.second;
        for (int i=piv2; i<x.first; i++) {
            replacementSeq[piv3++] = i;
        }
        piv2 = x.first + 1;
    }
    return piv3;
}
 
long long pow(int x, int time){
    long long res = 1, piv = x, mod = 1e9 + 9;
    while (time) {
        if(time&1) res *= piv;
        piv *= piv;
        res %= mod;
        piv %= mod;
        time >>= 1;
    }
    return res;
}
 
int newSeq[100005];
int countReplacement(int n, int inputSeq[]){
    if(!valid(n,inputSeq)) return 0;
    int piv = 0, piv2 = n, cnt = 0;
    long long res = 1;
    for (int i=0; i<n; i++) {
        if(inputSeq[i] > n) newSeq[piv++] = inputSeq[i];
    }
    if(piv == n) res = piv;
    if(piv == 0) return 1;
    cnt = piv;
    sort(newSeq,newSeq+piv);
    for (int i=0; i<piv; i++) {
        res *= pow(cnt,newSeq[i] - piv2 - 1);
        piv2 = newSeq[i];
        cnt--;
        res %= 1000000009;
    }
    return (int)res;
}