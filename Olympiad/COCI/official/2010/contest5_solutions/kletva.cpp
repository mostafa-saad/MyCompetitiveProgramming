//HONI solution - no reflections
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

vector<vector<pair<int, int> > > keys;

int main(){
	int w, l, n;

	scanf("%d %d %d", &w, &l, &n);

	for (int i = 0; i < n; i++){
		vector<int> upper, lower;
		int minimal = -1;

		for (int j = 0; j < l; j++){
			int a;
			scanf("%d", &a);
			upper.push_back(a);
		}
		for (int j = 0; j < l; j++){
			int a;
			scanf("%d", &a);
			lower.push_back(a);
			if ( minimal == -1 || minimal > a )
				minimal = a;
		}

		vector<char> ok(keys.size(), 1);
		vector<pair<int, int> > me;

		for (int j = 0; j < l; j++){
			int thisoff, thiswidth;
			thisoff = lower[j] - minimal;
			thiswidth = w - upper[j] - lower[j];
			me.push_back(make_pair(thisoff, thiswidth));

			for (int k = 0; k < keys.size(); k++)
				if ( ok[k] && thisoff != keys[k][j].first || thiswidth != keys[k][j].second ) {
					ok[k] = 0;					
				}
		}	

		char isok = 0;
		for (int k = 0; k < keys.size(); k++)
			if ( ok[k] ) isok = 1;	

		if ( !isok || keys.size() == 0 ){
			keys.push_back(me);
		}
	}

	printf("%d\n", keys.size());
	return 0;
}
