#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

bool vis[27];
char arr[7][7];
char ret[27], obj[27];
int dp[6][6][6][6][6];

int f(int a, int b, int c, int d, int e){
    if(a < b || b < c || c < d || d < e) return 0;
    if(a > 5 || b > 5 || c > 5 || d > 5 || e > 5) return 0;
    if(a + b + c + d + e == 25) return 1;
    if(~dp[a][b][c][d][e]) return dp[a][b][c][d][e];
    char p = a + b + c + d + e + 'A';
    int ret = 0;
    if(!arr[0][a] || arr[0][a] == p) ret += f(a+1, b, c, d, e);
    if(!arr[1][b] || arr[1][b] == p) ret += f(a, b+1, c, d, e);
    if(!arr[2][c] || arr[2][c] == p) ret += f(a, b, c+1, d, e);
    if(!arr[3][d] || arr[3][d] == p) ret += f(a, b, c, d+1, e);
    if(!arr[4][e] || arr[4][e] == p) ret += f(a, b, c, d, e+1);
    return dp[a][b][c][d][e] = ret;
}

void getkth(int x){
    memset(vis,0,sizeof(vis));
    memset(arr,0,sizeof(arr));
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            for(int k=0; k<25; k++){
                if(vis[k]) continue;
                vis[k] = 1;
                arr[i][j] = k + 'A';
                memset(dp,-1,sizeof(dp));
                int tmp = f(0, 0, 0, 0, 0);
                if(x > tmp){
                    x -= tmp;
                    vis[k] = 0;
                }
                else{
                    break;
                }
            }
            ret[5*i+j] = arr[i][j];
        }
    }
}

bool compare(int x){
    for(int i=0; i<25; i++){
        if(ret[i] < obj[i]) return 0;
        if(ret[i] > obj[i]) return 1;
    }
    return 1;
}

int main(){
    memset(dp,-1,sizeof(dp));
    char q[5];
    scanf("%s",q);
    if(q[0] == 'W'){
        scanf("%s",obj);
        int s = 1, e = f(0,0,0,0,0);
        while(s != e){
            int m = (s+e)/2;
            getkth(m);
            if(compare(m)) e = m;
            else s = m+1;
        }
        printf("%d",s);
    }
    else{
        int t;
        scanf("%d",&t);
        getkth(t);
        puts(ret);
    }
}
