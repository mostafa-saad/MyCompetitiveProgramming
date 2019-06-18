#include "artclass.h"
#include <cstdlib>
#include <cmath>
#define D(i,j,k,l) (abs(R[i][j] - R[k][l])+abs(G[i][j] - G[k][l])+abs(B[i][j] - B[k][l]))
 
int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]) {
    int res = 0, cnt = 0;
    for (int i=0; i<H; i++) {
        for (int j=0; j<W-1; j++) {
            res += (D(i,j,i,j+1));
            cnt++;
        }
    }
    for (int j=0; j<W; j++) {
        for (int i=0; i<H-1; i++) {
            res += (D(i,j,i+1,j));
            cnt ++;
        }
    }
    res /= cnt;
    if(res < 10) return 4;
    else if(res < 27) return 1;
    else if(res < 55) return 2;
    else return 3;
}