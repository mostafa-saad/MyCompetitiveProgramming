#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;

vector<int> graph[1000005];
int n, opt, a[1000005];
lint res = 1e18, sum;

lint f(int x, int pa){
    lint mv = 0;
    lint s = 0;
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        lint t = f(graph[x][i],x);
        s += t;
        mv = max(mv,t);
    }
    s += a[x];
    mv = max(mv,sum-s);
    if(res > mv){
        res = mv;
        opt = x;
    }
    return s;
}

int LocateCentre(int N, int pp[], int S[], int D[]) {
    n = N;
    for(int i=0; i<n; i++){
    	a[i] = pp[i];
    	sum += a[i];
    }
    for(int i=0; i<n-1; i++){
    	graph[S[i]].push_back(D[i]);
    	graph[D[i]].push_back(S[i]);
    }
    f(0, -1);
    return opt;
}