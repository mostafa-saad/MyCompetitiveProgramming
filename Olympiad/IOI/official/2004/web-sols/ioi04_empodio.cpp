#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[1100005];
bool vis[1100005];

vector<pi> v;
stack<int> s_high, s_low;
set<pi> radix;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	a[n] = -1e9;
	s_low.push(n);
	int e = n-1;
	for(int i=n-1; i>=0; i--){
		while(!s_low.empty() && a[s_low.top()] > a[i]){
			s_low.pop();
		}
		while(!s_high.empty() && a[s_high.top()] < a[i]){
			vis[s_high.top()] = 0;
			pi obj = pi(a[s_high.top()] - s_high.top(), s_high.top());
			if(radix.find(obj) != radix.end()){
				radix.erase(obj);
			}
			s_high.pop();
		}
		int lim = min(e, s_low.top());
		int p = a[i] - i;
		set<pi> ::iterator t = radix.lower_bound(pi(p, -1));
		if(t != radix.end() && t->first == p && t->second <= lim){
			v.push_back(pi(i, t->second));
			e = i;
		}
		radix.insert(pi(p, i));
		s_low.push(i);
		s_high.push(i);
		vis[i] = 1;
	}
	reverse(v.begin(), v.end());
	printf("%d\n",v.size());
	for(int i=0; i<v.size(); i++){
		printf("%d %d\n",v[i].first+1, 1+v[i].second);
	}
}