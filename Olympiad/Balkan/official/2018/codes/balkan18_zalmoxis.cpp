#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 1000050;

int n, k, a[MAXN];

int dfs(int x, int c){
	if(x == 0 || c == 1){
		printf("%d ", x);
		return 1;
	}
	else{
		int x1 = dfs(x - 1, c / 2);
		int x2 = dfs(x - 1, (c + 1) / 2);
		return x1 + x2;
	}
}

int main(){
	cin >> n >> k;
	vector<int> v;
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		v.push_back(a[i]);
	}
	for(int i=0; i<30; i++){
		vector<int> b;
		for(int j=0; j<v.size(); ){
			if(v[j] > i){
				b.push_back(v[j]);
				j++;
			}
			else{
				int e = j;
				int ans = 0;
				while(e < v.size() && v[e] <= i){
					ans += (1 << v[e]);
					e++;
				}
				for(int k=j; k<e; k++){
					b.push_back(v[k]);
				}
				if((ans >> i) & 1) b.push_back(i);
				j = e;
			}
		}
		v = b;
	}
	int ptr = 0;
	int needy = n + k - (int)v.size();
	assert(needy >= 0);
	for(int i=0; i<v.size(); i++){
		if(ptr < n && v[i] == a[ptr]){
			printf("%d ", v[i]);
			ptr++;
		}
		else{
			needy -= dfs(v[i], needy + 1) - 1;
		}
	}
}
