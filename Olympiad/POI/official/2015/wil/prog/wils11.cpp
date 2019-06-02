/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wilcze doly                                        *
 *   Zlozonosc czasowa:    O(nlogn)                                           *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie prawie wzorcowe                        *
 *                                                                            *
 *****************************************************************************/

#include<iostream>
#include<algorithm>
#include<list>
using namespace std;

typedef long long int LL;

const int MAXN = 2000000;

int n, d;
LL p;
int w[MAXN + 3];
LL prefW[MAXN + 3], dVal[MAXN + 3];
list<int> List;

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
}

void PushIntoList(int ind){
  while(!List.empty() && dVal[ List.back() ] <= dVal[ind])
    List.pop_back();
  List.push_back(ind);
}

LL GetCurrMax(int beg, int end){
  PushIntoList(end);
  
  while(!List.empty() && List.front() < beg)
    List.pop_front();
  
  if(List.empty())
    return 0;
  return dVal[ List.front() ];
}

bool CheckInterval(int beg, int end){
  if(end > n) return false;
  
  LL sum = prefW[end] - prefW[beg-1];
  LL optD = GetCurrMax(beg, end-d+1);
  
  return (sum - optD <= p);
}

int CheckLenght(int len){
  List.clear();
  for(int i=1; i<=len-d; i++)
    PushIntoList(i);
  
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
  Preprocessing();
  cout<<Binsrch()<<endl;
    
  return 0;
}
