/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Czarnoksieznicy okraglego stolu                    *
 *   Autor programu:       Bartek Kostka                                      *
 *   Zlozonosc czasowa:    O((n + k) log k)                                   *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie czesciowe dla p <= 2                   *
 *                                                                            *
 *****************************************************************************/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1000*1000+7;
const int MAXK = 1007;
const int MOD = 1000*1000*1000+7;

int n, k, p;
vector <int> E[MAXN];
int x[MAXN], y[MAXN];

bool isenemy(int a, int b)
{
    auto it = lower_bound(E[a].begin(), E[a].end(), b);
    if(it == E[a].end())
        return false;
    return (*it)==b;
}

bool check(vector <int> &X)
{
    for(int i=0; i<(int)X.size(); i++)
    {
        int a = X[i],
            b = X[(i+1)%n];
        if(isenemy(a,b))
            return false;
        if(abs(a-b) > p)
            return false;
    }
    return true;
}

bool smallercheck(vector <int> &X)
{
    for(int i=0; i<(int)X.size()-1; i++)
    {
        int a = X[i],
            b = X[(i+1)%n];
        if(isenemy(a,b))
            return false;
        if(abs(a-b) > p)
            return false;
    }
    return true;
}

int go0()
{
    if(n==1)
        return 1;
    else
        return 0;
}

int go1()
{
    if(n==1)
        return 1;
    if(n==2)
    {
        if(isenemy(1,2) || isenemy(2,1))
            return 0;
        else
            return 1;
    }
    return 0;
}

int go2()
{
    if(n==1)
        return 1;
    long long wyn = 0;
    vector <int> X = {n};
    int an = n-1;
    while(an > 0)
    {
        X.push_back(an);
        an -= 2;
    }
    int bn = 2-n%2;
    while(bn < n)
    {
        X.push_back(bn);
        bn += 2;
    }
    if(check(X))
        wyn++;
    reverse(X.begin()+1, X.end());
    if(check(X))
        wyn++;
    return wyn;
}

int go3e()
{
    vector <int> X;
    for(int i=1; i<=n; i++)
        X.push_back(i);
    long long wyn = 0;
    do
    {
        if(check(X))
            wyn++;
    }while(next_permutation(X.begin(), X.end()-1));
    return wyn;
}

int main()
{
    scanf("%d%d%d", &n, &k, &p);
    while(k--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        E[a].push_back(b);
    }
    for(int i=1; i<=n; i++)
        sort(E[i].begin(), E[i].end());
    if(p==0)
        printf("%d\n", go0());
    if(p==1)
        printf("%d\n", go1());
    if(p==2)
        printf("%d\n", go2());
    return 0;
}
