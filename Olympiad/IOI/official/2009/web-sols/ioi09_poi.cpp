#include <cstdio>
#include <algorithm>
using namespace std;
  
int n,t,p;
int score[2005];
int w[2005][2005];
  
struct st{int sc,n,id;}a[2005];
bool cmp(st x, st y){return x.sc != y.sc ? (x.sc > y.sc) : (x.n != y.n ? x.n > y.n : x.id < y.id); }
  
int main(){
    scanf("%d %d %d",&n,&t,&p);
    for (int i=0; i<n; i++) {
        a[i].id = i+1;
        for (int j=0; j<t; j++) {
            scanf("%d",&w[i][j]);
            if(w[i][j] == 0) score[j]++;
            else a[i].n++;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<t; j++) {
            if(w[i][j] == 1) a[i].sc += score[j];
        }
    }
    sort(a,a+n,cmp);
    for (int i=0; i<n; i++) {
        if(a[i].id == p){
            printf("%d %d",a[i].sc,i+1);
            return 0;
        }
    }
}
