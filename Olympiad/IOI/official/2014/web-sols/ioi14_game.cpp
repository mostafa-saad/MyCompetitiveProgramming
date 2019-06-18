int m;
int cnt[1505][1505];
 
struct disj{
    int pa[1505], size[1505];
    void init(int n) {
        for(int i=0; i<n; i++) pa[i] = i, size[i] = 1;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    void uni(int p, int q){
        pa[q] = p;
        size[p] += size[q];
    }
    int get_size(int x){
        return size[find(x)];
    }
}disj;
 
void initialize(int n){
    m = n;
    disj.init(n);
}
 
int hasEdge(int u, int v){
    u = disj.find(u);
    v = disj.find(v);
    cnt[u][v]++;
    cnt[v][u]++;
    if(cnt[u][v] == disj.get_size(u) * disj.get_size(v)){
        disj.pa[v] = u;
        disj.size[u] += disj.size[v];
        for (int i=0; i<m; i++) {
            cnt[u][i] += cnt[v][i];
            cnt[i][u] += cnt[i][v];
        }
        return 1;
    }
    return 0;
}