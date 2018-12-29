// RozwiÄzanie z bĹÄdem - pominiÄcie duĹzych dzielnikĂlw
// KMR+sprawdzanie dzielnikĂlw
// O(n log^2 n + q sqrt(n))
// Lech Duraj

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define _scanf(...) if (scanf(__VA_ARGS__));

using namespace std;

const int maxn = 500002;
const int maxlog = 20;

struct triple
{
  int a,b,c;
  triple(int _a, int _b, int _c) : a(_a),b(_b),c(_c) {};
  triple() {};
};

bool operator<(const triple &x, const triple &y)
{
  return (x.b<y.b || (x.b==y.b && x.c<y.c));
}

char A[maxn];
int n, m;
int power2[maxn];
triple aux[maxn];
int kmr[maxlog][maxn];


bool equal(int a, int b, int len)
{
  int s = power2[len];
  int d = 1 << s;
  return kmr[s][a]==kmr[s][b] && kmr[s][a+len-d]==kmr[s][b+len-d];
}


int main()
{
  scanf("%d",&n);  
  _scanf("%s\n",A);
  power2[1] = 0;
  for(int i=2; i<=n; i++)
    power2[i] = power2[i/2]+1;
  m = power2[n];
  for(int i=0; i<n; i++)
    kmr[0][i] = A[i]-'a';
  for(int t=1; t<=m; t++)
  {
    int d = (1 << (t-1));
    for(int i=0; i+2*d<=n; i++)
      aux[i] = triple(i,kmr[t-1][i],kmr[t-1][i+d]);
    sort(aux,aux+n-2*d+1);
    int j = 0;
    for(int i=0; i+2*d<=n; i++)
    {
      int s = aux[i].a;
      if (i>0 && aux[i-1]<aux[i])
        kmr[t][s] = ++j;
      else
        kmr[t][s] = j;
    }
  }
  int q;
  _scanf("%d",&q);
  while(q--)
  {
    int a,b;
  _scanf("%d %d",&a,&b);
    a--; b--;
    int len = b-a+1;
    int sq = (int)sqrt(len) + 1;
    int period = len;
    for(int i=1; i<=sq; i++)
      if (len%i==0)
      {
        if (equal(a,a+i,len-i))
    {
          period = i;
      break;
    }
      }
    printf("%d\n",period);
  }
}
