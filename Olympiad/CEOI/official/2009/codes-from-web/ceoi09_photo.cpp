#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, s;
pi a[105];
map<int, int> mp;
 
int pos[200005];
int dp[105][105][105];
 
int getH(int p, int q){
    return s / max(1,a[q].first - a[p].first);
}
 
int f(int s, int e, int x){
    if(s > e) return 0;
    if(~dp[s][e][pos[x]]) return dp[s][e][pos[x]];
    if(a[s].second <= x) return dp[s][e][pos[x]] = f(s+1, e, x);
    if(a[e].second <= x) return dp[s][e][pos[x]] = f(s, e-1, x);
    int ret = 1e9;
    if(pos[getH(s, e)] > pos[x]){
        ret = f(s, e, getH(s, e)) + 1;
    }
    for(int i=s; i<e; i++){
        ret = min(ret, f(s, i, x) + f(i+1, e, x));
    }
    //printf("%d %d %d = %d\n",s,e,x,ret);
    return dp[s][e][pos[x]] = ret;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d",&n,&s);
    for(int i=1; i<=n; i++){
        int a, b;
        scanf("%d %d",&a,&b);
        mp[a] = max(mp[a], b);
    }
    int p = 0;
    map<int, int> ::iterator it = mp.begin();
    while(it != mp.end()){
        a[++p] = *it;
        pos[it->second] = 1;
        it++;
    }
    for(int i=1; i<=s; i++){
        pos[i] += pos[i-1];
    }
    printf("%d",f(1, p, 0));
}