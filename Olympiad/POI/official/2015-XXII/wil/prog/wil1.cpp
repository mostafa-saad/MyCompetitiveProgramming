/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wilcze doly                                        *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                         z wykorzystaniem listy z STL-a                     *
 *****************************************************************************/


#include<iostream>
#include<algorithm>
#include<list>
using namespace std;

typedef long long int LL;

const int MAXN = 2000000;

int n, d, M, currEnd;
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

LL GetCurrMax(int beg, int end){
  if(currEnd < end){
    currEnd = end;
    while(!List.empty() && dVal[ List.back() ] <= dVal[end])
      List.pop_back();
    List.push_back(end);
  }
  
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

int Solve(){
  int res = d;
  
  int candidate = d;
  List.push_back(1);
  currEnd = 1;
  for(int i=1; i<=n-d+1; i++){
    while(CheckInterval(i, candidate+1))
      candidate++;
    res = max(res, candidate-i+1);
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
