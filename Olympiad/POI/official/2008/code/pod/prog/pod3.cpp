/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pod3.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm wzorcowy O(2^|V| / sqrt(|V|)), implementacja     *
 *             na maskach bitowych na podstawie pomyslu Marka Cygana.    *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

const int MAX=26;
const int MAX_labeled=35000;        /* maksymalna stablicowana liczba */

int dig_sum[MAX_labeled];        /* tablica sum cyfr */
int lst_found[MAX_labeled][2];        /* tablica: lst_found[x][c] najmniejsza pozycja binarna w x na ktorej wystepuje cyfra c */

int digit_sum_label(int g){
    int ret=0;
    REP(i,15) if (g&(1<<i)) ret++;
    return ret;
}
/* obliczanie binarnej sumy cyfr - do tablicowania */

int last_found_label(int g,int digit){
    int ret;
    for(ret=0;ret<15;ret++) if ((digit==0)==((g&(1<<ret))==0)) break;
    return (ret==15)?1000:ret;
}
/* obliczanie ostatniej znalezionej cyfry w liczbie - do tablicowania */

inline void mk_label(){
    REP(i,MAX_labeled){
        dig_sum[i]=digit_sum_label(i);
        lst_found[i][0]=last_found_label(i,0);
        lst_found[i][1]=last_found_label(i,1);
    }
}
/* tablicowanie */

int digit_sum(int g){
    return dig_sum[g&((1<<15)-1)]+dig_sum[g>>15];
}
/* obliczanie sumy cyfr - w ogole */

int last_found(int g,int digit){
    int left=15+lst_found[g>>15][digit];
    int right=lst_found[g&((1<<15)-1)][digit];
    return (left>right)?right:left;
}
/* obliczanie ostatniej znalezionej cyfry - w ogole */

int maski[MAX];                        /* maski bitowe odpowiadajace wierszom macierzy sasiedztwa dla kolejnych wierzcholkow */
int degree[MAX];                /* liczba sasiadow kolejnych wierzcholkow */

int n,m,a,b;
int opt,opt_subset;                /* zapamientane optymalne rozwiazanie (koszt i podzial) */
int akt=0;                        /* aktualny koszt */
int subset;                        /* maska bitowa aktualnego polowienia*/

void xch(int a,int b){
    subset^=(1<<a);
    int k=digit_sum(maski[a]&subset);
    if (subset&(1<<a)) akt+=(degree[a]-(k<<1)); else akt-=(degree[a]-(k<<1));        /* naniesienie zmian w koszcie */
    /* a jest juz w przeciwnej polowce */
    subset^=(1<<b);
    k=digit_sum(maski[b]&subset);
    if (subset&(1<<b)) akt+=(degree[b]-(k<<1)); else akt-=(degree[b]-(k<<1));
    /* b jest juz w przeciwnej polowce */
    if (akt<opt) {opt=akt; opt_subset=subset;}        /* poprawa optymalnego rozwiazania */
}
/* wymiana miast a i b miedzy polowkami */

void perf(int k,int l){
    if ((k==0)||(l==0)) return;
    int seeked=((subset&(1<<(k+l-1)))>0)^1;         /* seeked - cyferka przeciwna do ostatniej w 
                                                rozwazanym fragmencie tablicy present, poszukiwana potem */
    if (seeked==1) perf(k-1,l); else perf(k,l-1);
    xch(last_found(subset,seeked),k+l-1);
    if (seeked==0) perf(k-1,l); else perf(k,l-1);
}
/* funkcja rekurencyjna przegladajaca ciagi k zer i l jedynek na pierwszych k+l miastach */

int main(){
    mk_label();
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;i++){
        scanf("%d%d",&a,&b); a--; b--;
        maski[a]|=(1<<b);
        maski[b]|=(1<<a);
        degree[a]++;
        degree[b]++;
    }        /* wczytywanie wejscia */
    subset=(1<<(n/2))-1;
    /* ustawienie podzbiorow */
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if ((maski[i]&(1<<j))&&(((subset&(1<<i))>0)^((subset&(1<<j))>0))) akt++;
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


