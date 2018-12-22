#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int> > implies;
vector<vector<int> > is_implied_by;
vector<set<int> > causes;

vector<int> proof;
vector<char> happened;

void consequences(int x){
	queue<int> Q;
	Q.push(x);
	happened[x] = 1;

	while ( !Q.empty() ){
		x = Q.front();
		Q.pop();

		for (int i = 0; i < implies[x].size(); i++)
			if ( !happened[implies[x][i]] ){
				happened[implies[x][i]] = 1;
				Q.push(implies[x][i]);
			}
	}
}

void find_causes(int x){
	if ( is_implied_by[x].size() == 0 )
		causes[x].insert(x);
	else {
		
		for (int i = 0; i < is_implied_by[x].size(); i++){
			if ( causes[is_implied_by[x][i]].size() == 0 )
				find_causes(is_implied_by[x][i]);

			// magic 
			for (set<int>::iterator it = causes[is_implied_by[x][i]].begin(); it != causes[is_implied_by[x][i]].end(); it++)
				causes[x].insert(*it);
		}
	}
}

int main(){
	int d, m, n;
	scanf("%d %d %d", &d, &m, &n);	

	happened.resize(d, 0);
	implies.resize(d);
	is_implied_by.resize(d);
	causes.resize(d);

	for (int i = 0; i < m; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		a--;b--;
		implies[a].push_back(b);
		is_implied_by[b].push_back(a);
	}

	for (int i = 0; i < n; i++){
		int a;
		scanf("%d", &a);
		a--;
		proof.push_back(a);
		happened[a] = 1;
		consequences(a);
	}

	for (int i = 0; i < d; i++)
		if ( causes[i].size() == 0 )
			find_causes(i);

/*	for (int i = 0; i < d; i++){
		printf("My %d causes are:", i);
		for (set<int>::iterator it = causes[i].begin(); it != causes[i].end(); it++)
			printf(" %d", *it);
		printf("\n");
	}
*/

	for (int i = 0; i < d; i++)
		if ( !happened[i] ){
			// more magic 
			char possible = 1;
			for (int j = 0; j < proof.size() && possible; j++){
				char skip = 1;
				for (set<int>::iterator it = causes[proof[j]].begin(); it != causes[proof[j]].end() && skip; it++)
					if ( causes[i].find(*it) == causes[i].end() )
						skip = 0;

				if ( !skip ) continue;
				happened[i] = 1;
				consequences(i);
				possible = 0;
			}				
		}
	

	char space = 0;
	for (int i = 0; i < d; i++) {
		if ( happened[i] ) {
			if ( space ) printf(" ");
			space = 1;
			printf("%d", i + 1);
		}
	}
	printf("\n");

	return 0;
}
