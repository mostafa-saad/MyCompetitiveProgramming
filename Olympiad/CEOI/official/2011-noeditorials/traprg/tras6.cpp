/* Slower solution of TRA/jlac012
 * Brutal O(m * min(west, east)) solution with an optimisation,
 * we search the reversed graph when there is more east than west junctions
 * Author: Mateusz Baranowski
 * Some improvements by Tomasz Kociumaka
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define pb push_back
#define MAXN 300001
#define VAR(v,i) __typeof(i) v=(i)
#define FORE(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

typedef pair<int, int> PII;

int n, m, A, B;
int i, l;
int tmp1, tmp2;
vector<PII> west; /* junctions on west riverbank */
vector<int> east, edges[MAXN]; /* junctions in road network */
int final[MAXN]; /* if junction reached inc. the result 1 in start vertex, >1 in this vertex*/
//int visited[MAXN];
/*struct d {
    vector<int> edges;
    int final;
};*/

//d data[MAXN];
vector<bool> vis2;
vector<bool> fin2;

int readInt() {
    int res = 0;
    int c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <='9') {
        res = 10*res + c - '0';
        c = getchar();
    }
    return res;
}
struct rd {
    int x;
    int y;
    int i;
    bool operator < (rd const& r) const {
        return (y < r.y) || (y == r.y && x < r.x);
    }
};
rd in[MAXN];
int perm[MAXN];

void read_input() {
  scanf ("%d %d %d %d", &n, &m, &A, &B);
  for(int i=1; i<=n; ++i) {
      in[i].x = readInt();
      in[i].y = readInt();
      in[i].i = i;
  }
  sort(in+1, in+n+1);
  for(int i=1; i<=n; ++i) {
      perm[in[i].i] = i;
  }
  for (int i = 1; i <= n; ++i) {
      tmp1 = in[i].x;
      tmp2 = in[i].y;
      final[i] = 0;
      if (tmp1 == 0) west.pb(make_pair(tmp2, i));
      else if (tmp1 == A) east.pb(i);
  }
  sort(west.begin(), west.end());
  /* mark destination, if number of |east|<|west| then we consider reversed graph */
  if (west.size() > east.size()) {
      for (size_t s = 0; s < west.size(); ++s) final[west[s].second] = 1;
      while (m-->0) {
          tmp1 = perm[readInt()];
          tmp2 = perm[readInt()];
          int i = readInt();
          edges[tmp2].pb(tmp1);
          if (i == 2) edges[tmp1].pb(tmp2);
      }
  } else {
      fin2 = vector<bool>(n+1, false);
      for (size_t s = 0; s < east.size(); ++s) fin2[east[s]] = true;
      while (m-->0) {
          tmp1 = perm[readInt()];
          tmp2 = perm[readInt()];
          int i = readInt();
          edges[tmp1].pb(tmp2);
          if (i == 2) edges[tmp2].pb(tmp1);
      }
  }
}

int reachableA(int v) {
    fill(vis2.begin(), vis2.end(), false);
    int result = 0;
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        i = q.front(); q.pop();
        if (final[i]) ++final[i];
        FORE(it, edges[i]) {
            if (!vis2[*it]) { vis2[*it] = true; q.push(*it); }
        }
    }
    return result;
}
int reachableB(int v) {
    fill(vis2.begin(), vis2.end(), false);
    int result = 0;
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        i = q.front(); q.pop();
        if (fin2[i]) ++result;
        FORE(it, edges[i]) {
            if (!vis2[*it]) { vis2[*it] = true; q.push(*it); }
        }
    }
    return result;
}


void generate_output() {
    vis2 = vector<bool>(n+1, false);
   // for (i = 1; i <= n; ++i) visited[i] = 0;
    if (west.size() > east.size()) {
        while (!east.empty()) {
            reachableA(east.back());
            east.pop_back();
        }
        while (!west.empty()) {
            printf ("%d\n", final[west.back().second] - 1);
            west.pop_back();
        }
    } else
        while (!west.empty()) {
            printf ("%d\n", reachableB(west.back().second));
            west.pop_back();
        }
}

int main() {
    read_input();
    generate_output();
    return 0;
}
