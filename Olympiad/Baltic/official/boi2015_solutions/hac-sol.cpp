/*
    Task: Hacker
    Model Solution 1
    Author: Krzysztof Kiljan
    Complexity: O(n log n)
    Uses set to calculate maximum on all ranges
 */

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

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
VI v;

int n, m, k, operCompNum, myCompNum;

// sums[i] = v[i] + ... v[i +myCompNum -1]
VI sums;

//Holds pairs <value, index in sums array>
set <PII> curSums;

void readInput()
{
    scanf("%d", &n);

    operCompNum = n / 2;
    myCompNum = n - operCompNum;

    REP(i, n)
    {
        scanf("%d", &k);
        v.PB(k);
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
}

PII calcMaxAns()
{
    int curStart = n - myCompNum + 1;
    int end = curStart + myCompNum;
    PII ans = MP(-1, -1);

    for (int i = curStart; i < end; i++)
        curSums.insert(MP(sums[i], i));

    ans = *(curSums.begin());

    while (end < 2 * n)
    {
        curSums.erase(MP(sums[curStart], curStart));
        curStart++;
        curSums.insert(MP(sums[end], end));
        end++;

        if (ans.ST < (*(curSums.begin())).ST)
        {
            ans = *(curSums.begin());
        }
    }

    return ans;
}

int solve()
{
    precompSums();
    PII ans = calcMaxAns();

    return ans.ST;
}

int main()
{
    readInput();
    duplicateV();
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}
