/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabb11.cpp                                                *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie bledne.                                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <numeric>
#include <cmath>
#include <cstdlib>
using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back
typedef long long ll;
typedef double D;
typedef long double ld;
typedef vector<int> VI;
typedef pair<int,int> PII;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(VAR(i,a);i<=(b);++i)
#define FORD(i,a,b) for(VAR(i,a);i>=(b);--i)
#define FORE(a,b) for(VAR(a,(b).begin());a!=(b).end();++a)
#define VAR(a,b) __typeof(b) a=(b)
#define SIZE(a) ((int)((a).size()))
#define ALL(x) (x).begin(),(x).end()
#define CLR(x,a) memset(x,a,sizeof(x))
#define COND 1
#define DB(x) { if(COND) { cerr << __LINE__ << " " << #x << " " << x << endl; }

const ll Q = (ll)(1e7) ;

int t[1001][1001], tab[1001];
multiset<ll> w,k;

int main()
{
    int tt;
    scanf("%d",&tt);    
    while(tt--)
    {
        int n,m;
        scanf("%d %d",&n,&m);
        w.clear();
        k.clear();
        REP(i,n) REP(j,m) scanf("%d",&t[i][j]);
        REP(i,n) 
        {
            ll bla = 0;
             REP(j,m) tab[j] = t[i][j];
            sort(tab,tab+m);
            REP(j,m) bla = bla + tab[j];
            bla = tab[m-1] * Q + tab[0];
            w.insert(bla);
        }
        REP(j,m) 
        {
            ll bla = 0;
             REP(i,n) tab[i] = t[i][j];
            sort(tab,tab+n);

            REP(i,n) bla = bla + tab[i];
            bla = tab[n-1] * Q + tab[0];
            k.insert(bla);
        }
        REP(i,n) REP(j,m) scanf("%d",&t[i][j]);
        REP(i,n) 
        {
            ll bla = 0;
            REP(j,m) tab[j] = t[i][j];
            sort(tab,tab+m);
            REP(j,m) bla = bla + tab[j];
            bla = tab[m-1] * Q + tab[0];
            multiset<ll>::iterator q = w.find(bla);
//            printf("%lld %lld %d\n",*q,bla,q==w.end());
            if(q != w.end()) 
                w.erase(q);
        }
        REP(j,m) 
        {
            ll bla = 0;
            REP(i,n) tab[i] = t[i][j];
            sort(tab,tab+n);
            REP(i,n) bla = bla + tab[i];
            bla = tab[n-1] * Q + tab[0];
            multiset<ll>::iterator q = k.find(bla);
            if(q != k.end()) k.erase(q);
        }
        if(w.empty() && k.empty()) puts("TAK");
        else puts("NIE");
    }
    return 0;
}
