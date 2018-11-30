#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double ld;

vector<int> g[10101];
int u[10101];
ll d[10101];

int n;

ll test(int x){
	queue<int> bfs;
	for (int i=1;i<=n;i++){
		u[i]=0;
		d[i]=0;
	}
	bfs.push(x);
	u[x]=1;
	d[x]=1;
	while (!bfs.empty()){
		int t=bfs.front();
		bfs.pop();
		for (int nx:g[t]){
			if (u[nx]==0){
				u[nx]=1;
				d[nx]=d[t]+1;
				bfs.push(nx);
			}
		}
	}
	ll v=0;
	for (int i=1;i<=n;i++){
		if (u[i]==0){
			return -1;
		}
		else{
			v+=d[i];
		}
	}
	return v;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	assert(n>=1&&n<=5000);
	int m=0;
	for (int i=1;i<=n;i++){
		int k;
		cin>>k;
		m+=k;
		for (int j=0;j<k;j++){
			int a;
			cin>>a;
			assert(a>=1&&a<=n&&a!=i);
			g[a].push_back(i);
		}
	}
	assert(m>=1&&m<=10000);
	ll v=-1;
	for (int i=1;i<=n;i++){
		ll asd=test(i);
		if (asd!=-1){
			if (v==-1) v=asd;
			else v=min(v, asd);
		}
	}
	cout<<v<<endl;
}
