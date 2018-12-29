/**
 * Solution to IOI 2009 problem "garage"
 *
 * Carl Hultquist, chultquist@gmail.com
 */

#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <cmath>
#include <deque>

using namespace std;

#define MAX_N 100
#define MAX_M 2000
#define MAX_R 100
#define MAX_W 10000

int main()
{
    int n, m;

    cin >> n >> m;
    assert(1 <= n && n <= MAX_N);
    assert(1 <= m && m <= MAX_M);

    int r[n];
    int w[m];

    // Keep track of which parking spaces are occupied, and where
    // each car has parked.
    bool occupied[n];
    int space[m];

    for (int i = 0; i < n; i++)
    {
        cin >> r[i];
        assert(1 <= r[i] && r[i] <= MAX_R);
        occupied[i] = false;
    }

    for (int i = 0; i < m; i++)
    {
        cin >> w[i];
        assert(1 <= w[i] && w[i] <= MAX_W);
        space[i] = -1;
    }

    // For efficiency, we keep track of the first available parking space
    int firstSpace = 0;

    // Queue for cars that are waiting for a parking space to free up.
    deque<int> q;

    // The total revenue
    int revenue = 0;

    for (int i = 0; i < 2 * m; i++)
    {
        int x;
        cin >> x;
        assert(-m <= x && x <= m);
        assert(space[abs(x) - 1] >= -1); // Cannot park a car in the garage more than once

        // Parking the car
        if (x > 0)
        {
            // Get a zero-based index for the car
            x--;

            // To simplify input processing, we push the car onto the queue for now.
            // We will immediately remove it from the queue shortly if there are
            // parking spaces available.
            q.push_back(x);
        }
        else
        {
            // Get a zero-based index for the car
            x = -1 - x;

            assert(space[x] >= 0); // Check that we've parked the car

            // Do the housekeeping necessary to "un-park" the car
            int spot = space[x];
            occupied[spot] = false;
            space[x] = -2;

            // Update our first available space if appropriate
            if (spot < firstSpace)
                firstSpace = spot;
        }

        // If there are any cars waiting to be parked and if we have space,
        // then park them.
        while (firstSpace < n && !q.empty())
        {
            // Park the first car in the queue
            assert(occupied[firstSpace] == false);

            // Money, money, money!
            revenue += w[q.front()] * r[firstSpace];

            // Housekeeping to park the car
            occupied[firstSpace] = true;
            space[q.front()] = firstSpace;
            q.pop_front();

            // Update our first available space
            while (firstSpace < n && occupied[firstSpace])
                firstSpace++;
        }
    }

    // And finally output the total revenue
    cout << revenue << endl;

    return 0;
}
