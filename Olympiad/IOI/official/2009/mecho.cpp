/**
 * A binary search solution for IOI 2009 problem "mecho"
 *
 * This solution should score 100%
 *
 * Carl Hultquist, chultquist@gmail.com
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <utility>
#include <deque>

using namespace std;

#define MAX_N 2000

int cx[4] = {1, -1, 0, 0};
int cy[4] = {0, 0, 1, -1};

char mainMap[MAX_N][MAX_N];
bool reachable[MAX_N][MAX_N];

// The time that it takes the bees to reach any cell in the map
int beeDistance[MAX_N][MAX_N];

int n, s;
int dx, dy;
int mx, my;

/**
 * Tests if Mecho is able to reach his home after staying with
 * the honey for the given delay time.
 */
bool test(int delay)
{
    // Check if the bees catch Mecho whilst he is still with
    // the honey.
    if (delay * s >= beeDistance[mx][my])
        return false;

    // Initialise data structures -- at the beginning of the search,
    // Mecho has only reached the cell with the honey. Note that it
    // is possible for the bees to catch Mecho at the honey -- but
    // we checked for this case above, and so if we reach this point
    // we know that Mecho is safe with the honey after the given
    // delay.
    memset(reachable, 0, sizeof(reachable));
    deque<pair<int, pair<int, int> > > q;
    q.push_back(make_pair(delay * s, make_pair(mx, my)));
    reachable[mx][my] = true;

    // Now do the main loop to see what other cells Mecho can reach.
    while (!q.empty())
    {
        int distance = q.front().first;
        int x = q.front().second.first;
        int y = q.front().second.second;

        q.pop_front();

        // If Mecho has reached his home, then we are done.
        if (mainMap[x][y] == 'D')
            return true;

        // Check neighbouring cells
        for (int c = 0; c < 4; c++)
        {
            int nx = x + cx[c];
            int ny = y + cy[c];

            // Check that the cell is valid, that it is not a tree, and
            // that Mecho can get here before the bees.
            if (nx < 0 || nx >= n || ny < 0 || ny >= n || mainMap[nx][ny] == 'T' || (distance + 1) >= beeDistance[nx][ny] || reachable[nx][ny])
                continue;

            // All OK, so add it to the queue
            q.push_back(make_pair(distance + 1, make_pair(nx, ny)));
            reachable[nx][ny] = true;
        }
    }

    // If we reach here, then Mecho was unable to reach his home.
    return false;
}
int main(int argc, char **argv)
{
    // Read in the data
    cin >> n >> s;

    deque<pair<int, int> > bq;
    memset(beeDistance, -1, sizeof(beeDistance));

    for (int i = 0; i < n; i++)
    {
        cin >> ws;
        for (int j = 0; j < n; j++)
        {
            cin >> mainMap[i][j];
            if (mainMap[i][j] == 'H')
            {
                bq.push_back(make_pair(i, j));
                beeDistance[i][j] = 0;
            }
            else if (mainMap[i][j] == 'M')
            {
                mx = i;
                my = j;

                // Bees can travel through the location of the honey
                mainMap[i][j] = 'G';
            }
            else if (mainMap[i][j] == 'D')
            {
                dx = i;
                dy = j;
            }
        }
    }

    // Precompute the time that it takes the bees to reach any other
    // cell in the map.
    while (!bq.empty())
    {
        int x = bq.front().first;
        int y = bq.front().second;

        bq.pop_front();

        for (int c = 0; c < 4; c++)
        {
            int nx = x + cx[c];
            int ny = y + cy[c];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n || mainMap[nx][ny] != 'G' || beeDistance[nx][ny] != -1)
                continue;

            beeDistance[nx][ny] = beeDistance[x][y] + s;
            bq.push_back(make_pair(nx, ny));
        }
    }

    // The bees can never enter Mecho's home, so set this to a large
    // sentinel value.
    beeDistance[dx][dy] = n * n * s;

    // Binary search to find the maximum delay time.
    int low = -1, high = 2 * n * n;
    while (high - low > 1)
    {
        int mid = (low + high) >> 1;
        if (test(mid))
            low = mid;
        else
            high = mid;
    }

    cout << low << endl;
    return 0;
}
