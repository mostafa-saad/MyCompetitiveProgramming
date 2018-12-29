/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wilcze doly                                        *
 *   Zlozonosc czasowa:    O(n^2logn)                                         *
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

int CheckLenght(int len){
  for(int i=1; i<=n-len+1; i++){
    if(CheckInterval(i, i+len-1))
      return true;
  }
  
  return false;
}

int Binsrch(){
  int beg=d, end = n+1;
  while(beg + 1 < end){
    int mid = (beg + end)/2;
    if(CheckLenght(mid))
      beg = mid;
    else
      end = mid;
  }
  
  return beg;
}

int main(){
  ios_base::sync_with_stdio(0);
  Read();
  cout<<Binsrch()<<endl;
    
  return 0;
}
