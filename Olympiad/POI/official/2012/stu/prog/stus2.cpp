/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O((n+sum{x_i}) * log(max{x_i}))                  *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<iostream>
using namespace std;

const int MAXN = 1000000; // 10^6
const int MAXX = 1000000; // 10^6
const int INF = 1000000001;

class min_queue {
  public:
    void clear() {
      front = back = Smintop = Sminbot = 0;
    }
    void push(int x) {
      T[back++] = x;
      while(Smintop != Sminbot && Smin[Smintop-1] > x)
        --Smintop;
      Smin[Smintop++] = x;
    }
    void pop() {
      if(Smin[Sminbot] == T[front])
        ++Sminbot;
      ++front;
    }
    int getMin() {
      return Smin[Sminbot];
    }
  private:
    int T[MAXX];
    int front, back;
    int Smin[MAXX];
    int Smintop, Sminbot;
};


int x[MAXN+1];
int lewa[MAXN+1];
int prawa[MAXN+1];
int dp[MAXX+1];

int n;
long long m;

min_queue Q;

void kop(int p, int t[]) {
  for(int i=0;i<=x[1];++i)
    dp[i] = x[1]-i;
  t[1] = dp[0];
  for(int i=2;i<=n;++i)
  {
    Q.clear();
    for(int j=0;j<=min(p, x[i-1]);++j)
      Q.push(dp[j]);
    for(int j=0;j<=min(x[i], x[i-1]+p);++j)
    {
      dp[j] = x[i]-j + Q.getMin();
      if(j+p+1 <= x[i-1])
        Q.push(dp[j+p+1]);
      if(j >= p)
        Q.pop();
    }
    for(int j=x[i-1]+p+1;j<=x[i];++j)
      dp[j] = INF;
    t[i] = dp[0];
  }
}

int gdzie_kopac(int p) {
  kop(p, lewa);
  reverse(x+1, x+n+1);
  kop(p, prawa);
  reverse(x+1, x+n+1);

  for(int i=1;i<=n;++i)
  {
    if(lewa[i] + prawa[n-i+1] - x[i] <= m)
      return i;
  }
  return -1;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(0);
  int h = 0; // najgrubsza warstwa piasku
  long long sumx = 0;
  cin >> n >> m;
  for(int i=1;i<=n;++i)
  {
    cin >> x[i];
    sumx += x[i];
    h = max(h, x[i]);
  }
  if(sumx <= m) {
    cout << 1 << ' ' << 0 << '\n';
    return 0;
  }
  int p = 1, q = h;
  while(p < q) // wyszukiwanie binarne po wyniku
  {
    int r = (p+q)/2;
    if(gdzie_kopac(r) != -1)
      q = r;
    else
      p = r + 1;
  }
  cout << gdzie_kopac(p) << ' ' << p << '\n';
  return 0;
}
