// Risov vzorak. Mal by byt OK.
#include <stdio.h>

#define MAXN 21

long long T[MAXN+1][MAXN][2];

void Init() {
  int i,j;

  T[1][0][0]=1;
  T[1][0][1]=1;

  for (i=2;i<=MAXN;i++) {
    T[i][0][0]=0;
    for (j=1;j<i;j++) {
      T[i][j][0]=T[i][j-1][0]+T[i-1][j-1][1];
    }
    
    T[i][i-1][1]=0;
    for (j=i-2;j>=0;j--) {
      T[i][j][1]=T[i][j+1][1]+T[i-1][j][0];
    }
  }
}

void Write(int n, long long c) {
  int P[MAXN],i,j,A[MAXN];

  if (n==1) {
    printf("1\n");
    return;
  }
  
  for (j=0;c>T[n][j][0]+T[n][j][1];j++) c-=T[n][j][0]+T[n][j][1];
  P[0]=j; 
  
  for (j=0;(j<P[0]) && (c>T[n-1][j][1]);j++) c-=T[n-1][j][1];
  if (j==P[0])
    for (;c>T[n-1][j][0];j++) c-=T[n-1][j][0];      
  P[1]=j;
 
  for (i=2;i<n;i++) {
    if (P[i-2]>P[i-1]) {
      for (j=P[i-1];c>T[n-i][j][0];j++) c-=T[n-i][j][0]; 
    } else {
      for (j=0;c>T[n-i][j][1];j++) c-=T[n-i][j][1];
    }
    
    P[i]=j;
  }

  for (i=0;i<n;i++) A[i]=1;
  for (i=0;i<n;i++) {
    P[i]++;
    j=0;
    while (1) {      
      if (A[j]) P[i]--;
      if (!P[i]) break;
      j++;
    }
    A[j]=0;
    P[i]=j+1;
  }
  
  for (i=0;i<n-1;i++)
    printf("%d ",P[i]);
  printf("%d\n",P[n-1]);
}

int main() {
  int i,k,n;
  long long c;
  
  Init();
  scanf("%d",&k);
  for (i=0;i<k;i++) {
    scanf("%d %Ld",&n,&c);
    Write(n,c);
  }

  return 0;
}
