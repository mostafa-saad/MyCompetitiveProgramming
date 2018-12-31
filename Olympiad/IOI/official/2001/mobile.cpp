// Web not official
// https://blog.csdn.net/ALPS233/article/details/51065493 
// http://poj.org/problem?id=1195

#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
#define maxn 1105
int C[maxn][maxn];
int n;

int get(int x,int y)
{
    int ret=0;
    while(x>0)
    {
        int yy=y;
        while(yy>0)
        {

            ret+=C[x][yy];
            //cout<<x<<"   "<<y<<"  "<<C[x][y]<<endl;
            yy-=yy&(-yy);
        }
        x-=x&(-x);
    }
    return ret;
}
void add(int x,int y,int c)
{
    while(x<=n)
    {
        int yy=y;
        while(yy<=n)
        {
            C[x][yy]+=c;
            //cout<<x<<"   "<<yy<<"  "<<C[x][yy]<<endl;
            yy+=yy&(-yy);
        }
        x+=x&(-x);

    }
}
int main()
{
    int p;
    int a,b,c,d;
    while(scanf("%d",&p)!=EOF)
    {
        if(p==3) return 0;
        if(!p)
        {
            scanf("%d",&n);
            memset(C,0,sizeof(C));
        }
        else if(p==1)
        {
            scanf("%d%d%d",&a,&b,&c);
            add(a+1,b+1,c);
            //printf("%d\n",get(4,4));
        }
        else if(p==2)
        {
            scanf("%d%d%d%d",&a,&b,&c,&d);
            printf("%d\n",get(c+1,d+1)+get(a,b)-get(c+1,b)-get(a,d+1));

        }
    }

}
