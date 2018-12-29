/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Egzamin na prawo jazdy (EGZ)                               *}
{*   Plik:    egzb1.cpp                                                  *}
{*   Autor:   Michal Brzozowski                                          *}
{*   Opis:    Rozwiazanie niepoprawne.                                   *}
{*                                                                       *}
{*************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

#define REP(i,n) for (int i=0;i<n;++i)
#define REPD(i,n) for (int i=n-1;i>=0;--i)

#define FOREACH(it,x) for (__typeof((x).begin()) it=((x).begin()); it!=(x).end();++it)
#define FOR(i,p,k) for (int i=p; i<=k;++i)

#define ALL(x) x.begin(),x.end()
#define NUM(x) x.to_ulong()

int n,d,k,p;

vector<int> podciag(vector<vector<int> >&ul1){
  vector<pair<int,int> > m1(p);
  vector<int> ile1;
  int l=0;
  REP(i,n) ile1.push_back(i);
  FOR(i,1,n-1){
    ile1[i]=min(ile1[i],ile1[i-1]+1);
    REP(j,ul1[i].size()){
      int a=1,b=l+1;
      while (a<b){
        int c=(a+b)/2;
        if (ul1[m1[c].first][m1[c].second]<ul1[i][j]) b=c; else a=c+1;
      }
      if (a>0) --a;
      if (a==l|| ul1[i][j]>=ul1[m1[a+1].first][m1[a+1].second]){
        m1[a+1]=make_pair(i,j);
        l=max(l,a+1);
      }
      ile1[i]=min(ile1[i],i-l);
    }
  }
  return ile1;
}

int main(){
  cin >> n>>d>>p>>k;
  
  vector<vector<int> > ul1(n);
  vector<vector<int> > ul2(n);

  REP(i,p){
    int x,y,z;
    cin >> x>>y>>z;
    if (z==1) ul1[x].push_back(y); else
      ul2[x-1].push_back(y);
  }
  REP(i,n){
    sort(ALL(ul1[i]));
    sort(ALL(ul2[i]));
  }
  vector<int> ile1=podciag(ul1);
  reverse(ALL(ul2));
  vector<int> ile2=podciag(ul2);
  reverse(ALL(ile2));
  
  int wyn=n;
  REP(i,n) if (ile1[i]==0 && ile2[i]==0) --wyn;
  cout << wyn<<endl;
}
