/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Rozwazamy tylko konce salatki bedace          *
 *                         dlugimi ciagami samych liter p                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int N = 1000 * 1000, T = 10 * 1000;
int n, res;
pair<int, int> p1, p2;
char fruit[N];
int first_smaller[2][N + 1];

pair<int, int> wyjmij(set<pair<int, int> > &len) {
    pair<int, int> res = make_pair(len.begin()->second,
                                   -len.begin()->first + len.begin()->second - 1);
    len.erase(len.begin());
    return res;
}


void calc_nxt() {
    int last[N + 2], sums[N + 1], mins;

    sums[0] = 0;
    mins = 0;
    for(int i = 1; i <= n; i++) {
        sums[i] = sums[i - 1] + (fruit[i - 1] == 'p' ? 1 : -1);
        mins = min(mins, sums[i]);
    }
    mins--;
    for(int i = 0; i <= n; i++) last[i] = n + 1;
    for(int i = n; i >= 0; i--) {
        first_smaller[0][i] = last[sums[i] - 1 - mins];
        last[sums[i] - mins] = i;
    }

    sums[n] = 0;
    mins = 0;
    for(int i = n - 1; i >= 0; i--) {
        sums[i] = sums[i + 1] + (fruit[i] == 'p' ? 1 : -1);
        mins = min(mins, sums[i]);
    }
    mins--;
    for(int i = 0; i <= n; i++) last[i] = -1;
    for(int i = 0; i <= n; i++) {
        first_smaller[1][i] = last[sums[i] - 1 - mins];
        last[sums[i] - mins] = i;
    }
}

void sprawdz(int l, int r) {
//	printf("sprawdz (%d, %d)\n", l, r);
    if(first_smaller[0][l] > r + 1 && first_smaller[1][r + 1] < l)
        res = max(res, r - l + 1);
}

void calc_res() {
    int clen = 0;
    set<pair<int, int> > len;
    for(int i = 0; i < n; i++) {
        if(fruit[i] == 'j') {
            clen = 0;
        } else {
            clen++;
            if(i + 1 == n || fruit[i + 1] == 'j') {
                pair<int, int> np = make_pair(-clen, i + 1 - clen);
                len.insert(np);
            }

        }
    }
    if(len.size() == 0) {
        res = 0;
    } else {
        res = -len.begin()->first;
        vector<pair<int, int> > cand;
        for(int i = 0; i < T; i++) {
            if(len.empty()) break;
            cand.push_back(wyjmij(len));
//			printf("(%d, %d)\n", cand.back().first, cand.back().second);
        }
        for(int i = 0; i < (int)cand.size(); i++) {
            for(int j = i + 1; j < (int)cand.size(); j++) {
                pair<int, int> c1 = cand[i], c2 = cand[j];
                int l = min(c1.first, c2.first),
                    r = max(c1.second, c2.second);
                sprawdz(l, r);
            }
        }
    }
}

int main() {
    scanf("%d %s", &n, fruit);
    calc_nxt();
    calc_res();
    printf("%d\n", res);
    return 0;
}
