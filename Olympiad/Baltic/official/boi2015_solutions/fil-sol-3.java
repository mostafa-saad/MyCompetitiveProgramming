// Adam Karczmarz

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class fil3 {

  private static class Task {
    private int N, M, K, S;
    private final int MAXK = 1000000;
    private int[] h, cnt;
    private boolean[] res, us;
    private ArrayList<ArrayList<Integer>> ve;
    private Stack<Integer> anc;
    
    public Task() {
      Scanner s = new Scanner(System.in);
      N = s.nextInt();
      M = s.nextInt();
      K = s.nextInt();
      S = s.nextInt();
      h = new int[N + M + 1];
      cnt = new int[MAXK + 1];
      res = new boolean[N + M + 1];
      us = new boolean[MAXK + 1];
      ve = new ArrayList<ArrayList<Integer>>();
      for (int i = 0; i <= N + M; ++i) {
        ve.add(new ArrayList<Integer>());
      }
      h[0] = 1; us[1] = true;
      for (int i = 1; i <= N + M; ++i) {
        int p = s.nextInt();
        h[i] = s.nextInt();
        ve.get(p).add(i);
        h[i] += h[p] + (i <= N ? 1 : 0);
        if (i <= N) {
          us[h[i]] = true;
        }
        anc = new Stack<Integer>();
      }
    }
    
    void add(int v, int delta, int x) {
      if (v > N) {
        return;
      }
      int y = h[v] + delta;
      if (y <= MAXK) {
        cnt[y] += x;
      }
      for (int w : ve.get(v)) {
        add(w, delta, x);
      }
    }
   

    private void case1(int v) {
      if (v > N) {
        int y = K - h[v];
        if (y > 0) {
          for (int d = 1; d * d <= y; ++d) {
            if (y % d == 0 && (cnt[d] > 0 || cnt[y / d] > 0)) {
              res[v] = true;
            }
          }
        }
        return;
      }
      add(v, S + 1 - h[v], 1);
      for (int w : ve.get(v)) {
        case1(w);
      }
      add(v, S + 1 - h[v], -1);
    }

    private void case2(int v) {
      if (v > N) {
        for (int a : anc) {
          int y = K - (h[v] - h[a]) - (S + 1);
          if (y >= 0 && us[y]) {
            res[v] = true;
          }
        }
        return;
      }
      anc.push(v);
      for (int w : ve.get(v)) {
        case2(w);
      }
      anc.pop();
    }
  
    private void case3() {
      for (int i = N + 1; i <= N + M; ++i) {
        if (h[i] == K) {
          res[i] = true;
        }
      }
    }
    
    public void comp() {
      case1(0); 
      case2(0);
      case3();
      for (int i = N + 1; i <= N + M; ++i) {
        System.out.println(res[i] ? "YES" : "NO");
      }
    }
  }
  
  public static void main(String[] args) {
    Task t = new Task();
    t.comp();
  }

}
