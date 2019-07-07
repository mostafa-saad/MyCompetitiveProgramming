import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		new Main().run();
	}
	private int[] target;
	private int N, renIndex = 0;
	private Map<String, Integer> ren;
	private boolean[] visited;
	private int[][] ch;
	public void run() {
		Kattio sc = new Kattio(System.in);
		N = sc.nextInt();
		if (N % 2 == 1) {
			System.out.println("-1");
			return;
		}

		target = new int[N];
		ren = new HashMap<String, Integer>();
		int[] indeg = new int[N];
		for (int i = 0; i < N; i++) {
			String a = sc.next();
			String b = sc.next();
			int aa = rename(a);
			int bb = rename(b);
			target[aa] = bb;
			indeg[bb]++;
		}

		ch = new int[N][];
		for (int i = 0; i < N; i++) {
			ch[i] = new int[indeg[i]];
			indeg[i] = 0;
		}

		for (int i = 0; i < N; i++) {
			ch[target[i]][indeg[target[i]]] = i;
			indeg[target[i]] += 1;
		}

		int res = 0;

		ArrayList<Integer> cycle = new ArrayList<>();
		visited = new boolean[N];
		for (int orig = 0; orig < N; orig++) {
			if (visited[orig]) continue;
			int at = orig;
			while (!visited[at]) {
				visited[at] = true;
				at = target[at];
			}

			cycle.clear();
			int start = at;
			do {
				cycle.add(at);
				at = target[at];
			} while (at != start);

			int S = cycle.size();
			int[] yes = new int[S];
			int[] no = new int[S];
			int[] maybe = new int[S];
			for (int i = 0; i < S; i++) {
				int prev = cycle.get((i == 0 ? S : i) - 1);
				int cur = cycle.get(i);
				int[] nch = new int[ch[cur].length - 1];
				int ind = 0;
				for (int j = 0; j < ch[cur].length; j++) {
					if (ch[cur][j] != prev) {
						nch[ind] = ch[cur][j];
						ind++;
					}
				}
				assert ind == nch.length;
				ch[cur] = nch;

				int[] r = rec(cur);
				no[i] = r[0];
				yes[i] = r[1];
				if (yes[i] > no[i]) throw new RuntimeException("a");
			}

			if (S == 1) {
				res += no[0];
			} else if (S == 2) {
				res += yes[0] + yes[1];
			} else {
				int[] dp = new int[S + 1];
				dp[S] = Integer.MAX_VALUE / 2;
				dp[S-1] = yes[S-1] + yes[0] + 1;
				for (int i = S-2; i >= 1; i--) {
					dp[i] = Math.min(no[i] + dp[i+1], yes[i] + yes[i+1] + 1 + dp[i+2]);
				}
				int r1 = dp[1];

				dp[S] = 0;
				dp[S-1] = no[S-1];
				for (int i = S-2; i >= 0; i--) {
					dp[i] = Math.min(no[i] + dp[i+1], yes[i] + yes[i+1] + 1 + dp[i+2]);
				}
				int r2 = dp[0];

				res += Math.min(r1, r2);
			}
		}

		System.out.println(res);
	}

	int[] rec(int at) {
		visited[at] = true;
		int bestWin = Integer.MIN_VALUE;
		int res = 0;
		for (int i = 0; i < ch[at].length; i++) {
			int x = ch[at][i];
			int[] r = rec(x);
			res += r[0];
			bestWin = Math.max(bestWin, r[0] - r[1]);
		}
		int res2 = res + 1;
		if (bestWin != Integer.MIN_VALUE) {
			res2 = Math.min(res2, res - bestWin + 1);
		}
		return new int[]{res2, res};
	}

	int rename(String s) {
		if (ren.containsKey(s)) {
			return ren.get(s);
		}
		int r = renIndex;
		renIndex++;
		ren.put(s, r);
		return r;
	}
}

class Kattio extends PrintWriter {
	public Kattio(InputStream i) {
		super(new BufferedOutputStream(System.out));
		r = new BufferedReader(new InputStreamReader(i));
	}
	public Kattio(InputStream i, OutputStream o) {
		super(new BufferedOutputStream(o));
		r = new BufferedReader(new InputStreamReader(i));
	}

	public boolean hasMoreTokens() {
		return peekToken() != null;
	}

	public int nextInt() {
		return Integer.parseInt(nextToken());
	}

	public double getDouble() { 
		return Double.parseDouble(nextToken());
	}

	public long getLong() {
		return Long.parseLong(nextToken());
	}

	public String next() {
		return nextToken();
	}


	private BufferedReader r;
	private String line;
	private StringTokenizer st;
	private String token;

	private String peekToken() {
		if (token == null) 
			try {
				while (st == null || !st.hasMoreTokens()) {
					line = r.readLine();
					if (line == null) return null;
					st = new StringTokenizer(line);
				}
				token = st.nextToken();
			} catch (IOException e) { }
		return token;
	}

	private String nextToken() {
		String ans = peekToken();
		token = null;
		return ans;
	}
}
