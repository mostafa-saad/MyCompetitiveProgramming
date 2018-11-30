// thomas fersch
#include <fstream>
#include <list>
using namespace std;

const int INF = 1000000;
const int MAX_N = 1000;

ifstream in("escape.in");
ofstream out("escape.out");

struct Edge {
	int from, to, capacity, flow;
	Edge(int f, int t, int c) {from = f; to = t; capacity = c; flow = 0; }
};

typedef list<Edge>::iterator EI;

struct Node {
	list<EI> edges;
	EI lastEdge;
};

int L, W, N;

Node nodes[2 * MAX_N + 2];
list<Edge> edges;

int xsoldier[MAX_N + 1];
int ysoldier[MAX_N + 1];

void add_edge(int from, int to, int capacity) {
	edges.push_front(Edge(from, to, capacity));
	nodes[from].edges.push_back(edges.begin());
	nodes[to].edges.push_back(edges.begin());
}

void input() {
	in >> L >> W >> N;
	for (int i = 1; i <= N; i++) in >> xsoldier[i] >> ysoldier[i];
	in.close();
}

void init_graph() {
	for (int i = 1; i <= N; i++) {
		add_edge(i, i + N, 1);
		if (W - ysoldier[i] <= 100) add_edge(0, i, INF);
		if (ysoldier[i] <= 100) add_edge(i + N, 2 * N + 1, INF);
		for (int j = i + 1; j <= N; j++) {
			long long dx = xsoldier[i] - xsoldier[j];
			long long dy = ysoldier[i] - ysoldier[j];
			if (dx * dx + dy * dy <= 40000) {
				add_edge(i + N, j, INF);
				add_edge(j + N, i, INF);
			}
		}
	}
}

bool bfs() {
	for (int i = 0; i <= 2 * N + 1; i++) nodes[i].lastEdge = edges.end();
	list<int> queue;
	queue.push_back(0);
	while (!queue.empty()) {
		int akt = queue.front();
		queue.pop_front();
		if (akt == 2 * N + 1) return true;
		for (list<EI>::iterator i = nodes[akt].edges.begin(); i != nodes[akt].edges.end(); i++) {
			int to = (*i)->to;
			if (to == akt) to = (*i)->from;
			if (nodes[to].lastEdge != edges.end() || to == 0) continue;
			if ((to == (*i)->to && (*i)->flow < (*i)->capacity) || (to == (*i)->from && (*i)->flow > 0)) {
				nodes[to].lastEdge = *i;
				queue.push_back(to);
			}
		}
	}
	return false;
}

void adjust_flows() {
	int akt = 2 * N + 1;
	while (nodes[akt].lastEdge != edges.end()) {
		EI e = nodes[akt].lastEdge;
		if (akt == e->to) {
			e->flow++;
			akt = e->from;
		} else {
			e->flow--;
			akt = e->to;
		}
	}
}

void output() {
	int nsoldiers = 0;
	for (list<EI>::iterator i = nodes[0].edges.begin(); i != nodes[0].edges.end(); i++) {
		nsoldiers += (*i)->flow;
	}
	out << nsoldiers << endl;
	out.close();
}

int main() {
	input();
	init_graph();
	while (bfs()) adjust_flows();
	output();
	return 0;
}
