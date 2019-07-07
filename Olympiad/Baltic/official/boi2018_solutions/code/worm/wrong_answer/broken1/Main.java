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

class Main {
	public static void main(String[] args) {
		Grader g = new Grader();
		if (g.K > 1) {
			System.err.println("not implemented");
		}
		else if (g.M > 1) {
			new Two().run(g);
		}
		else {
			System.err.println("not implemented");
		}
	}
}

class Two {
	void run(Grader g) {
		int lox = 0, hix = g.N;
		int loy = 0, hiy = g.M;
		while (lox+1 < hix || loy+1 < hiy) {
			if (hix-lox > hiy-loy) {
				int midx = (hix + lox) / 2;
				int best = -1, maxv = -1;
				for (int y = loy; y < hiy; y++) {
					int v = g.query(midx, y, 0);
					if (v > maxv) {
						maxv = v;
						best = y;
					}
				}
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
			}
			else {
				int midy = (hiy + loy) / 2;
				int best = -1, maxv = -1;
				for (int x = lox; x < hix; x++) {
					int v = g.query(x, midy, 0);
					if (v > maxv) {
						maxv = v;
						best = x;
					}
				}
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
			}
		}

		g.guess(lox, loy, 0);
	}
}
