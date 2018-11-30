/*
    Task: Hacker
    Slow solution 2
    Author: Krzysztof Kiljan
    Complexity: O(n^3)

    Brutal simulation, for every start S we brutally calculate what would be the result
    if second player started in any of the remaining points. For every point, we also brutally
    calculate the sum of the points in it.
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


//Calculates the sum from computers protectected by operator if started at "start" position
int calcOperProtection(int start)
{
    int sum = 0;

    for (int i = start; i < start + operCompNum; i++)
        sum += v[i];

    return sum;
}

// Calculates the value hacker will get assuming he will start at computer number nr
// Numbers in <0, n)

int tryStart(int nr)
{
    int res = 0;

    for (int i = 1; i <= n - operCompNum; i++)
        res = max(res, calcOperProtection(i + nr));

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
