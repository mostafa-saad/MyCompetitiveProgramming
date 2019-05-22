#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <queue>
#include <cassert>
using namespace std;
const int MAXN=250000,
  MAXV=100,
  MAXX=1000000;
FILE*fin=fopen ("therace.in", "r");
ofstream fout("therace.out");
int N, X [MAXN], V [MAXN], final_order [MAXN], order [MAXN], pos [MAXN];

struct event{
  int i,j;
  double time;
  bool operator<(const event e2) const{
    if (this->time>e2.time)return 1;
    if (this->time==e2.time&&double (X [this->i])+this->time*V [this->i] > double (X [e2.i])+e2.time*V [e2.i]) return 1;
    return 0;
  }
};
priority_queue<event> heap;


int stable_order (const void*a0, const void*b0){
  const int a=*(const int*)a0,
            b=*(const int*)b0;
  return (X [a]+V [a]*(MAXX+1))-
         (X [b]+V [b]*(MAXX+1));
}

void check_and_store (int i, int j){
  if ( V [i] <= V [j] ) return;
  event *E=new event ();
  E->i=i;E->j=j;E->time=double((X [j] - X [i]))/double((V [i] - V [j]));
  heap.push (*E);
}

int main (){
  //input
  fscanf (fin, "%d", &N);
  for (int i=0;i<N;i++)fscanf (fin, "%d%d", &X[i], &V[i]);
  //sort
  for (int i=0;i<N;i++) final_order [i]= i;
  qsort (final_order, N, sizeof (int), stable_order);
  //count passes
  int passes=0, VS[MAXV+1];
  for (int i=MAXV;i;i--) VS [i]=0;
  for (int i=0;i<N;i++) VS [V [i]]++;
  for (int i=N-1;i>=0;i--){
    VS [V [i]]--;
    for (int v=V [i]+1;v<=MAXV;v++) passes+=VS [v];
    passes%=1000000;
  }
  fout<<passes<<endl;
  //make heap
  for (int i=0;i<N;i++) {order [i]=i;pos [i]=i;}
  for (int i=0;i<N-1;i++) check_and_store (i, i+1);
  //print passes
  for (int i=0;i<10000;i++){
    if (heap.empty ())break;
    event E= heap.top (); heap.pop ();
    //skip obsolete
    if (pos [E.i]!=pos [E.j]-1){i--;continue;}
    //print
    fout<<E.i+1<<" "<<E.j+1<<endl;
    //xchg
    int posi= pos [E.j], posj= pos [E.i];
    pos [E.i]=posi;pos [E.j]=posj;
    order [posj]= E.j; order [posi]= E.i;
    if (posi<N-1) check_and_store (order [posi], order [posi+1]);
    if (posj>0)   check_and_store (order [posj-1], order [posj]);
  }
}
