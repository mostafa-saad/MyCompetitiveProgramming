/*
    Task: Hacker
    Slow solution 1
    Author: Krzysztof Kiljan
    Complexity: O(n^2)

    For every start position i, calculates the maximum protection operator can
    get and subtracts it from sum of all values. The result is max over all of these values
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
VI v;

int n, m, k, operCompNum, sumAll;

void readInput()
{
    sumAll = 0;
    scanf("%d", &n);

    operCompNum = n / 2;

    REP(i, n)
    {
        scanf("%d", &k);
        v.PB(k);
        sumAll += k;
    }
}

//makes   v -> vv, for easier further implementation

void duplicateV()
{
    REP(i, n)
    v.push_back(v[i]);
}


// First calculates sum of values of computers in range <start, start + operCompNum)
// than moves the range by one until end would reach position of start cyclically
int calcOperProtection(int start)
{
    int sum = 0;
    int ans = 0;
    int end = start + operCompNum;
    int curStart = start;

    for (int i = curStart; i < end; i++)
        sum += v[i];

    ans = max(ans, sum);

    while (end < start + n - 1)
    {
        sum -= v[curStart];
        curStart++;
        sum += v[end];
        end++;
        ans = max(ans, sum);
    }

    return ans;
}

// Calculates the value hacker will get assuming he will start at computer number nr
// Numbers in <0, n)

int tryStart(int nr)
{
    int res = calcOperProtection(1 + nr);
    return sumAll - res;
}

int solve()
{
    int ans = 0;

    REP(i, n)
    ans = max(ans, tryStart(i));

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
