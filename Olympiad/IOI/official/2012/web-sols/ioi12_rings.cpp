#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
    
vector<int> graph[1000005];
int n;
int deg[1000005];
int focus = -1;
bool deadend = 0;
   
int v[4];
int bad[4];
   
struct disj{
    int pa[1000005];
    int deg2[1000005];
    int deg3[1000005];
    int degx[1000005];
    int size[1000005];
    int without;
   
    void init(int n, int w){
        without = w;
        for(int i=0; i<=n; i++) pa[i] = i, size[i] = 1;
    }
    
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    
    void uni(int p, int q){
        if(p == without || q == without) return;
        degx[p]++;
        int px = find(p), qx = find(q);
        if(degx[p] == 2){
            deg2[px]++;
        }
        if(degx[p] == 3){
            deg3[px]++;
        }
        degx[q]++;
        if(degx[q] == 2){
            deg2[qx]++;
        }
        if(degx[q] == 3){
            deg3[qx]++;
        }
        p = px, q = qx;
        if(p == q) return;
        pa[q] = p;
        deg2[p] += deg2[q];
        deg3[p] += deg3[q];
        size[p] += size[q];
    }
   
    bool ckBad(int x){
        x = find(x);
        return (deg3[x] || (deg2[x] == size[x]));
    }
}disj, wotree[4];
    
void Init(int N){
    n = N;
    memset(v,-1,sizeof(v));
    disj.init(n,-1);
}
   
void Link(int A, int B){
    deg[A]++, deg[B]++;
    if(deg[A] <= deg[B]){
        swap(A,B);
    }
    if(deg[A] == 3 && v[0] == -1){
        v[0] = A;
        v[1] = B;
        v[2] = graph[A][0];
        v[3] = graph[A][1];
        for(int i=0; i<4; i++){
            wotree[i].init(n,v[i]);
            for(int j=0; j<n; j++){
                for(auto &k : graph[j]){
                    if(j < k) wotree[i].uni(j,k);
                }
                if(j != v[i] && wotree[i].ckBad(j)){
                    bad[i] = 1;
                    break;
                }
            }
        }
    }
    graph[A].push_back(B);
    graph[B].push_back(A);
    disj.uni(A,B);
    if(v[0] == -1){
        if(disj.ckBad(A)){
            if(focus == -1){
                focus = A;
            }
            else if(disj.find(focus) != disj.find(A)){
                deadend = 1;
            }
        }
    }
    else{
        for(int i=0; i<4; i++){
            if(bad[i]) continue;
            wotree[i].uni(A,B);
            if(wotree[i].ckBad(A)){
                bad[i] = 1;
            }
        }
    }
}
   
    
int CountCritical(){
    if(deadend == 1) return 0;
    if(disj.without != -1) return 1;
    else if(v[0] != -1){
        int cnt = 0;
        for(int i=0; i<4; i++){
            if(!bad[i]) cnt++;
        }
        return cnt;
    }
    else{
        if(focus == -1) return n;
        return disj.size[disj.find(focus)];
    }
}