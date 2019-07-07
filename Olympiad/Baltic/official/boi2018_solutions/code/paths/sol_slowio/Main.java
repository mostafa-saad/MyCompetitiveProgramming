import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	private ArrayList<Integer>[] eds;
	private int[] col;
	private long[][] memo;
	private int N, M, K;
	public void run() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		K = sc.nextInt();
		eds = new ArrayList[N];
		col = new int[N];
		memo = new long[1 << K][N];
		for (int i = 0; i < N; i++) eds[i] = new ArrayList<Integer>();
		for (int i = 0; i < N; i++) col[i] = sc.nextInt() - 1;
		for (int i = 0; i < M; i++) {
			int a = sc.nextInt();
			int b = sc.nextInt();
			a--;
			b--;
			eds[a].add(b);
			eds[b].add(a);
		}

		long res = 0;
		for (int i = 0; i < N; i++) {
			res += rec(1 << col[i], i);
		}
		res -= N;
		System.out.println(res);
	}

	long rec(int bits, int at) {
		if (memo[bits][at] != 0) {
			return memo[bits][at];
		}
		long ret = 1;
		for (int x : eds[at]) {
			int bits2 = bits | (1 << col[x]);
			if (bits != bits2) {
				ret += rec(bits2, x);
			}
		}
		memo[bits][at] = ret;
		return ret;
	}
}
