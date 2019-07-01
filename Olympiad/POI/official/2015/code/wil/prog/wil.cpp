/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wilcze doly                                        *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Autor programu:       Aleksander Lukasiewicz                             *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 2000000;

int n, d, M, currEnd;
LL p;
int w[MAXN + 3];
LL prefW[MAXN + 3], dVal[MAXN + 3];
LL List[MAXN + 3];
int front, back;

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
    while(front < back && dVal[ List[back - 1] ] <= dVal[end])
      back--;
    List[back++] = end;
  }
  
  while(front < back && List[front] < beg)
    front++;
  
  if(front==back)
    return 0;
  return dVal[ List[front] ];
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
  List[back++] = 1;
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
