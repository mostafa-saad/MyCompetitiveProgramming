import static java.lang.Math.*;

public class bubblesort2 {
  int[] countScans(int[] A, int[] X, int[] V) {
    int N = A.length, Q = X.length;
    
    int[] vals = new int[N + Q], poss = new int[N + Q], keys = new int[N + Q];
    for (int i = 0; i < N; ++i) {
      vals[i] = A[i];
      poss[i] = i;
      keys[i] = i;
    }
    for (int j = 0; j < Q; ++j) {
      vals[N + j] = V[j];
      poss[N + j] = X[j];
      keys[N + j] = N + j;
    }
    RadixSort.work = new int[N + Q];
    RadixSort.sort(keys, 0, N + Q, poss);
    RadixSort.sort(keys, 0, N + Q, vals);
    for (int i = 0; i < N + Q; ++i) {
      vals[keys[i]] = i;
    }
    
    SegmentTree seg = new SegmentTree(N + Q);
    seg.add(0, seg.n - 1, -BIG);
    
    int[] ans = new int[Q];
    int[] crt = new int[N];
    for (int i = 0; i < N; ++i) {
      crt[i] = vals[i];
      seg.add(crt[i], crt[i], +(BIG + i));
      seg.add(crt[i] + 1, seg.n - 1, -1);
    }
    for (int j = 0; j < Q; ++j) {
      int i = X[j];
      seg.add(crt[i], crt[i], -(BIG + i));
      seg.add(crt[i] + 1, seg.n - 1, +1);
      crt[i] = vals[N + j];
      seg.add(crt[i], crt[i], +(BIG + i));
      seg.add(crt[i] + 1, seg.n - 1, -1);
      ans[j] = seg.max[1];
    }
    return ans;
  }
  
  final int BIG = 10000000;
  
  class SegmentTree {
    int n;
    int[] max, add;
    SegmentTree(int n_) {
      for (n = 1; n < n_; n <<= 1) {}
      max = new int[n << 1];
      add = new int[n << 1];
      for (int a = 0; a < n << 1; ++a) {
        max[a] = 0;
        add[a] = 0;
      }
    }
    void prop(int a) {
      max[a] = add[a] + max(max[a << 1], max[a << 1 | 1]);
    }
    void add(int a, int b, int val) {
      int c = a += n, d = b += n;
      for (; a <= b; a >>= 1, b >>= 1, c >>= 1, d >>= 1) {
        if (c != a) prop(c);
        if (d != b) prop(d);
        if ((a & 1) != 0) { max[a] += val; add[a] += val; ++a; }
        if ((b & 1) == 0) { max[b] += val; add[b] += val; --b; }
      }
      for (; c > 0; c >>= 1, d >>= 1) {
        prop(c);
        prop(d);
      }
    }
  }
  
  static class RadixSort {
    static int[] work;
    static int[] buckets = new int[0x10001];
    static void sort(int[] v, int l, int r, int[] w) {
      for (int j = 0; j < 0x10000; ++j) buckets[j] = 0;
      for (int i = l; i < r; ++i) ++buckets[(w[v[i]] & 0xffff) + 1];
      for (int j = 1; j < 0x10000; ++j) buckets[j] += buckets[j - 1];
      for (int i = l; i < r; ++i) work[buckets[w[v[i]] & 0xffff]++] = v[i];
      for (int j = 0; j < 0x10000; ++j) buckets[j] = 0;
      for (int i = 0; i < r - l; ++i) ++buckets[(w[work[i]] >> 16) + 1];
      for (int j = 1; j < 0x10000; ++j) buckets[j] += buckets[j - 1];
      for (int i = 0; i < r - l; ++i) v[l + buckets[w[work[i]] >> 16]++] = work[i];
    }
  }
}
