/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Smieci                                           *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/

// Headers {{{
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define REP(i,n) for(int i=0; i<int(n); ++i)
#define FOR(i,j,k) for(int i=(j); i<=(k); ++i)
#define FORD(i,j,k) for(int i=(j); i>=(k); --i)
#define FOREACH(it,c) for(typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)
#define ST first
#define ND second
#define MP make_pair
#define ALL(a) (a).begin(),(a).end()
#define SQR(a) ((a)*(a))
#define debug(x) cerr << #x << " = " << x << '\n'
template<typename Q> inline int size(Q a) { return a.size(); }
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<pair<int,int> > VPII;
typedef unsigned long long ULL;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> PII;
const int INF=1000000000;
// }}}

const int MAXN=100005;

int n,m;
VI edges[MAXN];
VI uzyta[MAXN];
VI gdzie[MAXN];
int cur[MAXN];
int stos[MAXN],top=-1;
bool jest[MAXN];
vector<VI> res;

int main() {
	scanf("%d%d",&n,&m);
	REP(i,m) {
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if(c!=d) {
			--a; --b;
			edges[a].push_back(b);
			edges[b].push_back(a);
			gdzie[a].push_back(edges[b].size()-1);
			gdzie[b].push_back(edges[a].size()-1);
		}
	}
	REP(i,n) uzyta[i]=VI(edges[i].size(),false);
	REP(i,n) if(edges[i].size()%2) {
		printf("NIE\n");
		return 0;
	}
	// kazda odlozona krawedz zostaje uzyta!
	REP(i,n) if(cur[i]<int(edges[i].size())) {
		stos[++top]=i;
		jest[i]=true;
		while(top>=0) {
//			printf("TOP = %d\n",stos[top]);
			while(cur[stos[top]]<int(edges[stos[top]].size()) && uzyta[stos[top]][cur[stos[top]]])
				++cur[stos[top]];
//			printf("cur = %d\n",cur[stos[top]]);
			if(cur[stos[top]] == int(edges[stos[top]].size())) {
				jest[stos[top]]=false;
				--top;
				continue;
			}
//			printf("odkladam %d\n",edges[stos[top]][cur[stos[top]]]);
//			printf("uzyta[%d][%d] = true\n",stos[top],cur[stos[top]]);
//			printf("uzyta[%d][%d] = true\n",edges[stos[top]][cur[stos[top]]],gdzie[stos[top]][cur[stos[top]]]);
			uzyta[stos[top]][cur[stos[top]]]=true;
			uzyta[edges[stos[top]][cur[stos[top]]]][gdzie[stos[top]][cur[stos[top]]]]=true;
			stos[top+1]=edges[stos[top]][cur[stos[top]]];
			++cur[stos[top]];
			++top;
			if(jest[stos[top]]) {
//				printf("zdejmujemy cykl\n");
				// zdejmujemy cykl
				int u=stos[top];
				jest[u]=false;
				res.push_back(VI(1,u));
				--top;
				while(stos[top]!=u) {
					res.back().push_back(stos[top]);
					jest[stos[top]]=false;
					--top;
				}
				jest[u]=true;
				res.back().push_back(u);
			} else {
				jest[stos[top]]=true;
			}
		}
	}
	printf("%d\n",int(res.size()));
	REP(i,res.size()) {
		printf("%d ",int(res[i].size())-1);
		REP(j,res[i].size()) printf("%d ",res[i][j]+1);
		printf("\n");
	}
	return 0;
}
