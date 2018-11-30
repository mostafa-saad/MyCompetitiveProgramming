// TODO Watch out for overflows
#include <stdio.h>
#include <vector>
using namespace std;

typedef pair<int,int> PII;

const int NMAX = 100000;
const int MMAX = 1000000;

int N, M;
vector<int> adj[NMAX]; // adjacent edges
int change[NMAX]; // remaining change
int edgea[MMAX]; // first end of the edge
int edgeb[MMAX]; // second end of the edge

int plan[MMAX]; // amount of water Jester wants to pump into this edge
bool planned[MMAX]; // whether this amount is already known
int remadj[NMAX]; // number of adjacent edges for which the amount of water is not known yet

void visit(int i) { // handle reservoirs with only one one unknown adjacent edge (remove leaves)
	if (remadj[i] != 1)
		return;
	for (int ia = 0; ia < (int)adj[i].size(); ia++) {
		int e = adj[i][ia];
		if (!planned[e]) {
			// pump change[i] into e
			planned[e] = true;
			plan[e] = change[i];
			change[edgea[e]] -= plan[e];
			change[edgeb[e]] -= plan[e];
			plan[e] *= 2;
			remadj[edgea[e]]--;
			remadj[edgeb[e]]--;
			visit(edgea[e]);
			visit(edgeb[e]);
		}
	}
}

bool finished[NMAX];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &change[i]);
		finished[i] = false;
	}
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		edgea[i] = a;
		edgeb[i] = b;
		adj[a].push_back(i);
		adj[b].push_back(i);
		planned[i] = false;
	}
	for (int i = 0; i < N; i++)
		remadj[i] = adj[i].size();
	// remove leaves
	for (int i = 0; i < N; i++)
		visit(i);
	for (int i = 0; i < N; i++)
		if (remadj[i] > 2) { // not only cycles remaining
			printf("0\n");
			return 0;
		}
	for (int s = 0; s < N; s++) {
		if (finished[s] || remadj[s] != 2)
			continue;
		// find cycle starting at s
		vector<int> nodes; // reservoirs on the cycle
		vector<int> edges; // edges on the cycle
		int i = s;
		do {
			nodes.push_back(i);
			finished[i] = true;
			for (int ia = 0; ia < (int)adj[i].size(); ia++) {
				int e = adj[i][ia];
				if (!planned[e] && (nodes.size() == 1 || (nodes[nodes.size()-2] != edgea[e] && nodes[nodes.size()-2] != edgeb[e]))) {
					edges.push_back(e);
					if (edgea[e] != i)
						i = edgea[e];
					else
						i = edgeb[e];
					break;
				}
			}
		} while (i != s);
		if (nodes.size()%2 == 0) { // even cycle length
			printf("0\n");
			return 0;
		}
		// compute plans along the cycle
		int pl = 0;
		for (int t = 0; t < (int)nodes.size(); t++)
			pl += ((t == 0 || t%2 != 0) ? 1 : -1)*change[nodes[t]];
		for (int t = 0; t < (int)nodes.size(); t++) {
			planned[edges[t]] = true;
			plan[edges[t]] = pl;
			pl = 2*change[nodes[(t+1)%nodes.size()]]-pl;
		}
	}
	for (int i = 0; i < M; i++) {
		printf("%d\n", plan[i]);
	}
	return 0;
}
