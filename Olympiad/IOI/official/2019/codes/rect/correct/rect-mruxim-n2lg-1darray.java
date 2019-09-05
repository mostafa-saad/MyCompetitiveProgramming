import java.util.Arrays;

class rect {
	final int maxn = 3000 + 10;

	int n, m;

	int[] H;

	short[] L, R, U, D;
	short[] UL, DL, LU, RU;

	long[] v;
	int vs;

	private void precalc() {
		L = new short[maxn*maxn];
		R = new short[maxn*maxn];
		U = new short[maxn*maxn];
		D = new short[maxn*maxn];

		UL = new short[maxn*maxn];
		DL = new short[maxn*maxn];
		LU = new short[maxn*maxn];
		RU = new short[maxn*maxn];

		short[] st = new short[maxn];

		for(int i = 0; i < n; i++) {
			int t = 0;
			for(int j = 0; j < m; j++) {
				while(t > 0 && H[i*maxn+j] > H[i*maxn+st[t-1]]) t--;
				L[i*maxn+j] = (t > 0 ? st[t-1] : -1);
				st[t++] = (short)j;
			}
		}

		for(int i = 0; i < n; i++) {
			int t = 0;
			for(int j = m; j-- > 0; ) {
				while(t > 0 && H[i*maxn+j] > H[i*maxn+st[t-1]]) t--;
				R[i*maxn+j] = (t > 0 ? st[t-1] : -1);
				st[t++] = (short)j;
			}
		}

		for(int j = 0; j < m; j++) {
			int t = 0;
			for(int i = 0; i < n; i++) {
				while(t > 0 && H[i*maxn+j] > H[st[t-1]*maxn+j]) t--;
				U[i*maxn+j] = (t > 0 ? st[t-1] : -1);
				st[t++] = (short)i;
			}
		}

		for(int j = 0; j < m; j++) {
			int t = 0;
			for(int i = n; i-- > 0; ) {
				while(t > 0 && H[i*maxn+j] > H[st[t-1]*maxn+j]) t--;
				D[i*maxn+j] = (t > 0 ? st[t-1] : -1);
				st[t++] = (short)i;
			}
		}

		for(int j = 0; j < m; j++) for(int i = 0; i < n; i++) {
			if(U[i*maxn+j] != -1) {
				if(j > 0 && U[i*maxn+j] == U[i*maxn+j-1]) UL[i*maxn+j] = UL[i*maxn+j-1];
				else if(j > 0 && i == D[U[i*maxn+j]*maxn+j-1]) UL[i*maxn+j] = DL[U[i*maxn+j]*maxn+j-1];
				else UL[i*maxn+j] = (short)j;
			}
			if(D[i*maxn+j] != -1) {
				if(j > 0 && D[i*maxn+j] == D[i*maxn+j-1]) DL[i*maxn+j] = DL[i*maxn+j-1];
				else if(j > 0 && i == U[D[i*maxn+j]*maxn+j-1]) DL[i*maxn+j] = UL[D[i*maxn+j]*maxn+j-1];
				else DL[i*maxn+j] = (short)j;
			}
		}

		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
			if(L[i*maxn+j] != -1) {
				if(i > 0 && L[i*maxn+j] == L[(i-1)*maxn+j]) LU[i*maxn+j] = LU[(i-1)*maxn+j];
				else if(i > 0 && j == R[(i-1)*maxn+L[i*maxn+j]]) LU[i*maxn+j] = RU[(i-1)*maxn+L[i*maxn+j]];
				else LU[i*maxn+j] = (short)i;
			}
			if(R[i*maxn+j] != -1) {
				if(i > 0 && R[i*maxn+j] == R[(i-1)*maxn+j]) RU[i*maxn+j] = RU[(i-1)*maxn+j];
				else if(i > 0 && j == L[(i-1)*maxn+R[i*maxn+j]]) RU[i*maxn+j] = LU[(i-1)*maxn+R[i*maxn+j]];
				else RU[i*maxn+j] = (short)i;
			}
		}
	}

	private void check(int i1, int i2, int j1, int j2) {
		if(i2 < i1 || j2 < j1) return;
		if(!((R[i2*maxn+j1-1]-1 == j2 && RU[i2*maxn+j1-1] <= i1) || (L[i2*maxn+j2+1]+1 == j1 && LU[i2*maxn+j2+1] <= i1))) return;
		if(!((D[(i1-1)*maxn+j2]-1 == i2 && DL[(i1-1)*maxn+j2] <= j1) || (U[(i2+1)*maxn+j2]+1 == i1 && UL[(i2+1)*maxn+j2] <= j1))) return;
		v[vs++] = (((long)i1 * maxn + i2) * maxn + j1) * maxn + j2;
	}

	public long count_rectangles(int[][] _H) {
		n = _H.length;
		m = _H[0].length;
		H = new int[maxn*maxn];
		for (int i=0; i<n; ++i)
			for (int j=0; j<m; ++j)
				H[i*maxn+j] = _H[i][j];

		precalc();

		v = new long[maxn * maxn * 4];
		vs = 0;

		for(int i = 1; i < n-1; i++) for(int j = 1; j < m-1; j++) {
			if(U[(i+1)*maxn+j] != -1 && L[i*maxn+j+1] != -1) check(U[(i+1)*maxn+j]+1, i, L[i*maxn+j+1]+1, j);
			if(U[(i+1)*maxn+j] != -1 && R[i*maxn+j-1] != -1) check(U[(i+1)*maxn+j]+1, i, j, R[i*maxn+j-1]-1);
			if(D[(i-1)*maxn+j] != -1 && L[i*maxn+j+1] != -1) check(i, D[(i-1)*maxn+j]-1, L[i*maxn+j+1]+1, j);
			if(D[(i-1)*maxn+j] != -1 && R[i*maxn+j-1] != -1) check(i, D[(i-1)*maxn+j]-1, j, R[i*maxn+j-1]-1);
			if(D[(i-1)*maxn+j] != -1 && R[(D[(i-1)*maxn+j]-1)*maxn+j-1] != -1) check(i, D[(i-1)*maxn+j]-1, j, R[(D[(i-1)*maxn+j]-1)*maxn+j-1]-1);
			if(D[(i-1)*maxn+j] != -1 && L[(D[(i-1)*maxn+j]-1)*maxn+j+1] != -1) check(i, D[(i-1)*maxn+j]-1, L[(D[(i-1)*maxn+j]-1)*maxn+j+1]+1, j);
		}

		Arrays.sort(v, 0, vs);
		int ans = 0;
		for(int i = 0; i < vs; i++)
			if(i == 0 || v[i] != v[i-1])
				ans++;
		return ans;
	}
}
