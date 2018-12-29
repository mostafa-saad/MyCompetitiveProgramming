/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Czarnoksieznicy okraglego stolu                    *
 *   Autor programu:       Bartek Kostka                                      *
 *   Zlozonosc czasowa:    O((n + k) log k)                                   *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie niepoprawne (overflow)                 *
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

int go3p()
{
    for(int i=2; i<=8; i++)
    {
        vector <int> X;
        X.push_back(i);
        for(int k=1; k<i-1; k++)
            X.push_back(k);
        X.push_back(i-1);
        do
        {
            if(smallercheck(X))
                x[i]++;
            reverse(X.begin(), X.end());
            if(smallercheck(X))
                y[i]++;
            reverse(X.begin(), X.end());
        }
        while(next_permutation(X.begin()+1, X.end()-1)); 
    }
    for(int i=9; i<=n; i++)
    {
        vector <int> X, Y;
        X = {i,i-2};
        if(smallercheck(X))
            x[i] += y[i-1];
        reverse(X.begin(), X.end());
        if(smallercheck(X))
            y[i] += x[i-1];
        X = {i,i-3};
        Y = {i-2,i-1};
        if(smallercheck(X) && smallercheck(Y))
            x[i] += y[i-2];
        reverse(X.begin(), X.end());
        reverse(Y.begin(), Y.end());
        if(smallercheck(X) && smallercheck(Y))
            y[i] += x[i-2];
        X = {i,i-3,i-2,i-5};
        Y = {i-4,i-1};
        if(smallercheck(X) && smallercheck(Y))
            x[i] += y[i-4];
        reverse(X.begin(), X.end());
        reverse(Y.begin(), Y.end());
        if(smallercheck(X) && smallercheck(Y))
            y[i] += x[i-4];
        X = {i,i-3,i-6};
        Y = {i-5,i-2,i-4,i-1};
        if(smallercheck(X) && smallercheck(Y))
            x[i] += y[i-5];
        reverse(X.begin(), X.end());
        reverse(Y.begin(), Y.end());
        if(smallercheck(X) && smallercheck(Y))
            y[i] += x[i-5];
        x[i] %= MOD;
        y[i] %= MOD;
    }
    int wyn = 0;
    vector <int> X, Y;
    X = {n-1,n};
    if(smallercheck(X))
        wyn += x[n];
    X = {n,n-1};
    Y = {n-2,n};
    if(smallercheck(X) && smallercheck(Y))
        wyn += x[n-1];
    X = {n,n-3};
    Y = {n-4,n-1,n-2,n};
    if(smallercheck(X) && smallercheck(Y))
        wyn += x[n-3];
    X = {n,n-3,n-1,n-4};
    Y = {n-5,n-2,n};
    if(smallercheck(X) && smallercheck(Y))
        wyn += x[n-4];
    X = {n,n-1,n-2};
    Y = {n-3,n};
    if(smallercheck(X) && smallercheck(Y))
        wyn += x[n-2];
    X = {n,n-1,n-4};
    Y = {n-5,n-2,n-3,n};
    if(smallercheck(X) && smallercheck(Y))
        wyn += x[n-4];
    X = {n,n-2,n-5};
    Y = {n-4,n-1,n-3,n};
    if(smallercheck(X) && smallercheck(Y))
        wyn += y[n-4];
    X = {n,n-2,n-1,n-4};
    Y = {n-3,n};
    if(smallercheck(X) && smallercheck(Y))
        wyn += y[n-3];
    X = {n,n-1,n-4,n-2,n-5};
    Y = {n-6,n-3,n};
    if(smallercheck(X) && smallercheck(Y))
        wyn += x[n-5];
    //for(int i=1; i<=n; i++)
    //    cerr << x[i] << " " << y[i] << "\n";
    return wyn%MOD;
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
    if(p==3)
    {
        if(n<=8)
            printf("%d\n", go3e());
        else
            printf("%d\n", go3p());
    }
    return 0;
}
