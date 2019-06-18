#include <cstdio>
#include <queue>
#include <deque>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<lint,int> pi;
 
int n;
vector<pi> graph[1000005];
bool is_cycle[1000005];
int vis[1000005];
 
int is_tree, deg[1000005];
 
vector<int> eval;
queue<int> q, p;

void bfs2(int x){
    q.push(x);
    vis[x] = 1;
    eval.push_back(x);
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        for(int i=0; i<graph[qf].size(); i++){
            pi t = graph[qf][i];
            if(!vis[t.second]){
                q.push(t.second);
                vis[t.second] = 1;
                eval.push_back(t.second);
            }
        }
    }
    for (int i=0; i<eval.size(); i++) {
        if(deg[eval[i]]==1){
            q.push(eval[i]);
        }
    }
    while (!q.empty()) {
        int qf = q.front();
        q.pop();
        deg[qf] = 0;
        for (int i=0; i<graph[qf].size(); i++){
            pi t = graph[qf][i];
            if(deg[t.second]){
                deg[t.second]--;
                if(deg[t.second] == 1){
                    q.push(t.second);
                }
            }
        }
    }
    for (int i=0; i<eval.size(); i++) {
        if(deg[eval[i]]){
            is_cycle[eval[i]] = 1;
            is_tree = 0;
        }
    }
}
 
lint dist[1000005];

pi bfs(int x){
    q.push(x);
    p.push(0);
    dist[x] = 0;
    pi ret(0ll,0);
    while (!q.empty()) {
        int qf = q.front();
        int pf = p.front();
        q.pop();
        p.pop();
        ret = max(ret,pi(dist[qf],qf));
        for (int i=0; i<graph[qf].size(); i++) {
            int pos = graph[qf][i].second;
            if(is_cycle[pos] || pos == pf) continue;
            q.push(pos);
            p.push(qf);
            dist[pos] = dist[qf] + graph[qf][i].first;
        }
    }
    return ret;
}
 
lint largest[1000005];
int between[1000005];
int forward_pos[1000005];
pi dq[1000005];
int st, ed;

long long solve(int x){
    lint ret = 0;
    int pos = 0, par = 0;
    for (int i=0; i<eval.size(); i++) {
        if(is_cycle[eval[i]]){
            pos = eval[i];
            break;
        }
    }
    int started_position = pos;
    do{
        is_cycle[pos] = 0;
        pi longest_path = bfs(pos);
        ret = max(ret,bfs(longest_path.second).first);
        largest[pos] = longest_path.first;
        is_cycle[pos] = 1;
        for (int i=0; i<graph[pos].size(); i++) {
            int new_pos = graph[pos][i].second;
            if(is_cycle[new_pos] && new_pos != par){
                between[pos] = graph[pos][i].first;
                forward_pos[pos] = new_pos;
                par = pos;
                pos = new_pos;
                break;
            }
        }
    }while(pos != started_position);
     
    pos = started_position;
    st = ed = 0;
     
    lint cval = between[pos];
    int pos2 = forward_pos[pos];
    lint erase = 0;
    while(pos2 != pos){
        while (st < ed && dq[ed-1].first < cval + largest[pos2]) {
        	ed--;
        }
        dq[ed++] = pi(cval + largest[pos2],pos2);
        cval += between[pos2];
        pos2 = forward_pos[pos2];
    }
     
    do{
        if(dq[st].second == pos) st++;
        ret = max(ret,largest[pos] + dq[st].first - erase);
        while (st < ed && dq[ed-1].first < cval + largest[pos]) {
        	ed--;
        }
        dq[ed++] = pi(cval + largest[pos],pos);
        cval += between[pos];
        erase += between[pos];
        pos = forward_pos[pos];
    }while(pos != started_position);
     
    return ret;
}
 
int l[1000005], d[1000005];
 
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&l[i],&d[i]);
    }
    for (int i=1; i<=n; i++) {
        if(d[i] == -1) continue;
        if(l[l[i]] == i){
            d[i] = max(d[i],d[l[i]]);
            d[l[i]] = -1;
            graph[i].push_back(pi(d[i],l[i]));
            graph[l[i]].push_back(pi(d[i],i));
        }
        else{
            graph[i].push_back(pi(d[i],l[i]));
            graph[l[i]].push_back(pi(d[i],i));
        }
        deg[i]++;
        deg[l[i]]++;
    }
    long long ret = 0;
    for (int i=1; i<=n; i++) {
        if(!vis[i]){
            eval.clear();
            is_tree = 1;
            bfs2(i);
            if(!is_tree){
                ret += solve(i);
            }
            else{
                ret += bfs(bfs(i).second).first;
            }
        }
    }
    printf("%lld",ret);
}
