/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pod2.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm wzorcowy O(sqrt(|V|)2^|V|), implementacja        *
 *             z uzyciem STL.                                            *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <vector>

using namespace std;

const int MAX=26;

vector<int> present;                // reprezentacja aktualnego stanu polowek */
vector<vector<int> > sasiedzi;        // vector list sasiedztwa

int n,m,a,b;
int opt;
vector<int> opt_subset;                // optymalne rozwiazanie (koszt i polowienie)
int akt=0;                        // aktualny koszt

void xch(int a,int b){
    present[a]^=1;
    int k=0;
    for(int i=0;i<(int)sasiedzi[a].size();i++){k+=present[sasiedzi[a][i]];}
    if (present[a]) akt+=((int)sasiedzi[a].size()-(k*2)); else akt-=(sasiedzi[a].size()-(k*2));
    // a zmienia polowke - przeliczamy aktualny koszt
    
    present[b]^=1;
    k=0;
    for(int i=0;i<(int)sasiedzi[b].size();i++){k+=present[sasiedzi[b][i]];}
    if (present[b]) akt+=(sasiedzi[b].size()-(k*2)); else akt-=(sasiedzi[b].size()-(k*2));
    //b zmienia polowke - przeliczamy aktualny koszt
    
    if (akt<opt) {opt=akt; opt_subset=present;}
    // aktualizujemy rozwiazanie optymalne
}
// funkcja do wymiany miast a i b pomiedzy polowkami

void perf(int k,int l){
    if ((k==0)||(l==0)) return;
    int seeked=present[k+l-1]^1;        // indeks polowki przeciwnej do zawierajacej miasto
                                        // k+l, z ktorej miasto bedziemy szukac
    if (seeked==1) perf(k-1,l); else perf(k,l-1);
    int found;                // znalezione miasto do wymiany
    for(found=0;found<k+l;found++){if (present[found]==seeked) break;}
    xch(found,k+l-1);
    if (seeked==0) perf(k-1,l); else perf(k,l-1);
}
// funckaj rekurencyjna symulujaca wymiany w ciagu zlozonym z k zer i l jedynek na pierwszych k+l miastach

int main(){
    scanf("%d%d",&n,&m);
    sasiedzi=vector<vector<int> >(n,vector<int>());
    for(int i=0;i<m;i++){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a].push_back(b);
        sasiedzi[b].push_back(a);
    }
    // wczytywanie wejscia
    for(int i=0;i<n;i++){present.push_back((i<n/2)?1:0);}
    // ustawienie aktualnego podzialu
    for(int i=0;i<n;i++){
        for(int j=0;j<(int)sasiedzi[i].size();j++){
            if (present[i]^present[sasiedzi[i][j]]) akt++;
        }
    }
    // przelicznie kosztu
    akt>>=1;
    opt=akt;
    opt_subset=present;
    perf(n/2-1,n/2);
    int v=opt_subset[0];        // v - zmienna sygnujaca przynaleznosc miasta 1
    for(int i=0;i<n;i++){
        if (opt_subset[i]==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
