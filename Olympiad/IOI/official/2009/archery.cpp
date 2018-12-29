/**
 * Solution to IOI 2009 problem "archery"
 *
 * An O(NlogN) solution.
 *
 * Carl Hultquist, chultquist@gmail.com
 */

#include <iostream>
#include <cassert>
#include <cstring>
#include <utility>

using namespace std;

#define MAX_N 250000
#define MAX_M 1000000000

int n, m;
int ranks[MAX_N * 2];
int rank;

pair<int, int> cache[MAX_N];
bool cached[MAX_N];
int black[3 * MAX_N + 1], grey[3 * MAX_N + 1], white[3 * MAX_N + 1];

/**
 * An O(N) simulation of the tournament, given our starting
 * position. We also return the number of times that the
 * we get bumped from target 1 to target N.
 */
pair<int, int> simulate(int start)
{
    // As we might run multiple binary searches, we cache
    // the output from this routine for efficiency.
    int targ = start >> 1;
    if (cached[targ])
        return cache[targ];

    if (rank == 1)
        cache[targ] = make_pair(1, 0);
    else if (rank <= n + 1)
    {
        // We're part of the group of archers that circles
        // around after 2*N rounds. To find out where we
        // will finish after M rounds, we only consider what
        // happens on target 1. After 2*N rounds have taken
        // place, we note the next round at which we compete
        // on target 1 -- we can then easily compute where
        // we will finish, since for each successive round
        // we will move to the next target (as we'll be in
        // the cycle phase).

        memset(black, 0, sizeof(black));
        memset(grey, 0, sizeof(grey));
        memset(white, 0, sizeof(white));

        // Update the initial p values of the archers -- this is the
        // minimum number of rounds that it will take an archer to
        // reach the first target.
        grey[start >> 1] = 1;
        for (int i = 1; i < n * 2; i++)
        {
            int target = (i - 1 + (i > start ? 1 : 0)) >> 1;
            if (ranks[i] < rank)
                black[target]++;
            else
                white[target]++;
        }

        // Work out the ranks of the first two archers on the first target
        int archer1, archer2;
        if (start < 2)
        {
            archer1 = ranks[1];
            archer2 = rank;
        }
        else {
            archer1 = ranks[1];
            archer2 = ranks[2];
        }

        // And convert the ranks into counts of black, grey and white
        // archers.
        int s_black = 0, s_grey = 0, s_white = 0;
        if (archer1 < rank)
            s_black++;
        else if (archer1 == rank)
            s_grey++;
        else
            s_white++;
        if (archer2 < rank)
            s_black++;
        else if (archer2 == rank)
            s_grey++;
        else
            s_white++;

        int cumulative_black = 0, cumulative_grey = 0, cumulative_white = 0;
        int seen = -1;
        int bumps = 0;

        for (int round = 0; round < 3 * n; round++)
        {
            // Check if we've seen ourselves on target 1 after
            // enough rounds have passed.
            if (round >= 2 * n && (s_grey == 1))
            {
                seen = round;
                break;
            }

            // Determine the colour of the loser of this round
            int loser;
            if (s_black > 0)
            {
                if (s_black == 2)
                    loser = 0;
                else if (s_grey == 1)
                {
                    loser = 1;
                    bumps++;
                }
                else
                    loser = 2;
            }
            else
                loser = 2;

            // We expect the loser to make it back to the first target n
            // rounds from now at best (if they win all of their matches).
            int new_p = round + n;
            if (new_p <= 3 * n)
            {
                // We only consider cases below 3n, since that is as far
                // as we need to simulate.

                if (loser == 0)
                {
                    black[new_p]++;
                    s_black--;
                }
                else if (loser == 1)
                {
                    grey[new_p]++;
                    s_grey--;
                }
                else
                {
                    white[new_p]++;
                    s_white--;
                }
            }

            // Now pick an archer to move onto target 1. We add to our
            // consideration list all of the archers who we thought would
            // make it by the coming round.
            cumulative_black += black[round + 1];
            cumulative_grey += grey[round + 1];
            cumulative_white += white[round + 1];

            // Now pick the best archer out of our consideration
            // list.
            if (cumulative_black > 0)
            {
                s_black++;
                cumulative_black--;
            }
            else if (cumulative_grey > 0)
            {
                s_grey++;
                cumulative_grey--;
            }
            else
            {
                s_white++;
                cumulative_white--;
            }
        }

        if (m > seen)
            bumps++;

        cache[targ] = make_pair(n - ((m - seen + n - 1) % n), bumps);
    }
    else {
        // We're part of the group of weak archers that
        // gets stuck on some target after 2*N rounds. We
        // just need to work out what that target is.
        //
        // The idea is that as we simulate the tournament, we can only
        // end up with at most one weak archer on any target. So to
        // work out where we end up, we "push" the weaker archers around
        // the targets. Specifically, we only push ourself (the grey
        // archer) and all the archers weaker than us (white archers).

        // Keep track of the number of grey and white archers on each
        // target.
        int white[n], grey[n];
        memset(white, 0, sizeof(white));
        memset(grey, 0, sizeof(grey));

        grey[start >> 1] = 1;

        for (int i = 1; i < 2 * n; i++)
            if (ranks[i] > rank)
                white[(i - 1 + (i > start ? 1 : 0)) >> 1]++;

        // Now we push them around. We start at the first target and follow
        // the targets that archers would get moved to for losing on each
        // target, keeping track of how many archers we are pushing around.
        int shift_white = 0, shift_grey = 0;
        int bumps = 0;

        // It should take 2n rounds for the archers to settle. However, we
        // will only pick up some of the archers towards the end of our first
        // round, so we run for 3n rounds to accommodate this.
        for (int it = 0; it < 3; it++)
        {
            // Start at the first target
            int pos = 0;
            do {
                // Calculate the total number of archers we have on this
                // target, including the ones that we've pushed from the
                // previous target.
                int cur_white = white[pos] + shift_white;
                int cur_grey = grey[pos] + shift_grey;

                // Now leave an archer behind and work out how many we
                // should push to the next target.
                if (cur_white + cur_grey > 1)
                {
                    // More than one grey + white archer, so we must
                    // leave one behind and push the others.
                    if (pos > 0)
                    {
                        // If this is not the first target, then the
                        // grey archer advances, if present, and a
                        // white one stays.
                        white[pos] = 1;
                        shift_white = cur_white - 1;
                        grey[pos] = 0;
                        if (cur_grey > 0)
                            shift_grey = cur_grey;
                        else
                            shift_grey = 0;
                    }
                    else {
                        // If this is the first target, then the grey
                        // one stays (if present) and the white ones
                        // get pushed.
                        if (cur_grey > 0)
                        {
                            grey[pos] = 1;
                            white[pos] = 0;
                            shift_grey = cur_grey - 1;
                            shift_white = cur_white;
                        }
                        else
                        {
                            grey[pos] = 0;
                            white[pos] = 1;
                            shift_grey = 0;
                            shift_white = cur_white - 1;
                        }
                    }
                }
                else {
                    // Only one white or grey archer, so either leave
                    // them behind or push them depending on which target
                    // we are on.
                    if (pos > 0)
                    {
                        white[pos] = cur_white;
                        grey[pos] = cur_grey;
                        shift_white = 0;
                        shift_grey = 0;
                    }
                    else
                    {
                        if (cur_grey > 0)
                            bumps++;
                        white[pos] = 0;
                        grey[pos] = 0;
                        shift_white = cur_white;
                        shift_grey = cur_grey;
                    }
                }

                // Move onto the next position.
                if (pos == 0)
                    pos = n - 1;
                else
                    pos--;
            } while (pos > 0);
        }

        int i;
        for (i = 0; i < n; i++)
            if (grey[i] > 0)
            {
                cache[targ] = make_pair(i + 1, bumps);
                break;
            }

        // Sanity check
        assert(i < n && grey[i] > 0);
    }

    cached[targ] = 1;
    return cache[targ];
}

/**
 * Binary search for the best place to start within a given range
 * of starting positions. This assumes that our ending position will
 * not wrap as we try different starting positions; see the main
 * method below for details of how this is used.
 */
pair<int, int> search(int s, int e)
{
    pair<int, int> start, end, mid;
    int mi;
    start = simulate(s * 2 - 1);
    end = simulate(e * 2 - 1);
    while ((e - s) > 1)
    {
        mi = (s + e) >> 1;
        mid = simulate(mi * 2 - 1);

        if (start.first < mid.first)
        {
            e = mi;
            end = mid;
        }
        else {
            s = mi;
            start = mid;
        }
    }

    if (start.first < end.first)
        return make_pair(start.first, s);
    else
        return make_pair(end.first, e);
}

int main()
{
    memset(cached, 0, sizeof(cached));

    cin >> n >> m;
    assert(1 <= n && n <= MAX_N);
    assert(2 * n <= m && m <= MAX_M);

    //  We reduce m to take advantage of the fact that after
    // 2n rounds, the archers move around in a cyclical pattern.
    m = 2 * n + (m % n);

    for (int i = 0; i < n * 2; i++)
        cin >> ranks[i];

    rank = ranks[0];

    // We binary search to find the target to start at. To do this,
    // we may require two searches (one to find the point at which
    // we wrap around to the next target, and one to then find the
    // best target).
    int best_start;
    pair<int, int> start, end, mid;
    int s = 1, e = n, mi;
    start = simulate(s * 2 - 1);
    end = simulate(e * 2 - 1);
    if (start.second > end.second)
    {
        // There's a wrap. Start by finding the wrapping point.
        while ((e - s) > 1)
        {
            mi = (s + e) >> 1;
            mid = simulate(mi * 2 - 1);

            if (mid.second > end.second)
            {
                // We've wrapped, and so have gone too far.
                s = mi;
                start = mid;
            }
            else
            {
                // No wrap yet. Better push it a bit further.
                e = mi;
                end = mid;
            }
        }

        if (start.second > end.second)
            mi = e;
        else
            mi = s;

        pair<int, int> start_side = search(1, mi - 1);
        pair<int, int> end_side = search(mi, n);

        if (start_side.first < end_side.first)
            best_start = start_side.second;
        else
            best_start = end_side.second;
    }
    else
    {
        // No wrap, just binary search for the best place to
        // start.
        pair<int, int> best = search(1, n);
        best_start = best.second;
    }

    cout << best_start << endl;

    return 0;
}
