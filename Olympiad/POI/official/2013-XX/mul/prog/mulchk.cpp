/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Multidrink                                    *
 *   Autor:                Przemyslaw Horban                             *
 *   Opis:                 Weryfikator odpowiedzi programu zawodnika     *
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

#include "oi.h"

using namespace std;
#define fe(e,C) for(__typeof((C).begin()) e = (C).begin(); e != (C).end(); e++)
#define fi(i,n) for(int (i) = 0, __end = (n); (i) < __end; i++)
#define iterate_until(i,s,n) for(int (i) = (s), __end = (n); (i) < __end; i++)
#define iterate_to(i,a,b) ft(i,a,b)
#define ft(i,a,b) for(int (i) = (a), __end = (b); (i) <= __end; (i)++)
#define fd(i,a,b) for(int (i) = (a), __end = (b); (i) >= __end; (i)--)
#define fs(i,C) fi(i,SZ(C))
#define ALL(V) (V).begin(), (V).end()
#define SET(T, c) memset(T, c, sizeof(T))
#define VI vector<int>
#define PB push_back
#define PII pair<int, int>
#define SEC second
#define FST first
#define MP make_pair
#define SZ(C) ((int)(C).size())
#define SQR(a) ((a)*(a))
#define VII vector<PII>
#define SS stringstream
#define UNIQUE(V) (V).erase(unique(ALL(V)), (V).end())


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

string NO_SOLUTION_STR = "BRAK";

// Skips whitespace, seeking first continous string in file.
string readFirstString(const char *fileName) {
    oi::Scanner in(fileName, oi::PL);
    in.skipWhitespaces();
    char firstString[10];
    firstString[0] = 0;
    in.readString(firstString, 10);

    return firstString;
}

void chk_error_function(const char* msg, int line, int position) {
    printf("WRONG\n");
    printf("ERROR(line: %d, position: %d): %s\n", line, position, msg);
    exit(1);
}

vector<int> readPermutation(oi::Scanner *inPtr, size_t size) {
    oi::Scanner &in = *inPtr;
    vector<int> p;
    p.resize(size);

    iterate_until(i, 0, size) {
        in.skipWhitespaces();
        p[i] = in.readInt(1, size);
    }
    in.skipWhitespaces();
    in.readEof();

    // Checkinf if all values from [1, size] are in p
    vector<int> v(p);
    sort(ALL(v));
    UNIQUE(v);
    if(v.size() != size)
        in.error("Not a permutation.");

    return p;
}

bool isTwoSkipHamiltonPath1ToN(Tree *treePtr,
                               const vector<int> &permutation) {
    Tree &g = *treePtr;
    if(permutation.front() != 1 || permutation.back() != (int)g.nodeCount())
        return false;

    assert(permutation.size() == g.nodeCount());
    iterate_until(i, 0, permutation.size() - 1)
    if(!g.areDistantByAtMost2(permutation[i],
                              permutation[i+1]))
        return false;

    return true;
}

int main(int argc, char *argv[]) {
    const char *inputFile = argv[1];
    const char *userOutputFile = argv[2];
    const char *expOutputFile = argv[3];

    FILE *inputFileObj = fopen(inputFile, "r");
    assert(inputFileObj != NULL);
    Tree tree(inputFileObj, 1);
    fclose(inputFileObj);

    oi::Scanner userOutScn(userOutputFile, chk_error_function, oi::PL);
    if(readFirstString(expOutputFile) == NO_SOLUTION_STR) {
        char word[6];
        userOutScn.skipWhitespaces();
        userOutScn.readString(word, 5);

        if(word != NO_SOLUTION_STR) {
            // Just to be safe, we'll check if this answer is actually a
            // correct path.
            oi::Scanner secUserOutScn(userOutputFile, chk_error_function, oi::PL);

            // To znaczy ze wzorcowka jest zmaszczona, bo daje BRAK
            // ale zawodnik znalazl poprawna sciezke.
            bool weAreScrewed =
                isTwoSkipHamiltonPath1ToN(&tree, readPermutation(&secUserOutScn,
                                          tree.nodeCount()));
            if(weAreScrewed) {
                userOutScn.error("Uwaga! Rozwiazanie wzorcowe jest niepoprawne."
                                 "Koniecznie zglos to organizatorom.");
            } else {
                userOutScn.error("Contestant returned a solution, though non-exits");
            }
        } else {
            // He's almost there. Just ensure there is no garbage after NO_SOLUTION_STR
            userOutScn.skipWhitespaces();
            userOutScn.readEof();
        }
    } else {
        if(!isTwoSkipHamiltonPath1ToN(&tree, readPermutation(&userOutScn,
                                      tree.nodeCount()))) {
            userOutScn.error("Found path is not correct.");
        }
    }

    printf("OK\n");

    return 0;
}

