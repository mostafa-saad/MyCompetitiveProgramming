#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#define SZ(x) ((int)(x).size())
#define INF 1000

using namespace std;

vector<char> start; 
vector<pair<int, int> > moves;

set<vector<char> > visited;
map<vector<char>,  set<pair<int, pair<int, vector<char> > > >::iterator > locator;
set<pair<int, pair<int, vector<char> > > > opened;

vector<vector<int> > ndist;
vector<vector<int> > ndist_move;

char h_value(const vector<char>& state){
	int ret = 0;
	
	for (int i = 0; i < SZ(state); i++) {
		if (state[i] != i + 1)
			ret++;
	}

	return ret;
}

int cnt;

int solve(const vector<char>& state, const int& cutoff){	 
	int value = h_value(state);
	locator[state] = opened.insert(make_pair(value, make_pair(0, state))).first;

	while ( !opened.empty() ){
		vector<char> x = (*opened.begin()).second.second;
		int dist = (*opened.begin()).second.first;
		visited.insert(x);
		opened.erase(opened.begin());

		cnt++;
		if ( (cnt & (1<<20)) == 0) {
			printf("%d %d %d\n", cnt, dist, h_value(x));
		}
	
/*		printf("X: ");
		for (int i = 0; i < SZ(x); i++)
			printf("%d ", x[i]);
		printf("\n");*/
	
		char ok = 1;
		for (int i = 0; i < SZ(x) && ok; i++)
			if ( x[i] != i + 1 ) 
				ok = 0;

		if ( ok ) return dist;

		for (int i = 0; i < SZ(moves); i++){
			swap(x[moves[i].first], x[moves[i].second]);
			if ( visited.find(x) == visited.end() ){
				map<vector<char>,  set<pair<int, pair<int, vector<char> > > >::iterator >::iterator l = locator.find(x);
				value = h_value(x) + dist + 1;
				if ( value <= cutoff ){
					if ( l != locator.end() ) {
						if ( (*((*l).second)).first > value ) {
							opened.erase((*l).second);	
							locator[state] = opened.insert(make_pair(value, make_pair(dist + 1, x))).first;
						}
					}
					else {
						locator[state] = opened.insert(make_pair(value, make_pair(dist + 1, x))).first;
					}
				}
			}
			swap(x[moves[i].first], x[moves[i].second]);
		}
	}

	return -1;
}

int greedy_distance(const vector<char>& state){
	vector<char> x = state;
	int ret = 0;
	for (int i = 1; i <= SZ(state); i++){
		int loc = 0;
		for (; loc < SZ(x) && x[loc] != i; loc++);
		while ( loc != i - 1 ){
			int nloc = ndist_move[loc][i - 1];
			swap(x[loc], x[nloc]);
			loc = nloc;
			ret++;
		}
	}
	return ret;
}

int main(){
	int n;
	scanf("%d", &n);
	int m;
	scanf("%d", &m);
	ndist.resize(n);
	ndist_move.resize(n);
	for (int i = 0; i < n; i++){
		ndist[i].resize(n, INF);
		ndist_move[i].resize(n, -1);
		ndist[i][i] = 0;
		int a;
		scanf("%d", &a);
		start.push_back(a);
	}
	for (int i = 0; i < m; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		moves.push_back(make_pair(a, b));
		ndist[a][b] = 1;
		ndist[b][a] = 1;
		ndist_move[a][b] = b;
		ndist_move[b][a] = a;
	}

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if ( ndist[i][j] > ndist[i][k] + ndist[k][j] ){
					ndist[i][j] = ndist[i][k] + ndist[k][j];
					ndist_move[i][j] = k;
				}
			}

	int cutoff = greedy_distance(start);
	int ret = solve(start, cutoff);

	if ( ret == -1 ) printf("NEMA\n");
	else printf("%d\n", ret);	
			
	return 0;
}
