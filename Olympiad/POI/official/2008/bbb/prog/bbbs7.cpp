/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbs7.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieefektywne O(n * log n) na multisecie (STL) *
 *             nie miesci sie w pamieci.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <set>

using namespace std;

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)

const int MAX=1000*1000;
const int inf=2*1000*1000*1000+100;

char input[MAX];        // wejsciowe slowo +-
int height[MAX];        // wysokosci bilansu
int mn;                        // minimalna wysokosc bilansu przy rozwazanym przesunieciu
int n,p,q,x,y,h=0,k,M,opt=inf,r,ii;
/*        opt - znalezione optimum
        M - 2m z rozwiazania wzorcowego
        ii - pomocniczy indeks
        h - wysokosc w trakcie przetwarzania */
char ch;
multiset<int> queue;

int main(){
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    fgets(input,MAX,stdin);
    height[0]=0;
    queue.clear();
    queue.insert(0);
    /* inicjalizacja multiseta */
    REP(i,n){
        if (input[i]=='+') h++; else h--;
        queue.insert(h);
        height[i+1]=h;
    }
    /* przetworzenie slowa */
    FOR(i,n,2*n-1){
        if (input[i-n]=='+') h++; else h--;
        queue.erase(queue.find(height[i-n]));
        queue.insert(h);
        mn=p+*(queue.upper_bound(-inf))-height[i-n+1];
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
