/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Przekladanka                                     *
 *   Autor:             Jacek Migdal                                     *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define MAXN 2000
int answer[MAXN * MAXN];
int answerN;
int data[MAXN];
int dataN;
int begin;

void addAnswer(int num)
{
    if (answerN > 0 && answer[answerN - 1] * num > 0) {
        answer[answerN - 1] += num;
    } else {
        answer[answerN++] = num;
    }
}

void operationPlus() {
    begin--;
    if (begin < 0)
        begin += dataN;
    addAnswer(1);
}

void operationPlus2() {
    begin++;
    if (begin >= dataN)
        begin -= dataN;
    addAnswer(dataN - 1);
}

void operationMinus() {
    int next[2] = {(begin + 1) % dataN, (begin + 2) % dataN};
    int tmp = data[begin];
    data[begin] = data[next[1]];
    data[next[1]] = data[next[0]];
    data[next[0]] = tmp;
    addAnswer(-1);
}

int main()
{
    int i, j, n;
    scanf("%d", &n);
    dataN = n;
    for (i = 0 ; i < n ; ++i) {
        scanf("%d", &data[i]);
    }

    if (n <= 2) {
        if (n == 1 || 1 ==data[0]) {
            printf("0\n");
        } else {
            printf("1\n1a\n");
        }
        return 0;
    }

    for (j = 2 ; j <= (n - 2) ; ++j) {
        while (data[begin] != j) {
            operationPlus();
        }

        while (data[(begin - 1 + dataN) % dataN] != j - 1) {
            operationPlus();
            if (data[(begin - 1 + dataN) % dataN] != j - 1) {
                operationPlus();
                operationMinus();
            } else {
                operationMinus();
                operationMinus();
            }
        }
    }

    while (data[begin] != 1) {
        operationPlus();
    }

    if (data[(begin - 1 + dataN) % dataN] != n) {
        if (n % 2 == 1) {
            printf("NIE DA SIE\n");
            return 0;
        } else {
            operationPlus();

            while (data[(begin + 1) % dataN] != n) {
                operationMinus();
                operationMinus();
                operationPlus2();
                operationPlus2();
            }
            for (i = 0 ; i < n - 2 ; ++i) {
                operationPlus();
            }
        }
    }

    int nonZeroAns = 0;
    for(i = 0; i < answerN; ++i) {
        if (answer[i] % n != 0) nonZeroAns++;
    }
    printf("%d\n",nonZeroAns);
    
    for (i = 0 ; i < answerN ; ++i) {
        if (answer[i] % n != 0) {
            int x = answer[i] % n;
            if (x > 0) printf("%da ", x); else printf("%db ",x * (-1));
        }
    }
    printf("\n");

    return 0;
}
