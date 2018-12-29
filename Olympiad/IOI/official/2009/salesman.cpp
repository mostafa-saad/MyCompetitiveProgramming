/**
 * Solution to IOI 2009 problem "salesman"
 *
 * We use a C++ set to store the list of currently "active" fairs,
 * where an active fair is one that has a better profit than by
 * visiting the fair than reaching the same location from some
 * other fair. We then process the fairs in order of the time at
 * which they occur, using our active set to find the best fair
 * to come from in order to visit each new successive fair, and
 * updating the active set with the new fair afterwards.
 *
 * For fairs on the same day, we note that the most efficient
 * way of visiting these is to pick one as a starting point and
 * then visit fairs in a single direction. We test both the
 * upstream and downstream directions, and for each fair decide
 * whether it is better to go directly to this fair or to come
 * from the previous fair opposite to the direction in which
 * we are travelling.
 *
 * Carl Hultquist, chultquist@gmail.com
 */

#include <iostream>
#include <cassert>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX_N 500000
#define MAX_D_U 10
#define MAX_S 500001
#define MAX_T 500000
#define MAX_L 500001
#define MAX_M 4000

int n, d, u, s;

// Class for storing all the things we want to associate with a fair
typedef struct fair
{
    int t, l, m;
    int best;

    // Used for traversing upstream and downstream when fairs occur
    // on the same day.
    int baseBest;
    int curBest;

    // Order fairs first according to time, and secondly according
    // to their location (which makes the upstream and downstream
    // traversals much easier).
    bool operator <(const fair &f) const
    {
        if (t < f.t)
            return true;
        else if (t == f.t && l < f.l)
            return true;
        else
            return false;
    }
} fair;

// For our set, we want to order fairs by location only, so have
// a special comparator for this.
struct location_less
{
    bool operator ()(const fair &x, const fair &y)
    {
        return x.l < y.l;
    }
};

vector<fair> fairs;
set<fair, location_less> activeFairs;

/**
 * Computes the cost of travelling between two points on the river.
 */
double travelCost(double from, double to)
{
    if (from < to)
        return (to - from) * d;
    else
        return (from - to) * u;
}

/**
 * Queries for the best profit that we can expect to earn when
 * visiting fair i directly from some fair that occurred on a
 * previous day.
 *
 * We find the active fairs that occur to the left and right of
 * this one along the river -- it is fairly easy to show that our
 * optimal predecessor must be one of these fairs. Then we pick
 * the one which gives us a greater profit.
 */
int query(int i)
{
    set<fair, location_less>::iterator low = activeFairs.lower_bound(fairs[i]);
    set<fair, location_less>::iterator high = low;

    if (low != activeFairs.begin())
        low--;
    if (high == activeFairs.end())
        high--;

    return max(low->best - travelCost(low->l, fairs[i].l),
               high->best - travelCost(high->l, fairs[i].l)) + fairs[i].m;
}

/**
 * Updates our active fairs set with the given fair. Care must be
 * taken to ensure that this fair is actually active (if all fairs
 * are on distinct days then it will be, but if there are several on
 * the same day then there may be a better path to this location on
 * the river via some other fair).
 */
void update(int i)
{
    // Insert by default, we will remove it later if we need to.
    activeFairs.insert(fairs[i]);

    set<fair, location_less>::iterator thisFair = activeFairs.lower_bound(fairs[i]);
    set<fair, location_less>::iterator cur = thisFair;

    // Check upstream fairs
    while (cur != activeFairs.begin())
    {
        cur--;

        // Check if the fair we have just added is covered by the
        // previous fair in the set.
        if (cur->best - travelCost(cur->l, thisFair->l) >= thisFair->best)
        {
            // Yes, so remove and return
            activeFairs.erase(thisFair);
            return;
        }

        // Check if the fair we have just added covers the previous
        // fair in the set.
        if (thisFair->best - travelCost(thisFair->l, cur->l) < cur->best)
            // No, so stop removing non-active fairs
            break;

        // Remove the fair that is covered by our recently added one,
        // and which is thus no longer active.
        activeFairs.erase(cur);
        cur = thisFair;
    }

    // Check downstream fairs
    cur = thisFair;
    cur++;
    while (cur != activeFairs.end())
    {
        // Check if the fair we have just added is covered by the
        // next fair in the set.
        if (cur->best - travelCost(cur->l, thisFair->l) >= thisFair->best)
        {
            // Yes, so remove and return
            activeFairs.erase(thisFair);
            return;
        }

        // Check if the fair we have just added covers the next
        // fair in the set.
        if (thisFair->best - travelCost(thisFair->l, cur->l) < cur->best)
            break;

        // Remove the fair that is covered by our recently added one,
        // and which is thus no longer active.
        activeFairs.erase(cur);
        cur = thisFair;
        cur++;
    }
}

int main()
{
    scanf("%d %d %d %d", &n, &u, &d, &s);

    assert(1 <= n && n <= MAX_N);
    assert(1 <= d && d <= MAX_D_U);
    assert(1 <= u && u <= MAX_D_U);
    assert(1 <= s && s <= MAX_S);

    fairs.resize(n + 2);
    int maxT = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d %d", &fairs[i].t, &fairs[i].l, &fairs[i].m);

        assert(1 <= fairs[i].t && fairs[i].t <= MAX_T);
        assert(1 <= fairs[i].l && fairs[i].l <= MAX_L);
        assert(1 <= fairs[i].m && fairs[i].m <= MAX_M);

        maxT = max(maxT, fairs[i].t);
    }

    // Create a dummy fairs for the salesman's home at the beginning,
    // and also one at the end
    fairs[0].l = s;
    fairs[0].best = 0;
    fairs[0].t = -1;
    fairs[n + 1].l = s;
    fairs[n + 1].m = 0;
    fairs[n + 1].t = maxT + 1;

    sort(fairs.begin(), fairs.end());

    // At the beginning, only fair 0 (the salesman's home) is active
    activeFairs.insert(fairs[0]);

    for (int i = 1; i <= n; i++)
    {
        // Check to see if we have multiple fairs on the same day
        if (i == n || fairs[i].t != fairs[i + 1].t)
        {
            // No, so just do the simple approach of querying for
            // the best fair to come from in order to reach this
            // one, and update our data structure.

            fairs[i].best = query(i);

            update(i);
        }
        else
        {
            // Yes, there are multiple fairs happening on this day. We need
            // to choose the best way of picking which of these fairs to
            // visit.
            int first = i;
            while (i <= n && fairs[i].t == fairs[first].t)
                i++;
            i--;
            int last = i;

            // First, find the cheapest way of reaching each fair on this
            // day if we visit no other fairs on the same day.
            for (int j = first; j <= last; j++)
            {
                fairs[j].baseBest = query(j);
                fairs[j].best = fairs[j].baseBest;
            }

            // Now visit each of the fairs in both an upstream and
            // downstream direction, in each case seeing if it was
            // better to come via the previous fair.
            fairs[first].curBest = fairs[first].baseBest;
            for (int j = first + 1; j <= last; j++)
            {
                // See if it is better to come from the previous
                // fair.
                int profit = fairs[j - 1].curBest - travelCost(fairs[j - 1].l, fairs[j].l) + fairs[j].m;
                if (profit > fairs[j].baseBest)
                    fairs[j].curBest = profit;
                else
                    fairs[j].curBest = fairs[j].baseBest;

                if (fairs[j].curBest > fairs[j].best)
                    fairs[j].best = fairs[j].curBest;
            }

            // And upstream. Don't forget to start off with the base
            // value of visiting this fair directly (otherwise we will
            // use values fro the downstream pass, which will be
            // confusing).
            fairs[last].curBest = fairs[last].baseBest;
            for (int j = last - 1; j >= first; j--)
            {
                // See if it is better to come from the previous
                // fair.
                int profit = fairs[j + 1].curBest - travelCost(fairs[j + 1].l, fairs[j].l) + fairs[j].m;
                if (profit > fairs[j].baseBest)
                    fairs[j].curBest = profit;
                else
                    fairs[j].curBest = fairs[j].baseBest;

                if (fairs[j].curBest > fairs[j].best)
                    fairs[j].best = fairs[j].curBest;
            }

            // Update our query structure for all of these fairs, and
            // see if there is a better way home from any of them.
            for (int j = first; j <= last; j++)
                update(j);
        }
    }

    int best = query(n + 1);

    // Check that our profit is positive; if not then output 0
    // (indicating that the salesman simply stays at home for the
    // year).
    cout << (best < 0 ? 0 : best) << endl;

    return 0;
}
