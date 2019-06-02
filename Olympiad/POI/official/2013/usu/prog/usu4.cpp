/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Usuwanka                                      *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n log k)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie weryfikujace                      *
 *                         Buduje kolejne ruchy w zachlanny sposob       *
 *                                                                       *
 *************************************************************************/

#include <cassert>
#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;


typedef vector<int> Wybor;

stack< int > stosB;         // stos nieuzytych liter b
stack< Wybor > stosWyborow; // stos tworzonych wyborow
int n, k;
char lit;

vector< Wybor > wyjscie;

/*
 * Funkcja sprawdza, czy ostatni wybor jest pelny
 * i jesli tak, to go zapisuje i usuwa ze stosu
 */
bool checkPopSave() {

    if ( (int) stosWyborow.top().size() != k+1 )
        return false;

    wyjscie.push_back(stosWyborow.top());
    stosWyborow.pop();
    return true;
}


int main() {
    cin >> n >> k;

    for(int i=1; i<=n; ++i) {
        cin >> lit;

        if (lit == 'c' ) {
            stosWyborow.push(Wybor());

            // dokladamy do wyboru wolne litery 'b' z lewej
            while((int) stosWyborow.top().size() < k && !stosB.empty()) {
                stosWyborow.top().push_back( stosB.top() );
                stosB.pop();
            }
            stosWyborow.top().push_back(i);
            checkPopSave();

        } else {
            if ( stosWyborow.empty() ) {
                stosB.push(i);
            } else {
                stosWyborow.top().push_back(i);
                checkPopSave();
            }
        }
    }


    for(int r=n/(k+1)-1; r>=0; --r) {
        sort(wyjscie[r].begin(), wyjscie[r].end());

        for(int i=0; i<k+1; ++i)
            cout << wyjscie[r][i]  << " ";

        cout << "\n";
    }

    return 0;
}


