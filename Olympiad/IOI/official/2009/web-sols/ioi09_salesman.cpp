#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;

vector<pi> sales[500005];
vector<int> dpl[500005], dpr[500005];

int d,u,t;

struct rmq{
    int tree[1050000], lim;
    void init(){
        lim = (1<<19);
        for(int i=0; i<2*lim; i++){
            tree[i] = -2e9;
        }
    }
    void add(int x, int v){
        x += lim;
        tree[x] = max(tree[x],v);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int r = -2e9;
        while(s < e){
            if(s%2 == 1) r = max(r,tree[s++]);
            if(e%2 == 0) r = max(r,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r = max(r,tree[s]);
        return r;
    }
}rmq1, rmq2;

void input(){
    rmq1.init();
    rmq2.init();
    int n,s;
    scanf("%d %d %d %d",&n,&d,&u,&s);
    for (int i=1; i<=n; i++) {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        t = max(t,x);
        sales[x].push_back(pi(y,z));
    }
    sales[0].push_back(pi(s,0));
    sales[t+1].push_back(pi(s,0));
    t++;
    for (int i=0; i<=t; i++) {
        sort(sales[i].begin(),sales[i].end());
        dpl[i].resize(sales[i].size());
        dpr[i].resize(sales[i].size());
    }
}

int get_dpl(int i, int j){
    int r = -2e9;
    if(j) r = dpl[i][j-1] - u * (sales[i][j].first - sales[i][j-1].first);
    r = max(r,rmq1.q(sales[i][j].first,(1<<19) - 1) + sales[i][j].first * d);
    r = max(r,rmq2.q(0,sales[i][j].first-1) - sales[i][j].first * u);
    return r + sales[i][j].second;
}

int get_dpr(int i, int j){
    int r = -2e9;
    if(j != sales[i].size() - 1) r = dpr[i][j+1] - d * (sales[i][j+1].first - sales[i][j].first);
    r = max(r,rmq1.q(sales[i][j].first,(1<<19) - 1) + sales[i][j].first * d);
    r = max(r,rmq2.q(0,sales[i][j].first-1) - sales[i][j].first * u);
    return r + sales[i][j].second;
}

int main(){
    input();
    rmq1.add(sales[0][0].first,-d * sales[0][0].first);
    rmq2.add(sales[0][0].first,u * sales[0][0].first);
    for (int i=1; i<=t; i++) {
        for (int j=0; j<sales[i].size(); j++) {
            dpl[i][j] = get_dpl(i,j);
        }
        for (int j=(int)sales[i].size()-1; j>=0; j--) {
            dpr[i][j] = get_dpr(i,j);
        }
        for (int j=0; j<sales[i].size(); j++) {
            rmq1.add(sales[i][j].first,max(dpl[i][j],dpr[i][j]) - d * sales[i][j].first);
            rmq2.add(sales[i][j].first,max(dpl[i][j],dpr[i][j]) + u * sales[i][j].first);
        }
    }
    printf("%d",max(dpl[t][0],dpr[t][0]));
}
