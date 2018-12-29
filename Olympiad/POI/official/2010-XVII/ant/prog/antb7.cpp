/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Antysymetria (ANT)                               *
 *   Plik:              antb7.cpp                                        *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Rozwiazanie tworzy slownik podslow bazowych.     *
 *                      Posiada blad w wyszukiwaniu binarnym.            *
 *   Zlozonosc czasowa: O(n * (log n)^2)                                 *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)

const int MAXN=500011;

using namespace std;

char s[MAXN],ss[MAXN];

int tab[2][20][MAXN];
int dwa[30];
int n,curr=1;


void zrob_slownik() {
	REP(i,n) {
		if (s[i]=='0') tab[0][0][i]=1; else tab[0][0][i]=2;
		if (ss[i]=='0') tab[1][0][i]=1; else tab[1][0][i]=2;
	}
	int il=0;
	while (dwa[curr+1]<=n) {
		vector<pair<pair<int,int>,int> > v;
			REP(i,n-dwa[curr+1]+1) {
			v.push_back(make_pair(make_pair(tab[0][curr-1][i],tab[0][curr-1][i+dwa[curr]]),2*i));
			v.push_back(make_pair(make_pair(tab[1][curr-1][i],tab[1][curr-1][i+dwa[curr]]),2*i+1));
			}
		sort(v.begin(),v.end());

		if (v.size()>0) {
			il=1;
			tab[v[0].second%2][curr][v[0].second/2]=1; 
			FOR(i,1,v.size()-1) if (v[i].first==v[i-1].first) tab[v[i].second%2][curr][v[i].second/2]=il; else {
					il++;
					tab[v[i].second%2][curr][v[i].second/2]=il;
			}
		}
		curr++;
	}
}


inline bool is_equal(int p1,int k1,int p2,int k2) {
	FORD(i,curr,1) 
		if (k1-p1+1>=dwa[i]) {
			if (tab[0][i-1][p1]!=tab[1][i-1][p2]) return false; else { p1+=dwa[i]; p2+=dwa[i]; }
		}				
return true;
}


int main() {
scanf("%d",&n);
scanf("%s",s); 
REP(i,n) if (s[i]=='0') ss[n-i-1]='1'; else ss[n-i-1]='0';
long long wynik=0;
dwa[1]=1; FOR(i,2,20) dwa[i]=dwa[i-1]*2;

zrob_slownik();

int pocz,kon,max_radius,sr;

FOR(i,0,n-2) if (s[i]!=s[i+1]) {
    max_radius=min(i+1,n-1-i);
    pocz=i+1;
    kon=i+max_radius;
	while (pocz<kon) {
	    sr=(pocz+kon)/2;
	    if (is_equal(2*i-sr+1,i,n-sr-1,n-i-2)) pocz=sr; else kon=sr-1;
	    }
    wynik+=kon-i;
    }    

printf("%lld\n",wynik);
return 0;
}
