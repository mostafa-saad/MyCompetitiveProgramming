/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Przekladanka                                     *
 *   Autor:             Jacek Migdal                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                                                                       *
 *************************************************************************/

#include <list>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> answer;
list<int> data;

void addAnswer(int num)
{
    if (!answer.empty() && answer.back() * num > 0) {
        answer.back() += num;
    } else {
        answer.push_back(num);
    }
}

void operationPlus() {
    data.push_front(data.back());
    data.pop_back();
    addAnswer(1);
}

void operationMinus() {
    int a = *(++(++data.begin()));
    data.remove(a);
    data.push_front(a);
    addAnswer(-1);
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0 ; i< n ; ++i) {
        int a;
        scanf("%d", &a);
        data.push_back(a);
    }

    if (n <= 2) {
        if (n == 1 || 1 == *data.begin()) {
            printf("0\n");
        } else {
            printf("1\n1a\n");
        }
        return 0;
    }

    for (int j = 2 ; j <= (n - 2) ; ++j) {
        while (data.front() != j) {
            operationPlus();
        }

        while (data.back() != j - 1) {
            operationPlus();
            if (data.back() != j - 1) {
                operationPlus();
                operationMinus();
            } else {
                operationMinus();
                operationMinus();
            }
        }
    }

    while (data.front() != 1) {
        operationPlus();
    }

    if (data.back() != n) {
        printf("NIE DA SIE\n");
        return 0;
    }

    int nonZeroAns = 0;
    for(unsigned int i = 0; i < answer.size(); ++i) {
        if (answer[i] % n != 0) nonZeroAns++;
    }
    printf("%d\n",nonZeroAns);
    
    for (unsigned int i = 0 ; i < answer.size() ; ++i) {
        if (answer[i] % n != 0) {
            int x = answer[i] % n;
            if (x > 0) {
                printf("%da ",x);
            } else {
                printf("%db ",x * (-1));
            }
        }
    }
    printf("\n");

    return 0;
}
