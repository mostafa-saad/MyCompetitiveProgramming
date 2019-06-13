#include <cstdio>
#include <algorithm>

using namespace std;

struct edge{
  int i,a,b,c;
};

bool operator<(edge e1,edge e2)
{
  return e1.c>e2.c;
}

int rt(int a,int *uf)
{
  return uf[a]<0?a:uf[a]=rt(uf[a],uf);
}

int main()
{
  int n,m,k;
  scanf("%d%d%d",&n,&m,&k);
  static edge E[300000];
  for(int i=0;i<m;i++){
    E[i].i=i;
    scanf("%d%d%d",&(E[i].a),&(E[i].b),&(E[i].c));
    E[i].a--;
    E[i].b--;
  }
  sort(E,E+m);
  static int uf[10000][1000];
  for(int i=0;i<k;i++){
    for(int j=0;j<n;j++){
      uf[i][j]=-1;
    }
  }
  static int ans[300000];
  for(int i=0;i<m;i++){
    int a=E[i].a,b=E[i].b;
    int L=-1,R=k;
    while(L+1<R){
      int d=(L+R)/2;
      int ra=rt(a,uf[d]),rb=rt(b,uf[d]);
      if(ra==rb){
	L=d;
      }
      else{
	R=d;
      }
    }
    if(R<k){
      int ra=rt(a,uf[R]),rb=rt(b,uf[R]);
      if(-uf[R][ra]<-uf[R][rb]){
	uf[R][ra]=rb;
      }
      else if(-uf[R][ra]>-uf[R][rb]){
	uf[R][rb]=ra;
      }
      else{
	uf[R][ra]=rb;
	uf[R][rb]--;
      }
      ans[E[i].i]=R+1;
    }
    else{
      ans[E[i].i]=0;
    }
  }
  for(int i=0;i<m;i++){
    printf("%d\n",ans[i]);
  }
  return 0;
}
