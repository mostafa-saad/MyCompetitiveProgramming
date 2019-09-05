#include "vision.h"

using namespace std;

vector<int> fill(vector<int> &v)
{
    int n = v.size();
    vector<int> forward;
    for (int i = 0; i < n - 1; i++)
    {
        forward.push_back(i == 0 ? v[0] : add_or({forward[i - 1], v[i]}));
    }
    vector<int> backward;
    for (int i = 0; i < n - 1; i++)
    {
        backward.push_back(i == 0 ? v[n - 1] : add_or({backward[i - 1], v[n - 1 - i]}));
    }
    vector<int> result;
    for (int i = 0; i < n - 1; i++)
    {
        result.push_back(add_and({forward[i], backward[n - 2 - i]}));
    }
    return result;
}

vector<int> count(vector<int> &v, int begin, int end, int zero)
{
    vector<int> result;
    if (end - begin == 1)
    {
        result.push_back(v[begin]);
        return result;
    }
    int middle = (begin + end) / 2;
    vector<int> left = count(v, begin, middle, zero);
    vector<int> right = count(v, middle, end, zero);
    int carry = zero;
    int size = (left.size() > right.size() ? left.size() : right.size()) + 1;
    for (int i = 0; i < size; i++)
    {
        vector<int> cur;
        cur.push_back(carry);
        cur.push_back(i < left.size() ? left[i] : zero);
        cur.push_back(i < right.size() ? right[i] : zero);
        result.push_back(add_xor(cur));
        carry = add_or({add_and({cur[0], cur[1]}), add_and({cur[0], cur[2]}), add_and({cur[1], cur[2]})});
    }
    return result;
}

int compare(vector<int> &count, int c, int zero)
{
    vector<int> conditions;
    for (int i = 0; i < count.size(); i++)
    {
        conditions.push_back(c % 2 ? count[i] : add_not(count[i]));
        c /= 2;
    }
    return c > 0 ? zero : add_and(conditions);
}

void construct_network(int H, int W, int K)
{
    vector<int> rows;
    for (int y = 0; y < H; y++)
    {
        vector<int> row;
        for (int x = 0; x < W; x++)
        {
            row.push_back(y * W + x);
        }
        rows.push_back(add_or(row));
    }

    vector<int> cols;
    for (int x = 0; x < W; x++)
    {
        vector<int> col;
        for (int y = 0; y < H; y++)
        {
            col.push_back(y * W + x);
        }
        cols.push_back(add_or(col));
    }

    vector<int> rowsFilled = fill(rows);
    vector<int> colsFilled = fill(cols);
    vector<int> filled;
    for (int i = 0; i < H + W - 2; i++)
    {
        filled.push_back(i < H - 1 ? rowsFilled[i] : colsFilled[i - (H - 1)]);
    }
    int zero = add_xor({0, 0});
    vector<int> cnt = count(filled, 0, filled.size(), zero);
    compare(cnt, K, zero);
}