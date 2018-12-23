#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

const int maxN = 1e4 + 10;
const int maxQ = 100;

int t[maxN];
int n, l, q;

struct Quest {
    int k, i;
    Quest(int k, int i)
    : k(k), i(i) {}
    
    bool operator<(Quest const& o) const {
        return k < o.k;
    }
};

vector<Quest> quests;
int cnt[maxN];
int ans[maxQ][maxN];
int dp[maxN];

int count_diff(int x, int y) {
    int diff = 0;
    if(x > 0 && y > 0 && t[x - 1] != t[y - 1])
        diff--;
    if(t[x + l - 1] != t[y + l - 1])
        diff++;
    if(x == 0 || y == 0) {
        for(int i = 1; i < l; ++i)
            diff += t[x + i - 1] != t[y + i - 1];
    }
    return diff;
}

void ans_quests(int x) {
    for(int i = 0; i <= l; ++i)
        cnt[i] = 0;
    for(int i = n - l; i > 0; --i)
        dp[i] = dp[i - 1] + count_diff(x, i);
    dp[0] = count_diff(x, 0);

    for(int i = 0; i < n - l + 1; ++i)
        cnt[dp[i]]++;

    int k = 0, sum = 0;
    for(Quest const& q: quests) {
        while(k <= q.k) {
            sum += cnt[k];
            k++;
        }
        ans[q.i][x] = sum - 1;
    }
}

int main() {
    assert(scanf("%d%d", &n, &l) == 2);
    for(int i = 0; i < n; ++i)
        assert(scanf("%d", t + i) == 1);

    assert(scanf("%d", &q) == 1);
    for(int k, i = 0; i < q; ++i) {
        assert(scanf("%d", &k) == 1);
        quests.emplace_back(k, i);
    }
    sort(quests.begin(), quests.end());

    for(int i = 0; i < n - l + 1; ++i)
        ans_quests(i);

    for(int i = 0; i < q; ++i) {
        for(int j = 0; j < n - l + 1; ++j)
            printf("%d ", ans[i][j]);
        puts("");
    }
}
