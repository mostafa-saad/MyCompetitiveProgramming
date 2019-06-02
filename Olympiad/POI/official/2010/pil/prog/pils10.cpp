/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils10.cpp                                       *
 *   Autor:             Bartosz Gorski                                   *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Wyszukiwanie binarne i drzewa przedzialowe.      *
 *   Zlozonosc czasowa: O(n * (log n)^2)                                 *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

const int max_n = 3003000; 
const int max_pow = (1<<22); 
int a[max_n], t_max[max_pow], t_min[max_pow], n, m, t, l, c, r; 

int getDiff(int st, int en) { 
	int mn(min(a[st], a[en])) , mx(max(a[st], a[en])); 
	if (st != en) { 
		mn = min(mn, min(a[st + 1], a[en - 1])); 
		mx = max(mx, max(a[st + 1], a[en - 1])); 
	} 
	st += m; st /= 2; 
	en += m; en /= 2; 
	while (st / 2 != en / 2) { 
		if (st % 2 == 0) { 
			mn = min(mn, t_min[st + 1]); 
			mx = max(mx, t_max[st + 1]);             
		} 
		if (en % 2 == 1) { 
			mn = min(mn, t_min[en - 1]); 
			mx = max(mx, t_max[en - 1]);             
		}      
		st /= 2; 
	 	en /= 2; 
	} 
	return mx - mn;        
} 

int f(int p) { 
	if (p >= n) return n - 1; 
	return p;  
} 

void init() {
	m = 1; 
	while (m < n) m *= 2; 
	
	for (int i = m - 1; i >= 1; i--) { 
		if (i * 2 < m) { 
			t_max[i] = max(t_max[2 * i], t_max[2 * i + 1]);        
			t_min[i] = min(t_min[2 * i], t_min[2 * i + 1]); 
		} 
		else { 
			t_max[i] = max(a[f(2 * i - m)], a[f(2 * i + 1 - m)]); 
			t_min[i] = min(a[f(2 * i - m)], a[f(2 * i + 1 - m)]); 
		} 
	}
}

bool check(int l) {
	for(int i = 0; i < n - l + 1; ++i)
		if(getDiff(i, i + l - 1) <= t)
			return true;
	return false;
}	

int main()
{
	assert(scanf("%d%d", &t, &n) == 2);
	for(int i = 0; i < n; ++i)
		assert(scanf("%d", &a[i]) == 1);
	init();
	l = 1; r = n;
	while(l < r) {
		c = (l + r + 1) / 2;
		if(check(c))
			l = c;
		else
			r = c - 1;
	}
	printf("%d\n", l);
	return 0;
}
