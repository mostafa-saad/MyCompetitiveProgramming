// Patryk Czajka
// O(n *log(n))

#include <cstdio>
#include <vector>
using namespace std;

int r = 1;
const int maxN = 2e5 + 10;
const int inf = 2e9+10;


struct Tree {
    vector<int> tree;
    vector<int> change;

    void init() {
        tree.resize(2 * r);
        change.resize(2 * r);
    }

    void reset() {
        fill(tree.begin(), tree.end(), inf);
        fill(change.begin(), change.end(), inf);
    }

    void push(int x) {
        if(change[x] == inf)
            return;

        change[2 * x] = change[2 * x + 1] = change[x];
        tree[2 * x] = tree[2 * x + 1] = change[x];
        change[x] = inf;
    }

    void update(int x) {
        tree[x] = min(tree[2 * x + 1], tree[2 * x]);
    }

    int find(int val) {
        if(tree[1] >= val)
            return -1;
        
        int x = 1;
        while(x < r) {
            push(x);
            if(tree[2 * x + 1] >= val)
                x = 2 * x;
            else
                x = 2 * x + 1;
        }
        return x - r;
    }

    void put(int qa, int qb, int val, int a, int b, int x) {
        if(qa <= a && b <= qb) {
            change[x] = tree[x] = val;
            return;
        }
    
        int avg = (a + b) / 2;
        push(x);
        if(qa <= avg) put(qa, qb, val, a, avg, 2 * x);
        if(avg < qb) put(qa, qb, val, avg + 1, b, 2 * x + 1);
        update(x);
    }
};

const int FRESH = 0;
const int MID = 1;

Tree tree[2];
int t[maxN];


void reset() {
    tree[FRESH].reset();
    tree[MID].reset();
}

void init() {
    tree[FRESH].init();
    tree[MID].init();
}

int get_res() {
    return tree[MID].find(inf) + 1;
}

#define DEF 0, r - 1, 1
void add(int val, int dx) {
    int a, b;
    a = tree[MID].find(val + dx) + 1;
    b = tree[FRESH].find(val + dx) + 1;
    tree[MID].put(a, max(a, b), val + dx, DEF);

    a = tree[FRESH].find(val) + 1;
    tree[FRESH].put(a, a, val, DEF);
}

int n, X, res;

int main() {
    scanf("%d%d", &n, &X);
    while(r < n)
        r *= 2;
    for(int i = 0; i < n; ++i)
        scanf("%d", t + i);

    init();
    reset();
    for(int i = 0; i < n; ++i)
        add(t[i], X);
    res = max(res, get_res());

    printf("%d\n", res);
}
