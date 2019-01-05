/*
 * CEOI 2002 - PARTY 
 * program for solving 2-CNF-SAT inputs
 * (c) Miso Forisek
 *
 * input: 
 * N M
 * M lines follow, each contains 2 numbers x y 
 *   meaning (x | y)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 50047
#define MAXM 1000047

typedef struct { int x,y; } tEdge; 

int N,M;                // no. of variables, no. of clauses
tEdge E[2*MAXM];        // directed edges
int ec;                 // edge count
int V[2*MAXN];          // indices of vertices in E
int val[2*MAXN];        // DFS values of vertices
int Stack[2*MAXN],sc;   // stack used during DFS
int Comp[2*MAXN],ncomp; // strongly connected components
//int *CG[2*MAXN];        // component graph
int **CG;               // component graph
int Coutdeg[2*MAXN];    // outgoing degrees in the component graph
int Copposite[2*MAXN];  // opposite component
int Cvalue[2*MAXN];     // value assigned to a component
int Q[2*MAXN],inQ[2*MAXN],qs,qf; 
int i,j,kde,co,xx,yy,id,done;  


int Not(int co) { if (co<=N) return co+N; return co-N; }
int EdgeCmp(const void *a, const void *b){
  tEdge *aa,*bb; 
  aa=(tEdge *)a; bb=(tEdge *)b;
  if (aa->x!=bb->x) return ((aa->x)-(bb->x));
  return ((aa->y)-(bb->y));
}

int Visit(int co) {
  int i,min,m;
  int SIZE;
 
//  printf("  ..entered %d\n",co);
  id++; val[co]=id; min=id; Stack[sc++]=co;
  for (i=V[co];i<V[co+1];i++) {
//    printf("  ..trying %d\n",E[i].y);
    if (val[E[i].y]) { m=val[E[i].y]; } else { m=Visit(E[i].y); } 
    if (m<min) min=m; 
  }
  if (min==val[co]) {
    SIZE=0;
    while (1) {
      SIZE++;
      sc--; Comp[Stack[sc]]=ncomp; val[Stack[sc]]=2*N+10;
      if (Stack[sc]==co) break;
    }
    fprintf(stderr,"[%d vertices] ",SIZE);
    ncomp++;
  }
  return min;
}

int main(void){
  // LOAD
  scanf("%d %d",&N,&M);
  ec=0;
  for (i=0;i<M;i++){
    scanf("%d %d",&xx,&yy); if (xx<0) xx=N-xx; if (yy<0) yy=N-yy;
    E[ec].x=Not(xx); E[ec].y=yy; ec++;
    E[ec].x=Not(yy); E[ec].y=xx; ec++;
  }
  // BUILD THE GRAPH
  qsort(E,ec,sizeof(tEdge),EdgeCmp);
  E[ec].x=2*N+10; // sentinel
  kde=0; co=1;
  while (co<=2*N) { if (E[kde].x>=co) V[co++]=kde; else kde++; }
  V[2*N+1]=ec;

//  printf("Edges: "); for (i=0;i<ec;i++) printf("[%d %d] ",E[i].x,E[i].y); printf("\n");
//  printf("Vertices: "); for (i=1;i<=2*N+1;i++) printf("%d ",V[i]); printf("\n");

  // FIND STRONGLY CONNECTED COMPONENTS
  bzero(val,sizeof(val)); id=sc=ncomp=0;
  for (i=1;i<=2*N;i++) if (!val[i]) Visit(i);

  // CHECK WHETHER A SOLUTION EXISTS
  for (i=1;i<=N;i++) if (Comp[i]==Comp[i+N]) { printf("No solution.\n"); return 0; }

  // BUILD THE COMPONENT GRAPH
  CG=(int **) malloc( (ncomp+5)*sizeof(int *) );
  for (i=0;i<ncomp;i++) CG[i]=(int *) malloc( (ncomp+5)*sizeof(int) );
  for (i=0;i<ncomp;i++) for (j=0;j<ncomp;j++) CG[i][j]=0;
  for (i=0;i<ncomp;i++) { Coutdeg[i]=0; Cvalue[i]=-1; }
  for (i=1;i<=N;i++) { Copposite[ Comp[i] ]=Comp[i+N]; }
  for (i=1;i<=N;i++) { Copposite[ Comp[i+N] ]=Comp[i]; }
  for (i=0;i<ec;i++) if ( CG[ Comp[ E[i].x ] ][ Comp[ E[i].y ] ] == 0) {
    CG[ Comp[ E[i].x ] ][ Comp[ E[i].y ] ] = 1;
    Coutdeg[ Comp[ E[i].x ] ]++;
  }
  for (i=0;i<ncomp;i++) if (CG[i][i]) { CG[i][i]=0; Coutdeg[i]--; }

//  printf("Components: "); for (i=1;i<=2*N;i++) printf("%d ",Comp[i]); printf("\n");
//  printf("CG:\n");
//  for (i=0;i<ncomp;i++){
//    for(j=0;j<ncomp;j++) printf("%d ",CG[i][j]);
//    printf("\n");
//  }
//  printf("Outdegrees: "); for (i=0;i<ncomp;i++) printf("%d ",Coutdeg[i]); printf("\n");
  
  // LABEL THE COMPONENT GRAPH
  done=0;
  qs=0; qf=0;
  for (i=0;i<ncomp;i++) if (Coutdeg[i]==0) { Q[qf++]=i; inQ[i]=1; }
  while (done<(ncomp/2)) {
    kde=Q[qs++];
    if (Cvalue[kde]!=-1) continue;
    Cvalue[kde]=1; Cvalue[ Copposite[kde] ]=0;
    for (i=0;i<ncomp;i++) if (CG[i][kde]) { 
      Coutdeg[i]--;
      if ((!Coutdeg[i]) && (!inQ[i])) { Q[qf++]=i; inQ[i]=1; }
    }
    done++;
  }
  
  // OUTPUT THE SOLUTION
  done=0;
  for (i=1;i<=N;i++) if (Cvalue[Comp[i]]) done++;
  printf("%d\n",done);
  for (i=1;i<=N;i++) if (Cvalue[Comp[i]]) printf("%d\n",i);
  
  return 0;
}
