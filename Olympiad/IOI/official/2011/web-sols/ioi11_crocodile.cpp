#include <vector>
#include <queue>
#include <utility>
#include "crocodile.h"
using namespace std;
typedef pair<int,int> pi;
 
int v0[100005], v1[100005];
priority_queue<pi,vector<pi>,greater<pi> > pq;
vector<pi> graph[100005];
 
int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]){
    for (int i=0; i<M; i++) {
        graph[R[i][0]].push_back(pi(L[i],R[i][1]));
        graph[R[i][1]].push_back(pi(L[i],R[i][0]));
    }
    for (int i=0; i<K; i++) {
        v0[P[i]] = 1;
        pq.push(pi(0,P[i]));
    }
    while (!pq.empty()) {
        pi x = pq.top();
        pq.pop();
        if(v0[x.second] == 0){
            v0[x.second] = 1;
            continue;
        }
        if(v1[x.second]) continue;
        v1[x.second] = 1;
        if(x.second == 0) return x.first;
        for (int i=0; i<graph[x.second].size(); i++) {
            pi t = graph[x.second][i];
            if(v1[t.second]) continue;
            pq.push(pi(t.first + x.first,t.second));
        }
    }
    return -1;
}