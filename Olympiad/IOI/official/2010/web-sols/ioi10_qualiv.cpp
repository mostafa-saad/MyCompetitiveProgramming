int r,c,w,h,a[3005][3005];
int s[3005][3005], t[3005][3005];
 
int eval(int x){
	for (int i=1; i<=r; i++) {
	    for (int j=1; j<=c; j++) {
	        s[i][j] = s[i][j-1] + s[i-1][j] - s[i-1][j-1] + (a[i][j] > x);
	        t[i][j] = t[i][j-1] + t[i-1][j] - t[i-1][j-1] + (a[i][j] < x);
	    }
	}
	for (int i=1; i<=r-h+1; i++) {
	    for (int j=1; j<=c-w+1; j++) {
	        int sum_lower = t[i+h-1][j+w-1] - t[i-1][j+w-1] - t[i+h-1][j-1] + t[i-1][j-1];
	        int sum_higher = s[i+h-1][j+w-1] - s[i-1][j+w-1] - s[i+h-1][j-1] + s[i-1][j-1];
	        if(sum_higher <= sum_lower) return 1;
	    }
	}
	return 0;
}
 
int rectangle( int _n , int _m , int _r , int _c , int M[3001][3001] ){
	r = _n;
	c = _m;
	h = _r;
	w = _c;
    for (int i=1; i<=r; i++) {
        for (int j=1; j<=c; j++) {
        	a[i][j] = M[i-1][j-1];
        }
    }
    int s = 1, e = r*c;
    while (s != e) {
        int m = (s+e)/2;
        if(eval(m)) e = m;
        else s = m+1;
    }
    return e;
}