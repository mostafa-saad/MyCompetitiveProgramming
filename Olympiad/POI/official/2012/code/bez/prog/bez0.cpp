/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Bezpieczenstwo minimalistyczne                   *
 *   Autor:             Krzysztof Leszczynski                            *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;

const int MAXN=500100;
const int MAXM=3000000;
const int INF=1000000100;
const LL LONG_INF=LL(INF)*LL(INF);

struct skrzyzowanie //rownanie
{
    int P;
    int vis; 
    int a; //p_v=a+p;
    int b; //p_v=b-p;
    skrzyzowanie():vis(0),a(INF),b(INF){}
    bool reboot(int aa, int bb, int bezp) {
    vis=1;
    if(aa!=INF) {
      if(b!=INF && b!=(bezp-aa)) return 0;
      b=bezp-aa;
    }
    if(bb!=INF) {
      if(a!=INF && a!=(bezp-bb)) return 0;
      a=bezp-bb;
    }
    return 1;
    }
    bool get_new(int &mini, int &maxi)
    {
    vis=2;
    if(a!=INF && b!=INF) {
      if(mini>(b-a)/2) return 0;
      if(maxi<(b-a)/2) return 0;
      if(b-a<0) return 0;
      if((b-a)&1) return 0;
      mini=(b-a)/2;
      maxi=(b-a)/2;
      return 1;
    }
    if(a!=INF) {
      mini=max(mini,-a);
      maxi=min(maxi,P-a);
      return mini<=maxi;
    }
    if(b!=INF) {
      mini=max(mini,b-P);
      maxi=min(maxi,b);
      return mini<=maxi;
    }
    return 1;
    }
};

int n,m;
LL sum;
pair<LL,LL> ans;
vector<pair<int,int> > graf[MAXN];
skrzyzowanie sk[MAXN];

LL dfs(int a, int war)
{
    sk[a].vis=m;
    LL ret=0;
    for(typeof(graf[a].begin()) it=graf[a].begin(); it!=graf[a].end(); it++) {
    if(sk[it->first].vis==m) continue;
    ret+=dfs(it->first,war);
    }
    if(sk[a].a!=INF && sk[a].a+war<=sk[a].P && sk[a].a+war>=0) return ret+sk[a].a+war;
    if(sk[a].b!=INF && sk[a].b-war<=sk[a].P && sk[a].b-war>=0) return ret+sk[a].b-war;
    return LONG_INF;
}
bool dfs(int a, int &mini, int &maxi) { //odpowiednio wartosc minimalna i maxymalna dla 1-szego wierzcholka
     if(!sk[a].get_new(mini,maxi)) return 0;
     for(typeof(graf[a].begin()) it=graf[a].begin(); it!=graf[a].end(); it++) {
     if(sk[it->first].vis!=2) if(!dfs(it->first,mini,maxi)) return 0;
     }
     return 1;
}
bool dfs(int a)
{
    bool vis;
    for(typeof(graf[a].begin()) it=graf[a].begin(); it!=graf[a].end(); it++) {
    vis=sk[it->first].vis;
    if(!sk[it->first].reboot(sk[a].a,sk[a].b,it->second)) return 0;
    if(!vis) {if(!dfs(it->first)) return 0;}
    }
    return 1;
}
void read()
{
    int a,b,c;
    cin >> n >> m;
    for(int i=1; i<=n; i++) {cin >> sk[i].P; sum+=sk[i].P;}
  while(m--) {
    cin >> a >> b >> c;
    graf[a].push_back(make_pair(b,c));
    graf[b].push_back(make_pair(a,c));
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    read();
    int maxi,mini;
    LL ans1,ans2;
    for(int i=1; i<=n; i++) {
    if(sk[i].vis) continue;
    sk[i].a=0;
    if(!dfs(i)) {cout << "NIE\n"; return 0;}
    maxi=INF;
    mini=0;
    if(!dfs(i,mini,maxi)) {cout << "NIE\n"; return 0;}

    m=3; ans1=dfs(i,mini);
    m=4; ans2=dfs(i,maxi);
    if(ans1>=LONG_INF || ans2>=LONG_INF) {cout << "NIE\n"; return 0;}
    ans.first+=max(ans1,ans2);
    ans.second+=min(ans1,ans2);
    }
    
    cout << sum-ans.first << " " << sum-ans.second << endl;
    return 0;
}
