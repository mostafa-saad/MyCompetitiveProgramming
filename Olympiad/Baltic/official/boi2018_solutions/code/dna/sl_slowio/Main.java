import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int k = sc.nextInt();
		int r = sc.nextInt();
		int[] v = new int[n];
		int[] counts = new int[k];
		for (int i = 0; i < n; i++) {
			v[i] = sc.nextInt();
			counts[v[i]]++;
		}

		int failed = 0;
		int[] have = new int[k];
		int[] wanted = new int[k];
		for (int i = 0; i < r; i++) {
			int sym, co;
			sym = sc.nextInt();
			co = sc.nextInt();
			if (counts[sym] < co) {
				System.out.println("impossible");
				return;
			}
			wanted[sym] = co;
			failed++;
		}
		int i = 0, j = 0;
		int res = Integer.MAX_VALUE;
		for (;;) {
			if (failed > 0) {
				if (j == n) break;
				have[v[j]]++;
				if (have[v[j]] == wanted[v[j]]) failed--;
				j++;
			} else {
				int dif = j - i;
				if (dif < res) res = dif;
				if (have[v[i]] == wanted[v[i]]) failed++;
				have[v[i]]--;
				i++;
			}
		}
		System.out.println(res);
	}
}
