/* IOI 2009 "region" problem.
 *
 * Solution by Bruce Merry.
 *
 * This is the second solution described in the writeup. Briefly:
 * - queries are cached so that duplicate queries can be answered again quickly
 * - each new quality is answered in either O(A log B), O(B log A) or O(A + B),
 *   whichever is deemed fastest.
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>
#include <map>

using namespace std;

typedef long long ll;

/* An employee in the tree */
struct node
{
    int id;     /* New employee ID from a pre-order walk (0-based) */
    int region; /* Employee's home region */
    int low;    /* Lowest ID of managees */
    int high;   /* Highest ID of managees */
    vector<int> children;   /* Supervisees */
};

struct region
{
    vector<int> ids;                /* Sorted list of (new) employee IDs */
    /* Sorted of intervals with the same nesting level. Each pair is
     * (ID, depth) where ID is the left end-point of the interval (inclusive).
     * The right end-point is implicit from the following interval.
     */
    vector<pair<int, int> > ranges;
    int depth; /* Working depth during the DFS. */

    region() : ids(), ranges(), depth(0) {}
};

static int N, R, Q;
static vector<node> nodes;
static vector<region> regions;

/* Does a pre-order walk over the subtree rooted at root. id_pool contains
 * the next unused employee ID, and on return it will be updated to again
 * be the next available ID.
 *
 * This procedure builds the regions arrays, after which the tree is no
 * longer needed.
 */
static void process_tree(int root, int &id_pool)
{
    int id = id_pool++;
    int r = nodes[root].region;
    regions[r].ids.push_back(id);
    regions[r].depth++;
    /* Depth changed, so after this point we need a new range */
    regions[r].ranges.push_back(make_pair(id_pool, regions[r].depth));

    /* Recursively process children */
    for (size_t i = 0; i < nodes[root].children.size(); i++)
        process_tree(nodes[root].children[i], id_pool);
    regions[r].depth--;
    /* Undo the depth change, and start another interval after the last
     * managee.
     */
    regions[r].ranges.push_back(make_pair(id_pool, regions[r].depth));
}

/* Find smallest n such that 2^n <= x */
static int log2(int x)
{
    int ans = -1;
    while (x)
    {
        x >>= 1;
        ans++;
    }
    return ans;
}

/* Query in O(R2 log R1) time, by counting for each employee in r2. */
static ll query_by_id(const region &r1, const region &r2)
{
    ll ans = 0;
    for (size_t i = 0; i < r2.ids.size(); i++)
    {
        int pos = r2.ids[i];
        vector<pair<int, int> >::const_iterator site;
        /* Find the first range that starts at pos or later. This will
         * actually be the range after the one we want.
         */
        site = lower_bound(r1.ranges.begin(), r1.ranges.end(), make_pair(pos, INT_MAX));
        if (site == r1.ranges.begin())
        {
            /* pos is less than the start of the first range, so has no
             * manager in r2.
             */
            continue;
        }
        --site; /* Now we have the range we want. */
        ans += site->second;
    }
    return ans;
}

/* Query in O(R1 log R2) time, by counting for each employee in r1 */
static ll query_by_range(const region &r1, const region &r2)
{
    ll ans = 0;
    for (size_t i = 0; i + 1 < r1.ranges.size(); i++)
    {
        int pos1 = r1.ranges[i].first;
        int pos2 = r1.ranges[i + 1].first;
        ll depth = r1.ranges[i].second;

        /* Each employee from r2 in [pos1, pos2) has depth managers
         * from r1. Find the intersections of [pos1, pos2) with the
         * employee list for r2.
         */
        vector<int>::const_iterator first, last;
        first = lower_bound(r2.ids.begin(), r2.ids.end(), pos1);
        last = lower_bound(r2.ids.begin(), r2.ids.end(), pos2);
        ans += depth * (last - first);
    }
    return ans;
}

/* Query in O(R1 + R2) time, by counting for each employee in r1
 * but with a linear sweep instead of a binary search.
 */
static ll query_stitch(const region &r1, const region &r2)
{
    ll ans = 0;

    /* Find the first employee id that is in the first range */
    vector<int>::const_iterator id = r2.ids.begin();
    if (r1.ranges.empty())
        return 0;
    while (id != r2.ids.end() && *id < r1.ranges[0].first)
        id++;

    /* Iterate over the ranges as above */
    for (size_t i = 0; i + 1 < r1.ranges.size() && id != r2.ids.end(); i++)
    {
        int pos2 = r1.ranges[i + 1].first;
        ll depth = r1.ranges[i].second;

        /* Find the end of the section of employees from this range */
        vector<int>::const_iterator old_id = id;
        while (id != r2.ids.end() && *id < pos2)
            id++;
        ans += depth * (id - old_id);
    }
    return ans;
}

int main()
{
    scanf("%d %d %d", &N, &R, &Q);

    /* Load input and build tree */
    nodes.resize(N);
    regions.resize(R);
    scanf("%d", &nodes[0].region);
    nodes[0].region--;
    for (int i = 1; i < N; i++)
    {
        int parent;
        scanf("%d %d", &parent, &nodes[i].region);
        parent--;
        nodes[i].region--;
        nodes[parent].children.push_back(i);
    }

    /* Turn the tree into regions */
    int id_pool = 0;
    process_tree(0, id_pool);

    /* Process queries */
    map<pair<int, int>, ll> cache;
    for (int q = 0; q < Q; q++)
    {
        int r1, r2;
        scanf("%d %d", &r1, &r2);
        r1--;
        r2--;
        pair<int, int> key(r1, r2);
        if (cache.count(key))
        {
            /* Answer query from the cache */
            printf("%lld\n", cache[key]);
            fflush(stdout);
            continue;
        }

        /* Fudge factor to estimate the relative cost of binary search
         * versus linear walk. This will depend to some extent on the
         * memory system.
         */
        static const int LOG_FACTOR = 5;

        /* Pick the best query method */
        const region &region1 = regions[r1];
        const region &region2 = regions[r2];
        int size1 = region1.ids.size();
        int size2 = region2.ids.size();
        int costs[3] = {
            size1 * (log2(size2) + 2) * LOG_FACTOR,
            size2 * (log2(size1) + 2) * LOG_FACTOR,
            size1 + size2
        };
        ll ans = 0;
        switch (min_element(costs, costs + 3) - costs)
        {
        case 0:
            ans = query_by_range(region1, region2);
            break;
        case 1:
            ans = query_by_id(region1, region2);
            break;
        case 2:
            ans = query_stitch(region1, region2);
            break;
        }
        printf("%lld\n", ans);
        fflush(stdout);
        cache[key] = ans;
    }
    return 0;
}
