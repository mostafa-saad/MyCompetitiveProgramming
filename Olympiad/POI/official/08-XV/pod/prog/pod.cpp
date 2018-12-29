/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pod.cpp                                                   *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm wzorcowy O(sqrt(|V|)2^|V|).                      *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

const int MAX=26;

int present[MAX];                /* reprezentacja aktualnego stanu polowek (zerojedynkowo) */
int sasiedzi[MAX][MAX];                /* tablica list sasiedztwa */
int degree[MAX];                /* liczba sasiadow kolejnych wierzcholkow */

int n,m,a,b;
int opt,opt_subset;                /* zapamientane optymalne rozwiazanie (koszt i podzial) */
int akt=0;                        /* aktualny koszt */
int subset;                        /* present zapamietany jako maska bitowa */

void xch(int a,int b){
    subset^=(1<<a);
    present[a]^=1;
    int k=0;        /* licznik zliczajacy sasiadow a nalezacych do drugiej polowki */
    for (int i=0;i<degree[a];i++){k+=present[sasiedzi[a][i]];}
    if (present[a]) akt+=(degree[a]-(k<<1)); else akt-=(degree[a]-(k<<1));        /* naniesienie zmian w koszcie */
    /* a jest juz w przeciwnej polowce */
    subset^=(1<<b);
    present[b]^=1;
    k=0;
    for (int i=0;i<degree[b];i++){k+=present[sasiedzi[b][i]];}
    if (present[b]) akt+=(degree[b]-(k<<1)); else akt-=(degree[b]-(k<<1));
    /* b jest juz w przeciwnej polowce */
    if (akt<opt) {opt=akt; opt_subset=subset;}        /* poprawa optymalnego rozwiazania */
}
/* wymiana miast a i b miedzy polowkami */

void perf(int k,int l){
    if ((k==0)||(l==0)) return;
    int seeked=present[k+l-1]^1;         /* seeked - cyferka przeciwna do ostatniej w 
                                           rozwazanym fragmencie tablicy present, poszukiwana potem */
    if (seeked==1) perf(k-1,l); else perf(k,l-1);
    int found;
    for (found=0;found<k+l;found++){if (present[found]==seeked) break;}
    xch(found,k+l-1);
    if (seeked==0) perf(k-1,l); else perf(k,l-1);
}
/* funkcja rekurencyjna przegladajaca ciagi k zer i l jedynek na pierwszych k+l miastach */

int main(){
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;i++){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a][degree[a]++]=b;
        sasiedzi[b][degree[b]++]=a;
    }        /* wczytywanie wejscia */
    subset=(1<<(n/2))-1;
    for (int i=0;i<n;i++){present[i]=((i<n/2)?1:0);}
    /* ustawienie podzbiorow */
    for (int i=0;i<n;i++){
        for (int j=0;j<degree[i];j++){
            if (present[i]^present[sasiedzi[i][j]]) akt++;
        }
    }
    /* ustawienie kosztu */
    akt>>=1;
    opt=akt;
    opt_subset=subset;
    perf(n/2-1,n/2);
    int v=(opt_subset&1); /* zmienna trzymajaca przynaleznosc miasta 1 do polowki oznaczonej jako 1 */
    for(int i=0;i<n;i++){
        if (((opt_subset&(1<<i))!=0)==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
