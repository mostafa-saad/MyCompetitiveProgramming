import java.util.*;
import java.io.*;

public class Main {
	private static class Iv implements Comparable<Iv> {
		int a, b, idx;
		Iv(int a, int b, int idx) {
			this.a = a;
			this.b = b;
			this.idx = idx;
		}
		public int compareTo(Iv other) {
			if (a != other.a) return a < other.a ? -1 : 1;
			if (b != other.b) return b < other.b ? -1 : 1;
			return 0;
		}
	}

	private ArrayList<Iv> ivs;
	private int N, M;
	public void run() {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		M = sc.nextInt();
		ivs = new ArrayList<Iv>();
		for (int i = 0; i < M; i++) {
			int a = sc.nextInt();
			int b = sc.nextInt();
			ivs.add(new Iv(a, b, i));
		}

		Collections.sort(ivs);

		boolean[] ans = new boolean[M];
		int reachA = 0, reachB = 0;
		for (int i = 0; i < M; i++) {
			Iv iv = ivs.get(i);
			if (reachA <= reachB) {
				if (iv.a > reachA + 1) fail();
				reachA = Math.max(reachA, iv.b);
				ans[iv.idx] = true;
			}
			else {
				if (iv.a > reachB + 1) fail();
				reachB = Math.max(reachB, iv.b);
				ans[iv.idx] = false;
			}
		}
		if (reachA < N || reachB < N) fail();

		for (int i = 0; i < M; i++) {
			System.out.print(ans[i] ? "1" : "0");
		}
		System.out.println();
	}

	void fail() {
		System.out.println("impossible");
		System.exit(0);
	}

	public static void main(String[] args) {
		new Main().run();
	}
}
