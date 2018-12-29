/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wilcze doly                                        *
 *   Zlozonosc czasowa:    O(n^3)                                             *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/


#include<iostream>
#include<algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 2000000;

int n, d;
LL p;
int w[MAXN + 3];

void Read(){
  cin>>n>>p>>d;
  for(int i=1; i<=n; i++)
    cin>>w[i];
}

bool CheckInterval(int beg, int end){
  if(end > n) return false;
  
  LL sum = 0;
  for(int i=beg; i<=end; i++)
    sum += w[i];
  
  LL actual = 0;
  for(int i=beg; i<=beg+d-1; i++)
    actual += w[i];
  
  for(int i=beg; i<=end-d+1; i++){
    if(sum - actual <= p)
      return true;
    
    actual -= w[i];
    actual += w[i+d];
  }
  
  return false;
}

int Solve(){
  int res = d;
  for(int i=1; i<=n-d; i++){
    for(int j=i+d; j<=n; j++){
      if(CheckInterval(i, j))
	res = max(res, j-i+1);
    }
  }
  
  return res;
}

int main(){
  ios_base::sync_with_stdio(0);
  Read();
  cout<<Solve()<<endl;
    
  return 0;
}
