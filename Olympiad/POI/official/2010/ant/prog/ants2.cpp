/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Antysymetria (ANT)                               *
 *   Plik:              ants2.cpp                                        *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Rozwiazanie brutalnie troszke lepsze, gdyz       * 
 *                      sprawdza kazdy lancuch o dlugosci parzystej.     *
 *   Zlozonosc czasowa: O(n^3)                                           *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)

const int MAXN=500011;

using namespace std;

char s[MAXN];

int main() {
int n;
scanf("%d",&n);
scanf("%s",s);

int wynik=0;
bool no;
REP(i,n) 
   FOR(j,i+1,n-1) {
   no=false;
    FOR(k,i,j) if (s[k]==s[j-(k-i)]) no=true;
   if (no==false) wynik++;
   j++;
   }

printf("%d\n",wynik);
return 0;
}
