import java.util.*;
import java.io.*;

public class Main {
	public static void main(String[] args) {
		Kattio sc = new Kattio(System.in);
		int n = sc.getInt();
		int k = sc.getInt();
		int r = sc.getInt();
		int[] v = new int[n];
		int[] counts = new int[k];
		for (int i = 0; i < n; i++) {
			v[i] = sc.getInt();
			counts[v[i]]++;
		}

		int failed = 0;
		int[] have = new int[k];
		int[] wanted = new int[k];
		for (int i = 0; i < r; i++) {
			int sym, co;
			sym = sc.getInt();
			co = sc.getInt();
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

	public int getInt() {
		return Integer.parseInt(nextToken());
	}

	public double getDouble() { 
		return Double.parseDouble(nextToken());
	}

	public long getLong() {
		return Long.parseLong(nextToken());
	}

	public String getWord() {
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
