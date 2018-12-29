/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Lasuchy                                            *
 *   Autor programu:       Piotr Smulewicz                                    *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(1)                                               *
 *   Opis:                 rozwiazanie bledne                                 *
 *                         Kazdy wybiera tort na lewo                         *
 *****************************************************************************/

#include <vector>
#include <iostream>
int n;
int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin>>n;
    for(int i=1;i<=n;i++){
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
    return 0;
}

