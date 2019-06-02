/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wilcze doly                                        *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie prawie wzorcowe                        *
 *                                                                            *
 *****************************************************************************/


#include<iostream>
#include<algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 2000000;
const int MAXTREE = 4194304;

int n, d, M;
LL p;
int w[MAXN + 3];
LL prefW[MAXN + 3], dVal[MAXN + 3], tree[MAXTREE + 10];

void Read(){
  cin>>n>>p>>d;
  for(int i=1; i<=n; i++)
    cin>>w[i];
}

void Preprocessing(){
  for(int i=1; i<=n; i++)
    prefW[i] = prefW[i-1] + w[i];
  
  for(int i=1; i<=d; i++)
    dVal[1] += w[i];
  for(int i=2; i<=n-d+1; i++)
    dVal[i] = dVal[i-1] - w[i-1] + w[i+d-1];
  
  M = 1;
  while(M < n-d+1)
    M*=2;
  
  for(int i=1; i<=n-d+1; i++)
    tree[M+i-1] = dVal[i];
  for(int i=M-1; i>=1; i--)
    tree[i] = max(tree[2*i], tree[2*i+1]);
}

LL Query(int a, int b){
  int va = M+a-1, vb = M+b-1;
  LL res = max(tree[va], tree[vb]);
  
  while (va/2 != vb/2) {
    if (va%2 == 0) res = max(res, tree[va+1]);
    if (vb%2 == 1) res = max(res, tree[vb-1]);
    va/=2; vb/=2;
  }
  
  return res;
}

bool CheckInterval(int beg, int end){
  if(end > n) return false;
  
  LL sum = prefW[end] - prefW[beg-1];
  LL optD = Query(beg, end-d+1);
  
  return (sum - optD <= p);
}

int Solve(){
  int res = d;
  for(int i=1; i<=n-d+1; i++){
    while(CheckInterval(i, i+res))
      res++;
  }
  
  return res;
}

int main(){
  ios_base::sync_with_stdio(0);
  Read();
  Preprocessing();
  cout<<Solve()<<endl;
    
  return 0;
}
