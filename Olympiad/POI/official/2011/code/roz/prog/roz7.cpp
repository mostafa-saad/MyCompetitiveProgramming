/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(n * k)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<cassert>
#include<complex>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<sstream>
#include<stack>
#include<string>
#include<vector>
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n) for(int i=0;i<(n);++i)
#define fup FOR
#define fdo FORD
#define VAR(v,i) __typeof(i) v=(i)
#define FORE(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ALL(x) (x).begin(),(x).end()
#define SIZE(x) ((int)x.size())
#define siz SIZE
#define CLR(x) memset((x),0,sizeof (x))
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define SQR(a) ((a)*(a))

#define DEBUG 1
#define debug(x) {if(DEBUG) cerr << #x << " = " << x << endl;}
#define debugv(x) {if(DEBUG) {cerr << #x << " = "; FORE(it,(x)) cerr << *it << " . "; cerr  <<endl;}}

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef VI vi;
typedef LL lli;

const int INF = 1000000000;
const int ALF=26;
string S;
VI pos[ALF];


int main() {
    ios_base::sync_with_stdio(false);
    int n;

    cin >> n;
    cin >> S;
    REP(i,n) {
        pos[S[i]-'a'].PB(i);
    }
    int best=0;
    REP(i, ALF) pos[i].PB(INF);
    REP(i, ALF) {//więcej
        REP(j,ALF) {//mniej
           if (i==j || min(pos[i].size(), pos[j].size()) == 1) continue;
           VI::const_iterator it=pos[i].begin(), jt=pos[j].begin();
           VI::const_iterator iend=pos[i].end(), jend=pos[j].end();
           --iend; --jend;
           int cur=0;
           bool bs=true;
           while(it != iend || jt != jend) {
               if (*it < *jt) {
                   int k = 0;
                   while (*it < *jt) {
                       ++it; ++k;
                   }
                   cur += k;
                   if (!bs) best = max(best, cur);
                   else best = max(best, cur-1);
                   bs=false;
               }
               else {
                   ++jt;
                   cur--;
                   best = max(best, cur);
                   if (cur < 0) {
                       cur = 0;
                       bs=true;
                   }
               }
           }
        }
    }
    printf("%d\n",best);
	return 0;
}
