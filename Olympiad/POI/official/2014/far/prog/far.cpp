/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              FarmerCraft                                   *
 *   Autor:                Piotr Smulewicz                               *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <cassert>
#include <cstring>
using namespace std;
typedef long long LL;
const int INF = 1000*1000*1001;
const LL INFLL = (LL) INF * (LL) INF;
#define REP(i,n) for(i=0;i<(n);++i)
#define ALL(c) c.begin(),c.end()
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin()); i !=(c).end();++i)
#define PB push_back
#define MP make_pair
#define FI first
#define SE second


#define SIZE (501*1000)
int n,i,inst[SIZE],a,b;
int visited[SIZE];
vector<int> edg[SIZE];

pair<int,int> dfs(int i) {
    visited[i]=1;
    vector<pair< int,int> > pom;
    for(unsigned int j=0; j<edg[i].size(); j++)
        if(!visited[edg[i][j]])
            pom.PB(dfs(edg[i][j]));
    sort(ALL(pom));
    int ti=0;
    int in=inst[i]+ti;
    for(int j=pom.size()-1; j>0; j--) {
        if(pom[j].FI+pom[j-1].SE<pom[j-1].FI+pom[j].SE)
            swap(pom[j],pom[j-1]);
        in=max(in,ti+pom[j].FI);
        ti+=pom[j].SE;
    }
    if(pom.size()>0) {
        in=max(in,ti+pom[0].FI);
        ti+=pom[0].SE;
    }
    return make_pair(in+1,ti+2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin>>n;
    REP(i,n) {
        cin>>inst[i+1];
    }
    REP(i,n-1) {
        cin>>a>>b;
        edg[a].PB(b);
        edg[b].PB(a);
    }
    cout<<max(dfs(1).FI-1,inst[1]+2*n-2)<<endl;
}
