/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie bledne                               *
 *                      wybiera sobie pare z prawdopodobienstwem 0.5     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <vector>

const int MAX_L = 26;
const int INF = 1000000123;

int main() {
    srand(123);
    int n, returnAnswer = 0;
    scanf("%d", &n);
    std::vector<std::pair<int, int> > v;
    bool check[MAX_L]; for(int i = 0; i < MAX_L; i++) check[i] = false;

    char pop, x;
    int count = 1;
    scanf("%c%c", &pop, &pop);

    for(int i = 1; i < n; i++) {
        scanf("%c", &x);
        if (x != pop) {
            v.push_back(std::make_pair(pop - 'a', count));
            check[pop - 'a'] = true;
            pop = x;
            count = 1;
        } else {
            count++;
        }
    }
    v.push_back(std::make_pair(pop - 'a', count));
    check[pop - 'a'] = true;
    
    for(int bigger = 0; bigger < MAX_L; bigger++) if (rand()%2) {
        for(int smaller = 0; smaller < MAX_L; smaller++) 
            if (bigger != smaller && check[bigger] && check[smaller] && rand()%2) {
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
    printf("%d\n", returnAnswer);
    return 0;
}

