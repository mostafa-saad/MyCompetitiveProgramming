#include <cstdlib>
#include <cstdio>
#include <cstring> 
#include <vector>
#include <algorithm>
#include <queue>
#include "Annalib.h"

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

static long long a[100][10];
static long long b[100][10];
static long long c[100][10];
static bool exist_path[100][10];

bool compare_path(int j,int k,int i){
  return (a[j][k]+b[j][k]+c[j][k])<(a[j][i]+b[j][i]+c[j][i]);
}

int Anna(int N,int M,int A[],int B[],long long C[],int Q,int S[],int T[],int K,int U[]){
  
  long long brunoC[MMAX]; memcpy(brunoC,C,sizeof(long long)*M);
  for(int l=0;l<K;l++){brunoC[U[l]]=UNDEF;}
  
  long long dist[NMAX][NMAX];
  int next[NMAX][NMAX];
  wf(N,M,A,B,brunoC,dist,next);
  
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
    
    for(int j=0;j<Q;j++){
      if(!exist_path[j][k]){continue;}
      if(!exist_path[j][path[j]]){path[j]=k;continue;}
      data_max[head+path[j]]++;
      if(compare_path(j,k,path[j])){
        data[head+path[j]]++;
        path[j]=k;
      }
    }
    head+=k;
  }
  
  unsigned long long XX=0;
  
  for(int i=head-1;i>=0;i--){
    if(data_max[i]!=0){
      XX=XX*(data_max[i]+1)+data[i];
    }
  }
  while(XX>0){
    Tap(XX%2);
    XX=XX/2;
  }
}
