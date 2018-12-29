/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Czarnoksieznicy okraglego stolu                    *
 *   Autor programu:       Bartek Kostka                                      *
 *   Zlozonosc czasowa:    O(n * n!)                                          *
 *   Opis:                 rozwiazanie wykladnicze                            *
 *                                                                            *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1000007;
const int MAXK = 1007;

bool enemy[1007][1007];

int n, k, p;

bool check(vector <int> &X)
{
    for(int i=0; i<(int)X.size(); i++)
    {
        int a = X[i],
            b = X[(i+1)%n];
        if(enemy[a][b])
            return false;
        if(abs(a-b) > p)
            return false;
    }
    for(auto ele : X)
	cerr << ele << " ";
    cerr << "\n";
    return true;
}

int main()
{
    scanf("%d%d%d", &n, &k, &p);
    while(k--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        enemy[a][b] = true;
    }
    vector <int> X;
    for(int i=1; i<=n; i++)
        X.push_back(i);
    int wyn = 0;
    do
    {
        if(check(X))
            wyn++;
    }while(next_permutation(X.begin(), X.end()-1));
    printf("%d\n", wyn);
}
