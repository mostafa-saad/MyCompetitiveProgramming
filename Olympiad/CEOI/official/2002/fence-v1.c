// Marianov vzorak. Mal by byt OK
long long perm1[100][100];
long long perm2[100][100];
int perm[100];

void comp(int N)
{
  int n,i,j;
  perm1[1][0]=1;
  perm2[1][0]=1;
  for (n=2;n<=N;n++) {
    for (i=0;i<n;i++) {
      perm1[n][i]=perm2[n][i]=0;
      for (j=i+1;j<n;j++) 
        perm1[n][i]+=perm2[n-1][j-1];
      for (j=0;j<i;j++) 
        perm2[n][i]+=perm1[n-1][j];
    }
  }    
}

void rataj1(long long k, int zac, int typ, int n, int perm[])
{
  int i,j;
  int p2[100];
  long long l;
  if (n==0) return;
  
  if (typ==1) {
    l=0;
    for (i=0;i<zac && l+perm1[n][i]<=k;i++) {
      l+=perm1[n][i];
    }
    k-=l;
    printf(" %d",perm[i]);
    for (j=0;j<i;j++) p2[j]=perm[j];
    for (j=i;j<n-1;j++) p2[j]=perm[j+1];
    rataj1(k,i,2,n-1,p2);
  } else {
    l=0;
    for (i=zac;i<n && l+perm2[n][i]<=k;i++) {
      l+=perm2[n][i];
    }
    k-=l;
    printf(" %d",perm[i]);
    for (j=0;j<i;j++) p2[j]=perm[j];
    for (j=i;j<n-1;j++) p2[j]=perm[j+1];
    rataj1(k,i-1,1,n-1,p2);
  }
}

void rataj(long long k,int n,int perm[])
{
  int i,j;
  int p2[100];
  long long l;
  l=0;
  for (i=0;i<n && l+perm1[n][i]+perm2[n][i]<=k;i++) {
    l+=perm1[n][i]+perm2[n][i];
  }
  k-=l;
  printf("%d",perm[i]);
  for (j=0;j<i;j++) p2[j]=perm[j];
  for (j=i;j<n-1;j++) p2[j]=perm[j+1];

  if (k<perm2[n][i]) 
    rataj1(k,i-1,1,n-1,p2);
  else 
    rataj1(k-perm2[n][i],i,2,n-1,p2);
}

int main()
{
  int i,n,k;
  long long d;
  comp(20);
  for (i=0;i<20;i++) perm[i]=i+1;
  scanf("%d",&k);
  for (i=0;i<k;i++) {
    scanf("%d %lld",&n,&d);
    rataj(d-1,n,perm);
    printf("\n");
  }
  return 0;
}
