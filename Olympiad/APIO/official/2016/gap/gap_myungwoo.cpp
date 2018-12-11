/*
 * Author: Myungwoo Chun(myungwoo)
 * Time Complexity: O(N lg N)
 */
#include "gap.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
typedef long long lld;

lld findGap(int T, int N)
{
	if (T == 1){
		lld p = 0, q = (lld)1e18 + 1;
		vector <lld> arr;
		for (;;){
			lld mn, mx;
			MinMax(p+1, q-1, &mn, &mx);
			arr.pb(mn); arr.pb(mx);
			if (mn == mx || sz(arr) == N) break;
			p = mn, q = mx;
		}
		sort(all(arr));
		lld ans = 0;
		for (int i=1;i<sz(arr);i++)
			ans = max(ans, arr[i]-arr[i-1]);
		return ans;
	}else{
		lld mn, mx;
		MinMax(1, 1e18, &mn, &mx);
		if (N == 2) return mx-mn;
		lld size = mx-mn-1;
		lld s = mn+1, last = mn, ans = 0;
		for (int i=0;i<N-1;i++){
			lld e = s + size / (N-1) - 1;
			if (i < size % (N-1)) e++;
			MinMax(s, e, &mn, &mx);
			if (mn != -1){
				ans = max(ans, mn - last);
				last = mx;
			}
			s = e+1;
		}
		return max(ans, s - last);
	}
	return 0;
}
