#include "towns.h"
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
  
int dp[150][150];
  
int dist(int s, int e){
    if(s == e) return 0;
    if(s > e) swap(s,e);
    if(~dp[s][e]) return dp[s][e];
    return dp[s][e] = getDistance(s, e);
}
  
vector<pi> v;
  
int p, q, val;
 
bool diff(int s, int e){
    return dist(0, p) + dist(s, e) == dist(s, p) + dist(0, e);
}
  
vector<pi> segments;
bool match[111];
 
int solve(int s, int e){
    segments.clear();
    int curp = s, cnt = 1;
    match[s] = 1;
    for(int i=s+1; i<=e; i++){
        if(diff(v[curp].second, v[i].second)){
            match[i] = 0;
            cnt--;
            if(cnt == 0){
                segments.push_back(pi(curp, i));
                curp = i+1;
            }
        }
        else{
            match[i] = 1;
            cnt++;
        }
    }
    if(curp == e + 1) return 0;
    segments.push_back(pi(curp, e));
    int ret = 0;
    for(auto &i : segments){
        if(!diff(v[curp].second, v[i.first].second)){
            ret += count(match + i.first, match + i.second + 1, true);
        }
        else{
            for(int j=i.first; j<=i.second; j++){
                if(match[j] == 0 && !diff(v[j].second, v[curp].second)){
                    ret++;
                }
            }
        }
    }
    return ret;
}
  
int hubDistance(int N, int sub) {
    v.clear();
    memset(dp,-1,sizeof(dp));
    p = -1, val = -1, q = -1;
    for(int i=1; i<N; i++){
        if(val < dist(0, i)){
            val = dist(0, i);
            p = i;
        }
    }
    val = -1;
    for(int i=0; i<N; i++){
        if(val < dist(p, i)){
            val = dist(p, i);
            q = i;
        }
    }
    int qdist = 0;
    for(int i=0; i<N; i++){
        int fl = dist(p, i) - dist(0, i) + dist(0, p);
        if(i == q) qdist = fl / 2;
        v.push_back(pi(fl / 2, i));
    }
    sort(v.begin(), v.end());
    while(!v.empty() && v.back().first > qdist) v.pop_back();
    int R = val;
    int hmin = 1e9;
    for(int i=0; i<v.size(); ){
        int e = i;
        while(e < v.size() && v[e].first == v[i].first) e++;
        int tmp = max(val - v[i].first, v[i].first);
        if(R > tmp){
            R = tmp;
            hmin = 1e9;
        }
        if(R == tmp){
            int hub = max(solve(i, e-1), max(i, N - e));
            hmin = min(hmin, hub);
        }
        i = e;
    }
    if(hmin > N / 2) return -R;
    return R;
}