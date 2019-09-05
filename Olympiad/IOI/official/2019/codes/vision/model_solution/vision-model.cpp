#include "vision.h"

using namespace std;

inline int OR(vector<int> &Ns)
{
    return add_or(Ns);
}

inline int XOR(vector<int> &Ns)
{
    return add_xor(Ns);
}

inline int XOR(int A, int B)
{
    return add_xor({A, B});
}

inline int AND(int A, int B)
{
    return add_and({A, B});
}

inline int AND_NOT(int A, int B)
{
    return AND(A, add_not(B));
}

vector<int> diagonal(int H, int W, int N, bool D)
{
    vector<int> cells;
    int first, last, step;
    if (D)
    {
        first = N < W ? N : W * (N - W + 2) - 1;
        last = N < H ? N * W : (H - 1) * W + (N - H + 1);
        step = W - 1;
    }
    else
    {
        first = N < W ? W - 1 - N : W * (N - W + 1);
        last = N < H ? (N + 1) * W - 1 : H * W + (H - 2 - N);
        step = W + 1;
    }
    int cur = first;
    while (true)
    {
        cells.emplace_back(cur);
        if (cur == last)
        {
            break;
        }
        cur += step;
    }
    return cells;
}

void collect_diagonals(int H, int W, bool D, vector<int> &ors, vector<int> &xors)
{
    for (int i = 0; i < H + W - 1; i++)
    {
        vector<int> cells = diagonal(H, W, i, D);
        ors.emplace_back(OR(cells));
        xors.emplace_back(XOR(cells));
    }
}

int find_pair(const vector<int> &ors, const vector<int> &xors, int maxDistance)
{
    int n = maxDistance + 1;
    vector<int> curOrs(n), curXors(n), results;
    for (int i = 0; i < (int)ors.size(); i++)
    {
        curOrs[i % n] = ors[i];
        curXors[i % n] = xors[i];
        if (i >= maxDistance)
        {
            results.emplace_back(AND_NOT(OR(curOrs), XOR(curXors)));
        }
    }
    return OR(results);
}

void construct_network(int H, int W, int K)
{
    vector<int> orsA, xorsA, orsB, xorsB;
    collect_diagonals(H, W, true, orsA, xorsA);
    collect_diagonals(H, W, false, orsB, xorsB);
    AND_NOT(AND(find_pair(orsA, xorsA, K),
                find_pair(orsB, xorsB, K)),
            AND(find_pair(orsA, xorsA, K - 1),
                find_pair(orsB, xorsB, K - 1)));
}
