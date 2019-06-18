#include "grader.h"
#include "encoder.h"
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
 
int dist[36][1005];
vector<int> graph[1005];
 
bool vis[1005];
int par[1005];
queue<int> q;
 
void bfs(int* dist, int st){
    memset(vis,0,sizeof(vis));
    q.push(st);
    vis[st] = 1;
    while(!q.empty()){
        int qf = q.front();
        q.pop();
        for(auto &i : graph[qf]){
            if(vis[i]) continue;
            vis[i] = 1;
            dist[i] = dist[qf] + 1;
            par[i] = qf;
            q.push(i);
        }
    }
}
 
void encode(int nv, int nh, int ne, int *v1, int *v2){
    for(int i=0; i<ne; i++){
        graph[v1[i]].push_back(v2[i]);
        graph[v2[i]].push_back(v1[i]);
    }
    for(int i=nh-1; i>=0; i--){
        bfs(dist[i],i);
    }
    for(int i=1; i<nv; i++){
        for(int j=0; j<10; j++){
            encode_bit((par[i] >> j) & 1);
        }
    }
    for(int i=0; i<nh; i++){
        for(int j=1; j<nv; j+=5){
            int ret = 0;
            for(int k=0; k<5; k++){
                int dx = dist[i][j+k] - dist[i][par[j+k]] + 1;
                if(j+k >= nv) dx = 0;
                ret = ret * 3 + dx;
            }
            for(int i=0; i<8; i++){
                encode_bit((ret >> i) & 1);
            }
        }
    }
}