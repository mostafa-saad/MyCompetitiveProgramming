/**
 * Solution to IOI 2009 problem "hiring"
 *
 * O(NlogN) solution. We process the candidates in increasing
 * order of "utility" (where utility is the candidate's minimum
 * rate of pay per unit of qualification). If we hire a candidate
 * with utility U, then we know that for all candidates with
 * utility V < U we'll be able to meet their minimum salary
 * requirement. This is because:
 *
 * V =   S1 / Q1 < S2 / Q2   = U
 * =>    S1 < (Q1 / Q2) * S2 = the amount that candidate 1
 *                             will get paid
 *
 * The speedup to NlogN comes from the fact that we store the
 * candidates qualification values in a heap, giving O(logN)
 * time to insert them and then O(logN) time to remove over-
 * qualified candidates from the heap who are inflating the
 * cost too much.
 *
 * Carl Hultquist, chultquist@gmail.com
 */

#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdio>

using namespace std;

#define MAX_N 500000

class candidate
{
public:
    double s, q, r;
    int i;

    bool operator < (const candidate &c) const
    {
        return r < c.r;
    }
};

candidate c[MAX_N];
int n;
long long w;

int best = 0;
int bestIndex = 0;
double bestCost = 0;

int main()
{
    scanf("%d %lld", &n, &w);
    assert(1 <= n && n <= MAX_N);

    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &c[i].s, &c[i].q);
        c[i].r = c[i].s / c[i].q;
        c[i].i = i + 1;
    }

    sort(c, c + n);

    // We now have a list of the candidates sorted by their utility. We
    // process the candidates in this order, and add them to the list of
    // candidates chosen. While the set of candidates chosen costs us
    // too much, we remove the most qualified candidate (and thus the one
    // which is inflating the cost too much).
    double totalQual = 0;
    vector<double> heapQuals;
    heapQuals.reserve(n);
    for (int i = 0; i < n; i++)
    {
        heapQuals.push_back(c[i].q);
        push_heap(heapQuals.begin(), heapQuals.end());
        totalQual += c[i].q;
        double maxQual = w / c[i].r;
        while (totalQual > maxQual)
        {
            totalQual -= heapQuals[0];
            pop_heap(heapQuals.begin(), heapQuals.end());
            heapQuals.pop_back();
        }

        // If we have more candidates than we have previously
        // seen before, then make a note of the number and of
        // the last candidate that we processed.
        int num = (int) heapQuals.size();
        double cost = totalQual * c[i].r;
        if (num > best || (num == best && cost < bestCost))
        {
            best = num;
            bestCost = cost;
            bestIndex = i;
        }
    }

    // In order to maintain an O(NlogN) algorithm, we must
    // recreate the best set of candidates outside the main
    // loop (if we updated it inside the main loop, we could
    // trigger O(N) updates giving overall complexity of
    // O(N^2)!
    vector<pair<double, int> > heap;
    bool usedCandidate[n + 1];
    memset(usedCandidate, 0, sizeof(usedCandidate));

    totalQual = 0;
    for (int i = 0; i <= bestIndex; i++)
    {
        heap.push_back(make_pair(c[i].q, c[i].i));
        push_heap(heap.begin(), heap.end());
        totalQual += c[i].q;
        usedCandidate[c[i].i] = true;
    }

    // Remove over-qualified candidates
    double maxQual = w / c[bestIndex].r;
    while (totalQual > maxQual)
    {
        totalQual -= heap[0].first;
        usedCandidate[heap[0].second] = false;
        pop_heap(heap.begin(), heap.end());
        heap.pop_back();
    }

    // Output the list of candidates used
    printf("%d\n", best);
    for (int i = 1; i <= n; i++)
        if (usedCandidate[i])
            printf("%d\n", i);

    return 0;
}
