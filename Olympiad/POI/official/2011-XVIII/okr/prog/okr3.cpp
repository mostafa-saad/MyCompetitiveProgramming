/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Okresowosc                                       *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;


#define MAX 200010

/* KMP */
VI prefsufy(const string &s,int n)
{
  int p[MAX];
  p[0]=p[1]=0;
  FOR(i,2,n)
  {
    int j=p[i-1];
    while (j>0 && s[j+1]!=s[i]) j=p[j];
    if (s[j+1]==s[i]) j++;
    p[i]=j;
  }
  VI t;
  int j=p[n];
  while (j>0) { t.PB(j); j=p[j]; }
  reverse(ALL(t));
  return t;
}

VI dopelnienie(VI ps,int n)
{
  VI ok;
  REP(i,SIZE(ps)) ok.PB(n-ps[i]);
  return ok;
}


string doit(VI &ps,int n)
{
  string s;
  if (ps.empty())
  {
    if (n==1) s="0";
    else
    {
      REP(i,n-1) s+='0';
      s+='1';
    }
    return s;
  }

  VI ok=dopelnienie(ps,n);
  if (ok.back()<=n/2)
  {
    int o=ok.back();
    int ile=((n/o)-1)*o;
    while (!ok.empty() && ok.back()<=ile) { ok.pop_back(); ps.pop_back(); }
    REP(i,SIZE(ok)) ok[i]-=ile;
    int n1=n-ile;
    ps=dopelnienie(ok,n1);
    s=doit(ps,n1);
    while (SIZE(s)<n) s+=string(s.end()-o,s.end());
    return s;
  }
  
  int p=ps.back();
  ps.pop_back();
  string s1=doit(ps,p);
  s=s1;
  REP(i,n-2*p) s+='0';
  s+=s1;

  VI ps1=prefsufy(string("a")+s,n);
  if (!ps1.empty())
  {
    int o1=n-ps1.back();
    if (o1<=n/2) s[SIZE(s1)+n-2*p-1]='1';
  }
  return s;
}

int main()
{
  int ile;
  scanf("%d",&ile);
  while (ile--)
  {
    char st[MAX];
    scanf("%s",st);
    int n=strlen(st);
    VI ps=prefsufy(string("a")+string(st),n);
    string s=doit(ps,n);
    puts(s.c_str());
  }
  return 0;
}
