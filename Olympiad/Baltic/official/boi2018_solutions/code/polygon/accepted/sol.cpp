#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <stack>
using namespace std;

#define rep(i,a,b) for(int i = (a); i < (b); ++i)
#define trav(x, v) for(auto &x : (v))

int match00(vector<bool> necklace){ // given 0-1-necklace, how many pairs of adjacent 0's can be formed?
	int len = (int) necklace.size();

	bool allzero = true;
	rep(i,0,len) if(necklace[i]) allzero = false;

	if(allzero) return len / 2;

	int ans = 0;

	rep(i,0,len){
		int i1 = (i+1) % len;
		if(necklace[i] && !necklace[i1]){ //start of segment of 0's
			int curlen = 0;
			while(!necklace[i1]){
				++curlen;
				i1 = (i1 + 1) % len;
			}
			ans += curlen / 2;
		}
	}

	return ans;
}

int main() {
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

	vector<vector<int>> children(n);

	rep(i,0,n) children[ parent[i] ].push_back(i);

	int totmatch = 0;
	vector<bool> vis(n, false);
	vector<int> maxmatch(n, 0); // we don't really need
	vector<bool> aminmatch(n, false); // to store these
	vector<bool> oncycle(n, false);

	function<void(int)> calc = [&](int v){ // computes maxmatch[v]: the size of the maximal mathching in the subtree rooted at v, and aminmatch[v], which says if v is in all of these maximal matchings
		trav(u, children[v]) if(!oncycle[u]){
			calc(u);
			maxmatch[v] += maxmatch[u];

			if( !aminmatch[u] ) aminmatch[v] = true;
		}

		if( aminmatch[v] ) maxmatch[v]++;
	};

	rep(i,0,n) if(!vis[i]){
		
		int sizeofcomp = 0;
		stack<int> st;
		st.push(i);
		vis[i] = true;

		while(!st.empty()){
			int j = st.top();
			st.pop();
			
			++sizeofcomp;

			if(!vis[ parent[j] ]){
				vis[parent[j]] = true;
				st.push(parent[j]);
			}
			trav(k, children[j]) if(!vis[k]){
				vis[k] = true;
				st.push(k);
			}
		}

		int j = i;
		rep(_,0,sizeofcomp) j = parent[j];
		// now j is on the cycle

		vector<int> cycle;

		int j1 = j;
		do {
			oncycle[j1] = true;
			cycle.push_back(j1);
			j1 = parent[j1];
		} while(j1 != j);

		int curmatch = 0;
		vector<bool> necklace;

		trav(v, cycle){
			calc(v);
			curmatch += maxmatch[v];
			necklace.push_back( aminmatch[v] );
		}

		if(cycle.size() == 2){
			curmatch -= necklace[0] + necklace[1]; // if we have a relationship, then we shouldn't use those nodes anywhere else
			curmatch += 2;
		} else {
			curmatch += match00(necklace);
		}
		
		totmatch += curmatch;

	}

	cout << n - totmatch << endl;
}
