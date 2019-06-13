#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <numeric>
#include <algorithm>
#include <bitset>
#include <complex>
#include <functional>

using namespace std;

typedef unsigned uint;
typedef long long Int;

const int INF = 1001001001;
const Int INFLL = 1001001001001001001LL;

template<typename T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }
template<typename T> void chmin(T& a, T b) { if (a > b) a = b; }
template<typename T> void chmax(T& a, T b) { if (a < b) a = b; }

const int MAXN = 200050, MAXM = 200050, MAXC = 500050;
const int MAXV = MAXN, MAXE = MAXV * 5;

int N;
struct town {
    int id, X, Y;
} T[MAXN];
bool operator < (const town& a, const town& b)
{
    return a.Y != b.Y ? a.Y < b.Y : a.X < b.X;
}

int M;
int P[MAXM], Q[MAXM], R[MAXM], S[MAXM];
struct region_info {
    int Y, X1, X2, V;
} A[2 * MAXM];
bool operator < (const region_info& a, const region_info& b)
{
    return a.Y < b.Y;
}

int C;
int B[MAXC], H[MAXC];

int E;
struct edge {
    int u, v, w;
} ES[MAXE];
bool operator < (const edge& e, const edge& f)
{
    return e.w < f.w;
}

int U[MAXN];
void init(int n)
{
    for (int i = 0; i < n; ++i) {
        U[i] = i;
    }
}

int find(int x)
{
    if (U[x] != x) {
        U[x] = find(U[x]);
    }
    return U[x];
}

void uni(int x, int y)
{
    U[find(x)] = find(y);
}

Int F[MAXN], G[MAXN];

const int MAXSEG = MAXN + 2 * MAXM;
int seg_max[4 * MAXSEG], seg_added[4 * MAXSEG], MX;
void seg_init(int xc)
{
    MX = xc;
    memset(seg_max, 0, sizeof(seg_max));
    memset(seg_added, 0, sizeof(seg_added));
}

void seg_add(int al, int ar, int av, int x = 1, int l = 0, int r = MX)
{
    if (l == al && r == ar) {
        seg_added[x] += av;
        return;
    }

    int mid = (l + r) / 2;
    if (al < mid) seg_add(al, min(mid, ar), av, 2 * x + 0, l, mid);
    if (ar > mid) seg_add(max(al, mid), ar, av, 2 * x + 1, mid, r);

    seg_max[x] = max(seg_max[2 * x + 0] + seg_added[2 * x + 0], seg_max[2 * x + 1] + seg_added[2 * x + 1]);
}

int seg_query(int al, int ar, int x = 1, int l = 0, int r = MX)
{
    if (l == al && r == ar) {
        return seg_max[x] + seg_added[x];
    }

    int mid = (l + r) / 2, res = 0;
    if (al < mid) chmax(res, seg_query(al, min(mid, ar), 2 * x + 0, l, mid));
    if (ar > mid) chmax(res, seg_query(max(al, mid), ar, 2 * x + 1, mid, r));

    return res + seg_added[x];
}

int XS[MAXN + 4 * MAXM];

void add_edges_x()
{
    int ptr_t = 0, ptr_r = 0;

    for (int i = 0; i < N; ++i) {
        XS[i] = T[i].X;
    }
    for (int j = 0; j < 2 * M; ++j) {
        XS[N + 2 * j + 0] = A[j].X1;
        XS[N + 2 * j + 1] = A[j].X2;
    }
    sort(XS, XS + N + 4 * M);

    int XC = unique(XS, XS + N + 4 * M) - XS;
    for (int i = 0; i < N; ++i) {
        T[i].X = lower_bound(XS, XS + XC, T[i].X) - XS;
    }
    for (int j = 0; j < 2 * M; ++j) {
        A[j].X1 = lower_bound(XS, XS + XC, A[j].X1) - XS;
        A[j].X2 = lower_bound(XS, XS + XC, A[j].X2) - XS;
    }

    seg_init(XC);

    while (ptr_t < N) {
        while (ptr_r < 2 * M && A[ptr_r].Y < T[ptr_t].Y) {
            seg_add(A[ptr_r].X1, A[ptr_r].X2, A[ptr_r].V);
            ++ptr_r;
        }

        int next_t;
        for (next_t = ptr_t; next_t < N && T[ptr_t].Y == T[next_t].Y; ++next_t) ;
    
        for (int i = ptr_t; i + 1 < next_t; ++i) {
            if (seg_query(T[i].X, T[i + 1].X) == 0) {
                ES[E].u = T[i].id; ES[E].v = T[i + 1].id; ES[E].w = XS[T[i + 1].X] - XS[T[i].X]; ++E;
            }
        }
        ptr_t = next_t;
    }

    for (int i = 0; i < N; ++i) {
        T[i].X = XS[T[i].X];
    }
}

void create_graph()
{
    E = 0;

    for (int i = 0; i < N; ++i) {
        T[i].Y <<= 1;
    }
    for (int j = 0; j < M; ++j) {
        A[2 * j + 0].V = 1; A[2 * j + 1].V = -1;
        A[2 * j + 0].Y = Q[j] * 2 - 1; A[2 * j + 1].Y = S[j] * 2 + 1;
        A[2 * j + 0].X1 = A[2 * j + 1].X1 = P[j];
        A[2 * j + 0].X2 = A[2 * j + 1].X2 = R[j];
    }
    sort(T, T + N);
    sort(A, A + 2 * M);
    
    add_edges_x();

    for (int i = 0; i < N; ++i) {
        T[i].Y >>= 1;
        swap(T[i].X, T[i].Y);
        T[i].Y <<= 1;
    }
    for (int j = 0; j < M; ++j) {
        A[2 * j + 0].V = 1; A[2 * j + 1].V = -1;
        A[2 * j + 0].Y = P[j] * 2 - 1; A[2 * j + 1].Y = R[j] * 2 + 1;
        A[2 * j + 0].X1 = A[2 * j + 1].X1 = Q[j];
        A[2 * j + 0].X2 = A[2 * j + 1].X2 = S[j];
    }
    sort(T, T + N);
    sort(A, A + 2 * M);

    add_edges_x();
}

int kruskal()
{
    sort(ES, ES + E);
    init(N);

    int cmps = N;
    F[N] = G[N] = 0;

    for (int i = 0; i < E; ++i) {
        if (find(ES[i].u) != find(ES[i].v)) {
            --cmps;
            G[cmps] = ES[i].w;
            F[cmps] = F[cmps + 1] + ES[i].w;
            uni(ES[i].u, ES[i].v);
        }
    }

    return cmps;
}

int main()
{   
    scanf("%d%d%d", &N, &M, &C);

    for (int i = 0; i < N; ++i) {
        T[i].id = i;
        scanf("%d%d", &T[i].X, &T[i].Y);
    }

    for (int j = 0; j < M; ++j) {
        scanf("%d%d%d%d", &P[j], &Q[j], &R[j], &S[j]);
    }

    for (int k = 0; k < C; ++k) {
        scanf("%d%d", &B[k], &H[k]);
    }

    create_graph();
    int cmps = kruskal();

    for (int k = 0; k < C; ++k) {
        if (H[k] < cmps) {
            puts("-1");
        } else {
            int pos = lower_bound(G + cmps, G + N + 1, B[k], greater<int>()) - G;
            chmin(pos, H[k]);
            printf("%lld\n", F[pos] + (Int)pos * B[k]);
        }
    }

    return 0;
}
