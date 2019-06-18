#include "garden.h"
#include "gardenlib.h"
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
queue<int> q, p, d;
vector<int> ls;
 
vector<pi> graph[150005];
vector<int> graph1[300005];
 
int nxt[300005];
int low[150005];
int deg[300005];
int ped[300005];
 
bool vis[300005];
bool ans[150005];
 
void make_graph(int N, int M, int R[][2]){
    for (int i=0; i<M; i++) {
        for (int j=0; j<2; j++) {
            low[R[i][j]] = min(low[R[i][j]],i);
        }
        graph[R[i][0]].push_back(pi(R[i][1],i));
        graph[R[i][1]].push_back(pi(R[i][0],i));
    }
    for (int i=0; i<N; i++) {
        if(low[graph[i][0].first] == graph[i][0].second){
            nxt[2*i] = graph[i][0].first * 2 + 1;
        }
        else{
            nxt[2*i] = graph[i][0].first * 2;
        }
        if(graph[i].size() == 1){
            nxt[2*i+1] = nxt[2*i];
        }
        else{
            if(low[graph[i][1].first] == graph[i][1].second){
                nxt[2*i+1] = graph[i][1].first * 2 + 1;
            }
            else{
                nxt[2*i+1] = graph[i][1].first * 2;
            }
        }
    }
}
 
int dist0[150005], dist1[150005], peri0[150005], peri1[150005];
 
void solve(int x, int *dist, int *peri){
    memset(vis,0,sizeof(vis));
    q.push(x);
    p.push(-1);
    d.push(0);
    vis[x] = 1;
    while (!q.empty()) {
        int qf = q.front();
        int pf = p.front();
        int df = d.front();
        q.pop(), p.pop(), d.pop();
        pf = max(pf, ped[qf]);
        if(qf % 2 == 0){
            dist[qf/2] = df;
            peri[qf/2] = pf;
        }
        for (auto &i : graph1[qf]){
            if(!vis[i]){
                vis[i] = 1;
                q.push(i);
                p.push(pf);
                d.push(df + 1);
            }
        }
    }
}
 
void count_routes(int N, int M, int P, int R[][2], int Q, int G[])
{
    memset(ped,-1,sizeof(ped));
    memset(dist0,-1,sizeof(dist0));
    memset(dist1,-1,sizeof(dist1));
    memset(peri0,-1,sizeof(peri0));
    memset(peri1,-1,sizeof(peri1));
    memset(low,0x3f,sizeof(low));
    make_graph(N,M,R);
    for (int i=0; i<2*N; i++) {
        deg[i]++;
        deg[nxt[i]]++;
    }
    for (int i=0; i<2*N; i++) {
        if(deg[i] == 1){
            q.push(i);
        }
    }
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        deg[qf]--;
        deg[nxt[qf]]--;
        if(deg[nxt[qf]] == 1){
            q.push(nxt[qf]);
        }
    }
    for (int i=0; i<2*N; i++) {
        graph1[nxt[i]].push_back(i);
        if(deg[i]){
            int pos = i;
            ls.clear();
            while (deg[pos]) {
                deg[pos] = 0;
                ls.push_back(pos);
                pos = nxt[pos];
            }
            for (auto &i : ls){
                ped[i] = (int)ls.size();
            }
        }
    }
    solve(2*P,dist0,peri0);
    solve(2*P+1,dist1,peri1);
    for (int i=0; i<Q; i++) {
        int cnt = 0;
        for (int j=0; j<N; j++) {
            if(dist0[j] != -1){
                if(peri0[j] == -1){
                    if(dist0[j] == G[i]){
                        cnt++; continue;
                    }
                }
                else{
                    if(dist0[j] <= G[i] && (G[i] - dist0[j]) % peri0[j] == 0){
                        cnt++; continue;
                    }
                }
            }
            if(dist1[j] != -1){
                if(peri1[j] == -1){
                    if(dist1[j] == G[i]){
                        cnt++; continue;
                    }
                }
                else{
                    if(dist1[j] <= G[i] && (G[i] - dist1[j]) %peri1[j] == 0){
                        cnt++; continue;
                    }
                }
            }
        }
        answer(cnt);
    }
}