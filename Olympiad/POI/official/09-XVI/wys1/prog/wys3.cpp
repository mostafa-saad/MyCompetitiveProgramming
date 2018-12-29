/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspy na trojkatnej sieci (WYS)                           *
 *   Plik:     wys3.cpp                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie poprawne i optymalne, ale brzydkie.           *
 *                                                                       *
 *************************************************************************/

//#include<iostream>
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
#include<numeric>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define INFTY 100000000
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long ll;
typedef vector<string> VS;

ll nwd(ll a,ll b) { return !b?a:nwd(b,a%b); }
inline int CEIL(int a,int b) { return a%b ? a/b+1 : a/b; }
template <class T> inline T sqr(const T&a) { return a*a; }

VS parse(string s)
{
  string a;
  VS wyn;
  REP(i,(int)s.size())
    if (s[i]!=' ') a+=s[i];
    else if (!a.empty()) { wyn.PB(a); a=""; }
  if (!a.empty()) wyn.PB(a);
  return wyn;
}

int toi(char ch) { return int(ch)-int('0'); }

int chg(char ch) { return int(ch)-int('a'); }

int los(int m)
{
  return (int)((double)m*(rand()/(RAND_MAX+1.0)));
}

int ile;

PII kier[6];

int nrkier(PII p)
{
  REP(i,6) if (kier[i]==p) return i;
  return -1;
}

char skret(int p1,int p2)
{
  p2=(p2-p1+2+6)%6;
  return char('a'+p2);
}

vector<PII> daj_punkty(string w)
{
  vector<PII> t;
  t.PB(MP(0,0));
  t.PB(MP(0,2));
  REP(i,SIZE(w)-2)
  {
    PII p=t[SIZE(t)-2],q=t.back();
    int p1=nrkier(MP(q.FI-p.FI,q.SE-p.SE));
    p1+=int(w[i]-'a')-2;
    p1=(p1+6)%6;
    t.PB(MP(q.FI+kier[p1].FI,q.SE+kier[p1].SE));
  }
  return t;
}

string daj_stringa_pom(vector<PII> t)
{
  string s;
  REP(i,SIZE(t))
  {
    int j=(i+1)%SIZE(t);
    int k=(i+2)%SIZE(t);
    int p1=nrkier(MP(t[j].FI-t[i].FI,t[j].SE-t[i].SE));
    int p2=nrkier(MP(t[k].FI-t[j].FI,t[k].SE-t[j].SE));
    s+=skret(p1,p2);
  }
  string u=s;
  REP(i,SIZE(u)) { u+=u[0]; u.erase(u.begin()); if (u<s) s=u; }
  return s;
}

string daj_stringa(vector<PII> t)
{
  string s1=daj_stringa_pom(t);
  REP(i,SIZE(t)) t[i].FI=-t[i].FI;
  reverse(ALL(t));
  string s2=daj_stringa_pom(t);
  return min(s1,s2);
}

VS wyspy(string w)
{
  vector<PII> t=daj_punkty(w);
  VS wyn;
  REP(i,SIZE(t))
  {
    int j=(i+1)%SIZE(t);
    int p1=nrkier(MP(t[j].FI-t[i].FI,t[j].SE-t[i].SE));
    p1+=5; p1%=6;
    PII p=MP(t[i].FI+kier[p1].FI,t[i].SE+kier[p1].SE);
    vector<PII> pom=t;
    if (t[(i-1+SIZE(t))%SIZE(t)]==p)
      continue;
    else if (t[(i+2)%SIZE(t)]==p)
    {
      pom.erase(pom.begin()+j);
      if (j<i) i--;
      if (pom[(i+2)%SIZE(pom)]==pom[i])
      {
        int j=(i+1)%SIZE(pom);
        pom.erase(pom.begin()+j);
        if (j<i) i--;
        j=(i+1)%SIZE(pom);
        pom.erase(pom.begin()+j);
        if (j<i) i--;
      }
    }
    else
      pom.insert(pom.begin()+j,p);
    wyn.PB(daj_stringa(pom));
  }
  sort(ALL(wyn)); wyn.erase(unique(ALL(wyn)),wyn.end());
  return wyn;
}

VS wszystkie[11];

int main()
{
  kier[0]=MP(0,2); kier[1]=MP(1,1); kier[2]=MP(1,-1); kier[3]=MP(0,-2); kier[4]=MP(-1,-1); kier[5]=MP(-1,1);

  vector<PII> trojkat; trojkat.PB(MP(0,0)); trojkat.PB(MP(0,2)); trojkat.PB(MP(1,1));
  wszystkie[1].PB(daj_stringa(trojkat));
  FOR(i,1,9)
  {
    REP(j,SIZE(wszystkie[i]))
    {
      VS pom=wyspy(wszystkie[i][j]);
      REP(k,SIZE(pom)) wszystkie[i+1].PB(pom[k]);
    }
    sort(ALL(wszystkie[i+1]));
    wszystkie[i+1].erase(unique(ALL(wszystkie[i+1])),wszystkie[i+1].end());
  }

  scanf("%d",&ile);
  while (ile--)
  {
    char komenda[3];
    scanf("%s",komenda);
    if (komenda[0]=='K')
    {
      char w[100];
      scanf("%s",w);
      VS t=wyspy(string(w));
      printf("%d\n",SIZE(t));
      REP(i,SIZE(t))
      {
        printf("%s",t[i].c_str());
        if (i<SIZE(t)-1) putchar(' '); else puts("");
      }
    } else
    {
      int n;
      scanf("%d",&n);
      printf("%d\n",SIZE(wszystkie[n]));
      REP(i,SIZE(wszystkie[n]))
      {
        printf("%s",wszystkie[n][i].c_str());
        if (i<SIZE(wszystkie[n])-1) putchar(' '); else puts("");
      }
    }
  }
  return 0;
}
