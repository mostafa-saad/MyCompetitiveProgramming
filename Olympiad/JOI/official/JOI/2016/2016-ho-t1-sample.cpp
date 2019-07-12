#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long int64;
const int64 INF = 1e18;

int64 dfs(const int pos, const int M, const int K,
    const std::vector<int>& oranges, std::vector<int64>& memo)
{
    const int N = (int)oranges.size();
    if(pos >= N)
        return 0;
    if(memo[pos] < INF)
        return memo[pos];

    int64& ans = memo[pos];
    ans = INF;
    int64 max_orange = oranges[pos];
    int64 min_orange = oranges[pos];

    for(int right = pos; right < std::min(N, pos + M); ++right) {

        const int64 o = oranges[right];
        max_orange = std::max(max_orange, o);
        min_orange = std::min(min_orange, o);

        const int64 diff = max_orange - min_orange;
        const int64 cost = K + (right - pos + 1) * diff;
        const int64 total = cost + dfs(right + 1, M, K, oranges, memo);

        ans = std::min(ans, total);
    }

    return ans;
}

int main()
{
    int N, M, K;
    std::vector<int> oranges;

    scanf("%d%d%d", &N, &M, &K);
    oranges.resize(N);
    for(auto& o : oranges) {
        int t;
        scanf("%d", &t);
        o = t;
    }

    std::vector<int64> memo;
    memo.resize(N, INF);

    int64 ans = dfs(0, M, K, oranges, memo);

    printf("%lld\n", ans);

    return 0;
}
