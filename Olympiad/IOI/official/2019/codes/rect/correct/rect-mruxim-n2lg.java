import java.util.Arrays;

class rect {
	final int maxn = 3000 + 10;

	int n, m;

	int[][] H;

	short[][] L, R, U, D;
	short[][] UL, DL, LU, RU;

	long[] v;
	int vs;

	private void precalc() {
		L = new short[maxn][maxn];
		R = new short[maxn][maxn];
		U = new short[maxn][maxn];
		D = new short[maxn][maxn];

		UL = new short[maxn][maxn];
		DL = new short[maxn][maxn];
		LU = new short[maxn][maxn];
		RU = new short[maxn][maxn];

		short[] st = new short[maxn];

		for(int i = 0; i < n; i++) {
			int t = 0;
			for(int j = 0; j < m; j++) {
				while(t > 0 && H[i][j] > H[i][st[t-1]]) t--;
				L[i][j] = (t > 0 ? st[t-1] : -1);
				st[t++] = (short)j;
			}
		}

		for(int i = 0; i < n; i++) {
			int t = 0;
			for(int j = m; j-- > 0; ) {
				while(t > 0 && H[i][j] > H[i][st[t-1]]) t--;
				R[i][j] = (t > 0 ? st[t-1] : -1);
				st[t++] = (short)j;
			}
		}

		for(int j = 0; j < m; j++) {
			int t = 0;
			for(int i = 0; i < n; i++) {
				while(t > 0 && H[i][j] > H[st[t-1]][j]) t--;
				U[i][j] = (t > 0 ? st[t-1] : -1);
				st[t++] = (short)i;
			}
		}

		for(int j = 0; j < m; j++) {
			int t = 0;
			for(int i = n; i-- > 0; ) {
				while(t > 0 && H[i][j] > H[st[t-1]][j]) t--;
				D[i][j] = (t > 0 ? st[t-1] : -1);
				st[t++] = (short)i;
			}
		}

		for(int j = 0; j < m; j++) for(int i = 0; i < n; i++) {
			if(U[i][j] != -1) {
				if(j > 0 && U[i][j] == U[i][j-1]) UL[i][j] = UL[i][j-1];
				else if(j > 0 && i == D[U[i][j]][j-1]) UL[i][j] = DL[U[i][j]][j-1];
				else UL[i][j] = (short)j;
			}
			if(D[i][j] != -1) {
				if(j > 0 && D[i][j] == D[i][j-1]) DL[i][j] = DL[i][j-1];
				else if(j > 0 && i == U[D[i][j]][j-1]) DL[i][j] = UL[D[i][j]][j-1];
				else DL[i][j] = (short)j;
			}
		}

		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
			if(L[i][j] != -1) {
				if(i > 0 && L[i][j] == L[i-1][j]) LU[i][j] = LU[i-1][j];
				else if(i > 0 && j == R[i-1][L[i][j]]) LU[i][j] = RU[i-1][L[i][j]];
				else LU[i][j] = (short)i;
			}
			if(R[i][j] != -1) {
				if(i > 0 && R[i][j] == R[i-1][j]) RU[i][j] = RU[i-1][j];
				else if(i > 0 && j == L[i-1][R[i][j]]) RU[i][j] = LU[i-1][R[i][j]];
				else RU[i][j] = (short)i;
			}
		}
	}

	private void check(int i1, int i2, int j1, int j2) {
		if(i2 < i1 || j2 < j1) return;
		if(!((R[i2][j1-1]-1 == j2 && RU[i2][j1-1] <= i1) || (L[i2][j2+1]+1 == j1 && LU[i2][j2+1] <= i1))) return;
		if(!((D[i1-1][j2]-1 == i2 && DL[i1-1][j2] <= j1) || (U[i2+1][j2]+1 == i1 && UL[i2+1][j2] <= j1))) return;
		v[vs++] = (((long)i1 * maxn + i2) * maxn + j1) * maxn + j2;
	}

	public long count_rectangles(int[][] _H) {
		H = _H;
		n = H.length;
		m = H[0].length;

		precalc();

		v = new long[maxn * maxn * 4];
		vs = 0;

		for(int i = 1; i < n-1; i++) for(int j = 1; j < m-1; j++) {
			if(U[i+1][j] != -1 && L[i][j+1] != -1) check(U[i+1][j]+1, i, L[i][j+1]+1, j);
			if(U[i+1][j] != -1 && R[i][j-1] != -1) check(U[i+1][j]+1, i, j, R[i][j-1]-1);
			if(D[i-1][j] != -1 && L[i][j+1] != -1) check(i, D[i-1][j]-1, L[i][j+1]+1, j);
			if(D[i-1][j] != -1 && R[i][j-1] != -1) check(i, D[i-1][j]-1, j, R[i][j-1]-1);
			if(D[i-1][j] != -1 && R[D[i-1][j]-1][j-1] != -1) check(i, D[i-1][j]-1, j, R[D[i-1][j]-1][j-1]-1);
			if(D[i-1][j] != -1 && L[D[i-1][j]-1][j+1] != -1) check(i, D[i-1][j]-1, L[D[i-1][j]-1][j+1]+1, j);
		}

		Arrays.sort(v, 0, vs);
		int ans = 0;
		for(int i = 0; i < vs; i++)
			if(i == 0 || v[i] != v[i-1])
				ans++;
		return ans;
	}
}
