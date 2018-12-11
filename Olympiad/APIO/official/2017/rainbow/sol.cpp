#include <bits/stdc++.h>

#define sz(x) (int((x).size()))

struct RT {
    struct node {
        int sum, left, right;
        node() : sum(0), left(0), right(0) {}
        node(const node &n) : sum(n.sum), left(n.left), right(n.right) {}
        node(int s, int l, int r) : sum(s), left(l), right(r) {}
    };

    std::vector<node> nodes;

    int newNode(node n = node()) {
        nodes.push_back(n);
        return sz(nodes) - 1;
    }

    int init(int nl, int nr) {
        int n = newNode();
        int nm = (nl+nr)/2;
        if (nl+1 < nr) {
            int l = init(nl, nm);
            nodes[n].left = l;
            int r = init(nm, nr);
            nodes[n].right = r;
        }
        return n;
    }

    int update(int old, int nl, int nr, int ui) {
        int now = newNode(nodes[old]);
        if (nl == ui && nl + 1 == nr) {
            nodes[now].sum++;
        } else {
            int nm = (nl+nr)/2;
            if (ui < nm) {
                int l = update(nodes[old].left, nl, nm, ui);
                nodes[now].left = l;
            } else {
                int r = update(nodes[old].right, nm, nr, ui);
                nodes[now].right = r;
            }
            nodes[now].sum = nodes[nodes[now].left].sum + nodes[nodes[now].right].sum;
        }
        return now;
    }

    int query(int now, int nl, int nr, int ql, int qr) {
        if (ql <= nl && nr <= qr) {
            return nodes[now].sum;
        } else {
            int sum = 0;
            int nm = (nl+nr)/2;
            if (ql < nm) sum += query(nodes[now].left, nl, nm, ql, qr);
            if (nm < qr) sum += query(nodes[now].right, nm, nr, ql, qr);
            return sum;
        }
    }
};

const int MaxC = 200*1000+5;

std::set<std::pair<int, int>> squares, vertices, hEdges, vEdges;
// these range trees are "horizontal" range trees over columns,
// sweeping vertically over rows over time
RT rtSquares, rtVertices, rtHEdges, rtVEdges;
int rootsSquares[MaxC], rootsVertices[MaxC], rootsHEdges[MaxC], rootsVEdges[MaxC];
int minr, maxr, minc, maxc;

void setupRT(RT &rt, int *roots, std::set<std::pair<int, int>> &points) {
    roots[0] = rt.init(0, MaxC);
    auto it = points.begin();
    for (int i = 0; i < MaxC; i++) {
        if (i) roots[i] = roots[i-1];
        while (it != points.end() && it->first == i) {
            roots[i] = rt.update(roots[i], 0, MaxC, it->second);
            it++;
        }
    }
}

void init(int R, int C, int sr, int sc, int M, char *S) {
    squares.emplace(sr, sc);
    for (int i = 0; i < M; i++) {
        if (S[i] == 'N') sr--;
        else if (S[i] == 'S') sr++;
        else if (S[i] == 'E') sc++;
        else /* S[i] == 'W' */ sc--;
        squares.emplace(sr, sc);
    }

    minr = minc = MaxC + 5;
    maxr = maxc = -5;

    for (auto &square : squares) {
        int r, c; std::tie(r, c) = square;

        minr = std::min(minr, r);
        minc = std::min(minc, c);
        maxr = std::max(maxr, r);
        maxc = std::max(maxc, c);

        vertices.emplace(r, c);
        vertices.emplace(r+1, c);
        vertices.emplace(r, c+1);
        vertices.emplace(r+1, c+1);

        hEdges.emplace(r, c);
        hEdges.emplace(r+1, c);
        vEdges.emplace(r, c);
        vEdges.emplace(r, c+1);
    }

    setupRT(rtSquares, rootsSquares, squares);
    setupRT(rtVertices, rootsVertices, vertices);
    setupRT(rtHEdges, rootsHEdges, hEdges);
    setupRT(rtVEdges, rootsVEdges, vEdges);
}

// both coordinates are [inclusive, inclusive]
int queryRT(RT &rt, int *roots, int ay, int by, int ax, int bx) {
    assert(ax-1 <= bx && ay <= by + 1);
    return rt.query(roots[by], 0, MaxC, ax, bx + 1) -
           rt.query(roots[ay-1], 0, MaxC, ax, bx + 1);
}

int colour(int ar, int ac, int br, int bc) {
    int V = /* internal vertices */
            queryRT(rtVertices, rootsVertices, ar+1, br, ac+1, bc) +
            /* external vertices */
            4 + 2 * (br - ar + bc - ac);
    int E = /* internal edges */
            queryRT(rtHEdges, rootsHEdges, ar+1, br, ac, bc) +
            queryRT(rtVEdges, rootsVEdges, ar, br, ac+1, bc) +
            /* external edges */
            2 * (br - ar + 1 + bc - ac + 1);
    // black faces
    int BF = /* internal faces */
             queryRT(rtSquares, rootsSquares, ar, br, ac, bc) +
             /* the infinite, external face */
             1;
    // components (because the outer black component might not be
    // connected to the original black component)
    int C = ((ac < minc && maxc < bc && ar < minr && maxr < br) ? 2 : 1);
    // white faces
    int WF = 1 + C - V + E - BF;
    return WF;
}

