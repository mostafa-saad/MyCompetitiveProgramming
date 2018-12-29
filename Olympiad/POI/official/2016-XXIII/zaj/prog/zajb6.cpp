/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zajakniecia                                        *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie nieefektywne wykorzystujace rekurencje *
 *                         ze spamietywaniem.                                 *
 *****************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

const int MAXN = 15000;
const int MEMO = 10000000;

int n1, n2;
int A[MAXN + 3], B[MAXN + 3];
vector<int> posA[2*MAXN + 3], posB[2*MAXN + 3];
map<int,int> renumerate;
map< pair<int,int>, int> res;
int size;
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

void Preprocessing(){
    int curr = 0;
    for(int i=1; i<=n1; i++)
        if(renumerate.find(A[i]) == renumerate.end())
            renumerate[ A[i] ] = ++curr;
    for(int i=1; i<=n2; i++)
        if(renumerate.find(B[i]) == renumerate.end())
            renumerate[ B[i] ] = ++curr;

    for(int i=1; i<=n1; i++){
        A[i] = renumerate[ A[i] ];
        posA[ A[i] ].push_back(i);
    }
    for(int i=1; i<=n2; i++){
        B[i] = renumerate[ B[i] ];
        posB[ B[i] ].push_back(i);
    }
}

int Solve(int s1, int s2){
    if(res.find(make_pair(s1,s2)) != res.end())
        return res[make_pair(s1,s2)];

    if(s1>=n1 || s2>=n2){
        return 0;
    }

    int val = A[s1];
    vector<int>::iterator it = lower_bound(posA[val].begin(), posA[val].end(), s1);
    if(it != posA[val].end())
        it++;
    int u;
    if(it != posA[val].end())
        u = *it;
    else
        u = n1+1;

    it = lower_bound(posB[val].begin(), posB[val].end(), s2);
    if(it != posB[val].end())
        it++;
    int v;
    if(it != posB[val].end())
        v = *it;
    else
        v = n2+1;

    int cand1 = 0;
    if(u <= n1 && v <= n2)
        cand1 = 2 + Solve(u+1, v+1);

    int cand2 = Solve(s1+1, s2);

    if(size < MEMO){
        res[make_pair(s1,s2)] = max(cand1, cand2);
        size++;
    }
    return max(cand1, cand2);
}

int main(){
    ios_base::sync_with_stdio(0);
    Read();
	Optimization();
    Preprocessing();
    cout<<Solve(1, 1)<<endl;

    return 0;
}
