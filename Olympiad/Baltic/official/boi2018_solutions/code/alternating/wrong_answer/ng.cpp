// Picks a random "splitting point" and solves the problem greedily as if it
// was an interval and not a circle. Arcs that are not needed for the greedy are
// assigned randomly. This is repeated 20 times with different splitting points.

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;

const ll big = 1000000007;
const ll mod = 998244353;

ll n,m,k;

struct arc{
    int l,r,el;
};

set<int> S1;
set<int> S2;
bool B1[100001] = {0};
bool B2[100001] = {0};
vector<arc> arcs;
vi ind;

bool solved = 0;
vector<bool> solution;

void reset(){
    for(int c1 = 0; c1 < m; c1++){
        arcs[c1].el = 0;
    }
    for(int c1 = 0; c1 < n; c1++){
        S1.insert(c1);
        S2.insert(c1);
        B1[c1] = 0;
        B2[c1] = 0;
    }
}

void check(){
    int bad = 0;
    for(int c1 = 0; c1 < n ;c1++){
        bad += !B1[c1]+!B2[c1];
    }
    if(bad > 0)return;
    solved = 1;
    solution.clear();
    for(int c1 = 0; c1 < m; c1++){
        solution.push_back(arcs[c1].el-1);
    }
}

bool inside(int i, int x){
    if(arcs[i].l > arcs[i].r){
        return x >= arcs[i].l || x <= arcs[i].r;
    }
    else{
        return x >= arcs[i].l && x <= arcs[i].r;
    }
}

vi segs;
void assign_segments(int a, int b, int to){
    set<int>::iterator it;
    set<int>::iterator stop;
    if(to == 1){
        it = S1.lower_bound(a);
        stop = S1.end();
    }
    else{
        it = S2.lower_bound(a);
        stop = S2.end();
    }
    segs.clear();
    for(;it != stop;++it){
        int x = *it;
        if(x > b)break;
        segs.push_back(x);
    }

    for(int c1 = 0; c1 < sz(segs); c1++){
        if(to == 1){
            S1.erase(segs[c1]);
            B1[segs[c1]] = 1;
        }
        else{
            S2.erase(segs[c1]);
            B2[segs[c1]] = 1;
        }
    }
}

void assign_arc(int i, int to){
    arcs[i].el = to;
    int a = arcs[i].l;
    int b = arcs[i].r;

    if(a > b){
        assign_segments(0,b,to);
        assign_segments(a,n,to);
    }
    else{
        assign_segments(a,b,to);
    }
}

int split;
bool comp(int i, int j){
    return (arcs[i].l-split+n)%n < (arcs[j].l-split+n)%n;
}

void solve(int x){
    split = x;
    sort(all(ind),comp);
    reset();
    int p = 0;
    for(int c2 = 0; c2 < n; c2++){
        int c1 = (split+c2)%n;
        if(p >= m)break;
        if(arcs[ind[p]].l > c1)continue;
        bool fail = 0;
        while(!inside(ind[p],c1)){
            p++;
            if(p >= m){
                fail = 1;
                break;
            }
            if(arcs[ind[p]].l > c1){
                fail = 1;
                break;
            }
        }
        if(fail)continue;

        if(!B1[c1]){
            assign_arc(ind[p],1);
            p++;
            if(p >= m)continue;
            if(!inside(ind[p],c1))continue;
        }

        if(!B2[c1]){
            assign_arc(ind[p],2);
            p++;
        }
    }

    for(int c1 = 0; c1 < m; c1++){
        if(arcs[c1].el == 0)assign_arc(c1,rand()%2);
    }
    check();
}

//For debugging
ll CS[100001][2] = {0};
bool check_solution(){

    for(int c1 = 0; c1 < m; c1++){
        int l,r,a;
        l = arcs[c1].l;
        r = arcs[c1].r;
        a = solution[c1];
        if(l <= r){
            CS[l][a]++;
            CS[r+1][a]--;
        }
        else{
            CS[0][a]++;
            CS[r+1][a]--;
            CS[l][a]++;
        }
    }

    for(int c1 = 0; c1 < n; c1++){
        for(int c2 = 0; c2 < 2; c2++){
            if(c1 > 0)CS[c1][c2] += CS[c1-1][c2];
            if(CS[c1][c2] == 0)return 0;
        }
    }
    return 1;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("autput.txt","w",stdout);
    ll a,b,c,e;

    cin >> n >> m;
    for(int c1 = 0; c1 < m; c1++){
        cin >> a >> b;
        arcs.push_back({a-1,b-1,0});
        ind.push_back(c1);
    }

    int lim = 20;

    solve(0);

    for(int c1 = 0; c1 < lim ;c1++){
        solve(rand()%n);
        if(solved)break;
    }

    if(!solved){
        cout << "impossible\n";
    }
    else{
        assert(check_solution());
        for(int c1 = 0; c1 < m; c1++){
            cout << solution[c1];
        }
    }

    return 0;
}
