import java.util.ArrayList;
import java.util.Collections;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class lot3 {
  public static final int maxN = 10010;
  public static final int maxQ = 100;

  public static int[] t;
  public static int n, l, q;

  public static class Query implements Comparable<Query> {
    public int k, i;

    Query(int k_, int i_) {
      k = k_;
      i = i_;
    }

    public int compareTo(Query o) {
      if (k == o.k) return 0;
      return (k < o.k) ? -1 : 1;
    }
  }

  public static ArrayList<Query> quests;
  public static int[] cnt;
  public static int[][] ans;
  public static int[] dp;

  public static int count_diff(int x, int y) {
    int diff = 0;
    if (x > 0 && y > 0 && t[x - 1] != t[y - 1])
      diff--;
    if (t[x + l - 1] != t[y + l - 1])
      diff++;
    if (x == 0 || y == 0) {
      for (int i = 1; i < l; i++)
        diff += (t[x + i - 1] != t[y + i - 1]) ? 1 : 0;
    }
    return diff;
  }

  public static void ans_quests(int x) {
    for (int i = 0; i <= l; i++)
      cnt[i] = 0;
    for (int i = n - l; i > 0; i--)
      dp[i] = dp[i - 1] + count_diff(x, i);
    dp[0] = count_diff(x, 0);

    for (int i = 0; i < n - l + 1; i++)
      cnt[dp[i]]++;

    int k = 0, sum = 0;
    for (int i = 0; i < quests.size(); i++) {
      Query q = quests.get(i);
      while (k <= q.k) {
        sum += cnt[k];
        k++;
      }
      ans[q.i][x] = sum - 1;
    }
  }

  public static void main(String[] args) throws IOException {
    t = new int[maxN];
    quests = new ArrayList<Query>();
    cnt = new int[maxN];
    ans = new int[maxQ][maxN];
    for (int i = 0; i < maxQ; i++) ans[i] = new int[maxN];
    dp = new int[maxN];

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;

    st = new StringTokenizer(br.readLine());
    n = Integer.parseInt(st.nextToken());
    l = Integer.parseInt(st.nextToken());

    st = new StringTokenizer(br.readLine());
    for (int i = 0; i < n; i++)
      t[i] = Integer.parseInt(st.nextToken());

    st = new StringTokenizer(br.readLine());
    q = Integer.parseInt(st.nextToken());
    for (int i = 0; i < q; i++) {
      st = new StringTokenizer(br.readLine());
      int k = Integer.parseInt(st.nextToken());
      quests.add(new Query(k, i));
    }
    Collections.sort(quests);

    for (int i = 0; i < n - l + 1; i++)
      ans_quests(i);

    for (int i = 0; i < q; i++) {
      for (int j = 0; j < n - l + 1; j++) {
        System.out.print(ans[i][j]);
        System.out.print(" ");
      }
      System.out.println();
    }
  }
}
