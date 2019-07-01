/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Bezpieczenstwo minimalistyczne                   *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie weryfikujace                         *
 *                                                                       *
 *************************************************************************/

#define MAXN 500000
#define MAXM 3000000
#define ll long long
#define PLUS true
#define MINUS false

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct edge{
    int b;
    ll safe;
}_edge;

struct det{
    ll delta;
    bool sign;
};

ll pol[MAXN];
ll n, m;
vector <edge> ed[MAXN];

bool vis[MAXN];
det delta[MAXN];

ll pol_max, pol_min, pol_sum;

queue <int> BQ;

void set_delta(ll s, det da, det& db){
    //da + db = s => db = s - da
    db.sign = !da.sign;
    db.delta = s - da.delta;
}

int test_delta(ll s, det da, det db){
    if(da.delta + db.delta != s || da.sign == db.sign)return 1;
    return 0;
}

ll new_p(ll p_min, ll p_max, ll s, det da, det db){
    ll np;
    if(da.sign){
        //da.delta + db.delta + 2p = s
        //2p = s - da.delta - db.delta
        np = s - da.delta - db.delta;
    }
    else{
        //2p = da.delta + db.delta - s
        np = da.delta + db.delta - s;
    }
    if(np % 2)return -1;
    np /= 2;
    if(np < p_min || np > p_max)return -1;
    return np;
}

void set_new_p(ll &p_min, ll &p_max, det d, int v){
    ll npmin, npmax;
    if(d.sign){
        //0 <= d.delta + p <= pol[v]
        npmin = -d.delta;
        npmax = pol[v] - d.delta;
    }
    else{
        //0 <= d.delta - p <= pol[v]
        npmin = d.delta - pol[v];
        npmax = d.delta;
    }
    p_min = max(p_min, npmin);
    p_max = min(p_max, npmax);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        cin >> pol[i];
        pol_sum += pol[i];
    }
    for(int i = 0; i < m; ++i){
        int a, b;
        ll s;
        cin >> a >> b >> s;
        --a;
        --b;
        _edge.b = b;
        _edge.safe = s;
        ed[a].push_back(_edge);
        _edge.b = a;
        ed[b].push_back(_edge);
    }


    for(int i = 0; i < n; ++i){
        if(vis[i])continue;
        delta[i].delta = 0;
        delta[i].sign = PLUS;
        BQ.push(i);
        ll p_min = 0, p_max = pol[i];
        ll ar_v = 0, ar_p = 1;
        vis[i] = true;
        while(!BQ.empty()){
            int act = BQ.front();
            BQ.pop();
            for(size_t j = 0; j < ed[act].size(); ++j){
                int nxt = ed[act][j].b;
                if(vis[nxt]){
                    if(test_delta(ed[act][j].safe, delta[act], delta[nxt])){
                        p_min = p_max = new_p(p_min, p_max, ed[act][j].safe, delta[act], delta[nxt]);
                    }
                }
                else{
                    vis[nxt] = true;
                    set_delta(ed[act][j].safe, delta[act], delta[nxt]);
                    set_new_p(p_min, p_max, delta[nxt], nxt);
                    ar_v += delta[nxt].delta;
                    if(delta[nxt].sign)++ar_p;
                    else --ar_p;
                    BQ.push(nxt);
                }
            }
        }
        if(p_min > p_max || p_min < 0){
            cout << "NIE" << endl;
            return 0;
        }
        else{
            ll apol_min = ar_v + ar_p * p_min;
            ll apol_max = ar_v + ar_p * p_max;
            if(apol_min > apol_max)swap(apol_min, apol_max);
            pol_min += apol_min;
            pol_max += apol_max;
        }
    }
    cout << (pol_sum - pol_max) << " " << (pol_sum - pol_min) << endl;
    return 0;
}
