/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Hotele                                        *
 *   Autor:                Piotr Smulewicz                               *
 *   Zlozonosc czasowa:    O(n^4)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

#define ROZM 5*1001
int odle[ROZM];
int odw[ROZM];
vector<int> tab[ROZM];
vector<int> warstwy;
int odl,poz,pie,dru,trz,wynmod,rozm,roz,n,i,i2,i3,a,b,pom;
unsigned int j;
long long wyn;
void bfs(int a) {
    warstwy.clear();
    warstwy.push_back(a);
    int odl=0;
    int poz=0;
    rozm=1;
    do {
        while(poz<rozm) {
            roz=warstwy[poz];
            odw[roz]=a;
            odle[roz]=odl;
            for(j=0; j<tab[roz].size(); j++) {
                pom=tab[roz][j];
                if(odw[pom]!=a)
                    warstwy.push_back(pom);
            }
            ++poz;
        }
        rozm=warstwy.size();
        ++odl;
    } while(poz<rozm);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin>>n;
    for(i=0; i<n-1; ++i) {
        cin>>a>>b;
        tab[a].push_back(b);
        tab[b].push_back(a);
    }
    for(i=1; i<=n; ++i)
        for(i2=i+1; i2<=n; ++i2)
            for(i3=i2+1; i3<=n; ++i3) {
                bfs(i);
                if(odle[i2]==odle[i3]) {
                    bfs(i2);
                    if(odle[i3]==odle[i])
                        ++wyn;
                }
            }
    cout<<wyn<<endl;
    return 0;
}

