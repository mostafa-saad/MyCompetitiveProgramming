#include <cassert>
#include <cstdio>

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

int main() {
  int N, M;
  scanf("%d%d", &N, &M);
  std::vector<long long> A(N), B(M), S(N), T(M);
  for(int i = 0; i < N; i++) {
    long long a, s, p;
    scanf("%lld%lld%lld", &a, &s, &p);
    A[i] = a; S[i] = s; assert(p == 1);
  }
  for(int i = 0; i < M; i++) {
    long long b, t, q;
    scanf("%lld%lld%lld", &b, &t, &q);
    B[i] = b; T[i] = t; assert(q == 1);
  }

  std::vector<long long> as(1, 0), bs(1, 0);
  for(int i = 0; i < N; i++) {
    as.push_back(as.back() + A[i]);
  }
  for(int i = 0; i < M; i++) {
    bs.push_back(bs.back() + B[i]);
  }

  std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;
  int ans = 0;
  for(int i = 0; i < N; i++) {
    if(as[i + 1] <= S[i]) {
      ans++;
      pq.push(std::make_pair(S[i] - as[i + 1], i + 1));
    }
  }
  std::set<int> se;
  for(int i = 0; i < M; i++) {
    if(bs[i + 1] <= T[i]) {
      while(!pq.empty() && pq.top().first < bs[i + 1]) {
        se.insert(pq.top().second);
        pq.pop();
      }
      int p = std::upper_bound(as.begin(), as.end(), T[i] - bs[i + 1]) - as.begin();
      auto e = se.lower_bound(p);
      if(e != se.end()) {
        se.erase(e);
      }
      else {
        ans++;
      }
    }
  }

  printf("%d\n", ans);
  return 0;
}
