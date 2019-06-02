/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Hotele                                        *
 *   Autor:                Piotr Smulewicz                               *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

#define ROZM 5*1001
int odw[ROZM];
int przodek[ROZM];
vector<int> tab[ROZM];
vector<int> warstwy;
int odl,poz,pie,dru,trz,wynmod,rozm,roz,n,i,a,b,pom;
unsigned int j;
long long wyn;
void bfs(int a) {
    warstwy.clear();
    warstwy.push_back(a);
    int odl=0;
    int poz=0;
    rozm=1;
    do {
        pie=0;
        dru=0;
        trz=0;
        wynmod=0;
        while(poz<rozm) {
            roz=warstwy[poz];
            wyn+=wynmod;
            trz++;
            if(poz+1<rozm)
                if(przodek[roz]!=przodek[warstwy[poz+1]]) {
                    pie+=dru;
                    dru=trz;
                    trz=0;
                    wynmod+=dru*pie;
                }
            odw[roz]=a;
            for(j=0; j<tab[roz].size(); j++) {
                pom=tab[roz][j];
                if(odl==0)
                    przodek[pom]=pom;
                else
                    przodek[pom]=przodek[roz];
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
    for(i=0; i<n; ++i) {
        bfs(i+1);
    }
    cout<<wyn<<endl;
    return 0;
}

