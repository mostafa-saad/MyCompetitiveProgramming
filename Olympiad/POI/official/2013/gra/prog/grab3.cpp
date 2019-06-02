/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gra Tower Defense                             *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(n+m)                                        *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Stawia wieze w kazdym miescie                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)

int n, m, k;

int main() {
    std::ios_base::sync_with_stdio(0);
    //wczytanie wejscia
    cin >> n;
    cout << n << endl;
    for(int i=1; i<=n; i++) cout << i << " ";
    return 0;
}
