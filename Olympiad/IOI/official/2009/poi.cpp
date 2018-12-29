/**
 * Solution to IOI 2009 problem "poi"
 *
 * Carl Hultquist, chultquist@gmail.com
 */

#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

#define MAX_N 2000
#define MAX_T 2000

vector<int> solved[MAX_N];
int points[MAX_T];
int score[MAX_N];

/**
 * Method for comparing two contestants, for determining their
 * order in the rankings. Returns true if contestant with index
 * x should appear before y in the list (i.e. x ranks higher
 * than y).
 */
bool poiLess(int x, int y)
{
    // If x has a higher score, then they did better.
    if (score[x] > score[y])
        return true;
    else if (score[x] == score[y])
    {
        // If they have the same score, then see who solved more
        // problems.
        if (solved[x].size() > solved[y].size())
            return true;
        else if (solved[x].size() == solved[y].size())
            // Same number of problems, so base the decision on
            // the contestants' IDs.
            return x < y;
        else
            return false;
    }
    else
        return false;
}

int main()
{
    int n, t, p;

    scanf("%d %d %d", &n, &t, &p);
    assert(1 <= n && n <= MAX_N);
    assert(1 <= t && t <= MAX_T);
    assert(1 <= p && p <= n);

    p--;

    memset(points, 0, sizeof(points));

    // Now read in the information about which contestants solved
    // which problems. As we do this, we keep track for each problem
    // how many contestants did not solve it, and thus how many points
    // the problem will be worth.
    for (int i = 0; i < n; i++)
    {
        solved[i].reserve(n);
        int x;
        for (int j = 0; j < t; j++)
        {
            scanf("%d", &x);
            if (x == 1)
                // Solved, so make a note of this
                solved[i].push_back(j);
            else
                // Not solved, which means that the problem is worth
                // one extra point
                points[j]++;
        }
    }

    // We now work out the actual number of points that each
    // contestant receives, based on how many points the problem
    // ended up being worth.
    vector<int> sortedIds;
    sortedIds.reserve(n);
    for (int i = 0; i < n; i++)
    {
        score[i] = 0;
        for (unsigned int j = 0; j < solved[i].size(); j++)
            score[i] += points[solved[i][j]];
        sortedIds.push_back(i);
    }

    // Now sort the contestants.
    sort(sortedIds.begin(), sortedIds.end(), poiLess);

    // Now find out which position Philip came in
    for (int i = 0; i < n; i++)
        if (sortedIds[i] == p)
        {
            cout << score[p] << " " << (i + 1) << endl;
            return 0;
        }

    // Should never get here
    assert(false);

    return 0;
}
