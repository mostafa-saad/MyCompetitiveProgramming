/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     sloa.cpp                                                  *
 *   Autor:    Bartosz Walczak                                           *
 *   Opis:     Rozwiazanie alternatywne                                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <stack>
using namespace std;

bool test_case() {
    int n, k;
    scanf("%d", &n);
    stack<int> S;  // stos z ciagiem wejsciowym
    for (int i=0; i<n; ++i) { scanf("%d", &k); S.push(k); }
    stack<int> T;  // stos z fragmentem reprezentacji, ktory jeszcze nie zostal
                   // odciety z ciagu wyjsciowego
    int first = 0;  // indeks poczatkowego (najwiekszego) czlonu reprezentacji
    while (!S.empty()) {
        if (T.empty()) {
            // generowanie kolejnego czlonu reprezentacji:
            T.push(first+2 - (S.top()-first & 1));
            first = T.top();
        }
        int Stop = S.top(), Ttop = T.top();
        if ((Stop & 1) != (Ttop & 1)) return false;  // niezgodnosc
        // obciecie ciagu lub reprezentacji o zgodny fragment:
        S.pop(); T.pop();
        for (int j=Stop-1; j>Ttop; j-=2) S.push(j);
        for (int j=Ttop-1; j>Stop; j-=2) T.push(j);
    }
    return true;
}

int main() {
    int test_cases;
    scanf("%d", &test_cases);
    while (test_cases--) printf(test_case() ? "TAK\n" : "NIE\n");
    return 0;
}
