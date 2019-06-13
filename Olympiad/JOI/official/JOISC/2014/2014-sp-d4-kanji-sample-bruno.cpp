#include <cstdlib>
#include <cstdio>
#include <cstring> 
#include <vector>
#include <algorithm>
#include <queue>
#include "Brunolib.h"

using namespace std;

#define NMAX 310
#define MMAX 90010
#define QMAX 100
#define KMAX 15
#define UNDEF -1

static void wf(int N,int M, int A[],int B[], long long C[],long long dist[NMAX][NMAX],int next[NMAX][NMAX]){
  for(int i=0;i<N;i++){
    fill(dist[i],dist[i]+N,UNDEF);
    fill(next[i],next[i]+N,-1);
    for(int j=0;j<N;j++){
      if(i==j){dist[i][j]=0;}
    }
  }
  for(int i=0;i<M;i++){
    dist[A[i]][B[i]]=C[i];
    next[A[i]][B[i]]=i;
  }
  for(int k=0;k<N;k++){
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        if(dist[i][k]==UNDEF||dist[k][j]==UNDEF){continue;}
        if(dist[i][j]==UNDEF||dist[i][j]>dist[i][k]+dist[k][j]){
          dist[i][j]=dist[i][k]+dist[k][j];
          next[i][j]=next[i][k];
        }
  }}}
}
void Travel(int qno,int N,int A[],int B[],int S,int T,int next[NMAX][NMAX]){
  while(S!=T){
    Answer(next[S][T]);
    S=B[next[S][T]];
  }
}

static long long a[100][10];
static long long b[100][10];
static long long c[100][10];
static bool exist_path[100][10];

static int path1;
static int path2;
bool compare(int i,int j){
  return (a[i][path1]+b[i][path1]-a[i][path2]-b[i][path2])<(a[j][path1]+b[j][path1]-a[j][path2]-b[j][path2]);
}

int Bruno(int N,int M,int A[],int B[],long long C[],int Q,int S[],int T[],int K,int U[],int L,int X[]){
  
  long long dist[NMAX][NMAX];
  int next[NMAX][NMAX];
  wf(N,M,A,B,C,dist,next);

  unsigned long long XX=0;
  for(int i=L-1;i>=0;i--){
    XX=(XX<<1)+X[i];
  }
  
  for(int j=0;j<Q;j++){
    for(int k=0;k<K+1;k++){
      exist_path[j][k]=true;
      if(k==0){
        a[j][k]=dist[S[j]][T[j]];
        b[j][k]=0;
        c[j][k]=0;
      }
      else{
        a[j][k]=dist[S[j]][A[U[k-1]]];
        b[j][k]=dist[B[U[k-1]]][T[j]];
        c[j][k]=C[U[k-1]];
      }
      if(a[j][k]==UNDEF||b[j][k]==UNDEF){exist_path[j][k]=false;}
    }
  }
  
  int head=0;
  int data_max[QMAX];fill(data_max,data_max+QMAX,0);
  int data[QMAX];fill(data,data+QMAX,0);
  int path[QMAX];fill(path,path+QMAX,0);
  
  for(int k=1;k<K+1;k++){
    vector<vector<int> > vecs(K+1);
    for(int j=0;j<Q;j++){
      if(!exist_path[j][k]){continue;}
      if(!exist_path[j][path[j]]){path[j]=k;continue;}
      data_max[head+path[j]]++;
      vecs[path[j]].push_back(j);
    }
    for(int i=0;i<k;i++){
      if(vecs[i].size()!=0){
        data[head]=XX%(data_max[head]+1);
        XX=XX/(vecs[i].size()+1);
        path1 = k;
        path2 = i;
        sort(vecs[i].begin(),vecs[i].end(),compare);
        for(int j=0;j<vecs[i].size();j++){
          if(j<data[head]){path[vecs[i][j]]=k;}
        }
      }
      head++;
    }
  }

  for(int j=0;j<Q;j++){
    path[j]--;
    if(path[j]!=-1){
      Travel(j,N,A,B,S[j],A[U[path[j]]],next);
      Answer(U[path[j]]);
      Travel(j,N,A,B,B[U[path[j]]],T[j],next);
    }
    else{
      Travel(j,N,A,B,S[j],T[j],next);
    }
    Answer(-1);
  }
}
