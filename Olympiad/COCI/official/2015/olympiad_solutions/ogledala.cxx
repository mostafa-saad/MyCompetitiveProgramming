// Autor: Ivan Katanic

// O(N*logN*logM + K*logM*logM)
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long llint;
typedef pair<llint, llint> par;
#define len first
#define cnt second

const int MAXN = 100100;

struct Gap {
  llint len, cnt;
  int i;
};

llint a[MAXN];
llint b[MAXN];

vector<par> V;

void split(llint len) {
  V.clear();
  if (len == 0) return;

  V.push_back({len+1, 0});
  V.push_back({len, 1});
  
  for (int i = 0; i < (int)V.size(); i += 2) {
    assert(V[i].len == V[i+1].len + 1);

    llint next_len1 = V[i].len / 2, next_cnt1 = V[i].cnt;
    llint next_len2 = (V[i+1].len-1) / 2, next_cnt2 = V[i+1].cnt;
    
    V[i+1].len/2 == next_len1 ? next_cnt1 += V[i+1].cnt : next_cnt2 += V[i+1].cnt;
    (V[i].len-1)/2 == next_len1 ? next_cnt1 += V[i].cnt : next_cnt2 += V[i].cnt;
    
    if (next_len1 == 0 && next_len2 == 0) break;
    V.push_back({next_len1, next_cnt1});
    V.push_back({next_len2, next_cnt2});
  }
  
  while (V.size() && V.back().first == 0) V.pop_back();
  llint cnt1 = 0;
  while (V.size() && V.back().first == 1) {
    cnt1 += V.back().cnt;
    V.pop_back();
  }
  if (cnt1 > 0) V.push_back({1, cnt1});
}

llint query(int i, llint need_len, llint need_ind) {
  llint pos = a[i] + 1;
  llint len = a[i+1] - a[i] - 1;

  while (len > need_len) {
    split((len - 1) / 2);
    llint cnt = 0;
    for (auto &p: V)
      if (p.len == need_len) cnt += p.cnt;
    
    if (cnt >= need_ind) {
      len = (len - 1) / 2;
    } else {
      pos += 1 + (len - 1) / 2;
      len = len / 2;
      need_ind -= cnt;
    }
  }

  assert(len == need_len);
  return pos + (len-1)/2;
}

int main(void) {
  llint m;
  int n, k;
  scanf("%lld %d %d", &m, &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%lld", &a[i]); 
  a[0] = 0, a[n + 1] = m + 1;
  
  static vector<Gap> gaps;
  for (int i = 0; i <= n; ++i) {
    split(a[i+1] - a[i] - 1);
    for (auto &p: V)
      if (p.len > 0 && p.cnt > 0) gaps.push_back({p.len, p.cnt, i});
  }    
  sort(gaps.begin(), gaps.end(), [&] (const Gap &a, const Gap &b) {
      if (a.len != b.len) return a.len > b.len;
      return a.i < b.i;
    }
  );

  for (int i = 0; i < k; ++i) 
    scanf("%lld", &b[i]);   

  int curq = 0;
  while (curq < k && b[curq] <= n) printf("%lld\n", a[b[curq++]]);

  llint cur = n + 1;
  for (Gap &g: gaps) {
    while (curq < k && b[curq] < cur + g.cnt) {
      printf("%lld\n", query(g.i, g.len, b[curq] - cur + 1));
      curq++;
    }
    cur += g.cnt;
  }
  
  return 0;
}
