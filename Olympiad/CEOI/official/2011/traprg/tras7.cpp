/* Slower solution of TRA/jlac012
 * A bin-search solution.
 * Author: Tomasz Kociumaka, reusing some code by Mateusz Baranowski
 *
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define pb push_back
#define MAXN 300001

typedef pair<int, int> PII;

int n, m, A, B;
int i, l;
int tmp1, tmp2;
vector<PII> west, east; /* junctions on west riverbank */
vector<int> edges[MAXN], revedges[MAXN]; /* junctions in road network */
int eastern[MAXN]; /* equals 1 when junction lies on the east bank */
size_t visited[MAXN];
bool any[MAXN];

void read_input() {
  scanf ("%d %d %d %d", &n, &m, &A, &B);
  for (i = 1; i <= n; ++i) {
    scanf ("%d %d", &tmp1, &tmp2);
    eastern[i] = 0;
    if (tmp1 == 0) west.pb(make_pair(tmp2, i));
    else if (tmp1 == A) {
        east.pb(make_pair(tmp2, i));
        eastern[i] = 1;
    }
  }
  sort(west.begin(), west.end());
  sort(east.begin(), east.end());
  for (size_t s = 0; s < east.size(); ++s) {
      eastern[east[s].second] = s+1;
  }
  while (m-->0) {
    scanf ("%d %d %d", &tmp1, &tmp2, &i);
    edges[tmp1].pb(tmp2);
    revedges[tmp2].pb(tmp1);
    if (i == 2) {
        edges[tmp2].pb(tmp1);
        revedges[tmp1].pb(tmp2);
    }
  }
}

pair<int, int> reachable(int v, size_t s) {
    size_t j;
    int result = 0;
    int mx = 0;
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        i = q.front(); q.pop();
        result += (eastern[i] != 0);
        mx = max(eastern[i], mx);
        for (j = 0; j < edges[i].size(); ++j) {
            l = edges[i][j];
            if (visited[l] != s) { visited[l] = s; q.push(l); }
        }
    }
    return make_pair(result, mx);
}

void generate_output() {
    for (i = 1; i <= n; ++i) visited[i] = 0;
    queue<int> Q;
    for (i = 0; i < (int) east.size(); ++i) {
        Q.push(east[i].second);
        visited[east[i].second] = 1;
    }
    while (!Q.empty()) {
        i = Q.front(); Q.pop();
    //    printf("in %d\n", i);
        for (size_t j = 0; j < revedges[i].size(); ++j) {
            l = revedges[i][j];
            if (visited[l] != 1) { visited[l] = 1; Q.push(l); }
        }
    }
    for (i = 0; i < (int) west.size(); ++i) {
        any[i] = (visited[west[i].second] == 1);
     //   printf("%d: %d\n", i, any[i]);
    }

    for (i = 1; i <= n; ++i) visited[i] = 0;
    int s = (int) west.size();
    PII cur,  prev = make_pair(-1, -1);
    int delta = 1;
    int ph = 0;
    while(true) {
        ++ph;
       
        if (s-delta>=0) {
            if (!any[s-delta]) --delta;
            if (delta == 0) {
                printf("0\n");
                delta = 1;
                --s;
                continue;
            }
         //   printf("%d %d\n", s, delta);
            cur = reachable(west[s-delta].second, ph);
            if (cur == prev) {
                for (i=0; i<delta; ++i) printf("%d\n",(any[s-i-1])?cur.first:0);
                s -= delta;
                delta *= 2;
            } else {
                if (delta > 1) delta /= 2;
                else {
                    printf("%d\n", cur.first);
                    prev = cur;
                    --s;
                }
            }
        } else if (delta > 1){
            delta /= 2;
        } else break;
    }
}

int main() {
    read_input();
    generate_output();
    return 0;
}
