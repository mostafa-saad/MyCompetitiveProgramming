// Patryk Czajka
// O(n *log(n))

#include <cstdio>
#include <vector>
using namespace std;

const int r = 1 << 18;
const int maxN = 2e5 + 10;
const int inf = 2e9+10;


struct Tree {
    vector<int> tree;
    vector<int> change;
    
    Tree() {
        init();
    }
    
    void init() {
        tree.resize(2 * r);
        change.resize(2 * r);
    }

    void reset() {
        fill(tree.begin(), tree.end(), inf);
        fill(change.begin(), change.end(), inf);
    }

    void push(int x) {
        change[2 * x] = min(change[x], change[2 * x]);
        change[2 * x + 1] = min(change[x], change[2 * x + 1]);
        tree[2 * x] = min(tree[2 * x], change[2 * x]);
        tree[2 * x + 1] = min(tree[2 * x + 1], change[2 * x + 1]);
    }

    void update(int x) {
        tree[x] = min(min(tree[2 * x + 1], tree[2 * x]), change[x]);
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
            change[x] = min(change[x], val);
            tree[x] = min(tree[x], val);
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
const int END = 2;

Tree tree[3];
int t[maxN];


void reset() {
    tree[FRESH].reset();
    tree[MID].reset();
    tree[END].reset();
}

int get_res() {
    return max(max(tree[FRESH].find(inf), tree[MID].find(inf)), tree[END].find(inf)) + 1;
}

#define DEF 0, r - 1, 1
void add(int val, int dx) {
    int a, b;
    a = tree[MID].find(val) + 1;
    b = tree[END].find(val) + 1;
    tree[END].put(min(a, b), max(a, b), val, DEF);

    a = tree[MID].find(val + dx) + 1;
    b = tree[FRESH].find(val + dx) + 1;
    tree[MID].put(min(a, b), max(a, b), val + dx, DEF);

    a = tree[FRESH].find(val) + 1;
    tree[FRESH].put(a, a, val, DEF);
}

int n, X, res;

int main() {
    scanf("%d%d", &n, &X);
    for(int i = 0; i < n; ++i)
        scanf("%d", t + i);

    reset();
    for(int i = 0; i < n; ++i)
        add(t[i], X);
    res = max(res, get_res());

    printf("%d\n", res);
}
