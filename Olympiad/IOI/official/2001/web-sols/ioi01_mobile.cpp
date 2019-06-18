#include <cstdio>

struct b2{
    int tree[1050][1050], lim;
    void init(int n){
        lim = n+1;
    }
    void add(int x, int y, int a){
        x++; y++;
        while(x <= lim){
            for(int i = y; i <= lim; i += i & -i){
                tree[x][i] += a;
            }
            x += x & -x;
        }
    }
    int sum(int x, int y){
        x++; y++;
        int res = 0;
        while(x){
            for(int i = y; i; i -= i & -i){
                res += tree[x][i];
            }
            x -= x & -x;
        }
        return res;
    }
}tt;

int main(){
    while (1) {
        int q;
        int a,b,c,d;
        scanf("%d",&q);
        if(q == 0){
            scanf("%d",&a);
            tt.init(a);
        }
        if(q == 1){
            scanf("%d %d %d",&a,&b,&c);
            tt.add(a,b,c);
        }
        if(q == 2){
            scanf("%d %d %d %d",&a,&b,&c,&d);
            printf("%d\n",tt.sum(c,d) - tt.sum(a-1,d) - tt.sum(c,b-1) + tt.sum(a-1,b-1));
        }
        if(q == 3) return 0;
    }
}
