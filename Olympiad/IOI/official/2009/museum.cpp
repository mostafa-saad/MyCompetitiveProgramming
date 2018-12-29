/**
 * Solution to IOI 2009 problem "museum"
 *
 * To solve this problem, we start by observing that if we have three
 * vases with heights A, B and C, such that either A is odd and C even or
 * A even and C odd, then no matter what B is these three vases will not
 * violate the condition of the exhibition organisers. This is because
 * A + C must therefore be odd, and so is not divisble by 2, meaning that
 * it is impossible for B to be the average of A and C.
 *
 * We therefore start by arranging the vases such that we place all the
 * even vases first, and all the odd vases second. This gives an
 * arrangement that looks like this:
 *
 *  E1 E2 E3 ... Ex O1 O2 O3 ... Oy
 *
 * Since we know from the above observation that it is impossible to
 * choose A = Ei and B = Oj for any i and j such that there is a vase C
 * between these which violates the organisers' condition, it follows
 * that if there is a violation we must have either A = Ei and B = Ej
 * or A = Oi and B = Oj.
 *
 * Consider the even vases -- each has height 2X for some X. Suppose we
 * pick three vases with heights A = 2X, B = 2Y and C = 2Z such that
 * they violate the condition. We must then have 2 * 2Y = 2X + 2Z, which
 * implies that 2Y = X + Z. Similarly to above, it follows that X and Z
 * must either both be even or both be odd. If X and Z are even, then A
 * and C are divisible by 4, and if X and Z are odd then A and C are not
 * divisible by 4. To eliminate these condition violations, we thus arrange
 * the even group of vases such that they start with those divisible by 4
 * and are followed by those not divisible by 4.
 *
 * The odd case is similar -- if we pick three vases from the Oi's such
 * that A = 2X + 1, B = 2Y + 1 and C = 2Z + 1, it follows that for the
 * condition to be violated we must have 2Y = X + Z. This corresponds
 * to A and C both being congruent to either 1 or 3 modulo 4, and we can
 * avoid these conflicts by grouping the odd vases to have the ones whose
 * height modulo 4 is 1 first, followed by those whose height is 3 modulo
 * 4.
 *
 * We continue this process, regrouping for modulo 8, 16 etc until we
 * have reached N.
 *
 * A more cunning solution is to simply represent each height in binary,
 * reverse the binary digits, and sort according to these reversed values.
 * In this way, all even numbers will appear first (since their last binary
 * digit is 0, which after the reversal is their first digit). Sorting on
 * the second binary digit will sort according to residues modulo 4, by
 * the third according to modulo 8, etc.
 *
 * Carl Hultquist, chultquist@gmail.com
 */

#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

int main()
{
    int n;
    cin >> n;

    // Determine the number of bits we need to represent the height
    // of the tallest vase.
    int bits = 0;
    int cur = n;
    while (cur != 0)
    {
        cur >>= 1;
        bits++;
    }

    // Instead of storing explicit strings, we create a reverse numeric
    // encoding on the fly. For each vase, we store its encoding and the
    // actual vase height as a pair of integers. Sorting these later will
    // sort by the encoded value, giving us the order we want.
    pair<int, int> order[n];
    for (int i = 0; i < n; i++)
    {
        int x = 0;
        int b = bits - 1;
        cur = i + 1;
        while (cur != 0)
        {
            // Only add powers of two for bits that matter
            if (cur & 1)
                x += (1 << b);
            cur >>= 1;
            b--;
        }

        order[i] = make_pair(x, i + 1);
    }

    // Sort everything
    sort(order, order + n);

    // And output the final ordering
    for (int i = 0; i < n; i++)
        cout << order[i].second << endl;

    return 0;
}
