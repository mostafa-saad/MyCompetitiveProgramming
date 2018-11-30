/*
 * Model solution for Edytor
 * edi2.cpp zapisane w Javie
 * Autor: Wojtek Nadara
 *
 * Time: O(n log n)
 * Memory: O(n log n)
 *
 */

import java.io.*;
import java.util.*;



public class edi {
    private static final int N = (1 << 19);

    int n;
    int[] res = new int[N];
    PersTree[] pers = new PersTree[N];
    
    class PersTree {
      PersTree l;
      PersTree r;
      int bl, br, val;
      public PersTree (PersTree l_, PersTree r_, int bl_, int br_) {
        this.l = l_;
        this.r = r_;
        this.bl = bl_;
        this.br = br_;
        this.val = N;
      }
      
      public int Find(int lvl) {
        if (bl == br) {
          return bl;
        }
        int r_min = SafeMin(r);
        if (r_min < lvl) {
          return r.Find(lvl);
        }
        return l.Find(lvl);
      }
      
      PersTree Add(int pos, int lvl) {
        PersTree copy = new PersTree(l, r, bl, br);
        copy.val = Math.min(val, lvl);
        if (SafeIn(pos, l)) {
          copy.l = l.Add(pos, lvl);
        }
        if (SafeIn(pos, r)) {
          copy.r = r.Add(pos, lvl);
        }
        return copy;
      }
      
      int SafeMin(PersTree p) {
        if (p == null) {
          return N;
        }
        return p.val;
      }

      boolean SafeIn(int x, PersTree p) {
        return p != null && p.bl <= x && x <= p.br;
      }
    }
    
    public PersTree CreatePersTree(int l, int r) {
      if (l == r) {
        return new PersTree(null, null, l, r);
      }
      int m = (l + r) / 2;
      return new PersTree(CreatePersTree(l, m), CreatePersTree(m + 1, r), l, r);
    }

    public static void main(String[] args) {
		edi h = new edi();
		h.run();
    }
	
        
    public void run() {
      Scanner sc = new Scanner(System.in);
      PrintWriter out = new PrintWriter(System.out); //podmiana out na System.out w 99tej linijce powoduje dwukrotne zwolnienie programu :)
      int n = sc.nextInt();
      pers[0] = CreatePersTree(1, n);
      String s = "";
      for (int ii = 1; ii <= n; ii++) {
        //int op = 2 * (ii % 2) - 1;
        int op = sc.nextInt();
        if (op > 0) {
          res[ii] = op;
          pers[ii] = pers[ii - 1].Add(ii, 0);
        } else {
          int bef_to_undo = pers[ii - 1].Find(-op) - 1;
          res[ii] = res[bef_to_undo];
          pers[ii] = pers[bef_to_undo].Add(ii, -op);
        }
        System.out.println(res[ii]);
      }
    }
}
