#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 100005;
const long long INF = 1ll<<60;
vector<int> to[MAX_N], co[MAX_N];
long long dist[MAX_N];

struct dat {
  long long d;
  int v;
  dat(long long d, int v):d(d),v(v){}
  bool operator<(const dat& a)const{ return d>a.d;}
};

int main() {
  int n, m, c;
  long long sum = 0;
  scanf("%d%d%d",&n,&m,&c);
  for (int i = 0; i < m; i++) {
    int a, b, d;
    scanf("%d%d%d",&a,&b,&d);
    a--; b--;
    to[a].push_back(b); co[a].push_back(d);
    to[b].push_back(a); co[b].push_back(d);
    sum += d;
  }
  priority_queue<dat> q;
  q.push(dat(0,0));
  for (int i = 0; i < n; i++) dist[i] = INF;
  while(q.size()) {
    long long d = q.top().d; int v = q.top().v; q.pop();
    if (dist[v] != INF) continue;
    dist[v] = d;
    for (int i = 0; i < to[v].size(); i++) {
      q.push(dat(d+co[v][i],to[v][i]));
    }
  }
  for (int i = 0; i < n; i++) q.push(dat(dist[i],i));
  long long ans = INF;
  for (int i = 0; i < n; i++) {
    int v = q.top().v; q.pop();
    for (int j = 0; j < to[v].size(); j++) {
      if (dist[to[v][j]] == -1) sum -= co[v][j];
    }
    ans = min(ans,sum+dist[v]*c);
    dist[v] = -1;
  }
  printf("%lld\n",ans);
  return 0;
}