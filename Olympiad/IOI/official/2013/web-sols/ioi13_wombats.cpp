#include "wombats.h"
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;
 
struct node{
    int adj[205][205];
};
 
int a[5000][200], b[5000][200];
int n, m;
int opt[205][205];
 
node merge(node& a, node& b){
    node c;
    memset(c.adj,0x3f,sizeof(c.adj));
    // opt(i-1, j) <= opt(i,j) <= opt(i,j+1)
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            if(c.adj[0][i] > a.adj[0][j] + b.adj[j][i]){
                c.adj[0][i] = a.adj[0][j] + b.adj[j][i];
                opt[0][i] = j;
            }
        }
    }
    for(int i=1; i<m; i++){
        opt[i][m] = m-1;
        for(int j=m-1; j>=0; j--){
            for(int k=opt[i-1][j]; k<=opt[i][j+1]; k++){
                if(c.adj[i][j] > a.adj[i][k] + b.adj[k][j]){
                    c.adj[i][j] = a.adj[i][k] + b.adj[k][j];
                    opt[i][j] = k;
                }
            }
        }
    }
    return c;
}
 
node tmp[11];
struct seg{
    node tree[1050];
    void remake(int s, int e, int p){
        for(int i=s; i<=e; i++){
            for(int j=0; j<m; j++){
                for(int k=0; k<m; k++){
                    tmp[i-s].adj[j][k] = b[i][k] + abs((j ? a[i][j-1] : 0) - (k ? a[i][k-1] : 0));
                }
            }
        }
        tree[p] = tmp[0];
        for(int i=1; i<=e-s; i++){
            tree[p] = merge(tree[p], tmp[i]);
        }
    }
    void add(int pos, int ps, int pe, int p){
        if(pe - ps <= 10){
            remake(ps, pe, p);
            return;
        }
        int pm = (ps + pe) / 2;
        if(pos <= pm) add(pos, ps, pm, 2*p);
        else add(pos, pm+1, pe, 2*p+1);
        tree[p] = merge(tree[2*p], tree[2*p+1]);
    }
    void init(int ps, int pe, int p){
        if(pe - ps <= 10){
            remake(ps, pe, p);
            return;
        }
        int pm = (ps + pe) / 2;
        init(ps, pm, 2*p);
        init(pm+1, pe, 2*p+1);
        tree[p] = merge(tree[2*p], tree[2*p+1]);
    }
}seg;
 
void init(int R, int C, int H[5000][200], int V[5000][200]) {
    n = R, m = C;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            a[i][j] = H[i][j] + (j ? a[i][j-1] : 0);
            b[i][j] = V[i][j];
        }
    }
    seg.init(0,n-1,1);
}
 
void changeH(int P, int Q, int W) {
    int diff = W - (a[P][Q] - (Q ? a[P][Q-1] : 0));
    for(int i=Q; i<m; i++){
        a[P][i] += diff;
    }
    seg.add(P,0,n-1,1);
}
 
void changeV(int P, int Q, int W) {
    b[P][Q] = W;
    seg.add(P,0,n-1,1);
}
 
int escape(int V1, int V2) {
    return seg.tree[1].adj[V1][V2];
}