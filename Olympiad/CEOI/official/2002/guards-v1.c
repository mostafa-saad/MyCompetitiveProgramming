#define MAX 247

int M,N;

int A[MAX][MAX];

int R[MAX][MAX];
int C[MAX][MAX];

int G[MAX*MAX][2];
int PR[MAX*MAX]; 
int PC[MAX*MAX];

int r,c;

int augment()
{
  int buf[MAX*MAX];
  int S[MAX*MAX];
  int zbuf, kbuf;
  int i, found, v, vb, va, tmp;
  int x;

  zbuf = kbuf = 0;
  for(i = 0; i < c; i++) S[i] = -1;
  for(i = 0; i < r; i++)
    if (PR[i] < 0) buf[kbuf++] = i;
  found = 0;
  while (zbuf < kbuf && !found) {
    v = buf[zbuf++];
    x = G[v][1];
    for(x=G[v][1]; x<N && A[G[v][0]][x]!=2; x++)
      if (A[G[v][0]][x]==0) {
        vb=C[G[v][0]][x];
        if (S[vb] < 0 && PC[vb] != v) {
          S[vb] = v;
          if (PC[vb] < 0) {
            found = 1;
            while (vb >= 0) {
              va = S[vb];
              tmp = PR[va];
              PR[va] = vb;
              PC[vb] = va;
              vb = tmp;
            }
            break;
          }
          buf[kbuf++] = PC[vb];
        }
      }
  }
  return found;
}


int main()
{
  int i,j,m,x;
  scanf("%d %d",&M,&N);
  for (i=0;i<M;i++) 
    for (j=0;j<N;j++)
      scanf("%d",&A[i][j]);
  c=0;
  for (j=0;j<N;j++) {
    for (i=0;i<M;i++) {
      if (A[i][j]==2) c++;
      else C[i][j]=c; 
    }
    c++;
  }
  r=0;
  for (i=0;i<M;i++) {
    G[r][0]=i; G[r][1]=0;
    for (j=0;j<N;j++) {
      if (A[i][j]==2) {r++; G[r][0]=i; G[r][1]=j+1;}
      else R[i][j]=r; 
    }
    r++;
  }

  for (i = 0; i < r; i++) PR[i] = -1;
  for (i = 0; i < c; i++) PC[i] = -1;
  for (m = 0; augment(); m++);

  printf("%d\n",m);         

  for (i=0;i<r;i++) {
    if (PR[i] >= 0) {
      for(x=G[i][1]; x<N && A[G[i][0]][x]!=2; x++)
        if (A[G[i][0]][x]==0 && C[G[i][0]][x]==PR[i]) 
          printf("%d %d\n",G[i][0]+1,x+1);  
    }
  }
  return 0;
}
