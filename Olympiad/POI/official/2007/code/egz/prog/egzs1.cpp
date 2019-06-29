/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Egzamin na prawo jazdy (EGZ)                               *}
{*   Plik:    egzs1.cpp                                                  *}
{*   Autor:   Michal Brzozowski                                          *}
{*   Opis:    Rozwiazanie za wolne.                                      *}
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
  vector<vector<int> > il1(n);
  il1[0].resize(ul1[0].size(),0);
  FOR(i,1,n-1){
    il1[i].resize(ul1[i].size(),0);
    REPD(j,ul1[i].size()){
      il1[i][j]=i-1;
      if (j<ul1[i].size()-1) il1[i][j]=min(il1[i][j],il1[i][j+1]);
      FOR(k,1,i-1){
        REPD(l,ul1[k].size())if(ul1[k][l]>=ul1[i][j]){
          il1[i][j]=min(il1[i][j],il1[k][l]+(i-k-1));
        }
      }
    }
  }
  vector<int> ile1(n,n+100);
  ile1[0]=0;
  FOR(i,1,n-1){
    ile1[i]=min(ile1[i],ile1[i-1]+1);
    if (il1[i].size()>0)
      ile1[i]=min(ile1[i],il1[i][0]);
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
    if (z==1) { 
      ul1[x].push_back(y);

    } else { 
      ul2[x-1].push_back(y);
    }
  }
  REP(i,n){
    sort(ALL(ul1[i]));
    sort(ALL(ul2[i]));
  }
  vector<int> ile1=podciag(ul1);
  reverse(ALL(ul2));
  vector<int> ile2=podciag(ul2);
  reverse(ALL(ile2));
  int wyn=0;

  REP(j,n) REP(i,j+1) if (ile2[i]+ile1[j]<=k) wyn=max(wyn,j-i+1);
  REP(i,n) if (ile1[i]==0 && ile2[i]==0) --wyn;
  cout << wyn <<endl;
}
