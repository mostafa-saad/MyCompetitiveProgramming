/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zajakniecia                                        *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Zlozonosc czasowa:    O((n1+n2)*2^(n1+n2))                               *
 *   Opis:                 rozwiazanie nieefektywne                           *
 *****************************************************************************/


#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<cassert>
using namespace std;

const int MAXN = 15000;

int n1, n2;
int A[MAXN + 3], B[MAXN + 3];
int readA[MAXN + 3], readB[MAXN + 3];
map<int,int> freqA, freqB;

void Read(){
    cin>>n1>>n2;
    assert(n1 <= 20 and n2 <= 20);
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

bool Check(vector<int> seqA, vector<int> seqB){
    if(seqA != seqB) return false;
    if(seqA.size()%2 != 0) return false;
    for(int i=0; i<(int)seqA.size(); i+=2)
        if(seqA[i] != seqA[i+1])
            return false;
    return true;
}

int Solve(){
    int ret = 0;
    int M1 = (1<<n1) - 1;
    int M2 = (1<<n2) - 1;
    for(int mask1 = M1; mask1 >= 0; mask1--)
        for(int mask2 = M2; mask2 >= 0; mask2--){
            vector<int> seqA, seqB;
            for(int i=0; i<n1; i++)
                if((1<<i) & mask1)
                    seqA.push_back(A[i+1]);
            for(int i=0; i<n2; i++)
                if((1<<i) & mask2)
                    seqB.push_back(B[i+1]);
            if(Check(seqA, seqB))
                ret = max(ret, (int)seqA.size());
        }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    Read();
	Optimization();
    cout<<Solve()<<endl;

    return 0;
}
