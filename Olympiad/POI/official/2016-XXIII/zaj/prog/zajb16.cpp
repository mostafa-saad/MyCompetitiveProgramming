/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zajakniecia                                        *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Zlozonosc czasowa:    O((n1+n2)*2^(n1+n2))                               *
 *   Opis:                 Rozwiazanie uzywajace O(n1*n2) pamieci             *
 *                         oraz zakladajace, ze A[i], B[i] <= 2000            *
 *****************************************************************************/


#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

const int MAXN = 2000;

int n1, n2;
int A[MAXN + 3], B[MAXN + 3];
int prevA[MAXN + 3], prevB[MAXN + 3];
vector<int> countsort[MAXN + 3];
int dp[MAXN + 3][MAXN + 3];
int readA[MAXN + 3], readB[MAXN + 3];
map<int,int> freqA, freqB;

void Read(){
    cin>>n1>>n2;
    for(int i=1; i<=n1; i++)
        cin>>readA[i];
    for(int i=1; i<=n2; i++)
        cin>>readB[i];
}

//Usuwamy wyrazy, ktore wystepuja mniej niz 2 razy w jednym z ciagow.
void Optimization(){
    for(int i=1; i<=n1; i++)
        if(freqA.find(readA[i]) != freqA.end())
            freqA[ readA[i] ]++;
        else
            freqA[ readA[i] ] = 1;
    for(int i=1; i<=n2; i++)
        if(freqB.find(readB[i]) != freqB.end())
            freqB[ readB[i] ]++;
        else
            freqB[ readB[i] ] = 1;

    for(int i=1; i<=n1; i++)
        if(freqA[ readA[i] ] == 1 || freqB.find(readA[i]) == freqB.end() || freqB[ readA[i] ] <= 1)
            freqA[ readA[i] ] = 0, freqB[ readA[i] ] = 0;
    for(int i=1; i<=n2; i++)
        if(freqB[ readB[i] ] == 1 || freqA.find(readB[i]) == freqA.end() || freqA[ readB[i] ] <= 1)
            freqB[ readB[i] ] = 0, freqA[ readB[i] ] = 0;

    int curr = 0;
    for(int i=1; i<=n1; i++)
        if(freqA[ readA[i] ] != 0)
            A[++curr] = readA[i];
    n1 = curr;
    curr = 0;
    for(int i=1; i<=n2; i++)
        if(freqB[ readB[i] ] != 0)
            B[++curr] = readB[i];
    n2 = curr;
}

void Preprocessing(int tab[], int n, int prev[]){
    for(int i=1; i<=MAXN; i++)
        countsort[i].clear();
    for(int i=1; i<=n; i++)
        countsort[ tab[i] ].push_back(i);
    for(int i=1; i<=MAXN; i++)
        for(int j=1; j<(int)countsort[i].size(); j++)
            prev[ countsort[i][j] ] = countsort[i][j-1];
}

int Solve(){
    for(int i=1; i<=n1; i++){
        for(int j=1; j<=n2; j++){
            dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            if(A[i] == B[j] && prevA[i] != 0 && prevB[j] != 0)
                dp[i][j] = max(dp[i][j], dp[ prevA[i] - 1 ][ prevB[j] - 1] + 2);
        }
    }

    return dp[n1][n2];
}

int main(){
    ios_base::sync_with_stdio(0);
    Read();
	Optimization();
    Preprocessing(A, n1, prevA);
    Preprocessing(B, n2, prevB);
    cout<<Solve()<<endl;

    return 0;
}
