#include <iostream>

using namespace std;
const int MAX_POKEMON = 70;

struct Pokemon{
    string name;
    int candyReq;
    int candyNo;
};

int n;
int maks, maksi;
int totalEvolution;
int evolutionNo[MAX_POKEMON];
Pokemon p[MAX_POKEMON];

int main (void){

    cin >> n;
    for (int i=0;i<n;i++){
        
        cin >> p[i].name;
        cin >> p[i].candyReq >> p[i].candyNo;
        
        while ( p[i].candyNo >= p[i].candyReq ){
            p[i].candyNo -= p[i].candyReq;
            p[i].candyNo += 2;
            evolutionNo[i]++;
            totalEvolution++;
        }

        if ( evolutionNo[i] > maks ){
            maks=evolutionNo[i];
            maksi=i;
        }

    }

    cout << totalEvolution << endl;
    cout << p[maksi].name << endl;

    return 0;

}
