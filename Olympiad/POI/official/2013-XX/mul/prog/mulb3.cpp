/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Multidrink                                    *
 *   Autor:                Przemyslaw Horban                             *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Opis:                 Rozwiazanie bledne, zawsze zachlannie skacze  *
 *                         do wezla najbardziej oddalonego od sciezki    *
 *                         u ~> v                                        *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<set>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<stack>
#include<cstdio>
#include<cmath>
#include<cassert>
#include<queue>
#include<vector>
#include<list>
#include<algorithm>
#include<map>
#include<cstring>
#include<cctype>

#define DEBUG 0
#define deb(x) if(DEBUG) { cout << #x << " = " << (x) << endl; }

using namespace std;
#define fe(e,C) for(__typeof((C).begin()) e = (C).begin(); e != (C).end(); e++)
#define foreach(VAR_DEF, C) \
  fe(__varname, C) \
    for(bool run_once = true; run_once; ) \
      for(VAR_DEF = *(__varname); run_once; run_once = false)
#define fi(i,n) for(int (i) = 0, __end = (n); (i) < __end; i++)
#define iterate_until(i,s,n) for(int (i) = (s), __end = (n); (i) < __end; i++)
#define iterate_to(i,a,b) ft(i,a,b)
#define ft(i,a,b) for(int (i) = (a), __end = (b); (i) <= __end; (i)++)
#define fd(i,a,b) for(int (i) = (a), __end = (b); (i) >= __end; (i)--)
#define fs(i,C) fi(i,SZ(C))
#define ALL(V) (V).begin(), (V).end()
#define SET(T, c) memset(T, c, sizeof(T))


// Przemyslaw Horban (extremegf@gmail.com)
//
// This code is shared among solutions and verifiers

#define fe(e,C) for(__typeof((C).begin()) e = (C).begin(); e != (C).end(); e++)
#define foreach(VAR_DEF, C) \
  fe(__varname, C) \
    for(bool run_once = true; run_once; ) \
      for(VAR_DEF = *(__varname); run_once; run_once = false)

#ifndef DEBUG
#define DEBUG 0
#endif

class Graph {
protected:
    int minNode, _edgeCount;
    vector<vector<int> > E;

public:

    Graph(int smallestNode, int largestNode) {
        minNode = smallestNode;
        int size = largestNode - (smallestNode - 1);
        E.clear();
        E.resize(size);
        _edgeCount = 0;
    }

    void addEdge(int u, int v) {
        _edgeCount += 1;

        u -= minNode;
        v -= minNode;

        E[u].push_back(v);
        E[v].push_back(u);
    }

    size_t neighbourCount(int u) const {
        return E[u - minNode].size();
    }

    vector<int> neighbours(int u) const {
        vector<int> neighs(E[u - minNode]);
        iterate_until(i, 0, neighs.size())
        neighs[i] += minNode;
        return neighs;
    }

    bool hasUnusedNeighbour(int u, const vector<bool> used) const {
        assert(nodeCount() + minNode - 1 < used.size());
        u -= minNode;
        foreach(int v, E[u]) {
            v += minNode;
            if(!used[v])
                return true;
        }
        return false;
    }

    size_t nodeCount() const {
        return E.size();
    }

    size_t edgeCount() const {
        return _edgeCount;
    }

    bool isConnected() const {
        vector<bool> onFringe(nodeCount(), false);
        vector<int> fringeNodes;

        fringeNodes.push_back(0);
        onFringe[0] = true;

        while(!fringeNodes.empty()) {
            int u = fringeNodes.back();
            fringeNodes.pop_back();

            fe(nextIt, E[u]) {
                int v = *nextIt;
                if(!onFringe[v]) {
                    fringeNodes.push_back(v);
                    onFringe[v] = true;
                }
            }
        }

        return count(ALL(onFringe), false) == 0;
    }
};


class TwoStepNeighIterator;

class Tree: public Graph {
    friend class TwoStepNeighIterator;
public:
    Tree(FILE *input, int numerationStart): Graph(numerationStart,
                read_int(input)) {
        while(edgeCount() < nodeCount() - 1)
            addEdge(read_int(input), read_int(input));

        buildFatherSonRelation();
    }

    // Haha! It takes O(1) time.
    bool areDistantByAtMost2(int u, int v, int *middleMan=NULL) const {
        u -= minNode;
        v -= minNode;

        if(middleMan) *middleMan = -1;

        // By definition they may be distant by 0
        if(u == v)
            return true;

        // Directly connected
        if(father[u] == v || father[v] == u)
            return true;

        // Distant by two edges
        //     v
        //    /
        //   m
        //  /
        // u
        if(father[father[u]] == v) {
            if(middleMan) *middleMan = father[u] + minNode;
            return true;
        }

        //     u
        //    /
        //   m
        //  /
        // v
        if(father[father[v]] == u) {
            if(middleMan) *middleMan = father[v] + minNode;
            return true;
        }

        //    m
        //  / |
        // u  v
        if(father[u] == father[v]) {
            if(middleMan) *middleMan = father[u] + minNode;
            return true;
        }


        return false;
    }

    bool fatherAndSon(int fatherNd, int childNd) const {
        childNd -= minNode;
        fatherNd -= minNode;
        return father[childNd] == fatherNd;
    }

    bool areNeighbours(int u, int v) const {
        u -= minNode;
        v -= minNode;
        // Directly connected
        return father[u] == v || father[v] == u;
    }

private:
    vector<int> father;

    void buildFatherSonRelation() {
        father.clear();
        father.resize(nodeCount());

        vector<bool> onFringe(nodeCount(), false);
        vector<int> fringeNodes;

        fringeNodes.push_back(0);
        onFringe[0] = true;
        father[0] = 0;

        while(!fringeNodes.empty()) {
            int u = fringeNodes.back();
            fringeNodes.pop_back();

            fe(nextIt, E[u]) {
                int v = *nextIt;
                // This is a Tree - if it's on fringe,
                // than it must be the father
                if(!onFringe[v]) {
                    // u adopts v
                    father[v] = u;
                    fringeNodes.push_back(v);
                    onFringe[v] = true;
                }
            }
        }
    }

    static int read_int(FILE *input) {
        int t;
        int result = fscanf(input, "%d", &t);
        assert(result == 1);
        return t;
    }
};

class TwoStepNeighIterator {
    const Tree *gPtr;
    int u;
    vector<int>::const_iterator nodesToGoIt, nodesToGoEnd;
    vector<int>::const_iterator neighbourIt, neighboursEnd;

public:
    TwoStepNeighIterator(const Tree *gPtr, int u): gPtr(gPtr), u(u) {
        const Tree &g = *gPtr;

        int root = u - g.minNode;;

        neighbourIt = g.E[root].begin();
        neighboursEnd = g.E[root].end();

        nodesToGoIt = g.E[root].begin();
        nodesToGoEnd = g.E[root].end();
    }

    int next() {
        if(neighbourIt != neighboursEnd) {
            int v = *neighbourIt + gPtr->minNode;
            neighbourIt++;
            if(v == u)
                return next();
            else
                return v;
        }
        else if(nodesToGoIt != nodesToGoEnd) {
            neighbourIt = gPtr->E[*nodesToGoIt].begin();
            neighboursEnd = gPtr->E[*nodesToGoIt].end();
            nodesToGoIt++;
            return next();
        }
        else
            return -1;

    }
};

// Iterative brutal path search
//
// CutoffMem is the datatype that cutOff function
// can use to memorize which cases have already been
// explored and make a cutoff decision based on that.
template<typename CutoffMem = char>
class PathSearch {
    const Tree &g;
    vector<int> p;
    vector<bool> used;
    vector<TwoStepNeighIterator> iters;
    vector<CutoffMem> cutoffMem;


public:
    PathSearch(const Tree &g): g(g) {}

    // Returns a vector with solution or empty vector if not found.
    vector<int> findTwoStepPath() {
        vector<int> solution;
        p.clear();
        p.push_back(1);
        used.clear();
        used.resize(g.nodeCount()+1, false);
        used[1] = true;

        if(DEBUG) {
            iterate_to(u, 1, g.nodeCount()) {
                TwoStepNeighIterator it(&g, u);
                printf("Sasiedzi %d: ", u);
                while(true) {
                    int v = it.next();
                    if(v == -1) break;
                    printf("%d ", v);
                }
                printf("\n");
            }
        }

        search_step();

        if(p.size() == g.nodeCount())
            solution.swap(p);

        return solution;
    }

    virtual ~PathSearch() {}
protected:
    virtual bool cutOff(const Tree &g,
                        int preLast, int last,
                        const vector<bool> &used,
                        CutoffMem *cutoffMemPtr) = 0;

private:
    void search_step() {
fake_recurse:
        if(p.size() == g.nodeCount() && p.back() == (int)g.nodeCount()) {
            // Solution found. Real return.
            return;
        }

        iters.push_back(TwoStepNeighIterator(&g, p.back()));
        p.push_back(-1);
        cutoffMem.push_back(CutoffMem());
        while(true) {
            p.back() = iters.back().next();
            if(p.back() == -1)
                break;
            if(DEBUG) {
                foreach(int u, p)
                printf("%d ", u);
                printf("\n");
            }
            if(!used[p.back()]) {
                used[p.back()] = true;
                // Jestem w p[-1], ostatni byl p[-2], uzyte sa used, a
                // a drzewo jest g.

                if(!cutOff(g, *(p.end()-2), *(p.end()-1), used, &*(cutoffMem.end()-1)))
                    goto fake_recurse; // search_step() - simulated recursive call
fake_return:
                // end of search_step() fake call
                used[p.back()] = false;
            }
        }
        p.pop_back();
        iters.pop_back();
        cutoffMem.pop_back();

        if(iters.empty()) // Real return - no solution found.
            return;
        else // return to callpoint in the while
            goto fake_return;
    }
};

class GreedyPathSearch {
    const Tree &g;


public:
    GreedyPathSearch(const Tree &g): g(g) {}

    // Returns a vector with solution or empty vector if not found.
    vector<int> findTwoStepPath() {
        computeDistsFromPath(1, g.nodeCount());

        vector<int> path;
        path.push_back(1);

        used.clear();
        used.resize(g.nodeCount() + 1, false);
        used[1] = true;

        while(true) {
            TwoStepNeighIterator it(&g, path.back());
            int cand = -1, maxDepth = -1;
            int u = it.next();
            while(u != -1) {
                deb(u);
                deb(d[u]);
                deb(maxDepth);
                deb(g.areNeighbours(path.back(), u))
                if(!used[u] &&
                        (d[u] > maxDepth || (d[u] == maxDepth &&
                                             g.areNeighbours(path.back(), u)))) {
                    cand = u;
                    maxDepth = d[u];
                }
                u = it.next();
            }
            if(cand == -1)
                break;

            used[cand] = true;
            deb(cand);
            path.push_back(cand);
        }

        if(path.size() == g.nodeCount() &&
                (size_t)path.back() == g.nodeCount())
            return path;
        else
            return vector<int>();
    }

private:
    vector<bool> used;
    vector<int> d;
    static const int INF = 1000000000;

    void computeDistsFromPath(int u, int v) {
        d.clear();
        d.resize(g.nodeCount() + 1, INF);
        vector<int> path = findPathFromTo(u, v);
        foreach(int u, path)
        d[u] = 0;
        foreach(int u, path)
        propagateDists(u);
    }

    void propagateDists(int u) {
        vector<int> neighs = g.neighbours(u);
        foreach(int v, neighs)
        if(d[v] == INF) {
            d[v] = 1 + d[u];
            propagateDists(v);
        }
    }

    vector<int> findPathFromTo(int u, int v) {
        used.clear();
        used.resize(g.nodeCount() + 1, false);

        vector<int> path;
        dfsPathFind(&path, v, u);

        return path;
    }

    bool dfsPathFind(vector<int> *pathPtr, int u, int goal) {
        used[u] = true;

        if(u == goal) {
            pathPtr->push_back(u);
            return true;
        }

        vector<int> neighs = g.neighbours(u);
        foreach(int v, neighs) {
            if(!used[v]) {
                if(dfsPathFind(pathPtr, v, goal)) {
                    pathPtr->push_back(u);
                    return true;
                }
            }
        }

        used[u] = false;
        return false;
    }
};

int main() {
    Tree g(stdin, 1);

    GreedyPathSearch seeker(g);

    vector<int> p = seeker.findTwoStepPath();
    if(!p.empty()) {
        fe(nodeIt, p)
        printf("%d\n", *nodeIt);
    } else
        puts("BRAK");

    return 0;
}

