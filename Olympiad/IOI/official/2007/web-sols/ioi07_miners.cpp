#include <cstdio>
#include <algorithm>
using namespace std;

int n;
char str[100005];

int ctoi(char t){
    if(t == 'M') return 0;
    return t == 'B' ? 1 : 2;
}

int dp[2][4][4][4][4];

int eval(int x, int y, int z){
    int r = (x == 3 ? 0 : 1 << x) | (y == 3 ? 0 : 1 << y) | (z == 3 ? 0 :1 << z);
    if(r == 7) return 3;
    else if(r == 6 || r == 3 || r == 5) return 2;
    else return 1;
}

int main(){
    scanf("%d %s",&n,str);
    for (int i=0; i<n; i++) {
        str[i] = ctoi(str[i]);
    }
    for (int i=n-1; i>=0; i--) {
        for (int j=0; j<4; j++) {
            for (int k=0; k<4; k++) {
                for (int l=0; l<4; l++) {
                    for (int m=0; m<4; m++) {
                        int c1 = dp[(i+1)%2][k][str[i]][l][m] + eval(j,k,str[i]);
                        int c2 = dp[(i+1)%2][j][k][m][str[i]] + eval(l,m,str[i]);
                        dp[i%2][j][k][l][m] = max(c1,c2);
                    }
                }
            }
        }
    }
    printf("%d",dp[0][3][3][3][3]);
}
