// Felix Arends
#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <list>
#include <cassert>
#include <ctime>

using namespace std;

typedef list<int> LI;

struct MinMaxQueue {
    LI          q, qmax, qmin;

    void push(int v) {
        q.push_back(v);

        // every v gets added to or removed from the qmin and qmax lists
        // at most once, hence get amortised O(1) runtime.
        while(!qmax.empty() && qmax.back() < v) qmax.pop_back();
        qmax.push_back(v);
        while(!qmin.empty() && qmin.back() > v) qmin.pop_back();
        qmin.push_back(v);
    }

    int peek() { return q.front(); }

    int pop() {
        int v = q.front();
        q.pop_front();
        if (v == qmax.front()) qmax.pop_front();
        if (v == qmin.front()) qmin.pop_front();
        return v;
    }

    int getMax() { return qmax.front(); }
    int getMin() { return qmin.front(); }
    size_t size() { return q.size(); }
};

FILE    *fin = fopen("sound.in", "r"),
        *fout = fopen("sound.out", "w"); 

int main() {
    int N, M, C;
    fscanf(fin, "%d %d %d", &N, &M, &C);

    int         v;
    bool        found = false;
    MinMaxQueue q;
    for (int n = 0; n < N; n++) {
        fscanf(fin, "%d", &v);
        q.push(v);
        if (n >= M) q.pop();
        if (n >= M-1 && q.getMax() - q.getMin() <= C) {
            found = true;
            fprintf(fout, "%d\n", n - M + 2);
        }
    }
    if (!found) fprintf(fout, "NONE\n");

    return 0;
}
