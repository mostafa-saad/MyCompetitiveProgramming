import static java.lang.Math.*;
import static java.util.Arrays.*;

public class collapse {
  final int BLOCK_SIZE = 333;
  final int MAX_HISTORY_LEN = 1000010;
  
  int[] simulateCollapse(int N, int[] T, int[] X, int[] Y, int[] W, int[] P) {
    this.N = N;
    this.C = T.length;
    this.Q = W.length;
    this.T = T;
    this.X = X;
    this.Y = Y;
    this.W = W;
    this.P = P;
    return run();
  }
  
  int N, C, Q;
  int[] T, X, Y, W, P;
  
  int[] run() {
    int[] ans = new int[Q];
    fill(ans, N);
    uf = new int[N];
    
    for (int phase = 0; phase < 2; ++phase) {
      for (int i = 0; i < C; ++i) {
        if (X[i] > Y[i]) {
          int tmp = X[i]; X[i] = Y[i]; Y[i] = tmp;
        }
      }
      
      int edgesLen = 0;
      for (int i = 0; i < C; ++i) if (T[i] == 0) {
        ++edgesLen;
      }
      Edge[] edges = new Edge[edgesLen];
      edgesLen = 0;
      for (int i = 0; i < C; ++i) if (T[i] == 0) {
        edges[edgesLen++] = new Edge(X[i], Y[i], i);
      }
      sort(edges);
      int[] link = new int[C];
      fill(link, C);
      for (int j = 0; j < C; ++j) if (T[j] == 1) {
        int e = ~binarySearch(edges, new Edge(X[j], Y[j], j)) - 1;
        if (e >= 0) {
          int i = edges[e].time;
          if (X[i] == X[j] && Y[i] == Y[j]) {
            link[i] = j;
            link[j] = i;
          }
        }
      }
      
      for (int i = 0; i < C; ) {
        // solve for cable plans [i, j)
        int j = min(i + BLOCK_SIZE, C);
        int queriesLen = 0;
        for (int h = 0; h < Q; ++h) {
          if (i <= W[h] && W[h] < j) {
            ++queriesLen;
          }
        }
        Query[] queries = new Query[queriesLen];
        queriesLen = 0;
        for (int h = 0; h < Q; ++h) {
          if (i <= W[h] && W[h] < j) {
            queries[queriesLen++] = new Query(W[h], P[h], h);
          }
        }
        sort(queries);
        
        fill(uf, -1);
        int cntGlobal = 0;
        
        int e = 0;
        for (Query q : queries) {
          // global edges
          for (; e < edgesLen && edges[e].y <= q.p; ++e) {
            if (edges[e].time < i && j <= link[edges[e].time]) {
              if (connect(edges[e].x, edges[e].y)) {
                ++cntGlobal;
              }
            }
          }
          // path compression
          for (int k = i; k < j; ++k) {
            if ((T[k] == 0 && k <= q.w && q.w < link[k]) || (T[k] == 1 && link[k] <= q.w && q.w < k)) {
              if (Y[k] <= q.p) {
                root(X[k]);
                root(Y[k]);
              }
            }
          }
          // backtracking
          historyLen = 0;
          int cntLocal = 0;
          for (int k = i; k < j; ++k) {
            if ((T[k] == 0 && k <= q.w && q.w < link[k]) || (T[k] == 1 && link[k] <= q.w && q.w < k)) {
              if (Y[k] <= q.p) {
                if (connectSaving(X[k], Y[k])) {
                  ++cntLocal;
                }
              }
            }
          }
          ans[q.id] -= cntGlobal;
          ans[q.id] -= cntLocal;
          for (int g = historyLen; g-- > 0; ) {
            uf[historyKey[g]] = historyVal[g];
          }
        }
        
        i = j;
      }
      
      for (int i = 0; i < C; ++i) {
        X[i] = N - 1 - X[i];
        Y[i] = N - 1 - Y[i];
      }
      for (int h = 0; h < Q; ++h) {
        P[h] = N - 2 - P[h];
      }
    }
    
    return ans;
  }
  
  int[] uf;
  int historyLen;
  int[] historyKey = new int[MAX_HISTORY_LEN];
  int[] historyVal = new int[MAX_HISTORY_LEN];
  int root(int u) {
    return (uf[u] < 0) ? u : (uf[u] = root(uf[u]));
  }
  boolean connect(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return false;
    if (uf[u] > uf[v]) { int tmp = u; u = v; v = tmp; }
    uf[u] += uf[v];
    uf[v] = u;
    return true;
  }
  void assignSaving(int key, int val) {
    if (uf[key] != val) {
      historyKey[historyLen] = key;
      historyVal[historyLen] = uf[key];
      ++historyLen;
      uf[key] = val;
    }
  }
  int rootSaving(int u) {
    if (uf[u] < 0) {
      return u;
    } else {
      assignSaving(u, rootSaving(uf[u]));
      return uf[u];
    }
  }
  boolean connectSaving(int u, int v) {
    u = rootSaving(u);
    v = rootSaving(v);
    if (u == v) return false;
    if (uf[u] > uf[v]) { int tmp = u; u = v; v = tmp; }
    assignSaving(u, uf[u] + uf[v]);
    assignSaving(v, u);
    return true;
  }
  
  class Edge implements Comparable<Edge> {
    int x, y, time;
    Edge(int x, int y, int time) {
      this.x = x;
      this.y = y;
      this.time = time;
    }
    public int compareTo(Edge o) {
      return (y != o.y) ? (y - o.y) : (x != o.x) ? (x - o.x) : (time - o.time);
    }
  }
  
  class Query implements Comparable<Query> {
    int w, p, id;
    Query(int w, int p, int id) {
      this.w = w;
      this.p = p;
      this.id = id;
    }
    public int compareTo(Query o) {
      return (p != o.p) ? (p - o.p) : (id - o.id);
    }
  }
}
