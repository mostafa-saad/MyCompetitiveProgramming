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
		Kattio sc = new Kattio(System.in);
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
