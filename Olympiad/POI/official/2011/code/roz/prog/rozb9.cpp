/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie bledne                               *
 *                      sprawdza najczescie wystepujace literki          *
 *                      ze wszystkimi innymi                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>


const int MAX_L = 26;
const int INF = 1000000123;
const int LIMIT = 1;

int main() {
    srand(123);
    int n, returnAnswer = 0;
    scanf("%d", &n);
    std::vector<std::pair<int, int> > v;
    int total[MAX_L];
    bool check[MAX_L]; 
    for(int i = 0; i < MAX_L; i++) {
        check[i] = false;
        total[i] = 0;
    }

    char pop, x;
    int count = 1;
    scanf("%c%c", &pop, &pop);
    total[pop - 'a']++;
    for(int i = 1; i < n; i++) {
        scanf("%c", &x);
        total[x - 'a']++;
        if (x != pop) {
            v.push_back(std::make_pair(pop - 'a', count));
            check[pop - 'a'] = true;
            pop = x;
            count = 1;
        } else {
            count++;
        }
    }
    std::vector<std::pair<int, int> > s;
    for(int i = 0; i < MAX_L; i++) {
        s.push_back(std::make_pair(total[i], i));
    }
    std::sort(s.begin(), s.end());
    std::reverse(s.begin(), s.end());

    v.push_back(std::make_pair(pop - 'a', count));
    check[pop - 'a'] = true;
    
    for(int b_iter = 0; b_iter < LIMIT; b_iter++) {
        int bigger = s[b_iter].second;
        for(int smaller = 0; smaller < MAX_L; smaller++) {
            if (bigger != smaller && check[bigger] && check[smaller]) {
                int prevBigger = 0, current = 0;
                bool wasSmaller = false;
                for(size_t i = 0; i < v.size(); i++) {
                    if (v[i].first == bigger) {
                        prevBigger += v[i].second;

                        if (wasSmaller) {
                            current += v[i].second;
                            returnAnswer = std::max(returnAnswer, current);
                        }
                    } else if (v[i].first == smaller) {
                        if (current == 0) {
                            current--; 
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
    }
    printf("%d\n", returnAnswer);
    return 0;
}

