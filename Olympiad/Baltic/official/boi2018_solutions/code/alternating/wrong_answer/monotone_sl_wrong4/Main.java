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
		Kattio sc = new Kattio(System.in);
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
				// if (iv.a > reachA + 1) fail();
				reachA = Math.max(reachA, iv.b);
				ans[iv.idx] = true;
			}
			else {
				// if (iv.a > reachB + 1) fail();
				reachB = Math.max(reachB, iv.b);
				ans[iv.idx] = false;
			}
		}
		if (reachA < N || reachB < N) fail();

		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < M; i++) {
			sb.append(ans[i] ? '1' : '0');
		}
		System.out.println(sb.toString());
	}

	void fail() {
		System.out.println("impossible");
		System.exit(0);
	}

	public static void main(String[] args) {
		new Main().run();
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
