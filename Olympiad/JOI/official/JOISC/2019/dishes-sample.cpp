#include <cstdio>

#include <algorithm>
#include <map>
#include <vector>

int main() {
  int N, M;
  scanf("%d%d", &N, &M);
  std::vector<long long> A(N), B(M), S(N), T(M), P(N), Q(M);
  for(int i = 0; i < N; i++) {
    long long a, s, p;
    scanf("%lld%lld%lld", &a, &s, &p);
    A[i] = a; S[i] = s; P[i] = p;
  }
  for(int i = 0; i < M; i++) {
    long long b, t, q;
    scanf("%lld%lld%lld", &b, &t, &q);
    B[i] = b; T[i] = t; Q[i] = q;
  }
  long long ans = 0;
  std::vector<long long> asum(N);
  long long sum = 0;
  std::vector<std::pair<long long, std::pair<int, long long>>> margin;
  for(int i = 0; i < N; i++) {
    sum += A[i];
    asum[i] = sum;
    if(sum <= S[i]) {
      ans += P[i];
      margin.push_back(std::make_pair(S[i] - sum, std::make_pair(i, P[i])));
    }
  }
  std::sort(margin.begin(), margin.end());
  std::map<int, long long> mp;
  sum = 0;
  int pos = 0;
  for(int i = 0; i < M; i++) {
    sum += B[i];
    std::vector<std::pair<int, long long>> v;
    while(pos < (int)margin.size() && margin[pos].first < sum) {
      v.push_back(margin[pos].second);
      pos++;
    }
    if(sum <= T[i]) {
      int p = std::upper_bound(asum.begin(), asum.end(), T[i] - sum) - asum.begin();
      if(p < N) {
        v.push_back(std::make_pair(p, -Q[i]));
      }
      else {
        ans += Q[i];
      }
    }
    std::sort(v.begin(), v.end());
    for(int j = (int)v.size() - 1; j >= 0; j--) {
      if(v[j].second > 0) {
        mp[v[j].first] += v[j].second;
      }
      else if(v[j].second < 0) {
        auto it = mp.lower_bound(v[j].first);
        long long rem = -v[j].second;
        while(rem > 0 && it != mp.end()) {
          if(rem < it->second) {
            it->second -= rem;
            rem = 0;
          }
          else {
            rem -= it->second;
            it = mp.erase(it);
          }
        }
        ans += rem;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}
