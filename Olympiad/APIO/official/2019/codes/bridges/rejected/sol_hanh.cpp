#include<bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a) for (int i = (b), _a = (a); i >= _a; i--)
#define REP(i, n) for (int i = 0, _n = (n); i < _n; i++)
#define FORE(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define ALL(v) (v).begin(), (v).end()
#define IS_INF(x)   (std::isinf(x))
#define IS_NAN(x)   (std::isnan(x))
#define fi   first
#define se   second
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x > y + eps) {
            x = y;
            return true;
        } else return false;
    }
template<class X, class Y>
    bool maximize(X &x, const Y &y) {
        X eps = 1e-9;
        if (x + eps < y) {
            x = y;
            return true;
        } else return false;
    }
template<class T>
    T Abs(const T &x) {
        return (x < 0 ? -x : x);
    }

/* Author: Van Hanh Pham */

/** END OF TEMPLATE - ACTUAL SOLUTION COMES HERE **/

class DisjointSet {
private:
    int n;
    int *lab;

public:
    DisjointSet(int n = 0) {
        this->n = n;
        lab = NULL;
        if (n > 0) lab = new int[n + 3];
        FOR(i, 1, n) lab[i] = -1;
    }

    int find(int x) {
        return lab[x] < 0 ? x : lab[x] = find(lab[x]);
    }

    bool join(int a, int b) {
        int x = find(a);
        int y = find(b);
        if (x == y) return false;
        if (lab[x] > lab[y]) swap(x, y);
        lab[x] += lab[y];
        lab[y] = x;
        return true;
    }

    int getSize(int x) {
        return -lab[find(x)];
    }

    void reset(void) {
        FOR(i, 1, n) lab[i] = -1;
    }

    void assign(int n) {
        this->n = n;
        reset();
    }
};

struct Edge {
    int u, v, cost;
    bool isStatic;

    Edge(int _u = 0, int _v = 0, int _cost = 0) {
        u = _u; v = _v; cost = _cost; isStatic = false;
    }
};

#define UPDATE   1
#define ASK   2
struct Query {
    int type, id, cost, answer;
    int *tmpCost;

    Query() {
        type = id = cost = answer = 0; tmpCost = NULL;
    }

    void input(void) {
        assert(scanf("%d%d%d", &type, &id, &cost) == 3);
    }

    bool goodEdge(int index) {
        return tmpCost[index] >= cost;
    }
};

class ReverseCompare {
public:
    bool operator () (const pair<int, int> &a, const pair<int, int> &b) const {
        return a.fi == b.fi ? a.se > b.se : a.fi > b.fi;
    }
};

#define MAX   100100
#define BLOCK    444

int numNode, numEdge, numQuery;
Edge edges[MAX];
Query queries[MAX];
vector<int> updates, asks, tmpEdges;
set<pair<int, int>, ReverseCompare> orderByCost;
DisjointSet dsu, tmpDSU;
int tmpNodeID[MAX], numTmpNode;

void loadTree(void) {
    int task; scanf("%d%d", &numNode, &numEdge);
    FOR(i, 1, numEdge) {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        edges[i] = Edge(u, v, c);
    }

    scanf("%d", &numQuery);
    FOR(i, 1, numQuery) {
        queries[i].input();
        if (queries[i].type == UPDATE) updates.push_back(i);
    }
}

void prepare(void) {
    FOR(i, 1, numEdge) orderByCost.insert(make_pair(edges[i].cost, i));
    dsu = DisjointSet(numNode);
    tmpDSU = DisjointSet(numNode);
}

bool CompareAsk(const int &x, const int &y) {
    return queries[x].cost > queries[y].cost;
}

void processBlock(int l, int r) { // all queries from l to r - 1
    asks.clear(); tmpEdges.clear();
    FOR(i, 1, numEdge) edges[i].isStatic = true;

    FOR(i, l, r - 1) {
        if (queries[i].type == UPDATE) {
            int j = queries[i].id;
            if (edges[j].isStatic) {
                edges[j].isStatic = false;
                tmpEdges.push_back(j);
            }
        } else asks.push_back(i);
    }

    FOR(i, l, r - 1) {
        if (queries[i].type == UPDATE) {
            int j = queries[i].id;
            orderByCost.erase(make_pair(edges[j].cost, j));
            edges[j].cost = queries[i].cost;
            orderByCost.insert(make_pair(edges[j].cost, j));
        } else {
            queries[i].tmpCost = new int[tmpEdges.size()];
            REP(j, tmpEdges.size()) queries[i].tmpCost[j] = edges[tmpEdges[j]].cost;
        }
    }

    dsu.reset();
    __typeof(orderByCost.begin()) ut = orderByCost.begin();
    sort(ALL(asks), CompareAsk);

    FORE(it, asks) {
        while (ut != orderByCost.end() && ut->fi >= queries[*it].cost) {
            if (edges[ut->se].isStatic) dsu.join(edges[ut->se].u, edges[ut->se].v);
            ut++;
        }

        numTmpNode = 0;
        REP(j, tmpEdges.size()) if (queries[*it].goodEdge(j)) {
            int jd = tmpEdges[j];
            int x = dsu.find(edges[jd].u);
            if (tmpNodeID[x] == 0) tmpNodeID[x] = ++numTmpNode;
            x = dsu.find(edges[jd].v);
            if (tmpNodeID[x] == 0) tmpNodeID[x] = ++numTmpNode;
        }
        if (tmpNodeID[dsu.find(queries[*it].id)] == 0) {
            queries[*it].answer = dsu.getSize(queries[*it].id);
            REP(j, tmpEdges.size()) if (queries[*it].goodEdge(j)) {
                int jd = tmpEdges[j];
                int x = dsu.find(edges[jd].u);
                int y = dsu.find(edges[jd].v);
                tmpNodeID[x] = tmpNodeID[y] = 0;
            }
        } else {
            tmpDSU.assign(numTmpNode);
            REP(j, tmpEdges.size()) if (queries[*it].goodEdge(j)) {
                int jd = tmpEdges[j];
                int x = dsu.find(edges[jd].u);
                int y = dsu.find(edges[jd].v);
                tmpDSU.join(tmpNodeID[x], tmpNodeID[y]);
            }
            int tmp = tmpDSU.find(tmpNodeID[dsu.find(queries[*it].id)]);
            REP(j, tmpEdges.size()) if (queries[*it].goodEdge(j)) {
                int jd = tmpEdges[j];
                int x = dsu.find(edges[jd].u);
                int y = dsu.find(edges[jd].v);
                if (tmpNodeID[x] > 0) {
                    if (tmpDSU.find(tmpNodeID[x]) == tmp) queries[*it].answer += dsu.getSize(x);
                    tmpNodeID[x] = 0;
                }
                if (tmpNodeID[y] > 0) {
                    if (tmpDSU.find(tmpNodeID[y]) == tmp) queries[*it].answer += dsu.getSize(y);
                    tmpNodeID[y] = 0;
                }
            }
        }
    }
}

void process(void) {
    if (queries[1].type != UPDATE) processBlock(1, updates.empty() ? numQuery + 1 : updates[0]);

    int i = 0;
    while (i < updates.size()) {
        int j = i + BLOCK;
        processBlock(updates[i], j < updates.size() ? updates[j] : numQuery + 1);
        i = j;
    }
    FOR(i, 1, numQuery) if (queries[i].type == ASK) printf("%d\n", queries[i].answer);
}

int main(void) {
#ifdef SKY
    freopen("tmp.txt", "r", stdin);
#endif // SKY
    loadTree();
    prepare();
    process();
    return 0;
}

/*** LOOK AT MY CODE. MY CODE IS AMAZING :D ***/
