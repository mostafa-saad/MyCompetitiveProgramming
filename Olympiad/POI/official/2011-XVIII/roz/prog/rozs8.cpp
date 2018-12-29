/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Miroslaw Michalski                               *
 *   Zlozonosc czasowa: O(n * k * k)                                     *
 *   Opis:              Rozwiazanie powolne                              *
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
    
    for(int bigger = 0; bigger < MAX_L; bigger++) {
        for(int smaller = 0; smaller < MAX_L; smaller++) 
            if (bigger != smaller && check[bigger] && check[smaller]) {
                int prevBigger = 0, current = 0;
                bool wasSmaller = false;
                for(int i = 0; i < v_tail; i++) {
                    if (v[i].first == bigger) {
                        prevBigger += v[i].second;

                        if (wasSmaller) {
                            current += v[i].second;
                            returnAnswer = std::max(returnAnswer, current);
                        }
                    } else if (v[i].first == smaller) {
                        if (current < v[i].second) {
                            current = -1; 
                        } else {
                            current -= v[i].second;
                        }
                        wasSmaller = true;
                        if (prevBigger - v[i].second > current) {
                            current = prevBigger - v[i].second;
                        }
                        returnAnswer = std::max(returnAnswer, current);
                        prevBigger = 0;
                    }
                }
            }
    }
    printf("%d\n", returnAnswer);
    return 0;
}

