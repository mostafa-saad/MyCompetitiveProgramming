#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include "dreaming.h"
using namespace std;
typedef pair<int,int> pi;
vector<pi> graph[100005];
 
int visited[100005];
int visited2[100005];
 
pi get_longest(int *vis, int x){
    queue<int> q,d;
    q.push(x);
    d.push(0);
    int max = -1, maxv = -1;
    vis[x] = 1;
    while (!q.empty()) {
        int qf = q.front();
        int df = d.front();
        if(df > max){
            max = df;
            maxv = qf;
        }
        q.pop();
        d.pop();
        for (int i=0; i<graph[qf].size(); i++) {
            pi p = graph[qf][i];
            if(!vis[p.second]){
                vis[p.second] = 1;
                q.push(p.second);
                d.push(df + p.first);
            }
        }
    }
    return pi(max,maxv);
}
 
int ret1, len;
 
int dfs(int x, int d, int p, int l){
    if(x == d) return 1;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i].second == p) continue;
        if(dfs(graph[x][i].second,d,x,l + graph[x][i].first)){
            ret1 = min(ret1,max(len-l,l));
            return 1;
        }
    }
    return 0;
}
 
int get_dia(int x){
    int p = get_longest(visited2,x).second;
    return get_longest(visited,p).first;
}
 
int get_rad(int x){
    int p = get_longest(visited2,x).second;
    pi dia = get_longest(visited,p);
    int q = dia.second;
    len = dia.first;
    ret1 = len;
    dfs(p,q,-1,0);
    return ret1;
}
 
int travelTime(int N, int M, int L, int* A, int* B, int* T){
    for (int i=0; i<M; i++) {
        graph[A[i]].push_back(pi(T[i],B[i]));
        graph[B[i]].push_back(pi(T[i],A[i]));
    }
    int ret = 0;
    for (int i=0; i<N; i++) {
        if(!visited[i]) ret = max(ret,get_dia(i));
    }
    memset(visited,0,sizeof(visited));
    memset(visited2,0,sizeof(visited2));
    vector<int> rad;
    for (int i=0; i<N; i++) {
        if(!visited[i]) rad.push_back(get_rad(i));
    }
    sort(rad.begin(),rad.end());
    reverse(rad.begin(),rad.end());
    if(rad.size() > 1){
        ret = max(ret,L + rad[0] + rad[1]);
    }
    if(rad.size() > 2){
        ret = max(ret,2*L + rad[1] + rad[2]);
    }
    return ret;
}