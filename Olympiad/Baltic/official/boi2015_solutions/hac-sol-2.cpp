/*
    Task: Hacker
    Model Solution 2
    Author: Krzysztof Kiljan
    Complexity: O(n log n)
    Uses segment tree to calculate maximum
 */

#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>

using namespace std;

#define REP(I,N) for(int I=0;I<(N);I++)
#define PB push_back
#define MP make_pair
#define ST first
#define ND second


typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long ll;

const int MAXN = 500013;
const int INF = 1000000001;
VI v;

int n, m, k, operCompNum, myCompNum, sumAll;

// sums[i] = v[i] + ... v[i +myCompNum -1]
VI sums;

//MinTree borrowed from "Algorytmika praktyczna", auth: P. Stanczyk

struct MinTree
{
    int* el, s;
    MinTree(int size)
    {
        el = new int[2 * (s = 1 << size)];
        REP(x, 2 * s) el[x] = INF;
    }

    ~MinTree()
    {
        delete[] el;
    }

    void Set(int p, int v)
    {
        for (p += s, el[p] = v, p >>= 1; p > 0; p >>= 1)
            el[p] = min(el[p << 1], el[(p << 1) + 1]);
    }

    int Find(int p, int k)
    {
        int m = INF;
        p += s;
        k += s;

        while (p < k)
        {
            if ((p & 1) == 1) m = min(m, el[p++]);

            if ((k & 1) == 0) m = min(m, el[k--]);

            p >>= 1;
            k >>= 1;
        }

        if (p == k) m = min(m, el[p]);

        return m;
    }
};

MinTree tree(20);

void readInput()
{
    sumAll = 0;
    scanf("%d", &n);

    operCompNum = n / 2;
    myCompNum = n - operCompNum;

    REP(i, n)
    {
        scanf("%d", &k);
        v.PB(k);
        sumAll += k;
    }
}

//makes   v -> vvv, for easier further implementation

void duplicateV()
{
    REP(j, 2)
    REP(i, n)
    v.push_back(v[i]);
}


// Precomputes sum of values of computers in range <start, start + myCompNum)
// for all starts possible
void precompSums()
{
    int sum = 0;
    int curStart = 0;
    int end = curStart + myCompNum;

    for (int i = curStart; i < end; i++)
        sum += v[i];

    sums.PB(sum);

    while (curStart < 2 * n)
    {
        sum -= v[curStart];
        curStart++;
        sum += v[end];
        end++;
        sums.PB(sum);
    }

    REP(i, (int) sums.size())
    {
        tree.Set(i, sums[i]);
    }
}



int calcMaxAns(int start)
{
    return tree.Find(start + n - myCompNum + 1, start + n);
}


int solve()
{
    precompSums();
    int ans = 0;

    REP(i, n)
    {
        ans = max(ans, calcMaxAns(i));
    }

    return ans;
}

int main()
{
    readInput();
    duplicateV();
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}
