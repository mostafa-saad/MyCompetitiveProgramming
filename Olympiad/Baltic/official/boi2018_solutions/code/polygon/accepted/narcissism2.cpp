#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); ++i)
#define trav(x, v) for(auto &x : (v))

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	if(n % 2 == 1){
		cout << -1 << endl;
		return 0;
	}
	map<string,int> rename;
	int curix = 0;
	vector<int> parent(n);
	rep(_,0,n){
		string s, t;
		cin >> s >> t;
		if(!rename.count(s)) rename[s] = curix++;
		if(!rename.count(t)) rename[t] = curix++;
		parent[ rename[s] ] = rename[t];
	}
	vector<int> deg(n, 0);
	rep(i,0,n) if( i != parent[i] ) ++deg[parent[i]];
	stack<int> leaf;
	rep(i,0,n) if(deg[i] == 0) leaf.push(i);
	vector<int> maxmatch(n, 0);
	vector<bool> aminmatch(n, false);
	int ans = n;
	while(!leaf.empty()){
		int a = leaf.top();
		leaf.pop();
		if( aminmatch[a] ) maxmatch[a]++;
		else aminmatch[parent[a]] = true;
		if( a == parent[a] ) ans -= maxmatch[a];
		else maxmatch[parent[a]] += maxmatch[a];
		if( --deg[parent[a]] == 0) leaf.push( parent[a] );
	}
	cout << ans << endl;
}
