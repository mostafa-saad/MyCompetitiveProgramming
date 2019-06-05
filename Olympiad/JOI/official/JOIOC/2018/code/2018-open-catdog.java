import static java.lang.Math.*;
import java.util.ArrayList;

public class catdog {
  final int BIG = 100000000;
  
  @SuppressWarnings("unchecked")
  void initialize(int N, int[] A, int[] B) {
    this.N = N;
    G = new ArrayList[N];
    for (int u = 0; u < N; ++u) {
      G[u] = new ArrayList<Integer>();
    }
    for (int i = 0; i < N - 1; ++i) {
      int u = A[i] - 1;
      int v = B[i] - 1;
      G[u].add(v);
      G[v].add(u);
    }
    
    par = new int[N];
    sz = new int[N];
    xs = new int[N];
    ys = new int[N];
    L = 0;
    dfs(0, -1);
    M = new int[L];
    for (int u = 0; u < N; ++u) {
      ++M[xs[u]];
    }
    us = new int[L][];
    for (int x = 0; x < L; ++x) {
      us[x] = new int[M[x]];
    }
    for (int u = 0; u < N; ++u) {
      us[xs[u]][ys[u]] = u;
    }
    segs = new SegmentTree[L];
    for (int x = 0; x < L; ++x) {
      segs[x] = new SegmentTree(M[x]);
    }
    
    colors = new int[N];
    lightCounts = new int[N][3];
    ans = 0;
  }
  
  int cat(int v) {
    return solve(v - 1, +1);
  }
  
  int dog(int v) {
    return solve(v - 1, -1);
  }
  
  int neighbor(int v) {
    return solve(v - 1, 0);
  }
  
  int solve(int u, int colorNew) {
    int f = segs[xs[u]].getValue(ys[u]);
    int sigF = Integer.signum(f);
    int sigFNew = Integer.signum(f + (colorNew - colors[u]) * BIG);
    // cost at u
    int[] counts = new int[3];
    counts[1 + (+1)] = lightCounts[u][1 + (+1)];
    counts[1 + (-1)] = lightCounts[u][1 + (-1)];
    if (ys[u] > 0) {
      ++counts[1 + Integer.signum(segs[xs[u]].getValue(ys[u] - 1))];
    }
    switch (colors[u]) {
      case +1: ans -= counts[1 + (-1)]; break;
      case -1: ans -= counts[1 + (+1)]; break;
      case  0: ans -= min(counts[1 + (+1)], counts[1 + (-1)]); break;
    }
    switch (colorNew) {
      case +1: ans += counts[1 + (-1)]; break;
      case -1: ans += counts[1 + (+1)]; break;
      case  0: ans += min(counts[1 + (+1)], counts[1 + (-1)]); break;
    }
    // cost at par[u]
    int p = par[u];
    if (p != -1) {
      counts[1 + (+1)] = lightCounts[p][1 + (+1)];
      counts[1 + (-1)] = lightCounts[p][1 + (-1)];
      if (ys[p] > 0) {
        ++counts[1 + Integer.signum(segs[xs[p]].getValue(ys[p] - 1))];
      }
      switch (colors[p]) {
        case +1: ans -= counts[1 + (-1)]; break;
        case -1: ans -= counts[1 + (+1)]; break;
        case  0: ans -= min(counts[1 + (+1)], counts[1 + (-1)]); break;
      }
      --counts[1 + sigF];
      ++counts[1 + sigFNew];
      switch (colors[p]) {
        case +1: ans += counts[1 + (-1)]; break;
        case -1: ans += counts[1 + (+1)]; break;
        case  0: ans += min(counts[1 + (+1)], counts[1 + (-1)]); break;
      }
    }
    // light edge counts
    if (p != -1 && xs[u] != xs[p]) {
      --lightCounts[p][1 + sigF];
      ++lightCounts[p][1 + sigFNew];
    }
    
    segs[xs[u]].add(ys[u], ys[u], (colorNew - colors[u]) * BIG);
    colors[u] = colorNew;
    for (; sigF < sigFNew; ++sigF) doIt(par[u], +1);
    for (; sigF > sigFNew; --sigF) doIt(par[u], -1);
    return ans;
  }
  
  int N;
  ArrayList<Integer>[] G;
  int[] par, sz;
  int L;
  int[] M;
  int[] xs, ys;
  int[][] us;
  SegmentTree[] segs;
  int[] colors;
  int[][] lightCounts;
  int ans;
  
  void dfs(int u, int p) {
    par[u] = p;
    sz[u] = 1;
    for (int v : G[u]) if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
    }
    for (int v : G[u]) if (v != p) {
      if (sz[u] <= sz[v] * 2) {
        xs[u] = xs[v];
        ys[u] = ys[v] + 1;
        return;
      }
    }
    xs[u] = L++;
    ys[u] = 0;
  }
  
  void doIt(int u, int s) {
    int chainMin = 0, chainMax = 0;
    switch (s) {
      case +1: chainMin = -1; break;
      case -1: chainMax = +1; break;
    }
    for (; u != -1; ) {
      int y = segs[xs[u]].getFirstOutsider(ys[u], chainMin, chainMax);
      boolean cont = false;
      if (y >= M[xs[u]]) {
        y = M[xs[u]] - 1;
        cont = true;
      }
      int f0 = segs[xs[u]].getValue(ys[u]);
      int f2 = segs[xs[u]].getValue(y);
      if (ys[u] <= y - 1) {
        int f1 = segs[xs[u]].getValue(y - 1);
        // cost at us[xs[u]][ys[u] + 1], ..., us[xs[u]][y - 1]
        ans += s * (f0 - f1);
        // cost at us[xs[u]][y]
        ans += costIncrease(s, f1, f2);
      }
      // cost at par[us[xs[u]][y]]
      int p = par[us[xs[u]][y]];
      if (p != -1) {
        int f3 = segs[xs[p]].getValue(ys[p]);
        ans += costIncrease(s, f2, f3);
      }
      // light edge counts
      if (p != -1 && xs[u] != xs[p]) {
        --lightCounts[p][1 + Integer.signum(f2)];
        ++lightCounts[p][1 + Integer.signum(f2 + s)];
      }
      // add s
      segs[xs[u]].add(ys[u], y, s);
      // next heavy path
      if (!cont) break;
      u = par[us[xs[u]][M[xs[u]] - 1]];
    }
  }
  
  // s = +1: ++ans for (0, <= -1), --ans for (-1, >= 0)
  // s = -1: ++ans for (0, >= +1), --ans for (+1, <= 0)
  int costIncrease(int s, int fU, int fP) {
    if (fU == 0 && Integer.signum(fP) == -s) return +1;
    if (fU == -s && Integer.signum(fP) != -s) return -1;
    return 0;
  }
  
  class SegmentTree {
    int n;
    int[] min, max, add;
    SegmentTree(int n_) {
      for (n = 1; n < n_; n <<= 1) {}
      min = new int[n << 1];
      max = new int[n << 1];
      add = new int[n << 1];
    }
    void refresh(int a) {
      min[a] = add[a] + min(min[a << 1], min[a << 1 | 1]);
      max[a] = add[a] + max(max[a << 1], max[a << 1 | 1]);
    }
    void propagate(int a) {
      min[a << 1] += add[a];
      max[a << 1] += add[a];
      add[a << 1] += add[a];
      min[a << 1 | 1] += add[a];
      max[a << 1 | 1] += add[a];
      add[a << 1 | 1] += add[a];
      add[a] = 0;
    }
    void propagateRecursive(int a) {
      if (a > 0) {
        propagateRecursive(a >> 1);
        if (a < n) propagate(a);
      }
    }
    void add(int a, int b, int val) {
      int c = a += n, d = b += n;
      for (; a <= b; a >>= 1, b >>= 1, c >>= 1, d >>= 1) {
        if (c != a) refresh(c);
        if (d != b) refresh(d);
        if ((a & 1) != 0) { min[a] += val; max[a] += val; add[a] += val; ++a; }
        if ((b & 1) == 0) { min[b] += val; max[b] += val; add[b] += val; --b; }
      }
      for (; c > 0; c >>= 1, d >>= 1) {
        refresh(c);
        refresh(d);
      }
    }
    int getValue(int a) {
      a += n;
      propagateRecursive(a);
      return min[a];
    }
    
    // min x (>= a) s.t. value at x is not in [p, q]
    int getFirstOutsider(int a, int p, int q) {
      a += n;
      int b = (n << 1) - 1;
      propagateRecursive(a);
      for (; a <= b; a >>= 1, b >>= 1) {
        if ((a & 1) != 0) {
          if (p <= min[a] && max[a] <= q) {
            ++a;
          } else {
            for (; a < n; ) {
              p -= add[a];
              q -= add[a];
              a <<= 1;
              if (p <= min[a] && max[a] <= q) ++a;
            }
            return a - n;
          }
        }
      }
      return n;
    }
  }
}
