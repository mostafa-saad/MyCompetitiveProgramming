/*
 * Author: Gyeonggeun Kim(kriii)
 * Time Complexity: O(N lg N)
 */
#include "gap.h"
#include <algorithm>
using namespace std;

long long findGap(int T, int N)
{
	long long mn, mx;
	long long ans = 0;
	MinMax(0,2e18,&mn,&mx);

	if (T == 1){
		for (int i=1;i<(N+1)/2;i++){
			long long mmn, mmx;
			MinMax(mn+1,mx-1,&mmn,&mmx);
			ans = max(ans,mmn-mn);
			ans = max(ans,mx-mmx);
			mn = mmn;
			mx = mmx;
		}
		ans = max(ans,mx-mn);
	}
	else{
		long long sz = (mx - mn + N - 1) / N;
		long long last = mn;
		for (long long s=mn+1,e=mn+sz,i=0;i<N;s+=sz,e+=sz,i++){
			if (e >= mx) e = mx - 1;
			if (s > e) break;
			long long mmn, mmx;
			MinMax(s,e,&mmn,&mmx);
			if (mmn != -1){
				ans = max(ans,mmn-last);
				last = mmx;
			}
		}
		ans = max(ans,mx-last);
	}
	return ans;
}
