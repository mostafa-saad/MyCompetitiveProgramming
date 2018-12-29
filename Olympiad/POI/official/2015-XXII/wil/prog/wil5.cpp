/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wilcze doly                                        *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 Rozwiazanie alternatywne                           *
 *                                                                            *
 *****************************************************************************/


#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;

typedef long long int LL;

const int MAXN = 2000005;

int T[MAXN];
LL sd[MAXN];
deque<pair<LL,int> > Q;

int main() {
    int n, d;
    LL p;

    scanf("%d%Ld%d", &n, &p, &d);
    for (int i = 0; i < n; i++)
        scanf("%d", &T[i]);

    LL curSum = 0LL;
    for (int i = 0; i < n; i++) {
        if (i >= d) curSum -= T[i-d];
        curSum += T[i];
        sd[i] = curSum;
    }

    int right = -1, result = 0;
    LL maxSum = 0LL;
    curSum = 0LL;
    for (int left = 0; left < n; left++) {
        if ((!Q.empty()) && (Q[0].second < left))
            Q.pop_front();

        while (true) {
            if (right == n-1)
                break;
            if ((curSum + T[right+1] - maxSum > p) && (curSum + T[right+1] - sd[right+1] > p))
                break;

            right++;
            curSum += T[right];
            while ((!Q.empty()) && (Q.back().first < sd[right]))
                Q.pop_back();
            Q.push_back(make_pair(sd[right], right-d));
            maxSum = Q[0].first;
        }

        result = max(result, right-left+1);
        curSum -= T[left];
    }

    printf("%d\n", result);

    return 0;
}
