/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Myjnie                                             *
 *   Zlozonosc czasowa:    O(n^3 * m)                                         *
 *   Zlozonosc pamieciowa: O(n^2 * m)                                         *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 55;
const int MAXM = 4005;

struct Person {
    int from, to, budget;
    Person() {}
    Person(int from, int to, int budget):
        from(from), to(to), budget(budget)
        {}
    bool operator<(const Person& otherPerson) const { return budget < otherPerson.budget; }
};

int nPoints, nPeople;
int peopleRange[MAXN][MAXN][MAXM];
int dp[MAXN][MAXN][MAXM];
int opt[MAXN][MAXN][MAXM];
int result[MAXN];
Person people[MAXM];

void PrecomputePeopleRanges() {
    for (int i = nPeople-1; i >= 0; i--) {
        for (int from = 0; from < nPoints; from++)
            for (int to = 0; to < nPoints; to++)
                peopleRange[from][to][i] = peopleRange[from][to][i+1];

        for (int from = 0; from <= people[i].from; from++)
            for (int to = people[i].to; to < nPoints; to++)
                peopleRange[from][to][i]++;
    }
}

int Compute() {
    for (int dist = 0; dist < nPoints; dist++)
    for (int from = 0; from+dist < nPoints; from++) {
    int to = from+dist;
    for (int priceIdx = nPeople-1; priceIdx >= 0; priceIdx--) {

    if (from > to) { dp[from][to][priceIdx] = 0; continue; }
    int resultValue = 0, optimalMin = from;
    for (int pos = from; pos <= to; pos++) {
        int leftResult = 0, rightResult = 0;
        if (from <= pos-1) leftResult = dp[from][pos-1][priceIdx];
        if (pos+1 <= to) rightResult = dp[pos+1][to][priceIdx];
        int peopleCount = peopleRange[from][to][priceIdx];
        if (pos-1 >= from) peopleCount -= peopleRange[from][pos-1][priceIdx];
        if (pos+1 <= to) peopleCount -= peopleRange[pos+1][to][priceIdx];
        int possibleResult = leftResult + rightResult + peopleCount * people[priceIdx].budget;
        if (possibleResult > resultValue) {
            resultValue = possibleResult;
            optimalMin = pos;
        }
    }
    if (priceIdx+1 < nPeople) {
        int possibleResult = dp[from][to][priceIdx+1];
        if (possibleResult > resultValue) {
            resultValue = possibleResult;
            optimalMin = -1;
        }
    }
    dp[from][to][priceIdx] = resultValue;
    opt[from][to][priceIdx] = optimalMin;
    }
    }

    return dp[0][nPoints-1][0];
}

void ClaimResult(int from, int to, int priceIdx) {
    if (from > to) return;
    if (priceIdx >= nPeople) return;
    if ((from == to) && (opt[from][to][priceIdx] == from)) {
        result[from] = priceIdx;
        return;
    }
    int optimalMin = opt[from][to][priceIdx];
    if (optimalMin == -1)
        ClaimResult(from, to, priceIdx+1);
    else {
        result[optimalMin] = priceIdx;
        ClaimResult(from, optimalMin-1, priceIdx);
        ClaimResult(optimalMin+1, to, priceIdx);
    }
}

int main() {
    scanf("%d%d", &nPoints, &nPeople);

    for (int i = 0; i < nPeople; i++) {
        int from, to, budg;
        scanf("%d%d%d", &from, &to, &budg);
        from--; to--;
        people[i] = Person(from, to, budg);
    }
    sort(people, people+nPeople);

    PrecomputePeopleRanges();

    for (int i = 0; i < nPoints; i++)
        for (int j = 0; j < nPoints; j++)
            for (int k = 0; k < nPeople; k++)
                dp[i][j][k] = -1;

    printf("%d\n", Compute());

    ClaimResult(0, nPoints-1, 0);

    for (int i = 0; i < nPoints; i++) {
        if (i > 0) printf(" ");
        printf("%d", people[result[i]].budget);
    }
    printf("\n");

    return 0;
}
