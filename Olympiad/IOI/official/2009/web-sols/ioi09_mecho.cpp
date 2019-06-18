#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
  
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
  
int n,s;
char str[805][805];
  
int vis[805][805];
int dep[805][805];
  
int sx, sy;
  
void bee(){
    queue<int> qx, qy, d;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if(str[i][j] == 'H'){
                qx.push(i);
                qy.push(j);
                d.push(0);
                vis[i][j] = 1;
            }
        }
    }
    while (!qx.empty()){
        int xf = qx.front();
        int yf = qy.front();
        int df = d.front();
        qx.pop();
        qy.pop();
        d.pop();
        dep[xf][yf] = df;
        for (int i=0; i<4; i++) {
            int nx = xf + dx[i];
            int ny = yf + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(vis[nx][ny]) continue;
            if(str[nx][ny] != 'G' && str[nx][ny] != 'M') continue;
            vis[nx][ny] = 1;
            qx.push(nx);
            qy.push(ny);
            d.push(df+1);
        }
    }
}
  
bool trial(int x){
    memset(vis,0,sizeof(vis));
    queue<int> qx, qy, d;
    qx.push(sx);
    qy.push(sy);
    d.push(x * s);
    vis[sx][sy] = 1;
    while (!qx.empty()) {
        int xf = qx.front();
        int yf = qy.front();
        int df = d.front();
        qx.pop();
        qy.pop();
        d.pop();
        if(str[xf][yf] == 'D') return 1;
        for (int i=0; i<4; i++) {
            int nx = xf + dx[i];
            int ny = yf + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(vis[nx][ny]) continue;
            if(str[nx][ny] != 'G' && str[nx][ny] !='D') continue;
            if(str[nx][ny] != 'D' && (df+1) / s >= dep[nx][ny]) continue;
            vis[nx][ny] = 1;
            qx.push(nx);
            qy.push(ny);
            d.push(df+1);
        }
    }
    return 0;
}
  
int main(){
    scanf("%d %d",&n,&s);
    for (int i=0; i<n; i++) {
        scanf("%s",str[i]);
        for (int j=0; j<n; j++) {
            if(str[i][j] == 'M') sx = i, sy = j;
        }
    }
    bee();
    int s = 0, e = dep[sx][sy]-1;
    while (s != e) {
        int m = (s+e+1)/2;
        if(trial(m)) s = m;
        else e = m-1;
    }
    if(trial(s)) printf("%d",s);
    else printf("-1");
}
