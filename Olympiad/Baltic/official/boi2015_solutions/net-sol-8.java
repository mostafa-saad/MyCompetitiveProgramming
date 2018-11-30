// Kamil Debowski
// AC Solution
import java.util.*;
import java.util.Scanner;

public class net {
    static int nax = 500 * 1000 + 5;
    static int[] leaves = new int[nax];
    static ArrayList<ArrayList<Integer>> w = new ArrayList<ArrayList<Integer>>();
    static ArrayList<ArrayList<Integer>> sets = new ArrayList<ArrayList<Integer>>();
    static int half;
    static void dfs_first(int a, int father) {
        leaves[a] = 0;
        for(int i = 0; i < w.get(a).size(); ++i) {
            int b = w.get(a).get(i);
            if(b == father) {
                w.get(a).remove(i);
                --i;
            }
            else {
                dfs_first(b, a);
                leaves[a] += leaves[b];
            }
        }
        if(w.get(a).isEmpty()) leaves[a] = 1;
    }
    static void give_leaves(int a, int sets_i) {
        for(int b : w.get(a))
            give_leaves(b, sets_i);
        if(w.get(a).isEmpty()) // leaf
            sets.get(sets_i).add(a);
    }

    static int dajOstatni(int i) {
        int ret = sets.get(i).get(sets.get(i).size()-1);
        sets.get(i).remove(sets.get(i).size()-1);
        return ret;
    }

    static void dfs(int a) {
        int big = 0;
        for(int b : w.get(a))
            if(leaves[b] > leaves[big])
                big = b;
        if(leaves[big] > half) {
            for(int b : w.get(a))
                if(b != big)
                    give_leaves(b, 0);
            dfs(big);
            return;
        }
        for(int b : w.get(a))
            for(int i = 0; i < 3; ++i)
                if(leaves[b] + sets.get(i).size() <= half) {
                    give_leaves(b, i);
                    break;
                }
        for(int i = 0; i < half; ++i) {
            int x = 0;
            for(int j = 1; j <= 2; ++j)
                if(sets.get(j).size() > sets.get(x).size())
                    x = j;
            int y = 0;
            if(x == 0) y = 1;
            for(int j = 1; j <= 2; ++j)
                if(j != x && sets.get(j).size() > sets.get(y).size())
                    y = j;
            System.out.println(dajOstatni(x) + " " + dajOstatni(y));
        }
        int x = 0;
        for(int j = 1; j <= 2; ++j)
            if(sets.get(j).size() > sets.get(x).size())
                x = j;
        if(!sets.get(x).isEmpty())
            System.out.println(dajOstatni(x) + " " + a);
    }

    public static void main(String[] args) throws java.io.IOException {
        try{
            Scanner sc = new Scanner(System.in);
            int n = sc.nextInt();
            for(int i = 0; i <= n; ++i)
                w.add(new ArrayList<Integer>());
            for(int i = 0; i < 3; ++i)
                sets.add(new ArrayList<Integer>());
            if(n == 1) {
                System.out.println("0");
                return;
            }
            if(n == 2) {
                System.out.println("1");
                System.out.println("1 2");
                return;
            }
            for(int i = 0; i < n - 1; ++i) {
                int a = sc.nextInt();
                int b = sc.nextInt();
                w.get(a).add(b);
                w.get(b).add(a);
            }
            int root = 1;
            while(w.get(root).size() < 2) root++;
            dfs_first(root, 0);
            half = leaves[root] / 2;
            System.out.println((leaves[root] + 1) / 2);
            dfs(root);
        }
        catch (java.lang.Exception E)
        {
            E.printStackTrace();
        }
    }
}
