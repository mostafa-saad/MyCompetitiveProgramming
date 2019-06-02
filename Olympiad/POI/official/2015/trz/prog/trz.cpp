/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Trzy wieze                                         *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
const int MAXLEN = 1000000;

char str[MAXLEN+1];

bool allDifferent(int a, int b, int c) {
    return a != b && a != c && b != c;
}

int solveAllSame(int i, int j) {
    int length = j-i+1;
    if (str[i] == str[j] && str[i] == str[i+1] && str[j-1] == str[j]) {
        int it1 = i+2, it2 = j-2;
        while (it1 < it2 && str[it1] == str[i] && str[it2] == str[i])
            it1++, it2--;
        return length-(it1-i+1);
    }
    else {
        if (!allDifferent(str[i], str[i+1], str[i+2]))
            return length-3;
        if (strncmp(str+i, str+j-2, 3) == 0) {
            int it1 = i, it2 = j;
            while (it1+2 <= j && strncmp(str+i, str+it1, 3) == 0)
                it1 += 3;
            while (it2-2 >= i && strncmp(str+i, str+it2-2, 3) == 0)
                it2 -= 3;
            if (it1 > it2)
                return 1;
            return std::max(solveAllSame(it1, j), solveAllSame(i, it2));
        }
        return length-3;
    }
}

int solve(int i, int j) {
    int length = j-i+1;
    
    int count[3] = { };
    for (int it=i; it<=j; it++)
        count[(int)str[it]-1]++;
    
    if (allDifferent(count[0], count[1], count[2]))
        return length;

    if (count[0] == count[1] && count[0] == count[2])
        return solveAllSame(i, j);
    else {
        int d = 1, t = 2;
        if (count[0] == count[2])
            d = 2, t = 3;
        else if (count[0] == count[1])
            d = 3, t = 1;

        if (str[i] == str[j] && str[i] == d) {
            int it1 = i+1, it2 = j-1;
            while (it1 < j && str[it1] == d)
                it1++;
            while (it2 > i && str[it2] == d)
                it2--;
            if (it1 > it2)
                return length;
            return std::max(solve(it1, j), solve(i, it2));
        }

        if (count[t-1] == count[d-1]+1) {
            if (str[i] == d || str[j] == d)
                return length-2;
            if (str[i] == str[i+1] || str[i] == str[j] || str[j] == str[j-1])
                return length-2;
            if (str[i + 1] == d || str[j - 1] == d) // dodatkowy przypadek, ktorego nie bylo
                return length-2;
            return std::max(solveAllSame(i+2, j), solveAllSame(i, j-2));
        }
        else
            return length-1;
    }
}

int main() {
    int n;
    assert(scanf("%d%s", &n, str) == 2);
    for (int i=0; i<n; i++)
        if (str[i] == 'B')
            str[i] = 1;
        else if (str[i] == 'C')
            str[i] = 2;
        else
            str[i] = 3;
    printf("%d\n", solve(0, n-1));
}
