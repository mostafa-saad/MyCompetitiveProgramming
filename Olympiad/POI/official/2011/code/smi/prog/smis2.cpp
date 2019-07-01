/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Smieci                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(2^n)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Przechodze wszystkimi mozliwosciami dfs i szukam *
 *                      cyklu prostego, jak znajde to usuwam i szukam    *
 *                      od nowa                                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <list>
#include <stack>
using namespace std;
#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define SZ(x) int((x).size()) 
#define ALL(x) (x).begin(),(x).end()
#define CLR(x,w) memset((x),w,sizeof (x))
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef long long int lli;
typedef vector<lli> vl;
typedef pair<lli, lli> pll;
typedef vector<pll> vll;

typedef list<pii>::iterator iter;
#define MAXN 100005
#define MAXM 1000005

int ile = 1, n, m, a, b, licznik[MAXN], ki;
bool s1, s2, vis[MAXN];
iter it[2 * MAXM];
list<pii> kraw[MAXN];
vector<int> cykl, res, dlg;

void add(int x,int y){
	kraw[x].push_front(pii(y,ile));
	kraw[y].push_front(pii(x,ile+1));
	it[ile++] = kraw[y].begin();
	it[ile++] = kraw[x].begin();
	licznik[x]++;
	licznik[y]++;
}

bool check(){
	FOR(i, 1, n)
		if(licznik[i] & 1)
			return false;
	return true;
}

bool go(int x, int ojc, int papa){
	if(vis[x] && x == papa){
		cykl.PB(x);
		return true;
	}

	if(vis[x])
		return false;

	vis[x] = true;
	FORE(i, kraw[x])
		if(i->X != ojc && go(i->X, x, papa)){
			cykl.PB(x);
			kraw[i->X].erase(it[i->Y]);
			kraw[x].erase(i);
			vis[x] = false;
			return true;
		}
	vis[x] = false;
	return false;	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> m;
	REP(i, m){
		cin >> a >> b >> s1 >> s2;
		if(s1 != s2)
			add(a,b);
	}

	if (!check()){
		cout << "NIE" << endl;
		return 0;
	}

	FOR(i,1,n)
		while(kraw[i].begin() != kraw[i].end())
		{
			go(i, 0, i);
			
			dlg.PB(cykl.size());
			FORE(j, cykl)
				res.PB(*j);
		   	res.PB(0);
			cykl.clear();
		}
	
	int akt = 0;
	cout << dlg.size() << endl;
	FORE(j, dlg){
		cout << *j - 1 << " ";
		while(res[akt]){
			cout << res[akt] << " ";
			akt++;
		}
		cout << endl;
		akt++;
	}

	return 0;
}
