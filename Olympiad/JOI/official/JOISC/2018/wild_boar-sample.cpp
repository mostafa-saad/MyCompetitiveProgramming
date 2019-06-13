#include <bits/stdc++.h>

using namespace std;

using ll = long long int;
using pl = tuple<ll, ll>;
using tl = tuple<ll, ll, ll>;

const ll INFLL = 1e18;

ll N, M, T, L;
vector<tl> G[2010]; // (to, cost, id)

vector<tl> edges; // (from, to, cost)

vector<ll> eds[4010];

ll x[200010];
ll p[200010];
ll q[200010];

vector<tl> sp[2010][2010]; // (cost, next_start, prev_end)
vector<tl> node[400010]; // (cost, next_start, prev_end)

ll size = 1;

vector<tl> calc_top_five(vector<tl> ps){
  vector<tl> res(5, make_tuple(INFLL, INFLL, INFLL));
  int n = ps.size();
  for(int i = 0; i < n; i++){
    if(get<0>(ps[i]) < get<0>(res[0])){
      res[0] = ps[i];
    }
  }
  for(int i = 0; i < n; i++){
    if(get<1>(ps[i]) != get<1>(res[0]) && get<0>(ps[i])< get<0>(res[1])){
      res[1] = ps[i];
    }
    if(get<2>(ps[i]) != get<2>(res[0]) && get<0>(ps[i])< get<0>(res[3])){
      res[3] = ps[i];
    }
  }
  for(int i = 0; i < n; i++){
    if(get<1>(ps[i]) != get<1>(res[0]) && get<2>(ps[i]) != get<2>(res[1]) && get<0>(ps[i]) < get<0>(res[2])){
      res[2] = ps[i];
    }
    if(get<2>(ps[i]) != get<2>(res[0]) && get<1>(ps[i]) != get<1>(res[3]) && get<0>(ps[i]) < get<0>(res[4])){
      res[4] = ps[i];
    }
  }
  return res;
}

vector<tl> merge(vector<tl> s, vector<tl> t){
  vector<tl> ps(0);
  for(int i = 0; i < (int)s.size(); i++){
    for(int j = 0; j < (int)t.size(); j++){
      if(get<2>(s[i]) != get<1>(t[j])){
        ps.emplace_back(get<0>(s[i]) + get<0>(t[j]), get<1>(s[i]), get<2>(t[j]));
      }
    }
  }
  return calc_top_five(ps);
}

void init_segment_tree(ll k, ll l, ll r){
  if(r - l == 1){
    if(l < L-1){
      node[k] = sp[x[l]][x[l+1]];
    } else {
      node[k] = vector<tl>(5, make_tuple(INFLL, INFLL, INFLL));
    }
  } else {
    init_segment_tree(k*2+1, l, (l+r)/2);
    init_segment_tree(k*2+2, (l+r)/2, r);
    node[k] = merge(node[k*2+1], node[k*2+2]);
  }
}

void init_segment_tree(){
  size = 1;
  while(size < L-1){
    size *= 2;
  }
  init_segment_tree(0, 0, size);
}

void update(ll p, ll k, ll l, ll r){
  if(r - l == 1){
    assert(l == p && l < L-1);
    node[k] = sp[x[l]][x[l+1]];
  } else {
    ll m = (l + r) / 2;
    if(p < m){
      update(p, k*2+1, l, m);
    } else {
      update(p, k*2+2, m, r);
    }
    node[k] = merge(node[k*2+1], node[k*2+2]);
  }
}

void update(ll p){
  update(p, 0, 0, size);
}

vector<tl> query(ll k, ll l, ll r){
  if(r <= L-1){
    return node[k];
  } else if(L-1 <= l){
    assert(false);
  } else {
    ll m = (l+r)/2;
    vector<tl> resa = query(k*2+1, l, m);
    if(L-1 <= m){
      return resa;
    }
    vector<tl> resb = query(k*2+2, m, r);
    return merge(resa, resb);
  }
}

ll answer(){
  return get<0>(query(0, 0, size)[0]);
}

vector<ll> dijkstra(ll s){
  vector<ll> dist(2*M, INFLL);
  dist[s] = get<2>(edges[s]);
  vector<ll> state(N, -1);
  priority_queue<pl, vector<pl>, greater<pl> > que;
  que.emplace(get<2>(edges[s]), s);
  while(!que.empty()){
    ll d, p;
    tie(d, p) = que.top();
    que.pop();
    if(d > dist[p]){
      continue;
    }
    ll cur = get<1>(edges[p]);
    if(state[cur] == -1){
      for(auto &w: G[cur]){
        ll to, co, id;
        tie(to, co, id) = w;
        if(id/2 == p/2){
          continue;
        }
        if(d + co < dist[id]){
          dist[id] = d + co;
          que.emplace(dist[id], id);
        }
      }
      state[cur] = p;
    } else if(p != state[cur]){
      ll id = (state[cur]/2*2) + (1 - state[cur]%2);
      ll co = get<2>(edges[id]);
      if(d + co < dist[id]){
        dist[id] = d + co;
        que.emplace(dist[id], id);
      }
   } 
 } 
  return dist;
}

void input(){
  scanf("%lld %lld %lld %lld", &N, &M, &T, &L);
  for(ll i = 0; i < M; i++){
    ll a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    a--;
    b--;
    G[a].emplace_back(b, c, 2*i);
    G[b].emplace_back(a, c, 2*i+1);
    edges.emplace_back(a, b, c);
    edges.emplace_back(b, a, c);
  }
  for(ll i = 0; i < L; i++){
    scanf("%lld", &x[i]);
    x[i]--;
  }
  for(ll i = 0; i < T; i++){
    scanf("%lld %lld", &p[i], &q[i]);
    p[i]--;
    q[i]--;
  }
}

int main(){
  input();

  for(int i = 0; i < 2*M; i++){
    eds[i] = dijkstra(i);
  }
  
  for(int i = 0; i < 2*M; i++){
    for(int j = 0; j < 2*M; j++){
      ll s, t, a, b, _;
      tie(s, a, _) = edges[i];
      tie(b, t, _) = edges[j];
      sp[s][t].emplace_back(eds[i][j], a, b);
    }
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      sp[i][j] = calc_top_five(sp[i][j]);
    }
  }

  init_segment_tree();
  
  for(ll i = 0; i < T; i++){
    x[p[i]] = q[i];
    if(p[i] < L-1){
      update(p[i]);
    }
    if(p[i] > 0){
      update(p[i]-1);
    }
    ll ans = answer();
    if(ans == INFLL){
      ans = -1;
    }
    printf("%lld\n", ans);
  }

  return 0;
}
