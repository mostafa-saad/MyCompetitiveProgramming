#include <cstdio>
#include <vector>
#include <stack>

#define MAXN 5010

using namespace std;

typedef long long llint;

struct line {
    
    bool vertical;

    double a, b;
    int x1, y1, x2, y2;

    line () {}
    line (int _x1, int _y1, int _x2, int _y2) {
        x1 = _x1; x2 = _x2;
        y1 = _y1; y2 = _y2;
        vertical = _x1 == _x2;
        if (!vertical) 
            a = (double) (y1 - y2) / (x1 - x2);
        else
            a = 0;
        b = y1 - a * x1;
    }

    double get_y(double x) {
        return a * x + b;
    }

};

const double eps = 1e-10;

bool bio[MAXN];

int n;

line l[MAXN];

vector <int> v[MAXN];
stack <int> sol;

inline bool lt(const double &a, const double &b) { 
    return b - a > eps; 
}

inline bool connected(int i, int j) {
    double x1 = (double) max(l[i].x1, l[j].x1), x2 = (double) min(l[i].x2, l[j].x2);
    if (i == j || lt(x2, x1)) return false;
    return lt(l[i].get_y(x1), l[j].get_y(x1));
}

void dfs(int stick) {

    bio[stick] = true;
    
    for (int i = 0; i < (int) v[stick].size(); ++i)
        if (!bio[v[stick][i]]) dfs(v[stick][i]);

    sol.push(stick + 1);

}

int main(void) {

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 > x2) { 
            swap(x1, x2);
            swap(y1, y2);
        }
        l[i] = line(x1, y1, x2, y2);
    }

    for (int i = 0; i < n; ++i)  
        for (int j = 0; j < n; ++j)
            if (connected(i, j))
                v[i].push_back(j);

    for (int i = 0; i < n; ++i)
        if (!bio[i]) dfs(i);
    
    while (!sol.empty()) {
        printf("%d ", sol.top());
        sol.pop();
    }
    printf("\n");

    return 0;

}
