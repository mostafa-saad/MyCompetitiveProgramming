import java.io.*;

class Grader {
	public int N, M, K, Q;

	public Grader() {
		try {
			String[] ar = new BufferedReader(new InputStreamReader(System.in)).readLine().split(" ");
			N = Integer.parseInt(ar[0]);
			M = Integer.parseInt(ar[1]);
			K = Integer.parseInt(ar[2]);
			Q = Integer.parseInt(ar[3]);
			is = new FileInputStream(FileDescriptor.in);
			os = new FileOutputStream(FileDescriptor.out);
			buf = new byte[100];
		} catch(Exception e) { throw new RuntimeException(e); }
	}

	public int query(int x, int y, int z) {
		if (x < 0 || y < 0 || z < 0 || x >= N || y >= M || z >= K) return -1;
		try {
			os.write(("? " + (x+1) + " " + (y+1) + " " + (z+1) + "\n").getBytes());
			int ret = 0;
			for (;;) {
				int count = is.read(buf);
				if (count == 0 || buf[0] == 45) System.exit(0);
				for (int i = 0; i < count; i++) {
					if (buf[i] == 10) return ret;
					ret *= 10;
					ret += (int)(buf[i] - 48);
				}
			}
		} catch(Exception e) { throw new RuntimeException(e); }
	}

	public void guess(int x, int y, int z) {
		try {
			os.write(("! " + (x+1) + " " + (y+1) + " " + (z+1) + "\n").getBytes());
			System.exit(0);
		} catch(Exception e) { throw new RuntimeException(e); }
	}

	private FileInputStream is;
	private FileOutputStream os;
	private byte[] buf;
}

public class Main {
	public static void main(String[] args) {
		Grader g = new Grader();
		if (g.K > 1) {
			new Three().run(g);
		}
		else if (g.M > 1) {
			new Two().run(g);
		}
		else {
			new One().run(g);
		}
	}
}

class One {
	Grader g;
	double phi = 0.6180339887498949;
	void run(Grader g) {
		this.g = g;
		int x = (int)(g.N * phi);
		int fx = g.query(x, 0, 0);
		int y = rec(0, g.N, x, fx);
		g.guess(y, 0, 0);
	}

	// Find a local maximum with value >= fx in [lo, hi), given that f(x) = fx
	int rec(int lo, int hi, int x, int fx) {
		if (lo + 1 == hi) {
			return lo;
		}
		if (x < lo) throw new RuntimeException("a");
		if (x >= hi) throw new RuntimeException("b");
		int y = hi-1 - (x - lo);
		if (lo + 2 == hi) {
			if (x == y) throw new RuntimeException("c");
			int fy = g.query(y, 0, 0);
			return fy > fx ? y : x;
		}

		if (y <= x) {
			y = lo + (int)((x - lo) * phi);
		} else {
			y = hi-1 - (int)((hi-1 - x) * phi);
		}

		if (y < lo) throw new RuntimeException("d");
		if (y >= hi) throw new RuntimeException("e");
		if (x == y) throw new RuntimeException("f");

		int fy = g.query(y, 0, 0);
		if (fx >= fy) {
			if (y < x) return rec(y+1, hi, x, fx);
			else return rec(lo, y, x, fx);
		} else {
			if (x < y) return rec(x+1, hi, y, fy);
			else return rec(lo, x, y, fy);
		}
	}
}

class Two {
	void run(Grader g) {
		int lox = 0, hix = g.N;
		int loy = 0, hiy = g.M;
		int candx = -1, candy = -1, candv = -1;
		while (lox+1 < hix || loy+1 < hiy) {
			if (hix-lox > hiy-loy) {
				int midx = (hix + lox) / 2;
				if (midx == candx) --midx;
				int best = -1, maxv = -1;
				for (int y = loy; y < hiy; y++) {
					int v = g.query(midx, y, 0);
					if (v > maxv) {
						maxv = v;
						best = y;
					}
				}
				if (candv >= maxv) {
					if (candx < midx) hix = midx;
					else lox = midx + 1;
				} else {
					int left = g.query(midx-1, best, 0);
					int right = g.query(midx+1, best, 0);
					if (left > maxv) {
						hix = midx;
					}
					else if (right > maxv) {
						lox = midx + 1;
					}
					else {
						g.guess(midx, best, 0);
					}
					candv = maxv;
					candx = midx;
					candy = best;
				}
			}
			else {
				int midy = (hiy + loy) / 2;
				if (midy == candy) --midy;
				int best = -1, maxv = -1;
				for (int x = lox; x < hix; x++) {
					int v = g.query(x, midy, 0);
					if (v > maxv) {
						maxv = v;
						best = x;
					}
				}
				if (candv >= maxv) {
					if (candy < midy) hiy = midy;
					else loy = midy + 1;
				} else {
					int left = g.query(best, midy-1, 0);
					int right = g.query(best, midy+1, 0);
					if (left > maxv) {
						hiy = midy;
					}
					else if (right > maxv) {
						loy = midy + 1;
					}
					else {
						g.guess(best, midy, 0);
					}
					candv = maxv;
					candx = best;
					candy = midy;
				}
			}
		}

		g.guess(lox, loy, 0);
	}
}

class Three {
	int bestv = -1;
	int bestx = -1;
	int besty = -1;
	int bestz = -1;

	int rand(int lim) {
		return (int)Math.floor(Math.random() * lim);
	}

	void test(Grader g, int x, int y, int z) {
		int v = g.query(x, y, z);
		if (v > bestv) {
			bestv = v;
			bestx = x;
			besty = y;
			bestz = z;
		}
	}

	void run(Grader g) {
		for (int i = 0; i < g.Q / 2; i++) {
			test(g, rand(g.N), rand(g.M), rand(g.K));
		}

		int[] dx = {-1,0,0,0,0,1};
		int[] dy = {0,-1,0,0,1,0};
		int[] dz = {0,0,-1,1,0,0};
		while (true) {
			boolean found = false;
			for (int i = 0; i < 6; i++) {
				int x = bestx + dx[i];
				int y = besty + dy[i];
				int z = bestz + dz[i];
				if (x < 0 || y < 0 || z < 0 || x >= g.N || y >= g.M || z >= g.K) continue;
				int v = g.query(x, y, z);
				if (v > bestv) {
					bestv = v;
					bestx = x;
					besty = y;
					bestz = z;
					found = true;
					break;
				}
			}
			if (!found) {
				break;
			}
		}

		g.guess(bestx, besty, bestz);
	}
}
