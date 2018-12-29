/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zajakniecia                                        *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie zakladajace, ze kazda liczba wystepuje *
 *                         w kazdym z ciagow co najwyzej dwa razy             *
 *****************************************************************************/

#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

const int MAXN = 15000;

int n1, n2, n;
pair<int,int> readA[MAXN + 3], readB[MAXN + 3];
pair<int,int> A[MAXN + 3], B[MAXN + 3];
pair< pair<int,int>, pair<int,int> > intervals[MAXN + 3];
map<int,int> freqA, freqB;
int dp[MAXN + 3];

void Read(){
    cin>>n1>>n2;
    for(int i=1; i<=n1; i++)
        cin>>readA[i].first, readA[i].second = i;
    for(int i=1; i<=n2; i++)
        cin>>readB[i].first, readB[i].second = i;
}

//Usuwamy wyrazy, ktore wystepuja mniej niz 2 razy w jednym z ciagow.
void Optimization(){
    for(int i=1; i<=n1; i++)
        if(freqA.find(readA[i].first) != freqA.end())
            freqA[ readA[i].first ]++;
        else
            freqA[ readA[i].first ] = 1;
    for(int i=1; i<=n2; i++)
        if(freqB.find(readB[i].first) != freqB.end())
            freqB[ readB[i].first ]++;
        else
            freqB[ readB[i].first ] = 1;

    for(int i=1; i<=n1; i++)
        if(freqA[ readA[i].first ] == 1 || freqB.find(readA[i].first) == freqB.end() || freqB[ readA[i].first ] <= 1)
            freqA[ readA[i].first ] = 0, freqB[ readA[i].first ] = 0;
    for(int i=1; i<=n2; i++)
        if(freqB[ readB[i].first ] == 1 || freqA.find(readB[i].first) == freqA.end() || freqA[ readB[i].first ] <= 1)
            freqB[ readB[i].first ] = 0, freqA[ readB[i].first ] = 0;

    int curr = 0;
    for(int i=1; i<=n1; i++)
        if(freqA[ readA[i].first ] != 0)
            A[++curr] = readA[i];
    n1 = curr;
    curr = 0;
    for(int i=1; i<=n2; i++)
        if(freqB[ readB[i].first ] != 0)
            B[++curr] = readB[i];
    n2 = curr;
}

void Preprocessing(){
    sort(A+1, A + n1 + 1);
    sort(B+1, B + n2 + 1);
    n = 0;
    for(int i=1; i<=n1; i+=2)
        intervals[++n] = make_pair(make_pair(A[i].second, A[i+1].second), make_pair(B[i].second, B[i+1].second));
    sort(intervals+1, intervals+n+1);
}

int Solve(){
    for(int i=1; i<=n; i++){
        dp[i] = 2;
        for(int j=1; j<i; j++)
            if(intervals[j].first.second < intervals[i].first.first && intervals[j].second.second < intervals[i].second.first)
                dp[i] = max(dp[i], dp[j] + 2);
    }
    int res = 0;
    for(int i=1; i<=n; i++)
        res = max(res, dp[i]);

    return res;
}

int main(){
    ios_base::sync_with_stdio(0);
    Read();
    Optimization();
    Preprocessing();
    cout<<Solve()<<endl;

    return 0;
}
