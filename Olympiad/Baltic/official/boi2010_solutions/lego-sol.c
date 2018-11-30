#include <stdio.h>
#define MAXL 6
#define MAXH 6
#define MAXN (MAXL/2)*(MAXL/2)

char view[MAXH][2][MAXL+1];
int supp[MAXH+1][10000],nb[MAXH+1];
long long cnt, np[MAXH+1][10000];
int H, pos[MAXN];
int map[MAXL][MAXL];

void MLX(int h, int nr, int lastx, int lasty) {
  int x, y, i,j,k,q,deg;
  char c[MAXN];
  for(x=lastx;x<MAXL-1;x++) {
      for(y=(x==lastx)?lasty+1:0;y<MAXL-1;y++) {
          if(map[x][y]==-1 && map[x][y+1]==-1) {
            pos[nr]=x*(MAXL-1)+y;
            map[x][y]=map[x+1][y]=map[x][y+1]=map[x+1][y+1]=nr;
            MLX(h,nr+1,x,y);
            map[x][y]=map[x+1][y]=map[x][y+1]=map[x+1][y+1]=-1;
          }
        }
  }
  //Is this configuration consistent with indata?
  for(i=0;i<nr;i++) c[i]='-';
  for(i=0;i<2;i++) {
    for(j=0;j<MAXL;j++) {
      q=-1;
      for(k=0;k<MAXL;k++) {
        if(i==0) { x=j; y=k;}
        if(i==1) { y=j; x=MAXL-1-k;}
        if(i==2) { x=MAXL-1-j; y=MAXL-1-k;}
        if(i==3) { y=MAXL-1-j; x=k;}
        if(map[x][y]!=-1) {
          q=map[x][y];
          break;
        }
      }
      if(q==-1 && view[h][i][j]!='.') return;
      if(q!=-1) {
        if(view[h][i][j]=='.') return;
        if(c[q]=='-') c[q]=view[h][i][j];
        if(c[q]!=view[h][i][j]) return;
      }
    }
  }
  //Is there any hidden pieces that can have any color?
  deg=1;
  for(i=0;i<nr;i++) if(c[i]=='-') deg*=3;

  //print();
  //Sum over possibilities
  np[h+1][nb[h+1]]=0;
  for(i=0;i<nb[h];i++) {
    for(j=0;j<nr;j++) if(((supp[h][i] >> pos[j]) & 1) == 0) break;
    if(j==nr) {
      np[h+1][nb[h+1]]+=np[h][i]*deg;
      cnt+=np[h][i]*deg;
    }
  }
  //Calculate its support for next layer
  if(np[h+1][nb[h+1]]>0) {
    supp[h+1][nb[h+1]]=0;
    for(x=0;x<MAXL-1;x++) for(y=0;y<MAXL-1;y++) {
        q=x*(MAXL-1)+y;
        if(map[x][y]!=-1 || map[x][y+1]!=-1 || map[x+1][y]!=-1 || map[x+1][y+1]!=-1) {
          supp[h+1][nb[h+1]]|=(1<<q);
        }
      }
    nb[h+1]++;
  }
}


int main() {
  freopen("lego.in", "rt", stdin);
  freopen("lego.out", "wt", stdout);
  int i,j,h;
  scanf("%d",&H);
  for(i=0;i<2;i++) for(h=H-1;h>=0;h--) {
      scanf("%s", view[h][i]);
    }
  nb[0]=1;
  np[0][0]=1;
  supp[0][0]=~0; //Full support
  for(h=0;h<H;h++) {
    cnt=0;
    for(i=0;i<MAXL;i++) for(j=0;j<MAXL;j++) map[i][j]=-1;
    MLX(h,0,-1,-1);
  }
  printf("%I64d\n", cnt);
  return 0;
}
