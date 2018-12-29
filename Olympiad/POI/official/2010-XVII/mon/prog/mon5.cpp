/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Monotonicznosc (MON)                             *
 *   Plik:              mon5.cpp                                         *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie alternatywne.                        *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int kN = 20003, kK = 103, kValMax = 1000003, kLog = 14; 
const int kRang=2712333;

int n, k;
char S[kK];
int A[kN], EQ[kValMax], R[kN];

inline bool cmp(int a, int b, char c) {
  if (c == '<') return a < b;
  else if(c == '=') return a == b;
  return a > b;
}

struct RangeTree {
  int T[kRang];
  virtual int func(int a, int b) {
    return max(a, b); 
  };
  void update(int x,int l,int r,int to,int val){
    if(l==r) {
      T[x] = func(T[x], val);
    }
    else{
      int s=(l+r)/2;
      if(to <= s) update(x*2,l,s,to,val);
      else update(x*2+1,s+1,r,to,val);
      T[x]=func(T[x*2],T[x*2+1]);
    }
  }
  void update(int x, int val) {
    return update(1, 0, kValMax, x, val); 
  }
  int range_func(int x,int l,int r,int lt,int rt){
    if(l == lt && r == rt) return T[x];
    int s=(l+r)/2;
    if(rt <= s) return range_func(x*2,l,s,lt,rt);
    else if(s < lt) return range_func(x*2+1,s+1,r,lt,rt);
    return func(range_func(x*2,l,s,lt,s), range_func(x*2+1,s+1,r,s+1,rt));
  }
  int range_func(int from, int to) {
    if( from > to) return 0;
    return range_func(1, 0, kValMax, from, to);
  }
};

RangeTree Gre;
RangeTree Low;

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) { 
    scanf("%d", A + i);
  }
  char tmp[2];
  for (int i = 0; i < k; ++i) {
    scanf("%s", tmp);
    S[i]=tmp[0];
  }
  int res = 0, res_pos = 0;
  for (int i = 0; i < n; ++i) {
    R[i] = EQ[A[i]] + 1;
    R[i] = max(R[i], Low.range_func(0, A[i] - 1) + 1);
    R[i] = max(R[i], Gre.range_func(A[i] + 1, kValMax) + 1);
    if (res < R[i]) {
      res = R[i];
      res_pos = i;
    }
    char c = S[(R[i] - 1) % k];
    if (c == '=') EQ[A[i]] = R[i];
    else if (c == '<') Low.update(A[i], R[i]);
    else Gre.update(A[i], R[i]);
  }
  printf("%d\n",res);
  R[res_pos] = -1;
  res--;
  while(res) {
    int last = A[res_pos];
    res_pos--;
    while(R[res_pos] != res || !cmp(A[res_pos], last, S[(res - 1)%k]))
      res_pos--;
    R[res_pos] = -1;
    res--;
  }
  for(int i = 0; i < n; ++i) if(R[i] == -1) printf("%d ", A[i]);
  puts("");
  return 0;
}
