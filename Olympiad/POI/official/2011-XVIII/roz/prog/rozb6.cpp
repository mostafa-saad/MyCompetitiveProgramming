/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie bledne                               *
 *                      nie sprawdza wszystkich literek                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>

const int MAX_L = 26;
const int MAX_N = 1000023;
const int INF = 1000000123;

int main() {
    int n, returnAnswer = 0, v_tail = 0;
    scanf("%d", &n);
    std::pair<int, int> v[MAX_N];
    bool check[MAX_L]; for(int i = 0; i < MAX_L; i++) check[i] = false;

    char pop, x;
    int count = 1;
    scanf("%c%c", &pop, &pop);

    for(int i = 1; i < n; i++) {
        scanf("%c", &x);
        if (x != pop) {
            v[v_tail++] = std::make_pair(pop - 'a', count);
            check[pop - 'a'] = true;
            pop = x;
            count = 1;
        } else {
            count++;
        }
    }
    v[v_tail++] = std::make_pair(pop - 'a', count);
    check[pop - 'a'] = true;

    int prevBigger[MAX_L], current[MAX_L];
    bool wasSmaller[MAX_L];

    for(int bigger = 0; bigger < MAX_L/2; bigger++) { //MiMi:: tutaj jest blad 
        if (check[bigger]) {
            for(int i=0; i<MAX_L; i++) {
                prevBigger[i] = 0;
                current[i] = 0;
                wasSmaller[i] = false;
            }
            for(int i = 0; i < v_tail; i++) {
                if (v[i].first == bigger) {
                    for(int smaller = 0; smaller < MAX_L; smaller++)
                        if (check[smaller] && smaller != bigger) {
                            prevBigger[smaller] += v[i].second;

                            if (wasSmaller[smaller]) {
                                current[smaller] += v[i].second;
                                returnAnswer = std::max(returnAnswer, current[smaller]);
                            }
                        }
                } else {
                    if (current[v[i].first] == 0) {
                        current[v[i].first]--; 
                    } else {
                        current[v[i].first] -= v[i].second;
                    }
                    wasSmaller[v[i].first] = true;
                    if (prevBigger[v[i].first] - v[i].second > current[v[i].first]) {
                        current[v[i].first] = prevBigger[v[i].first] - v[i].second;
                    }
                    returnAnswer = std::max(returnAnswer, current[v[i].first]);
                    prevBigger[v[i].first] = 0;
                }
            }
        }
    }
    printf("%d\n", returnAnswer);
    return 0;
}

