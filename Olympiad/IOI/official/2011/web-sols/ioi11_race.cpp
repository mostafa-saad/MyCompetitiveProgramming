#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
typedef pair<int,int> pi;
 
vector<pi> graph[200005];
 
int ret = 1e9;
int size[200005], maxtree[200005];
int kill[200005];
int k;
 
vector<int> new_vis;
 
int dfs(int p, int pa){
    if(kill[p]) return 0;
    new_vis.push_back(p);
    int cs = 1;
    int maxv = 0;
    for (int i=0; i<graph[p].size(); i++) {
        if(graph[p][i].second == pa) continue;
        int t = dfs(graph[p][i].second,p);
        maxv = max(t,maxv);
        cs += t;
    }
    maxtree[p] = maxv;
    return size[p] = cs;
}
 
int get_mid(int p){
    for (int i=0; i<new_vis.size(); i++) {
        size[new_vis[i]] = 0;
        maxtree[new_vis[i]] = 0;
    }
    new_vis.clear();
    int full = dfs(p,-1);
    int mid_pos = 0, mid_res =1e9;
    for (int i=0; i<new_vis.size(); i++) {
        maxtree[new_vis[i]] = max(maxtree[new_vis[i]],full - size[new_vis[i]]);
        if(mid_res > maxtree[new_vis[i]]){
            mid_pos = new_vis[i];
            mid_res = maxtree[mid_pos];
        }
    }
    return mid_pos;
}
 
int *v;
int *stamp;
int timestamp;
 
void solve(int p){
    ++timestamp;
    int mid = get_mid(p);
    kill[mid] = 1;
    v[0] = 0;
    stamp[0] = timestamp;
    for (int i=0; i<graph[mid].size(); i++) {
        if(kill[graph[mid][i].second]) continue;
        queue<int> q,d,p,l;
        vector<int> cd1, cd2;
        if(graph[mid][i].first > k) continue;
        q.push(graph[mid][i].second);
        d.push(graph[mid][i].first);
        l.push(1);
        p.push(mid);
        while (!q.empty()) {
            int qf = q.front();
            int df = d.front();
            int pf = p.front();
            int lf = l.front();
            cd1.push_back(df);
            cd2.push_back(lf);
            if(stamp[k-df] == timestamp) ret = min(v[k-df] + lf,ret);
            q.pop();
            d.pop();
            p.pop();
            l.pop();
            for (int i=0; i<graph[qf].size(); i++) {
                int pos = graph[qf][i].second;
                if(kill[pos] || pos == pf) continue;
                if(df + graph[qf][i].first > k) continue;
                q.push(pos);
                d.push(df + graph[qf][i].first);
                p.push(qf);
                l.push(lf + 1);
            }
        }
        for (int i=0; i<cd1.size(); i++) {
            if(stamp[cd1[i]] != timestamp){
                v[cd1[i]] = cd2[i];
                stamp[cd1[i]] = timestamp;
            }
            else v[cd1[i]] = min(v[cd1[i]],cd2[i]);
        }
    }
    for (int i=0; i<graph[mid].size(); i++) {
        if(kill[graph[mid][i].second]) continue;
        solve(graph[mid][i].second);
    }
}
 
int best_path(int N, int K, int H[][2], int L[]){
    for (int i=0; i<N-1; i++) {
        graph[H[i][0]].push_back(pi(L[i],H[i][1]));
        graph[H[i][1]].push_back(pi(L[i],H[i][0]));
    }
    v = (int*)calloc(K+1,sizeof(int));
    stamp = (int*)calloc(K+1,sizeof(int));
    k = K;
    solve(0);
    if(ret > 1e8) return -1;
    return ret;
}