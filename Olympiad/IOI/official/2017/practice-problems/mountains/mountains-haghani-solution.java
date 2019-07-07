class mountains {

	public int maximum_deevs(int y[]) {
		int n = y.length;
		int[][] dp = new int[n + 1][n + 1];
		Point[] p = new Point[n];
		for (int i = 0; i < n; i++)
			p[i] = new Point(i, y[i]);
		for (int r = 1; r <= n; r++) {
			int sum = 0, last = r - 1;
			Point bn = new Point(p[r - 1].getX(), p[r - 1].getY() - 1);
			dp[r - 1][r] = 1;
			for (int l = r - 2; l >= 0; l--)
			{
				dp[l][r] = dp[l][r - 1];
				if (ccw(p[l], bn, p[r - 1]) >= 0)
				{
					sum += dp[l + 1][last];
					last = l;
					bn = p[l];
				}
				dp[l][r] = Math.max(dp[l][r], 1 + sum + dp[l][last]);
			}
		}
		return dp[0][n];
	}

	long ccw(Point a, Point b, Point c) {
		return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
	}

}

class Point {
	
	private final long x;
	private final long y;

	public Point(long x, long y) {
		this.x = x;
		this.y = y;
	}

	public long getX() {
		return x;
	}

	public long getY() {
		return y;
	}

}

