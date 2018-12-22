#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 500005;

typedef pair<int, int> pii;

struct igrac {
    int rb, k, iz;
    igrac(int _rb = 0, int _k = 0, int _iz = 0) {
        rb = _rb; k = _k; iz = _iz;
    }
    bool operator < (const igrac &a) const {
        if (k != a.k)
            return k > a.k;
        return rb < a.rb;
    }
};

int n, m;
igrac igraci[maxn];

vector<pii> zamjene[maxn];

long long z;

int brz;
vector<int> poc6;

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &igraci[i].k, &igraci[i].iz);
        igraci[i].rb = i + 1;
    }
    sort(igraci, igraci + n);
    int x = 0, y = 0;
    int prev = -1;
    for (int i = 0; i < n && x < 6; i++) {
        igrac curr = igraci[i];
        if (curr.iz == 0)
            continue;
        int tmp = min(curr.iz, m - y);
        if (y == 0)
            poc6.push_back(curr.rb);
        else 
            if (x != 5 && curr.iz == m) {
                x++;
                poc6.push_back(curr.rb);
                z += (long long)curr.k * m;
                continue;
            }
        else {
            brz++;
            zamjene[y].push_back(pii(prev, curr.rb));
        }
        y += tmp;
        z += (long long)tmp * igraci[i].k;
        igraci[i].iz -= tmp;
        prev = curr.rb;
        if (y == m) {
            x++;
            y = 0;
        }
        i--;
    } 
    printf("%lld\n", z);
    for (int i = 0; i < 6; i++)
        printf("%d ", poc6[i]);
    printf("\n%d\n", brz);
    for (int i = 1; i < m; i++) {
        reverse(zamjene[i].begin(), zamjene[i].end());
        for (int j = 0; j < zamjene[i].size(); j++)
            printf("%d %d %d\n", i, zamjene[i][j].first, zamjene[i][j].second);
    }
    return 0;
}
