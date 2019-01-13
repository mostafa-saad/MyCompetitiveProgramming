/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Pracowity Jas                                      *
 *   Autor:                Bartosz Lukasiewicz                                *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/



#include <cstdio>
typedef long long ll;

const int MAXN=1000000;
const ll MOD=1000000007LL;
const int R=1<<20;

int P[MAXN+5], tree[2*R];
ll T[MAXN+5];

int next(int k)
{
  return (k+1)/2;
}

void add(int k)
{
  k+=R;
  tree[k]=1;
  while(k>1)
  {
    k/=2;
    tree[k]=tree[2*k]+tree[2*k+1];
  }
}

int less(int k)
{
  k+=R;
  int result=0;
  while(k>1)
  {
    if(k%2==1) result+=tree[k-1];
    k/=2;
  }
  return result;
}

int main()
{
  int n;
  scanf("%d", &n);

  for(int i=1; i<=n; i++)
    scanf("%d", &P[i]);
  
  T[1]=0;
  for(int i=2; i<=n; i++)
    T[i]=(ll(i)*T[i-1]+ll(i-1)*ll(next(i)))%MOD;

  ll result=0;
  for(int i=1; i<=n; i++)
  {
    add(P[i]);
    ll nr=P[i]-less(P[i]);
    result+=(nr-1)*T[n-i];
    result+=(nr-1)*next(n-i+1);
    result%=MOD;
  }

  printf("%lld\n", result);  
  
  return 0;
}