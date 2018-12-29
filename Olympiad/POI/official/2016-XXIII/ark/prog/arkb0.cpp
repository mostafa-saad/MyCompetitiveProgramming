/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Jakub Radoszewski                                  *
 *   Zlozonosc czasowa:    O(m * n * k)                                       *
 *   Opis:                 Rozwiazanie silowe                                 *
 *****************************************************************************/


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

const int MAX_N=2000;
const int MAX_K=1000000;

int n,m,k;
int plansza[2*MAX_N+1][2*MAX_N+1][2];
PII klocki[MAX_K+1];

vector<PII> cztery_pola(PII klocek)
{
  vector<PII> t;
  int x=klocek.FI,y=klocek.SE;
  t.PB(MP(2*x+1,2*y));
  t.PB(MP(2*x+1,2*y+2));
  t.PB(MP(2*x,2*y+1));
  t.PB(MP(2*x+2,2*y+1));
  return t;
}

int main()
{
  scanf("%d%d%d",&m,&n,&k);
  REP(i,k)
  {
    int x,y;
    scanf("%d%d",&x,&y);
    --x; --y;
    klocki[i+1]=MP(x,y);
    vector<PII> pola=cztery_pola(MP(x,y));
    REP(j,4)
    {
      int a=pola[j].FI, b=pola[j].SE;
      //printf("%d %d: %d\n",a,b,i+1);
      if (plansza[a][b][0]) plansza[a][b][1]=i+1; else plansza[a][b][0]=i+1;
    }
  }

  int x=m,y=0,dx=-1,dy=1;
  int ruch=0;
  while (k>0)
  {
    //printf("%d %d, %d\n",x,y,k); sleep(3);
    int x1=x+dx,y1=y+dy;
    ++ruch;
    if (x1<0 || x1>2*m) { dx=-dx; x1+=2*dx; }
    if (y1<0 || y1>2*n) { dy=-dy; y1+=2*dy; }
    x=x1; y=y1;
    if (plansza[x][y][0] || plansza[x][y][1])
    {
      int klocek=max(plansza[x][y][0],plansza[x][y][1]);
      if (plansza[x-dx][y+dy][0]==klocek || plansza[x-dx][y+dy][1]==klocek) dy=-dy; else dx=-dx;
      vector<PII> pola=cztery_pola(klocki[klocek]);
      REP(j,4)
      {
        int a=pola[j].FI, b=pola[j].SE;
        REP(z,2) if (plansza[a][b][z]==klocek) plansza[a][b][z]=0;
      }
      --k;
    }
  }
  printf("%d\n",ruch);
  return 0;
}
