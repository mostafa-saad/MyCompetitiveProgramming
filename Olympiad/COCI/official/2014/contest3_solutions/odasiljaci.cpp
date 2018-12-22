#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 300010;

struct svjetlo {
	svjetlo(int _a) : a(_a), b(0) {}
	svjetlo(int _a, int _b) : a(_a), b(_b) {}

	int a, b;
};

int n, d, t[MAXN], x[MAXN], h[MAXN];
double s[2][MAXN];
vector <svjetlo> v;

void update(svjetlo &, int);
double drop(const svjetlo &);

int main() {
	scanf("%d%d", &n, &d);
	
	++n;
	
	for(int i = 1; i < n; ++i)
		scanf("%d%d%d", t + i, x + i, h + i);
	
	x[n] = d;
	++n;
	
	for(int k = 0; k < 2; ++k) {
        for(int i = 0; i < n - 1; ++i) {
        	for(; v.size() && h[v.back().a] <= h[i]; v.pop_back());
        	
        	if(v.size())
	    		for(update(v.back(), i); v.size() > 1; v.pop_back()) {
	    			update(v[v.size() - 2], i);
	    			if(drop(v.back()) < drop(v[v.size() - 2]))
	    				break;
	    		}
        	
        	if(t[i]) {
        		v.push_back(i);
        		s[k][i] = x[i];
        	}
        	else
        		if(v.size())
        			s[k][i] = min(drop(v.back()), (double)x[i + 1]);
        		else
        			s[k][i] = x[i + 1];
        }

	    if(!k) {
	        reverse(t, t + n);
	        reverse(x, x + n);
	        reverse(h, h + n);

	        for(int i = 0; i < n; ++i)
	            x[i] = d - x[i];
	           
	        v.clear();
	    }
    }

    reverse(s[1], s[1] + n);

    for(int i = 0; i < n; ++i)
        s[1][i] = d - s[1][i];

    double t = 0.;
    for(int i = 0; i < n - 1; ++i)
        if(s[0][i] > s[1][i + 1])
            t += s[0][i] - s[1][i + 1];

    printf("%.6lf\n", d - t);
    
	return 0;
}

void update(svjetlo &s, int c) {
	if(drop(s) < drop(svjetlo(s.a, c)))
		s.b = c;
}

double drop(const svjetlo &s) {
	int &x1 = x[s.a], &y1 = h[s.a], &x2 = x[s.b], &y2 = h[s.b];
	
	return ((double)x1 * (y1 - y2) - (double)y1 * (x1 - x2)) / (y1 - y2);
}
