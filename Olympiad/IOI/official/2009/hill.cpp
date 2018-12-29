/**
 * Solution to IOI 2009 problem "hill"
 *
 * We employ a divide and conquer algorithm, by scanning all cells on a
 * line that cuts the area in half. For the highest cell in that line (call
 * it X), we scan the cells on either side of the line adjacent to that
 * cell. We now have a few cases:
 *
 * 1) All the cells surrounding X are of lower height. X is then a hill
 * 2) At least one of the cells adjacent to X and not on the line is
 *    higher than X. If both cells are higher, then use the highest one;
 *    call the higher cell Y. Either Y is a hill, or there is another
 *    cell in the same half of the area as Y which is higher than it and
 *    is a hill.
 *
 * In the event of option 2, the area being scanned can be shrunk to the
 * half in which Y lies, and the process repeated. The only minor thing
 * that must be catered for, is the case where we scan a line and the
 * highest adjacent cell lies in the half different to the globally best
 * height in the whole area. In such cases, the other half should be
 * recursed into, otherwise a true hill might not be found. Consider
 * the following map:
 *
 *    18  7  9 10  5  3
 *    12  6  8 11  4  2
 *    17 13 12 14 15 16
 *
 * and suppose that we started by scanning the whole of the middle row.
 * We would find that 12 is the highest cell, and scan the cells adjacent
 * to it, with heights 17 and 18. Since 18 is the highest, we would recurse
 * into the top portion of the map, meaning we are required to solve the
 * sub-problem:
 *
 *   18 7 9 10 5 3
 *
 * We attack this problem by scanning the middle column, say the 9. Since
 * it is the only cell in the column it is also the highest, and we scan
 * the cells on either side, finding that 10 is higher. If we now recursed
 * into the right half of this row, we would fail to find a hill -- since
 * the 10 is actually bordered by an 11 below it. Instead, we must realise
 * that although the 10 seems like it might be a hill, we have seen a higher
 * value of 18 and must thus recurse to the left.
 *
 * Similarly, if we scanned the 10 as the middle column, we might be
 * tempted to declare it a hill, as the 9 and 5 adjacent to it are both
 * lower. Again, this is erroneous, and remedied by the fact that we have
 * seen a higher cell which lies to the left of the 10.
 *
 * Carl Hultquist, chultquist@gmail.com
 */

#include <iostream>
#include <cstdlib>

using namespace std;

// We cache queries for efficiency, so that if our algorithm happens
// to query for a height more than once we don't actually issue the
// query.
int cache[1000][1000];

/**
 * Query for the height at co-ordinates (x,y), where x and y are
 * 0-indexed.
 */
long long query(int x, int y)
{
    if (cache[x][y] == -1)
    {
        // We have not queried for this pair of co-ordinate yet, so find
        // out what the height is and store it in the cache.
        cout << "0 " << x + 1 << " " << y + 1 << endl;
        cout.flush();

        cin >> cache[x][y];
    }

    return cache[x][y];
}

/**
 * Identifies a hill at the given co-ordinates and terminates the program.
 */
void identify_hill(int x, int y)
{
    cout << "1 " << x + 1 << " " << y + 1 << endl;
    cout.flush();

    exit(0);
}

int main()
{
    int n, m;
    cin >> n >> m;

    // Initialise the cache
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cache[i][j] = -1;

    // Start by considering the whole area
    int x1 = 0, x2 = n - 1, y1 = 0, y2 = m - 1;

    // The greatest height and co-ordinates at which this height was
    // observed.
    int curBest = -1;
    int bestX = -1, bestY = -1;

    // Keep recursing until we have only a single cell left
    while (x1 != x2 || y1 != y2)
    {
        int w = x2 - x1;
        int h = y2 - y1;

        // We split based on which dimension is greater, so as to eliminate
        // a greater portion of the remaining area.
        if (w > h)
        {
            // Divide along the height
            int mid = (x1 + x2) / 2;

            // Scan the column
            int bestH = -1;
            int by = -1;
            for (int y = y1; y <= y2; y++)
            {
                int h = query(mid, y);
                if (h > bestH)
                {
                    bestH = h;
                    by = y;
                }
            }

            // Check the adjacent cells to the highest cell in the
            // column
            int bx = mid;
            if (mid > 0 && query(mid - 1, by) > bestH)
            {
                bestH = query(mid - 1, by);
                bx = mid - 1;
            }
            if (mid < (n - 1) && query(mid + 1, by) > bestH)
            {
                bestH = query(mid + 1, by);
                bx = mid + 1;
            }

            // If both adjacent cells are lower, and the height of
            // this cell is greater than the best we have seen thus
            // far, then this must be a hill.
            if (bx == mid && bestH > curBest)
                identify_hill(bx, by);

            // If we have found a higher cell than any seen thus far,
            // update our state.
            if (bestH > curBest)
            {
                curBest = bestH;
                bestX = bx;
                bestY = by;
            }

            // Choose a half of the map to recurse into, always choosing
            // the side with the highest cell seen thus far.
            if (bestX > mid)
                x1 = mid + 1;
            else
                x2 = mid - 1;
        }
        else
        {
            // Divide along the width
            int mid = (y1 + y2) / 2;

            // Scan the row
            int bestH = -1;
            int bx = -1;
            for (int x = x1; x <= x2; x++)
            {
                int h = query(x, mid);
                if (h > bestH)
                {
                    bestH = h;
                    bx = x;
                }
            }

            // Check the adjacent cells to the highest cell in the
            // row
            int by = mid;
            if (mid > 0 && query(bx, mid - 1) > bestH)
            {
                bestH = query(bx, mid - 1);
                by = mid - 1;
            }
            if (mid < (m - 1) && query(bx, mid + 1) > bestH)
            {
                bestH = query(bx, mid + 1);
                by = mid + 1;
            }

            // If both adjacent cells are lower, and the height of
            // this cell is greater than the best we have seen thus
            // far, then this must be a hill.
            if (by == mid && bestH > curBest)
                identify_hill(bx, by);

            // If we have found a higher cell than any seen thus far,
            // update our state.
            if (bestH > curBest)
            {
                curBest = bestH;
                bestX = bx;
                bestY = by;
            }

            // Choose a half of the map to recurse into, always choosing
            // the side with the highest cell seen thus far.
            if (bestY > mid)
                y1 = mid + 1;
            else
                y2 = mid - 1;
        }
    }

    // If we have narrowed our area down to a single cell, then this cell
    // must be higher than any seen thus far and is thus a hill.
    identify_hill(x1, y1);

    return 0;
}
