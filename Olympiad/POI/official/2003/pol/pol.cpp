/*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Po³±czenia                                     *
 *   Plik:                pol.cpp                                        *
 *   Autor:               Rafa³ Rusin                                    *
 *************************************************************************/

#include <stdio.h>

#define FOR(i,a,b) for(int i=(a); i<(b); ++i)

template<class T>
void swap(T &a,T &b) {
  T c=a; a=b; b=c;
}


const int K=100,MAX_N=100,INF=6000000;

int n;
int D[2][MAX_N][MAX_N][K];


/////////////////////
// Kopiec
const int MAX_HEAP=K+10;

struct Element {
  int w,a,b;
};

int heap_rozm;
Element heap_el[MAX_HEAP];

void heap_init() {
  heap_rozm=0;
}

void heap_up(int p) {
  while (p>1 && heap_el[p/2].w>heap_el[p].w) {
    int p2=p/2;
    swap(heap_el[p],heap_el[p2]);
    p=p2;
  }  
}

void heap_down(int p) {
  for (;;) {
    int p2=p*2;
    if (p2<heap_rozm && heap_el[p2].w>heap_el[p2+1].w) p2++;
    else if (p2>heap_rozm) break;
    
    if (heap_el[p2].w<heap_el[p].w) {
      swap(heap_el[p],heap_el[p2]);
    } else break;
        
    p=p2;
  }
}

bool heap_empty() {
  return heap_rozm==0;
}

void heap_put(Element e) {
  heap_rozm++;
  heap_el[heap_rozm]=e;
  heap_up(heap_rozm);
}

Element heap_get() {
  Element e=heap_el[1];
  heap_el[1]=heap_el[heap_rozm];
  heap_rozm--;
  heap_down(1);

  return e;
}


//////////////////////////
// Podstawowe operacje
void op_copy(int *pzbiorDocelowy,int *pzbiorWzor) {
  FOR(i,0,K) pzbiorDocelowy[i]=pzbiorWzor[i];
}

void op_sum(int *pzbiorA,int *pzbiorB) {
  int pzbiorTmp[K];
  int pA=0,pB=0;
  FOR(i,0,K) {
    if (pzbiorA[pA]<pzbiorB[pB]) {
      pzbiorTmp[i]=pzbiorA[pA];
      pA++;
    } else {
      pzbiorTmp[i]=pzbiorB[pB];
      pB++;
    }
  }
 
  op_copy(pzbiorA,pzbiorTmp); 
}


void op_add(int *pzbiorA,int *pzbiorB) {
  if (pzbiorA[0]==INF || pzbiorB[0]==INF) {
    FOR(i,0,K) pzbiorA[i]=INF;
  } else {
    int pzbiorTmp[K];
    heap_init();
    FOR(i,0,K) {
      Element e;
      e.w=pzbiorA[i]+pzbiorB[0];
      if (e.w>INF) e.w=INF;
      e.a=i; e.b=0;
      heap_put(e);
    }
  
    FOR(i,0,K) {
      Element e;
      e=heap_get();
      pzbiorTmp[i]=e.w;
    
      e.b++;
      if (e.b<K) {
        e.w=pzbiorA[e.a]+pzbiorB[e.b];
        if (e.w>INF) e.w=INF;
        heap_put(e);
      }
    }
  
    op_copy(pzbiorA,pzbiorTmp);
  }  
}


void op_mult(int *pzbiorA) {
  int pzbiorTmp[K];
  int wynik[K];
  
  FOR(i,0,K) {
    wynik[i]=pzbiorA[i];
    pzbiorTmp[i]=pzbiorA[i];
  }  
   
  FOR(i,1,K) {
    op_add(pzbiorTmp,pzbiorA);
    op_sum(wynik,pzbiorTmp);
  }

  op_copy(pzbiorA,wynik);
}
//////////////////////////////////


int main() {
  int m;
  scanf("%i %i\n",&n,&m);

  FOR(i,0,n) {
    FOR(j,0,n) {
      FOR(k,0,K) {
        D[0][i][j][k]=INF;
      }
    }
  }
  
  FOR(i,0,m) {
    int a,b,w;
    scanf("%i %i %i\n",&a,&b,&w);
   
    D[0][a-1][b-1][0]=w;
  }
  
  FOR(l,0,n) {
    int pa=l&1;
    int pn=1-pa;
    

    
    op_copy(D[pn][l][l],D[pa][l][l]);
    op_mult(D[pn][l][l]);
    
    
    int pzbiorTmp[K];
    
    FOR(i,0,n) {
      FOR(j,0,n) if (!(i==l && j==l)) {
        op_copy(pzbiorTmp,D[pa][i][l]);
        op_add(pzbiorTmp,D[pa][l][j]);
        
        op_copy(D[pn][i][j],D[pa][i][j]);
        
        op_sum(D[pn][i][j],pzbiorTmp);
        
        op_add(pzbiorTmp,D[pn][l][l]);
        
        op_sum(D[pn][i][j],pzbiorTmp);
      }
    }
  }
  
  // Odpowiadanie na zadane pytania
  
  int l_pytan;
  scanf("%i\n",&l_pytan);
  FOR(i,0,l_pytan) {
    int a,b,c;
    scanf("%i %i %i\n",&a,&b,&c);
    
    int r=D[n&1][a-1][b-1][c-1];
    if (r==INF) r=-1;
    printf("%i\n",r);
  }
  
  return 0;
}
