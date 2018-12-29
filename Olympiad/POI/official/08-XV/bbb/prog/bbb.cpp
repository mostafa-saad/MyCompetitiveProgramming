/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbb.cpp                                                   *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe, zlozonosc O(n).                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)

const int MAX=1100*1000;
const int inf=2*1000*1000*1000+100;

char input[MAX];        /* wejsciowe slowo +/- */
int height[MAX];        /* wysokosci wymodelowane tym slowem */
int min_prefix[MAX];        /* minima w prefiksach */
int min_sufix[MAX];        /* minima w sufiksach */
int n,p,q,x,y,h=0,min=inf,k,l_pre,l_suf,opt=inf,r,m;
/* l_pre,l_suf - minimalna wartosc w prefiksie i sufiksie */
/* min - znalezione minimum wysokosci (do min_prefix i min_sufix) */
/* h - aktualne wysokosc */
/* opt - znalezione optimum */
char ch;

int main(){
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    height[0]=0;
    fgets(input+1,MAX,stdin);
    FOR(i,1,n){
        if (input[i]=='+') h++; else h--;
        height[i]=h;
    }
    /* wypelnianie wysokosci */
    REP(i,n+1){
        if (min>height[i]) min=height[i];
        min_prefix[i]=min;
    }
    min=inf;
    FORD(i,n,0){
        if (min>height[i]) min=height[i];
        min_sufix[i]=min;
    }
    /* wypelnianie tablic minimow prefiksow i sufiksow */
    FOR(i,1,n){
        l_suf=(height[i]-min_sufix[i])-p;                //-l_suf z opracowania
        if (l_suf<0) l_suf=0;
        l_pre=(-min_prefix[i])+(height[i]-height[n])-p;        //-l_pre z opracowania
        if (l_pre<0) l_pre=0;
        /* wyznaczanie l_pre i l_suf - minimow po przestawieniu w sufiksie i prefiksie odpowiednio */
        if (l_suf<l_pre) l_suf=l_pre;
        /* znalezienie a:=l_suf */
        l_suf+=(l_suf&1); //l_suf=2m
        if (q-p>height[n]+l_suf) k=(q-p-height[n])>>1; else k=l_suf+((height[n]-(q-p))>>1);
        /* wyliczenie liczby potrzebnych zmian znaku dla danego przesuniecia */
        r=y*(n-i)+x*k;
        if (r<opt) opt=r;
        /* aktualizacja wyniku */
    }
    printf("%d\n",opt);
    return 0;
}
