/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbb6.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie o z³o¿onoœci O(n * log n) na wlasnym stogu.   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)

const int MAX=1000*1000+100;
const int inf=2*1000*1000*1000+100;

char input[MAX];    // wejsciowe slowo +-
int height[MAX];    // wysokosci bilansu
int mn;             // minimalna wysokosc bilansu przy rozwazanym przesunieciu
int n,p,q,x,y,h=0,k,M,opt=inf,r,ii;
/*        opt - znalezione optimum
        M - 2m z rozwiazania wzorcowego
        ii - pomocniczy indeks
        h - wysokosc w trakcie przetwarzania */
char ch;

int heap[MAX][2];       // stog - korzen w 1, [0] -> wysokosc bilansu,
                        // [1] -> na ktorej pozycji wysokosc zostala osiagnieta

int gdzie[2*MAX];       // tablica z zapisanymi miejscami na stogu, gdzie sa
                        // wysokosci odpowiednich bilansow

int hsize;              // wielkosc stogu

/* IMPLEMENTACJA STOGU */

inline void xch(int a,int b){
    gdzie[heap[a][1]]=b;
    gdzie[heap[b][1]]=a;
    swap(heap[a][0],heap[b][0]);
    swap(heap[a][1],heap[b][1]);
}
/* funkcja zamieniajaca elementy stogu a i b */

inline void heapup(int l){
    while ((l>1)&&(heap[l][0]<heap[l>>1][0])){
        xch(l,l>>1);
        l>>=1;
    }
}
/* funkcja przesuwajaca w miare mozliwosci element l w gore stogu */

inline void heapdown(int l){
    int v;        /* v - kandydat z synow do zamiany */
    while ((l<<1)<=hsize){
        v=(l<<1);
        if ((v<hsize)&&(heap[v+1][0]<heap[v][0])) ++v;
        if (heap[l][0]>heap[v][0]) xch(l,v); else break;
        l=v;
    }
}
/* funkcja przesuwajaca w miare mozliwosci element l w dol stogu */

void heapadd(int val,int key){
    heap[++hsize][0]=val;
    heap[hsize][1]=key;
    gdzie[key]=hsize;
    heapup(hsize);
}
/* funkcja dodajaca element o wartosci val i kluczu key do stogu */

void heapdelete(int key){
    gdzie[heap[hsize][1]]=gdzie[key];
    heap[gdzie[key]][0]=heap[hsize][0];
    heap[gdzie[key]][1]=heap[hsize][1];
    hsize--;
    heapdown(gdzie[key]);
}
/* funckja wyrzucajaca ze stogu element o kluczu key */

/* KONIEC IMPLEMENTACJI STOGU */

int main(){
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    fgets(input,MAX,stdin);
    height[0]=0;
    hsize=1; heap[1][0]=0; heap[1][1]=0; gdzie[0]=1;
    /* inicjalizacja stogu */
    REP(i,n){
        if (input[i]=='+') h++; else h--;
        heapadd(h,i+1);
        height[i+1]=h;
    }
    /* przetworzenie slowa */
    FOR(i,n,2*n-1){
        if (input[i-n]=='+') h++; else h--;
        heapdelete(i-n);
        heapadd(h,i+1);
        mn=p+heap[1][0]-height[i-n+1];
        /* obliczenie minimalnej wysokosci bilansu */
        ii=i-n+1;
        M=(mn>0)?0:(-mn);
        M+=(M&1); //M=2m
        if (q-p>height[n]+M) k=(q-p-height[n])>>1; else k=M+((height[n]-(q-p))>>1);
        /* obliczenie liczby potrzebnych zmian znaku */
        r=y*(n-ii)+x*k;
        if (r<opt) opt=r;
        /* aktualizacja optimum */
    }
    /* przetworzenie zdublowanego slowa z zapisywaniem wyniku */
    printf("%d\n",opt);
    return 0;
}

